#region Copyright(c) Travis Robinson

// Copyright (c) 2011-2012 Travis Robinson <libusbdotnet@gmail.com>
// All rights reserved.
// 
// Read.Isochronous
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
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Threading;
using Test.Devices;
using libusbK;
using libusbK.Examples;

namespace Read.Isochronous
{
    // ReSharper disable InconsistentNaming

    internal class Program
    {
        #region TODO USER: Set the test parameters for your device.

        public static IsoTestParameters Test = new IsoTestParameters(0x04d8, 0xfa2e, 0, 0x82, 3, 64, "xfer-iso-read.txt", 24);

        #endregion

        private static void Main(string[] args)
        {
            bool success;
            WINUSB_PIPE_INFORMATION pipeInfo;
            UsbK usb;
            USB_INTERFACE_DESCRIPTOR interfaceDescriptor;

            // Find and configure the device.
            if (!Test.ConfigureDevice(out pipeInfo, out usb, out interfaceDescriptor)) return;

#if BMFW
            // TODO FOR USER: Remove this block if not using benchmark firmware.
            // This configures devices running benchmark firmware for streaming DeviceToHost transfers.
            Console.WriteLine("Configuring for benchmark device..");
            BM_TEST_TYPE testType = BM_TEST_TYPE.READ;
            success = Benchmark.Configure(usb, BM_COMMAND.SET_TEST, interfaceDescriptor.bInterfaceNumber, ref testType);
            if (!success)
            {
                Console.WriteLine("Bench_Configure failed.");
            }
#endif
            // Create the ISO transfer queue.  This class manages the pending and outstanding transfer lists.
            ReadIsoTransferQueue readXfers = new ReadIsoTransferQueue(usb, ref pipeInfo, Test.MaxOutstandingTransfers, Test.IsoPacketsPerTransfer);

            if (!Test.ShowTestReady()) goto Done;

            // Always issue a reset pipe prior to re/starting an ISO stream.
            usb.ResetPipe(pipeInfo.PipeId);

            // This example will not manage the start frame manually, but this is
            // how I might caculate the starting point.
            usb.GetCurrentFrameNumber(out readXfers.FrameNumber);
            unchecked
            {
                // Add some start latency
                readXfers.FrameNumber += 32;

                // Start FrameNumber at an interval of 8.
                readXfers.FrameNumber -= ((readXfers.FrameNumber)%8);
            }

            // This is a counter/timer used only for statistics gathering.
            Thread.Sleep(0);
            Test.Dcs.Start();

            // Transfer processing loop
            do
            {
                IsoTransferItem isoTransferItem;
                int transferred;
                int errorCode;
                // While buffers exist in the completed list, submit them. 
                while (readXfers.Completed.Count > 0 && readXfers.TotalSubmittedCount < Test.MaxTransfersTotal)
                {
                    errorCode = readXfers.SubmitNextRead();
                    if (errorCode != 0)
                    {
                        Console.WriteLine("IsoReadPipe failed. ErrorCode: {0:X8}h", errorCode);
                        goto Done;
                    }
                }

                if (readXfers.Outstanding.Count == 0)
                {
                    // The MAX_TRANSFERS_TOTAL test limit hit.
                    Console.WriteLine("Done!");
                    goto Done;
                }

                // Wait for the oldest transfer to complete.
                errorCode = readXfers.WaitRead(out isoTransferItem, 1000, out transferred);
                if (errorCode != 0)
                {
                    Console.WriteLine("OvlPool.Wait failed. ErrorCode: {0:X8}h", errorCode);
                    goto Done;
                }

                // Report iso status.
                IsoXferReport(readXfers, isoTransferItem, transferred);

                if (readXfers.CompletedCount == 1) Test.Dcs.Start();
            } while (true);

            Done:
            readXfers.Destroy();
            Test.Free();

            usb.Free();
        }

        private static void IsoXferReport(ReadIsoTransferQueue readIsoTransfers, IsoTransferItem isoTransferItem, int transferLength)
        {
            int packetPos;
            Test.Dcs.Stop(transferLength);
            if (readIsoTransfers.LastStartFrame == 0)
            {
                Test.LogLn("#{0}: StartFrame={1:X8}h TransferLength={2} BPS-average:{3}",
                           readIsoTransfers.CompletedCount,
                           isoTransferItem.Iso.StartFrame,
                           transferLength,
                           Math.Round(Test.Dcs.Bps, 2));
            }
            else
            {
                int lastFrameCount = isoTransferItem.Iso.StartFrame - readIsoTransfers.LastStartFrame;
                Test.LogLn("#{0}: StartFrame={1:X8}h TransferLength={2} BPS-average:{3} LastFrameCount={4}",
                           readIsoTransfers.CompletedCount,
                           isoTransferItem.Iso.StartFrame,
                           transferLength,
                           Math.Round(Test.Dcs.Bps, 2),
                           lastFrameCount);
            }

            int numPackets = isoTransferItem.Iso.NumberOfPackets;
            for (packetPos = 0; packetPos < numPackets; packetPos++)
            {
                KISO_PACKET isoPacket;
                isoTransferItem.Iso.GetPacket(packetPos, out isoPacket);
                if (isoPacket.Length > 1)
                {
                    // This is somewhat specific to data that is returned by the benchmark firmware.
                    byte firstPacketByte = isoTransferItem.Buffer[isoPacket.Offset];
                    byte secondPacketByte = isoTransferItem.Buffer[isoPacket.Offset + 1];
                    Test.LogLn("  [{0:000}] Length={1} B0={2:X2}h B1={3:X2}h", packetPos, isoPacket.Length, firstPacketByte, secondPacketByte);
                }
                else
                {
                    Test.LogLn("  [{0:000}] Empty Packet", packetPos);
                }
            }

            readIsoTransfers.CompletedCount++;
            readIsoTransfers.LastStartFrame = isoTransferItem.Iso.StartFrame;
        }
    }

