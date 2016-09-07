#region Copyright(c) Travis Robinson

// Copyright (c) 2012 Travis Robinson <libusbdotnet@gmail.com>
// All rights reserved.
// 
// UsbStream.cs
// 
// Created:      03.05.2012
// Last Updated: 03.07.2012
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

using System;
using System.Diagnostics;
using System.IO;
using System.Runtime.InteropServices;
using libusbK;

namespace Xfer.UsbStream
{
    // ReSharper disable InconsistentNaming

    public class UsbStream : Stream
    {
        public static bool UseCallbacks = true;

        private readonly KSTM_CALLBACK mCallbacks;
        protected readonly byte mPipeId;
        protected StmK mStm;
        protected UsbK mUsb;
        private bool mbDisposed;

        public UsbStream(UsbK usb,
                         byte pipeId,
                         int maxTransferSize,
                         int maxPendingTransfers,
                         int maxPendingIo,
                         bool useTimeout,
                         UInt16 timeout)
        {
            mUsb = usb;
            mPipeId = pipeId;

            if (UseCallbacks)
            {
                mCallbacks.Complete = StmComplete;
                if (((mPipeId & AllKConstants.USB_ENDPOINT_DIRECTION_MASK) > 0))
                {
                    mCallbacks.Submit = StmSubmitRead;
                }
                else
                {
                    mCallbacks.Submit = StmSubmitWrite;
                }
            }
            KSTM_FLAG flags = useTimeout ? KSTM_FLAG.USE_TIMEOUT | (KSTM_FLAG) timeout : KSTM_FLAG.NONE;

            mStm = new StmK(mUsb.Handle,
                            pipeId,
                            maxTransferSize,
                            maxPendingTransfers,
                            maxPendingIo,
                            ref mCallbacks,
                            flags);
        }

        public override bool CanRead
        {
            get
            {
                return ((mPipeId & AllKConstants.USB_ENDPOINT_DIRECTION_MASK) > 0);
            }
        }

        public override bool CanSeek
        {
            get
            {
                return false;
            }
        }

        public override bool CanWrite
        {
            get
            {
                return ((mPipeId & AllKConstants.USB_ENDPOINT_DIRECTION_MASK) == 0);
            }
        }

        protected override void Dispose(bool disposing)
        {
            if (!mbDisposed)
            {
                mStm.Dispose();
                mStm = null;
                mUsb = null;
                mbDisposed = true;
            }
            base.Dispose(disposing);
        }

        public override int Read(byte[] buffer, int offset, int count)
        {
            int transferred;
            bool success = mStm.Read(buffer, offset, count, out transferred);

            Debug.WriteLineIf(!success,
                              String.Format("Failed reading from usb stream. ErrorCode={0:X8}h",
                                            Marshal.GetLastWin32Error()),
                              "ERROR");

            return !success ? 0 : transferred;
        }

        public bool Start()
        {
            return mStm.Start();
        }

        public bool Stop(int timeoutCancelMs)
        {
            return mStm.Stop(timeoutCancelMs);
        }

        public override void Write(byte[] buffer, int offset, int count)
        {
            int transferred;

            bool success = mStm.Write(buffer, offset, count, out transferred);
            if (!success)
            {
                // This is caused by a lack of 'PendingTransfer' slots.
                Debug.WriteLine(
                                String.Format("Failed writing to usb stream. ErrorCode={0:X8}h",
                                              Marshal.GetLastWin32Error()),
                                "ERROR");
                return;
            }

            // If the KSTM_FLAG.NO_PARTIAL_XFERS is *not* set, StmK will transfer as many bytes as it can and return true.
            Debug.WriteLineIf(transferred != count,
                              String.Format("Not all bytes were written. Expected:{0} Transferred:{1}",
                                            count,
                                            transferred),
                              "ERROR");
        }

        public override void Flush()
        {
        }

        private int StmComplete(KSTM_INFO stmInfo, KSTM_XFER_CONTEXT xferContext, int stmXferContextIndex, int errorCode)
        {
            Debug.WriteLineIf(errorCode != ErrorCodes.Success,
                              String.Format("Failed completing transfer. PipeID:{0:X2}h ErrorCode:{1:X8}h",
                                            mPipeId,
                                            errorCode),
                              "ERROR");
            return errorCode;
        }

        private int StmSubmitRead(KSTM_INFO info,
                                  KSTM_XFER_CONTEXT xferContext,
                                  int xferContextIndex,
                                  IntPtr nativeOverlapped)
        {
            int notUsedForAsync;
            int bufferSize = xferContext.BufferSize;

            bool success = mUsb.ReadPipe(mPipeId, xferContext.Buffer, bufferSize, out notUsedForAsync, nativeOverlapped);
            int errorCode = Marshal.GetLastWin32Error();

            if (!success && errorCode == ErrorCodes.IoPending) return ErrorCodes.Success;

            Debug.WriteLine(
                            String.Format("Failed submitting transfer. PipeID:{0:X2}h ErrorCode:{1:X8}h",
                                          mPipeId,
                                          errorCode),
                            "ERROR");
            return errorCode;
        }

        private int StmSubmitWrite(KSTM_INFO info,
                                   KSTM_XFER_CONTEXT xferContext,
                                   int xferContextIndex,
                                   IntPtr nativeOverlapped)
        {
            int notUsedForAsync;
            int bufferSize = xferContext.TransferLength;

            bool success = mUsb.WritePipe(mPipeId, xferContext.Buffer, bufferSize, out notUsedForAsync, nativeOverlapped);
            int errorCode = Marshal.GetLastWin32Error();

            if (!success && errorCode == ErrorCodes.IoPending) return ErrorCodes.Success;

            Debug.WriteLine(
                            String.Format("Failed submitting transfer. PipeID:{0:X2}h ErrorCode:{1:X8}h",
                                          mPipeId,
                                          errorCode),
                            "ERROR");

            return errorCode;
        }

        #region Not Supported

        public override long Length
        {
            get
            {
                throw new NotSupportedException();
            }
        }

        public override long Position
        {
            get
            {
                throw new NotSupportedException();
            }
            set
            {
                throw new NotSupportedException();
            }
        }

        public override long Seek(long offset, SeekOrigin origin)
        {
            throw new NotSupportedException();
        }

        public override void SetLength(long value)
        {
            throw new NotSupportedException();
        }

        #endregion
    }
}