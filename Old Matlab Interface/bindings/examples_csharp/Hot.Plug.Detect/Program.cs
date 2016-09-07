#region Copyright(c) Travis Robinson

// Copyright (c) 2012 Travis Robinson <libusbdotnet@gmail.com>
// All rights reserved.
// 
// Hot.Plug.Detect
// 
// Last Updated: 04.28.2012
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
using libusbK;

namespace Hot.Plug.Detect
{
    internal class Program
    {
        // ReSharper disable InconsistentNaming

        #region For Window Applications
        private const int WM_USER = 0x400;
        private const int WM_USER_HOT_BASE = WM_USER;
        private const int WM_USER_HOT_REMOVAL = WM_USER_HOT_BASE;
        private const int WM_USER_HOT_ARRIVAL = WM_USER_HOT_BASE + 1;
        #endregion

        private static void Main()
        {
            KHOT_PARAMS hotInitParams = new KHOT_PARAMS();

            // In the real world, you would want to filter for only *your* device(s).
            hotInitParams.PatternMatch.DeviceInterfaceGUID = "*";

            // The PLUG_ALL_ON_INIT flag will force plug events for matching devices that are already connected.
            hotInitParams.Flags = KHOT_FLAG.PLUG_ALL_ON_INIT;

            hotInitParams.OnHotPlug = OnHotPlug;

            /* Instead of a callback you can send/post messages directly to a window handle.
            hotInitParams.UserHwnd = MyForm.Handle;
            hotInitParams.UserMessage = WM_USER_HOT_BASE;
            */

            Console.WriteLine("Monitoring libusbK arrival/removal events.");
            Console.WriteLine("[PatternMatch]");
            Console.WriteLine(hotInitParams.PatternMatch.ToString());
            Console.WriteLine("Press [ENTER] to exit..");

            while (Console.KeyAvailable) Console.ReadKey(true);

            // You may set your initial hot handle user context like this.
            // This example is using it to count connected devices and detect the first OnHotPlug event (Int32.MaxValue).
            AllKFunctions.LibK_SetDefaultContext(KLIB_HANDLE_TYPE.HOTK, new IntPtr(Int32.MaxValue));

            // Start hot-plug detection.
            HotK hot = new HotK(ref hotInitParams);

            Console.ReadLine();

            hot.Free();
        }

        private static void OnHotPlug(KHOT_HANDLE hotHandle,
                                      KLST_DEVINFO_HANDLE deviceInfo,
                                      KLST_SYNC_FLAG plugType)
        {
            string plugText;

            int totalPluggedDeviceCount = (int) hotHandle.GetContext().ToInt64();
            if (totalPluggedDeviceCount == int.MaxValue)
            {
                Console.WriteLine("OnHotPlug is being called for the first time on handle:{0}", hotHandle.Pointer);
                totalPluggedDeviceCount = 0;
            }

            switch (plugType)
            {
                case KLST_SYNC_FLAG.ADDED:
                    plugText = "Arrival";
                    totalPluggedDeviceCount++;
                    break;
                case KLST_SYNC_FLAG.REMOVED:
                    plugText = "Removal";
                    totalPluggedDeviceCount--;
                    break;
                default:
                    throw new ArgumentOutOfRangeException("plugType");
            }

            hotHandle.SetContext(new IntPtr(totalPluggedDeviceCount));

            Console.WriteLine("\n[OnHotPlug] Device {0}:{1} \n",
                              plugText,
                              deviceInfo);
            Console.WriteLine("Total Plugged Device Count: {0}",
                              totalPluggedDeviceCount);
        }
    }
}