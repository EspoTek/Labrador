#region Copyright(c) Travis Robinson
// Copyright (c) 2012 Travis Robinson <libusbdotnet@gmail.com>
// All rights reserved.
// 
// TestParameters.cs
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
using System.Globalization;
using System.IO;
using System.Runtime.InteropServices;
using System.Text.RegularExpressions;
using Win32;


namespace libusbK.Examples
{
    internal abstract class TestParameters
    {
        protected TestParameters(int vid,
                                 int pid,
                                 int altInterfaceId,
                                 int pipeId,
                                 int maxTransfersTotal,
                                 string logFilename)
        {
            MI = -1;
            ;
            Vid = vid;
            Pid = pid;
            PipeId = pipeId;
            AltInterfaceId = altInterfaceId;
            MaxTransfersTotal = maxTransfersTotal;
            LogFilename = logFilename;
        }


        #region Public Members
        public int AltInterfaceId;

        public bool ConfigureDevice(out WINUSB_PIPE_INFORMATION pipeInfo,
                                    out UsbK usb,
                                    out USB_INTERFACE_DESCRIPTOR interfaceDescriptor)
        {
            bool success;
            Console.WriteLine("Finding usb device by VID/PID.. ({0:X4}h / {1:X4}h)",
                              Vid,
                              Pid);

            // Use a patttern match to include only matching devices.
            // NOTE: You can use the '*' and '?' chars as wildcards for all chars or a single char (respectively). 
            KLST_PATTERN_MATCH patternMatch = new KLST_PATTERN_MATCH();
            if (MI != -1)
                patternMatch.DeviceID = String.Format("USB\\VID_{0:X4}&PID_{1:X4}&MI_{2:X2}*",
                                                        Vid,
                                                        Pid,
                                                        MI);
            else
                patternMatch.DeviceID = String.Format("USB\\VID_{0:X4}&PID_{1:X4}*",
                                                        Vid,
                                                        Pid);

            LstK deviceList = new LstK(KLST_FLAG.NONE,
                                       ref patternMatch);
            KLST_DEVINFO_HANDLE deviceInfo;
            interfaceDescriptor = new USB_INTERFACE_DESCRIPTOR();
            pipeInfo = new WINUSB_PIPE_INFORMATION();
            usb = null;

            // Iterate the devices looking for a matching alt-interface and endpoint id.
            while (deviceList.MoveNext(out deviceInfo))
            {
                // libusbK class contructors can throw exceptions; For instance, if the device is
                // using the WinUsb driver and already in-use by another application.
                Console.WriteLine("Opening usb device..");
                usb = new UsbK(deviceInfo);

                Console.WriteLine("Finding interface and endpoint by PipeId..");
                success = FindPipeAndInterface(usb,
                                               out interfaceDescriptor,
                                               out pipeInfo);
                if (success) break;

                Console.WriteLine("PipeId {0:X2}h not found on this device.",
                                  PipeId);
                usb.Free();
                usb = null;
            }
            if (ReferenceEquals(usb,
                                null))
            {
                Console.WriteLine("Usb device not found: {0}",
                                  patternMatch.DeviceID);
                success = false;
                goto Done;
            }

            MI = interfaceDescriptor.bInterfaceNumber;
            AltInterfaceId = interfaceDescriptor.bAlternateSetting;
            PipeId = pipeInfo.PipeId;

            // Set interface alt setting.
            Console.WriteLine("Setting interface #{0} to bAlternateSetting #{1}..",
                              interfaceDescriptor.bInterfaceNumber,
                              interfaceDescriptor.bAlternateSetting);
            success = usb.SetAltInterface(interfaceDescriptor.bInterfaceNumber,
                                          false,
                                          interfaceDescriptor.bAlternateSetting);
            if (!success)
            {
                Console.WriteLine("SetAltInterface failed. ErrorCode={0:X8}h",
                                  Marshal.GetLastWin32Error());
                Console.WriteLine(interfaceDescriptor.ToString());
            }

            Done:
            deviceList.Free();

            return success;
        }

