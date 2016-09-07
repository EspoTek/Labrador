#region Copyright(c) Travis Robinson

// Copyright (c) 2011-2012 Travis Robinson <libusbdotnet@gmail.com>
// All rights reserved.
// 
// Xfer.Stm
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
using System.Threading;
using Test.Devices;
using libusbK;
using libusbK.Examples;

// ReSharper disable InconsistentNaming

namespace Xfer.Stm
{
    internal class Program
    {
        #region TODO USER: Set the test parameters for your device.

        public static StmTestParameters Test = new StmTestParameters(0x04d8, 0xfa2e, 0, 0x81, 1024, null, -1, 4, 64);

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

            KSTM_CALLBACK callback = new KSTM_CALLBACK();
            StmK stm = new StmK(
                usb.Handle,
                pipeInfo.PipeId,
                Test.TransferBufferSize,
                Test.MaxPendingTransfers,
                Test.MaxPendingIO,
                ref callback,
                KSTM_FLAG.USE_TIMEOUT | (KSTM_FLAG) 3000);

            byte[] tempBuffer = new byte[Test.TransferBufferSize];

            Thread.Sleep(0);
            // This is just a counter/timer for statistics gathering.
            Test.Dcs.Start();
            success = stm.Start();

            long totalTransferCount = 0;
            while (success)
            {
                int transferred;
                if ((pipeInfo.PipeId & 0x80) == 0x80)
                {
                    success = stm.Read(tempBuffer, 0, tempBuffer.Length, out transferred);
                    if (!success) break;
                }
                else
                {
                    success = stm.Write(tempBuffer, 0, tempBuffer.Length, out transferred);
                    if (!success) break;
                }

                string dataPrefix = String.Format("  Data Prefix: [{0:X2} {1:X2} {2:X2} {3:X2} {4:X2} {5:X2} {6:X2} {7:X2}] ",
                                                  tempBuffer[0],
                                                  tempBuffer[1],
                                                  tempBuffer[2],
                                                  tempBuffer[3],
                                                  tempBuffer[4],
                                                  tempBuffer[5],
                                                  tempBuffer[6],
                                                  tempBuffer[7]);

                Console.WriteLine(
                                  totalTransferCount > Test.MaxTransfersTotal
                                      ? "#{0}: [Stream Stopped] {1} transferred. {2}"
                                      : "#{0}: {1} transferred. {2}",
                                  totalTransferCount.ToString("0000"),
                                  transferred,
                                  dataPrefix);

                totalTransferCount++;

                if (totalTransferCount == Test.MaxTransfersTotal)
                    success = stm.Stop(3000);
            }

            Console.WriteLine("Done. TotalTransfers:{0} ErrorCode:{1:X8}h", totalTransferCount, Marshal.GetLastWin32Error());

            stm.Free();

            Done:
            usb.Free();
        }
    }
}