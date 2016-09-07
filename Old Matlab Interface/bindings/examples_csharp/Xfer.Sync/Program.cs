#region Copyright(c) Travis Robinson

// Copyright (c) 2011-2012 Travis Robinson <libusbdotnet@gmail.com>
// All rights reserved.
// 
// Xfer.Sync
// 
// Last Updated: 03.08.2012
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
using System.Runtime.InteropServices;
using Test.Devices;
using libusbK;
using libusbK.Examples;

// ReSharper disable InconsistentNaming

namespace Xfer.Sync
{
    internal class Program
    {
        #region TODO USER: Set the test parameters for your device.

        public static StmTestParameters Test = new StmTestParameters(0x04d8, 0xfa2e, 0, 0x01, 1024, null, -1, 4, 64);

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
                Test.TransferBufferSize = pipeInfo.MaximumPacketSize*64;

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

            // In most cases, you should to set the pipe timeout policy before using synchronous I/O.
            // By default, sync transfers wait infinitely for a transfer to complete.

            // Set the pipe timeout policy to 3000ms
            int[] pipeTimeoutMS = new[] {3000};
            usb.SetPipePolicy(
                              (byte) Test.PipeId,
                              (int) PipePolicyType.PIPE_TRANSFER_TIMEOUT,
                              Marshal.SizeOf(typeof (int)),
                              pipeTimeoutMS);

            int totalTransfers = 0;
            success = true;
            byte[] tempBuffer = new byte[Test.TransferBufferSize];
            while (success && totalTransfers++ < Test.MaxTransfersTotal)
            {
                int transferred;
                if ((Test.PipeId & 0x80) > 0)
                    success = usb.ReadPipe((byte) Test.PipeId, tempBuffer, tempBuffer.Length, out transferred, IntPtr.Zero);
                else
                    success = usb.WritePipe((byte) Test.PipeId, tempBuffer, tempBuffer.Length, out transferred, IntPtr.Zero);

                Console.WriteLine("#{0:0000} Transferred {1} bytes.", totalTransfers, transferred);
            }

            if (!success)
            {
                Console.WriteLine("An error occured transferring data. ErrorCode: {0:X8}h", Marshal.GetLastWin32Error());
            }

            Done:
            usb.Free();
        }
    }
}