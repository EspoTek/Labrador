#region Copyright(c) Travis Robinson

// Copyright (c) 2011-2012 Travis Robinson <libusbdotnet@gmail.com>
// All rights reserved.
// 
// List.Devices
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
using libusbK;

namespace List.Devices
{
    internal class Program
    {
        private static void Main()
        {
            int deviceIndex = 0;
            int deviceCount = 0;
            KLST_DEVINFO_HANDLE deviceInfo;
            LstK lst = new LstK(KLST_FLAG.NONE);

            lst.Count(ref deviceCount);
            while (lst.MoveNext(out deviceInfo))
            {
                // Write some information about the device.
                string displayLine = String.Format("{0} of {1}: {2}",
                                                   ++deviceIndex,
                                                   deviceCount,
                                                   deviceInfo.DeviceDesc);
                Console.WriteLine(displayLine);
                Console.WriteLine("- " + deviceInfo.DeviceID);
                Console.WriteLine();
            }

            if (deviceCount == 0)
                Console.WriteLine("No devices found!\n");

            lst.Free();
        }
    }
}