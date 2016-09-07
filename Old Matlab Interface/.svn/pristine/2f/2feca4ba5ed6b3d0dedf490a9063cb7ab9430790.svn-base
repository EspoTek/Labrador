#region Copyright(c) Travis Robinson
// Copyright (c) 2012 Travis Robinson <libusbdotnet@gmail.com>
// All rights reserved.
// 
// HiPerfTimer.cs
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


using System.ComponentModel;
using System.Runtime.InteropServices;


namespace Win32
{
    internal class HiPerfTimer
    {
        #region Public Members
        public HiPerfTimer()
        {
            startTime = 0;
            stopTime = 0;
            length = 0;

            if (QueryPerformanceFrequency(out freq) == false)
            {
                // high-performance counter not supported 
                throw new Win32Exception();
            }
        }

        /// <summary>
        ///   Gets the bytes per second
        /// </summary>
        public double Bps
        {
            get
            {
                double duration = Duration;
                if (duration.Equals(0.0)) return 0.0;
                return length/duration;
            }
        }

        /// <summary>
        ///   Gets the duration of the timer (in seconds)
        /// </summary>
        public double Duration
        {
            get
            {
                return (stopTime - startTime)/(double) freq;
            }
        }

        /// <summary>
        ///   Gets the duration of the timer (in seconds)
        /// </summary>
        public long Ticks
        {
            get
            {
                long tDiff = stopTime - startTime;
                tDiff = (tDiff*10000000)/freq;

                return tDiff;
            }
        }
        /// <summary>
        ///   Start the timer
        /// </summary>
        public void Start()
        {
            length = 0;
            QueryPerformanceCounter(out startTime);
        }

        /// <summary>
        ///   Stop the timer
        /// </summary>
        public void Stop()
        {
            QueryPerformanceCounter(out stopTime);
        }

        public void Stop(int addLength)
        {
            QueryPerformanceCounter(out stopTime);
            length += addLength;
        }
        #endregion


        #region Private Members
        [DllImport("Kernel32.dll")]
        private static extern bool QueryPerformanceCounter(out long lpPerformanceCount);

        [DllImport("Kernel32.dll")]
        private static extern bool QueryPerformanceFrequency(out long lpFrequency);

        private readonly long freq;
        private long length;
        private long startTime, stopTime;
        #endregion
    }
}