        public HiPerfTimer Dcs = new HiPerfTimer();

        public void FillFromCommandLine(string commandLine)
        {
            commandLine = Regex.Replace(commandLine,
                                        "^(\".+?\"|\\S+)\\s*",
                                        "");
            string exp = String.Empty;
            exp += makeArgExpression("Vid",
                                     NumberStyles.HexNumber) + "|";
            exp += makeArgExpression("Pid",
                                     NumberStyles.HexNumber) + "|";
            exp += makeArgExpression("PipeId",
                                     NumberStyles.HexNumber) + "|";
            exp += makeArgExpression("AltId",
                                     NumberStyles.Integer) + "|";
            exp += makeArgExpression("MI",
                                     NumberStyles.Integer) + "|";
            exp += makeArgExpression("Log",
                                     NumberStyles.None);

            m_CommandArguments = Regex.Matches(commandLine,
                                               exp,
                                               RegexOptions.ExplicitCapture | RegexOptions.IgnoreCase |
                                               RegexOptions.IgnorePatternWhitespace);

            foreach (Match m in m_CommandArguments)
            {
                Group gVid = m.Groups["Vid"];
                Group gPid = m.Groups["Pid"];
                Group gMI = m.Groups["MI"];
                Group gPipeId = m.Groups["PipeId"];
                Group gAltId = m.Groups["AltId"];
                Group gLog = m.Groups["Log"];
                Group gIsHex = m.Groups["IsHex"];

                if (gVid.Success)
                    Vid = gIsHex.Success
                              ? UInt16.Parse(gVid.Value,
                                             NumberStyles.HexNumber)
                              : UInt16.Parse(gVid.Value);
                else if (gPid.Success)
                    Pid = gIsHex.Success
                              ? UInt16.Parse(gPid.Value,
                                             NumberStyles.HexNumber)
                              : UInt16.Parse(gPid.Value);
                else if (gMI.Success)
                    MI = gIsHex.Success
                             ? UInt16.Parse(gMI.Value,
                                            NumberStyles.HexNumber)
                             : UInt16.Parse(gMI.Value);
                else if (gPipeId.Success)
                    PipeId = gIsHex.Success
                                 ? Byte.Parse(gPipeId.Value,
                                              NumberStyles.HexNumber)
                                 : Byte.Parse(gPipeId.Value);
                else if (gAltId.Success)
                    AltInterfaceId = gIsHex.Success
                                         ? Byte.Parse(gAltId.Value,
                                                      NumberStyles.HexNumber)
                                         : Byte.Parse(gAltId.Value);
                else if (gLog.Success)
                    LogFilename = gLog.Value;
                else
                {
                    throw new Exception("Invalid argument:" + m.Value);
                }
            }
        }

        public bool FindPipeAndInterface(UsbK usb,
                                         out USB_INTERFACE_DESCRIPTOR interfaceDescriptor,
                                         out WINUSB_PIPE_INFORMATION pipeInfo)
        {
            if (FindPipeAndInterface(usb,
                                     out interfaceDescriptor,
                                     out pipeInfo,
                                     AltInterfaceId,
                                     PipeId))
            {
                AltInterfaceId = interfaceDescriptor.bAlternateSetting;
                PipeId = pipeInfo.PipeId;

                return true;
            }
            return false;
        }

