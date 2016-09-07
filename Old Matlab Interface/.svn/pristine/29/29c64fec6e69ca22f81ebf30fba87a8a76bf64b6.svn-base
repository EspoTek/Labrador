#region Copyright(c) Travis Robinson
// Copyright (c) 2012 Travis Robinson <libusbdotnet@gmail.com>
// All rights reserved.
// 
// fHandleTest.cs
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
using System.Collections.Generic;
using System.Diagnostics;
using System.Threading;
using System.Windows.Forms;
using libusbK;


namespace Handle.Test
{
    public partial class fHandleTest : Form
    {
        private LstK LstKField;
        private List<LstK> LstKList = new List<LstK>();

        private TextBoxTraceListener mListener;

        public fHandleTest()
        {
            InitializeComponent();
        }

        ~fHandleTest()
        {
        }

        private void createAndExplictlyDestroyToolStripMenuItem_Click(object sender, EventArgs e)
        {
            LstK lstTemp = new LstK(KLST_FLAG.NONE);
            lstTemp.Dispose();
        }

        private void runGarbageCollectorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            GC.Collect(GC.MaxGeneration, GCCollectionMode.Forced);
        }

        private void referenceToolStripMenuItem_Click(object sender, EventArgs e)
        {
            LstK lstTemp = new LstK(KLST_FLAG.NONE);
            LstKList.Add(lstTemp);
            LstKField = lstTemp;
        }

        private void derefrenceToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (LstKList.Count > 0)
            {
                LstKList.Clear();
            }
            else
            {
                LstKField = null;
            }
        }

        private void createWithoutExplictDestroyToolStripMenuItem_Click(object sender, EventArgs e)
        {
            LstK lstTemp = new LstK(KLST_FLAG.NONE);
            int count = 0;
            lstTemp.Count(ref count);
        }

        private void fHandleTest_Load(object sender, EventArgs e)
        {
            mListener = new TextBoxTraceListener(txtOutput, ThreadPriority.Lowest);
            Debug.Listeners.Add(mListener);
        }

        private void fHandleTest_FormClosed(object sender, FormClosedEventArgs e)
        {
            Debug.Listeners.Remove(mListener);
            mListener.Free();
        }

        private void exhaustAllHandlesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            LstKList.Clear();
            LstKField = null;
            int count = 0;
            try
            {
                while (true)
                {
                    new LstK(KLST_FLAG.NONE);
                    count++;
                }
            }
            catch
            {
            }

            Debug.Print("All handles exhausted. Count:{0}", count);
        }

        private void testListenerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            new TestListener(64);
        }
    }
}