    internal class IsoTransferItem
    {
        public byte[] Buffer;
        public GCHandle BufferGC;
        public IsoK Iso;
        public KOVL_HANDLE Ovl;
    }

    internal class ReadIsoTransferQueue
    {
        #region Transfer lists

        public LinkedList<IsoTransferItem> Completed = new LinkedList<IsoTransferItem>();
        public LinkedList<IsoTransferItem> Master = new LinkedList<IsoTransferItem>();
        public LinkedList<IsoTransferItem> Outstanding = new LinkedList<IsoTransferItem>();

        #endregion

        #region Core queue members

        public readonly int DataBufferSize;
        public readonly OvlK OvlPool;
        public readonly WINUSB_PIPE_INFORMATION PipeInfo;
        public readonly UsbK Usb;

        #endregion

        #region Frame management

        public int FrameNumber;
        public int LastStartFrame;

        #endregion

        #region Statisitics

        public uint CompletedCount;
        public uint TotalSubmittedCount;

        #endregion

        public ReadIsoTransferQueue(UsbK usb, ref WINUSB_PIPE_INFORMATION pipeInfo, int maxPendingTransfers, int numberOfPackets)
        {
            PipeInfo = pipeInfo;
            Usb = usb;
            OvlPool = new OvlK(usb.Handle, maxPendingTransfers, KOVL_POOL_FLAG.NONE);
            DataBufferSize = (pipeInfo.MaximumPacketSize*numberOfPackets);
            for (int pos = 0; pos < maxPendingTransfers; pos++)
            {
                IsoTransferItem isoTransferItem = new IsoTransferItem();

                isoTransferItem.Buffer = new byte[pipeInfo.MaximumPacketSize*numberOfPackets];
                isoTransferItem.BufferGC = GCHandle.Alloc(isoTransferItem.Buffer, GCHandleType.Pinned);

                isoTransferItem.Iso = new IsoK(numberOfPackets, 0);
                isoTransferItem.Iso.SetPackets(pipeInfo.MaximumPacketSize);

                OvlPool.Acquire(out isoTransferItem.Ovl);

                Master.AddLast(isoTransferItem);
                Completed.AddLast(isoTransferItem);
            }
        }

        public void Destroy()
        {
            // Cancel any outstanding IO and release the OvlK.
            foreach (IsoTransferItem myIsoBuffer in Outstanding)
            {
                int transferred;
                OvlPool.WaitAndRelease(myIsoBuffer.Ovl, 0, out transferred);
            }
            Completed.Clear();
            Outstanding.Clear();

            foreach (IsoTransferItem myIsoBuffer in Master)
            {
                myIsoBuffer.Iso.Free();
                myIsoBuffer.BufferGC.Free();
            }
            Master.Clear();
            OvlPool.Free();
        }

        private static void SetNextFrameNumber(IsoTransferItem isoTransferItem)
        {
        }

        public int SubmitNextRead()
        {
            // Pull from head of Completed list and push to end of Outstanding list
            IsoTransferItem isoTransferItem = Completed.First.Value;
            Completed.RemoveFirst();
            Outstanding.AddLast(isoTransferItem);

            // If managing a start frame manually, set it here and update the the frame counter for the next transfer.
            SetNextFrameNumber(isoTransferItem);

            // Prepare the OvlK handle to be submitted.
            OvlPool.ReUse(isoTransferItem.Ovl);

            // The data buffer was pinned earlier when it was allocated.  Always pin managed memory before using it
            // in an asynchronous function to keep the framework from tampering with it.
            Usb.IsoReadPipe(PipeInfo.PipeId,
                            isoTransferItem.Buffer,
                            DataBufferSize,
                            isoTransferItem.Ovl,
                            isoTransferItem.Iso.Handle);

            int errorCode = Marshal.GetLastWin32Error();

            // 997 is ERROR_IO_PENDING. For async, this means so far so good.
            // IE: The transfer is submitted but we won't know if a problem occurs until it is completed.
            if (errorCode != ErrorCodes.IoPending) return errorCode;

            TotalSubmittedCount++;

            return 0;
        }

        public int WaitRead(out IsoTransferItem isoTransferItem, int i, out int transferred)
        {
            isoTransferItem = Outstanding.First.Value;
            bool success = OvlPool.Wait(isoTransferItem.Ovl, 1000, KOVL_WAIT_FLAG.NONE, out transferred);
            if (!success)
            {
                return Marshal.GetLastWin32Error();
            }

            Outstanding.RemoveFirst();
            Completed.AddLast(isoTransferItem);

            return 0;
        }
    }
}