#region Copyright(c) Travis Robinson

// Copyright (c) 2011-2012 Travis Robinson <libusbdotnet@gmail.com>
// All rights reserved.
// 
// Xfer.UsbStream
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
using System.Diagnostics;
using System.IO;
using System.Threading;
using Test.Devices;
using libusbK;
using libusbK.Examples;

namespace Xfer.UsbStream
{
    internal class Program
    {
        #region TODO USER: Set the test parameters for your device.

        public static StmTestParameters Test = new StmTestParameters(0x04d8, 0xfa2e, 0, 0x81, 1024, null, -1, 4, 64);

        #endregion

        private static bool FormatBrokenStrings(int fixedLength, string preAdd, ref string sPartialRead, ref string sRead)
        {
            if (sRead.Length != fixedLength)
            {
                // partial read.
                if (!String.IsNullOrEmpty(sPartialRead))
                {
                    sPartialRead += sRead;
                    if (sPartialRead.Length != fixedLength)
                        return false;

                    sRead = sPartialRead;
                    sPartialRead = String.Empty;
                }
                else
                {
                    sPartialRead = sRead;
                    return false;
                }
            }
            sRead = preAdd + sRead.Substring(preAdd.Length);
            return true;
        }

        private static void Main()
        {
            bool success;
            UsbK usb;
            WINUSB_PIPE_INFORMATION pipeInfoRead;
            USB_INTERFACE_DESCRIPTOR interfaceDescriptorRead;

            WINUSB_PIPE_INFORMATION pipeInfoWrite;
            USB_INTERFACE_DESCRIPTOR interfaceDescriptorWrite;

            // Find the IN endpoint and configure the device.
            Test.PipeId = Test.PipeId | AllKConstants.USB_ENDPOINT_DIRECTION_MASK;
            if (!Test.ConfigureDevice(out pipeInfoRead, out usb, out interfaceDescriptorRead)) return;

            // Find the OUT endpoint.
            Test.PipeId = Test.PipeId & ~AllKConstants.USB_ENDPOINT_DIRECTION_MASK;
            if (!Test.FindPipeAndInterface(usb, out interfaceDescriptorWrite, out pipeInfoWrite)) return;

            Debug.Assert(
                         interfaceDescriptorRead.bInterfaceNumber == interfaceDescriptorWrite.bInterfaceNumber,
                         "This example requires the IN and OUT endpoints have the same bInterfaceNumber.");

            Debug.Assert(
                         pipeInfoRead.MaximumPacketSize > 0 && 
                         pipeInfoRead.MaximumPacketSize == pipeInfoWrite.MaximumPacketSize,
                         "This example requires the IN and OUT endpoints have the same MaximumPacketSize.");

            // We will keep the buffer >= 1024.
            // To satisfy StmK it must also be an interval of MaximumPacketSize
            if (Test.TransferBufferSize == -1)
                Test.TransferBufferSize = pipeInfoWrite.MaximumPacketSize * ((1024 + pipeInfoWrite.MaximumPacketSize-1) / pipeInfoWrite.MaximumPacketSize);

#if BMFW
            // TODO FOR USER: Remove this block if not using benchmark firmware.
            // This configures devices running benchmark firmware for streaming DeviceToHost transfers.
            Console.WriteLine("Configuring for benchmark device..");
            BM_TEST_TYPE testType = BM_TEST_TYPE.LOOP;
            success = Benchmark.Configure(usb, BM_COMMAND.SET_TEST, interfaceDescriptorRead.bInterfaceNumber, ref testType);
            if (!success)
            {
                Console.WriteLine("Bench_Configure failed.");
            }
#endif
            if (!Test.ShowTestReady()) goto Done;

            UsbStream stmRead = new UsbStream(usb,
                                              pipeInfoRead.PipeId,
                                              Test.TransferBufferSize,
                                              Test.MaxPendingTransfers,
                                              Test.MaxPendingIO,
                                              true,
                                              1);
            UsbStream stmWrite = new UsbStream(usb,
                                               pipeInfoWrite.PipeId,
                                               Test.TransferBufferSize,
                                               Test.MaxPendingTransfers,
                                               Test.MaxPendingIO,
                                               true,
                                               3000);

            StreamReader stmReader = new StreamReader(stmRead);
            StreamWriter stmWriter = new StreamWriter(stmWrite);

            stmRead.Start();
            stmWrite.Start();

            Char[] chTemp = new char[Test.TransferBufferSize];
            while (stmReader.Read(chTemp, 0, chTemp.Length) > 0)
            {
                Console.WriteLine("Flushing packets..");
            }
            string sWrite = String.Empty;
            string sPartialRead = String.Empty;
            string sRead;
            const string lineFormat = "Tx#{0:000000} This string is being looped through endpoints {1:X2}h and {2:X2}h";
            int lineLength = String.Format(lineFormat, 0, 0, 0).Length;

            // This is a counter/timer used only for statistics gathering.
            Thread.Sleep(0);
            Test.Dcs.Start();

            for (int iTransfers = 0; iTransfers < Test.MaxTransfersTotal; iTransfers++)
            {
                sWrite = String.Format(lineFormat, iTransfers, pipeInfoWrite.PipeId, pipeInfoRead.PipeId);
                stmWriter.WriteLine(sWrite);
                Console.WriteLine(sWrite);

                if ((iTransfers & 8) > 0) stmWriter.Flush();
                if (iTransfers <= 16 || (String.IsNullOrEmpty((sRead = stmReader.ReadLine()))))
                    continue;

                if (!FormatBrokenStrings(lineLength, "Rx", ref sPartialRead, ref sRead)) continue;
                Console.WriteLine(sRead);
            }

            stmWriter.Flush();
            while (!(String.IsNullOrEmpty((sRead = stmReader.ReadLine()))))
            {
                if (!FormatBrokenStrings(lineLength, "Rx", ref sPartialRead, ref sRead)) continue;
                Console.WriteLine(sRead);
            }

            Test.Dcs.Stop();
            TimeSpan ts = new TimeSpan(Test.Dcs.Ticks);
            Console.WriteLine("Elapsed Time:\n\t{0} mins\n\t{1} secs\n\t{2} msecs", Math.Floor(ts.TotalMinutes), ts.Seconds, ts.Milliseconds);

            stmWriter.Dispose();
            stmReader.Dispose();

            Done:
            usb.Free();
        }
    }
}