        public static bool FindPipeAndInterface(UsbK usb,
                                                out USB_INTERFACE_DESCRIPTOR interfaceDescriptor,
                                                out WINUSB_PIPE_INFORMATION pipeInfo,
                                                int altInterfaceId,
                                                int pipeId)
        {
            byte interfaceIndex = 0;
            interfaceDescriptor = new USB_INTERFACE_DESCRIPTOR();
            pipeInfo = new WINUSB_PIPE_INFORMATION();
            while (usb.SelectInterface(interfaceIndex,
                                       true))
            {
                byte altSettingNumber = 0;
                while (usb.QueryInterfaceSettings(altSettingNumber,
                                                  out interfaceDescriptor))
                {
                    if (altInterfaceId == -1 || altInterfaceId == altSettingNumber)
                    {
                        byte pipeIndex = 0;
                        while (usb.QueryPipe(altSettingNumber,
                                             pipeIndex++,
                                             out pipeInfo))
                        {
                            if ((pipeInfo.MaximumPacketSize > 0) &&
                                pipeId == -1 || pipeInfo.PipeId == pipeId ||
                                ((pipeId & 0xF) == 0 && ((pipeId & 0x80) == (pipeInfo.PipeId & 0x80))))
                            {
                                goto FindInterfaceDone;
                            }
                            pipeInfo.PipeId = 0;
                        }
                    }
                    altSettingNumber++;
                }
                interfaceIndex++;
            }

            FindInterfaceDone:
            return pipeInfo.PipeId != 0;
        }

        public void Free()
        {
            if (fileLoggingEnabled && logStream != null)
            {
                logStream.Flush();
                logStream.Close();
                logStream = null;
            }
        }

        public void Init()
        {
            if (!String.IsNullOrEmpty(LogFilename))
            {
                logStream = new StreamWriter(LogFilename);
                fileLoggingEnabled = true;
            }
        }

        public void Log(String text)
        {
            if (fileLoggingEnabled) logStream.Write(text);
            else Console.Write(text);
        }

        public void Log(String format,
                        params object[] args)
        {
            if (fileLoggingEnabled)
                logStream.Write(format,
                                args);
            else
                Console.Write(format,
                              args);
        }

        public string LogFilename;

        public void LogLn(String text)
        {
            if (fileLoggingEnabled) logStream.WriteLine(text);
            else Console.WriteLine(text);
        }

        public void LogLn(String format,
                          params object[] args)
        {
            if (fileLoggingEnabled)
                logStream.WriteLine(format,
                                    args);
            else
                Console.WriteLine(format,
                                  args);
        }

        public int MI;
        public int MaxTransfersTotal;
        public int Pid;
        public int PipeId;

        public bool ShowTestReady()
        {
            while (Console.KeyAvailable)
                Console.ReadKey(true);

            Console.WriteLine("Test ready:");
            Console.Write(ToString());

            if (!String.IsNullOrEmpty(LogFilename))
                Console.WriteLine("Logging output to file: {0}",
                                  LogFilename);

            Console.WriteLine("Press 'Q' to abort or any other key to continue..");
            ConsoleKeyInfo key = Console.ReadKey(true);
            if (key.KeyChar == 'q' || key.KeyChar == 'Q') return false;

            Console.WriteLine();
            Console.WriteLine("Starting test..");
            Console.WriteLine();

            return true;
        }

        public override string ToString()
        {
            return
                String.Format(
                    "Vid: {0:X4}h\nPid: {1:X4}h\nMI: {2:X2}h\nPipeId: {3:X2}h\nMaxTransfersTotal: {4}\n\nLogFilename: {5}\n",
                    Vid,
                    Pid,
                    MI,
                    PipeId,
                    MaxTransfersTotal,
                    LogFilename);
        }

        public int Vid;
        #endregion


        #region Private Members
        private bool fileLoggingEnabled;

        private StreamWriter logStream;
        private MatchCollection m_CommandArguments;

        private string makeArgExpression(string argName,
                                         NumberStyles argType)
        {
            const string argsep = @"\W\s*";

            switch (argType)
            {
                case NumberStyles.None:
                    return String.Format(@"(({0}{1}(?<{0}>{2}))\s*)",
                                         argName,
                                         argsep,
                                         "(\".+?\"|\\S+)");
                case NumberStyles.Integer:
                case NumberStyles.HexNumber:
                    return String.Format(@"(({0}{1}(?<IsHex>0x)?(?<{0}>[0-9A-F]+))(?<IsHex>h)?\s*)",
                                         argName,
                                         argsep);
                default:
                    throw new Exception();
            }
        }
        #endregion
    }

