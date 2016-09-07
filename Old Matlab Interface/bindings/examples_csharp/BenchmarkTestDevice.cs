#region Copyright(c) Travis Robinson
// Copyright (c) 2012 Travis Robinson <libusbdotnet@gmail.com>
// All rights reserved.
// 
// BenchmarkTestDevice.cs
// 
// Created:      03.05.2012
// Last Updated: 03.05.2012
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
using System.Runtime.InteropServices;
using libusbK;


// ReSharper disable CheckNamespace

namespace Test.Devices
// ReSharper restore CheckNamespace
{
    public enum BM_COMMAND
    {
        SET_TEST = 0x0E,
        GET_TEST = 0x0F,
    };

    public enum BM_TEST_TYPE
    {
        NONE = 0x00,
        READ = 0x01,
        WRITE = 0x02,
        LOOP = READ | WRITE,
    };

    public static class Benchmark
    {
        //! Custom vendor requests that must be implemented in the benchmark firmware.


        #region Public Members
        public static bool Configure(UsbK usb,
                                     BM_COMMAND command,
                                     byte interfaceNumber,
                                     ref BM_TEST_TYPE testType)
        {
            int transferred;
            WINUSB_SETUP_PACKET pkt;
            byte[] data = new byte[1];

            pkt.RequestType = (1 << 7) | (2 << 5);
            pkt.Request = (byte) command;

            pkt.Value = (ushort) testType;
            pkt.Index = interfaceNumber;
            pkt.Length = 1;

            bool success = usb.ControlTransfer(pkt,
                                               Marshal.UnsafeAddrOfPinnedArrayElement(data,
                                                                                      0),
                                               1,
                                               out transferred,
                                               IntPtr.Zero);
            testType = (BM_TEST_TYPE) data[0];
            return success;
        }
        #endregion
    }
}