#region Copyright(c) Travis Robinson
// Copyright (c) 2012 Travis Robinson <libusbdotnet@gmail.com>
// All rights reserved.
// 
// TextBoxTraceListener.cs
// 
// Created:      03.02.2012
// Last Updated: 03.03.2012
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
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.Threading;
using System.Windows.Forms;


namespace Handle.Test
{
    public class TestListener
    {
        #region Public Members
        public TestListener(int threadCount)
        {
            mThreadCount = threadCount;
            while (threadCount-- > 0)
                mThreadList.Add(new Thread(DebugDumpProc));

            threadCount = mThreadCount;

            foreach (Thread thread in mThreadList)
                thread.Start((mThreadCount) - (threadCount--));

            Thread.Sleep(0);
        }
        #endregion


        #region Private Members
        private static void DebugDumpProc(object state)
        {
            for (int iLine = 0; iLine < 64; iLine++)
                Debug.Print("Debug test output. ThreadIndex:{0:000}  Line:{1:000}", (int) state, iLine);
        }

        private readonly int mThreadCount;
        private readonly List<Thread> mThreadList = new List<Thread>();
        #endregion
    }

    public class TextBoxTraceListener : TraceListener
    {
        #region Nested Delegates
        private delegate void WriteDelegate(string message);
        #endregion


        #region Public Members
        public TextBoxTraceListener(TextBox textBox, ThreadPriority priority)
        {
            mTraceLines = ArrayList.Synchronized(mTraceLinesUnsafe);
            mTextBox = textBox;
            writeInvokeCb = WriteInvoke;
            mUiThread = new Thread(ListenerOutputProc);
            mUiThread.Priority = priority;

            mUiThread.Start(this);
        }

        /// <summary>Calls the dispose method.</summary>
        public virtual void Free()
        {
            if (mUiThread != null)
                mCancelEvent.Set();

            mUiThread = null;
        }

        public override void Write(string message)
        {
            ArrayList traceLines = mTraceLines;
            traceLines.Add(message);
            mOutputReadySemaphore.Release();
        }

        public override void WriteLine(string message)
        {
            Write(message + Environment.NewLine);
        }
        #endregion


        #region Private Members
        private static void ListenerOutputProc(object state)
        {
            TextBoxTraceListener listener = (TextBoxTraceListener) state;

            while (true)
            {
                int waitRet = WaitHandle.WaitAny(new WaitHandle[] {listener.mOutputReadySemaphore, listener.mCancelEvent});
                if (waitRet != 0) break;

                ArrayList traceLines = listener.mTraceLines;
                String sLines = String.Empty;
                DateTime dtNow = DateTime.Now;
                while (true)
                {
                    sLines += String.Format("[{0:00}:{1:00}:{2:00}:{3:000}] {4}", dtNow.Hour, dtNow.Minute, dtNow.Second, dtNow.Millisecond, traceLines[0] as string);
                    traceLines.RemoveAt(0);

                    if (!listener.mOutputReadySemaphore.WaitOne(0)) break;
                }

                try
                {
                    listener.mTextBox.Invoke(listener.writeInvokeCb, new object[] {sLines});
                }
                catch
                {
                    break;
                }
            }
        }

        private void WriteInvoke(string message)
        {
            mTextBox.AppendText(message);
        }

        private readonly ManualResetEvent mCancelEvent = new ManualResetEvent(false);

        private readonly Semaphore mOutputReadySemaphore = new Semaphore(0, int.MaxValue);
        private readonly TextBox mTextBox;
        private readonly ArrayList mTraceLines;
        private readonly ArrayList mTraceLinesUnsafe = new ArrayList();
        private Thread mUiThread;
        private readonly WriteDelegate writeInvokeCb;
        #endregion
    }
}