    internal class IsoTestParameters : TestParameters
    {
        #region Public Members
        public IsoTestParameters(int vid,
                                 int pid,
                                 int altInterfaceId,
                                 int pipeId,
                                 int maxOutstandingTransfers,
                                 int maxTransfersTotal,
                                 string logFilename,
                                 int isoPacketsPerTransfer)
            : base(vid,
                   pid,
                   altInterfaceId,
                   pipeId,
                   maxTransfersTotal,
                   logFilename)
        {
            IsoPacketsPerTransfer = isoPacketsPerTransfer;
            MaxOutstandingTransfers = maxOutstandingTransfers;

            FillFromCommandLine(Environment.CommandLine);
            Init();
        }

        public int IsoPacketsPerTransfer;
        public int MaxOutstandingTransfers;

        public override string ToString()
        {
            string fmt = String.Empty;
            fmt += "IsoPacketsPerTransfer: {0}\n";
            fmt += "MaxOutstandingTransfers: {1}\n";

            object[] args = new object[]
                                {
                                    IsoPacketsPerTransfer, MaxOutstandingTransfers
                                };
            return base.ToString() + string.Format(fmt,
                                                   args);
        }
        #endregion
    }

    internal class StmTestParameters : TestParameters
    {
        #region Public Members
        public StmTestParameters(int vid,
                                 int pid,
                                 int altInterfaceId,
                                 byte pipeId,
                                 int maxTransfersTotal,
                                 string logFilename,
                                 int transferBufferSize,
                                 int maxPendingIO,
                                 int maxPendingTransfers)
            : base(vid,
                   pid,
                   altInterfaceId,
                   pipeId,
                   maxTransfersTotal,
                   logFilename)
        {
            TransferBufferSize = transferBufferSize;
            MaxPendingIO = maxPendingIO;
            MaxPendingTransfers = maxPendingTransfers;

            FillFromCommandLine(Environment.CommandLine);
            Init();
        }

        public int MaxPendingIO;
        public int MaxPendingTransfers;

        public override string ToString()
        {
            string fmt = String.Empty;
            fmt += "TransferBufferSize: {0}\n";
            fmt += "MaxPendingIO: {1}\n";
            fmt += "MaxPendingTransfers: {2}\n";

            object[] args = new object[]
                                {
                                    TransferBufferSize, MaxPendingIO, MaxPendingTransfers
                                };
            return base.ToString() + string.Format(fmt,
                                                   args);
        }

        public int TransferBufferSize;
        #endregion
    }

    internal class AsyncTestParameters : TestParameters
    {
        #region Public Members
        public AsyncTestParameters(int vid,
                                 int pid,
                                 int altInterfaceId,
                                 byte pipeId,
                                 int maxTransfersTotal,
                                 string logFilename,
                                 int transferBufferSize,
                                 int maxPendingIO)
            : base(vid,
                   pid,
                   altInterfaceId,
                   pipeId,
                   maxTransfersTotal,
                   logFilename)
        {
            TransferBufferSize = transferBufferSize;
            MaxPendingIO = maxPendingIO;

            FillFromCommandLine(Environment.CommandLine);
            Init();
        }

        public int MaxPendingIO;

        public override string ToString()
        {
            string fmt = String.Empty;
            fmt += "TransferBufferSize: {0}\n";
            fmt += "MaxPendingIO: {1}\n";

            object[] args = new object[]
                                {
                                    TransferBufferSize, MaxPendingIO
                                };
            return base.ToString() + string.Format(fmt,
                                                   args);
        }

        public int TransferBufferSize;
        #endregion
    }
}