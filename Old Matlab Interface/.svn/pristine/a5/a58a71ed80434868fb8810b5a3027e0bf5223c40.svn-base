#region Copyright(c) Travis Robinson

// Copyright (c) 2011-2012 Travis Robinson <libusbdotnet@gmail.com>
// All rights reserved.
// 
// Hot.Plug.Detect.GUI
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

using System;
using System.Windows.Forms;
using libusbK;

namespace Hot.Plug.Detect.GUI
{
    public partial class Form1 : Form
    {
        private const int WM_USER = 0x400;

        private const int WM_USER_HOT_BASE = WM_USER;
        private const int WM_USER_HOT_REMOVAL = WM_USER_HOT_BASE;
        private const int WM_USER_HOT_ARRIVAL = WM_USER_HOT_BASE + 1;
        private HotK mHotK;
        private KHOT_PARAMS mHotParams;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            mHotParams.PatternMatch.DeviceInterfaceGUID = "*";
            
            // Set the Hwnd handle.
            mHotParams.UserHwnd = Handle;

            // Set the base user message.  This can be any value greater than or equal to 0x400
            mHotParams.UserMessage = WM_USER_HOT_BASE;
            
            // After initializing, send plug events for devices that are currently connected.
            mHotParams.Flags = KHOT_FLAG.PLUG_ALL_ON_INIT;

            // This will cause HotK to use PostMessage instead of SendMessage.
            mHotParams.Flags |= KHOT_FLAG.POST_USER_MESSAGE;

            mHotK = new HotK(ref mHotParams);
        }

        private void OnHotPlugInvoked(KHOT_HANDLE hotHandle, KLST_DEVINFO_HANDLE deviceInfo, KLST_SYNC_FLAG plugType)
        {
            string symbolicLink = deviceInfo.SymbolicLink;
            switch (plugType)
            {
                case KLST_SYNC_FLAG.ADDED:
                    int iRow = dgvDevices.Rows.Add(new object[] {symbolicLink, deviceInfo.DeviceDesc, deviceInfo.DeviceID});
                    dgvDevices.Rows[iRow].Cells[1].ToolTipText = deviceInfo.ToString();
                    dgvDevices.Rows[iRow].Cells[2].ToolTipText = deviceInfo.Common.ToString();
                    break;
                case KLST_SYNC_FLAG.REMOVED:
                    foreach (DataGridViewRow row in dgvDevices.Rows)
                    {
                        if (row.Cells[0].Value as string != symbolicLink) continue;
                        dgvDevices.Rows.Remove(row);
                        break;
                    }
                    break;
                default:
                    throw new ArgumentOutOfRangeException("plugType");
            }
        }

        protected override void WndProc(ref Message m)
        {
            /* When using the HotK UserHwnd and UserMsg, the add/remove events are seperated into to different messages.
             * Removal = UserMsg + 0
             * Arrival = UserMsg + 1
             */
            if (m.Msg == WM_USER_HOT_REMOVAL || m.Msg == WM_USER_HOT_ARRIVAL)
            {
                KHOT_HANDLE hotHandle = new KHOT_HANDLE(m.WParam);
                KLST_DEVINFO_HANDLE deviceInfo = new KLST_DEVINFO_HANDLE(m.LParam);
                KLST_SYNC_FLAG plugType = (m.Msg == WM_USER_HOT_REMOVAL) ? KLST_SYNC_FLAG.REMOVED : KLST_SYNC_FLAG.ADDED;

                OnHotPlugInvoked(hotHandle, deviceInfo, plugType);
                return;
            }
            base.WndProc(ref m);
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            mHotK.Dispose();
        }
    }
}