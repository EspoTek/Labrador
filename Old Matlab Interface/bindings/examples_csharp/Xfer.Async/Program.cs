#region Copyright(c) Travis Robinson

// Copyright (c) 2011-2012 Travis Robinson <libusbdotnet@gmail.com>
// All rights reserved.
// 
// Xfer.Async
// 
// Last Updated: 03.09.2012
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
// 	  
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS 
// IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED 
// TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
// PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TRAVIS LEE ROBINSON 
// BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
// THE POSSIBILITY OF SUCH DAMAGE.

#endregion

#define BMFW

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Runtime.InteropServices;
using Test.Devices;
using libusbK;
using libusbK.Examples;

// ReSharper disable InconsistentNaming

namespace Xfer.Async
{
    internal class Program
    {
        #region TODO USER: Set the test parameters for your device.

        public static AsyncTestParameters Test = new AsyncTestParameters(0x04d8, 0xfa2e, 0, 0x81, 9, null, -1, 3);

        #endregion

        private static void Main()
        {
            bool success;

            WINUSB_PIPE_INFORMATION pipeInfo;
            UsbK usb;
            USB_INTERFACE_DESCRIPTOR interfaceDescriptor;

            // Find and configure the device.
            if (!Test.ConfigureDevice(out pipeInfo, out usb, out interfaceDescriptor)) return;
            if (Test.TransferBufferSize == -1)
                Test.TransferBufferSize = pipeInfo.MaximumPacketSize * 64;

#if BMFW
            // TODO FOR USER: Remove this block if not using benchmark firmware.
            // This configures devices running benchmark firmware for streaming DeviceToHost transfers.
            Console.WriteLine("Configuring for benchmark device..");
            BM_TEST_TYPE testType = ((Test.PipeId & 0x80) > 0) ? BM_TEST_TYPE.READ : BM_TEST_TYPE.WRITE;
            success = Benchmark.Configure(usb, BM_COMMAND.SET_TEST, interfaceDescriptor.bInterfaceNumber, ref testType);
            if (!success)
            {
                Console.WriteLine("Bench_Configure failed.");
            }
#endif
            if (!Test.ShowTestReady()) goto Done;

            /* In most cases, you should clear the pipe timeout policy before using asynchronous I/O. (INFINITE)
             * This decreases overhead in the driver and generally we managed the timeout ourselves from user code.
             * 
             * Set the PIPE_TRANSFER_TIMEOUT policy to INFINITE:
            */
            int[] pipeTimeoutMS = new[] {0};
            usb.SetPipePolicy((byte) Test.PipeId,
                              (int) PipePolicyType.PIPE_TRANSFER_TIMEOUT,
                              Marshal.SizeOf(typeof (int)),
                              pipeTimeoutMS);


            /* In some cases, you may want to set the RAW_IO pipe policy.  This will impose more restrictions on the
             * allowable transfer buffer sizes but will improve performance. (See documentation for restrictions)
             * 
             * Set the RAW_IO policy to TRUE:
            */
            int[] useRawIO = new[] {1};
            usb.SetPipePolicy((byte)Test.PipeId,
                              (int)PipePolicyType.RAW_IO,
                              Marshal.SizeOf(typeof(int)),
                              useRawIO);

            int totalSubmittedTransfers = 0;
            int totalCompletedTransfers = 0;

            /* We need a different buffer for each MaxPendingIO slot because they will all be submitted to the driver 
             * (outstanding) at the same time.
             */
            byte[][] transferBuffers = new byte[Test.MaxPendingIO][];

            OvlK ovlPool = new OvlK(usb.Handle, Test.MaxPendingIO, KOVL_POOL_FLAG.NONE);
            List<GCHandle> transferBufferGCList = new List<GCHandle>(Test.MaxPendingIO);
            success = true;

            // Start transferring data synchronously; one transfer at a time until the test limit (MaxTransfersTotal) is hit.
            while (success && totalCompletedTransfers < Test.MaxTransfersTotal)
            {
                KOVL_HANDLE ovlHandle;
                int transferred;
                while (success && totalSubmittedTransfers < Test.MaxTransfersTotal)
                {
                    // Get the next KOVL_HANDLE
                    if (!ovlPool.Acquire(out ovlHandle))
                    {
                        // This example expects a failure of NoMoreItems when the pool has no more handles to acquire.  This is
                        // our indication that it is time to begin waiting for a completion.
                        Debug.Assert(Marshal.GetLastWin32Error() == ErrorCodes.NoMoreItems);
                        break;
                    }

                    // Get the next transfer buffer
                    int transferBufferIndex = totalSubmittedTransfers % Test.MaxPendingIO;
                    if (transferBuffers[transferBufferIndex] == null)
                    {
                        /* This index has not been allocated yet.  We need a different buffer for each MaxPendingIO
                         * slot because they will all be submitted to the driver (outstanding) at the same time.
                         */

                        Console.WriteLine("Allocating transfer buffer at index:{0}", transferBufferIndex);
                        transferBuffers[transferBufferIndex] = new byte[Test.TransferBufferSize];

                        // Transfer buffers should be pinned so the garbage collector cannot move the memory.
                        transferBufferGCList.Add(GCHandle.Alloc(transferBuffers[transferBufferIndex], GCHandleType.Pinned));
                    }

                    byte[] transferBuffer = transferBuffers[transferBufferIndex];

                    int not_used_for_async;
                    if ((Test.PipeId & AllKConstants.USB_ENDPOINT_DIRECTION_MASK) > 0)
                    {
                        success = usb.ReadPipe((byte) Test.PipeId, transferBuffer, transferBuffer.Length, out not_used_for_async, ovlHandle);
                    }
                    else
                    {
                        FillMyBufferForWrite(transferBuffer, out transferred);
                        success = usb.WritePipe((byte)Test.PipeId, transferBuffer, transferred, out not_used_for_async, ovlHandle);
                    }

                    if (Marshal.GetLastWin32Error() == ErrorCodes.IoPending)
                    {
                        success = true;
                        totalSubmittedTransfers++;
                        Console.WriteLine("Pending  #{0:0000} {1} bytes.", totalSubmittedTransfers, transferBuffer.Length);
                    }
                    else
                        Console.WriteLine("Pending  #{0:0000} failed. ErrorCode={1:X8}h", totalSubmittedTransfers, Marshal.GetLastWin32Error());
                }
                if (!success) break;

                // Wait for the oldest transfer to complete and release the ovlHandle to the pool so it can be re-acquired.
                success = ovlPool.WaitOldest(out ovlHandle, 1000, KOVL_WAIT_FLAG.RELEASE_ALWAYS, out transferred);
                totalCompletedTransfers++;

                if (success)
                {
                    if ((Test.PipeId & AllKConstants.USB_ENDPOINT_DIRECTION_MASK) > 0)
                    {
                        ProcessMyBufferFromRead(transferBuffers[(totalCompletedTransfers-1) % Test.MaxPendingIO], transferred);
                    }
                    Console.WriteLine("Complete #{0:0000} {1} bytes.", totalCompletedTransfers, transferred);
                }
                else
                    Console.WriteLine("Complete #{0:0000} Wait failed. ErrorCode={1:X8}h", totalCompletedTransfers, Marshal.GetLastWin32Error());
            }

            if (!success)
                Console.WriteLine("An error occured transferring data. ErrorCode: {0:X8}h", Marshal.GetLastWin32Error());

            ovlPool.Free();

            // Free the GC handles allocated for the transfer buffers
            foreach (GCHandle gcHandle in transferBufferGCList)
                gcHandle.Free();

            Done:
            usb.Free();
        }

        #region TODO USER: Use these functions to process and fill the transfer buffers

        private static void ProcessMyBufferFromRead(byte[] transferBuffer, int transferred)
        {
        }

        private static void FillMyBufferForWrite(byte[] transferBuffer, out int length)
        {
            length = transferBuffer.Length;
        }

        #endregion
    }
}