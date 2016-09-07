// Copyright (c) 2011 Ekkehard Domning (edomning@adcocom-broadcast.com)
// Portions Copyright (c) 2012 Alberto Semenzato
// All rights reserved.
//
// Pascal libusbK Bindings
// Created on: 12.8.2011
//
// History:
//
// 2011-08-12 Initial release (Ekkehard Domning)
//
// 2012-02-10 Added Hotplug Event Notifier API, LstK_InitEx, implicit linking
//            and minor stuff (Alberto Semenzato)
//
// 2012-03-09 Added LibK_SetContext, LibK_GetContext, HotK_FreeAll,
//            KSTM_BEFORE_COMPLETE_CB, OvlK_WaitOldest,
//            LibK_SetDefaultContext, LibK_GetDefaultContext,
//            3.0.5.10 changes has been applied (Alberto Semenzato)
//
// Functions not in the original sources:
//
// GetIsoPacketFromIsoContext: helper to get a pointer to a specific packet
//
// UsbK_InitFromDevicePath: example showing a way to init a device
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// Notes:
//
// Default setting uses dynamic linking, see below and remove the compiler
// directive to change to implicit linking
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
// IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
// TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
// PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TRAVIS LEE ROBINSON
// OR EKKEHARD DOMNING OR ALBERTO SEMENZATO BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
// OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

unit libusbK;

// Import of the functions of libusbK.dll

// Conditional compiling "DynamicLink"
// defined:   the unit will load the DLL on startup and assign all functions,
//            if all functions available the variable "DllAvailable" becomes
//            true
// undefined: implicit linking, the application failes if the DLL is not
//            available

{$DEFINE DynamicLink}

interface

  uses

    Windows;

  const

    LIBUSBK_DLL = 'libusbK.dll';

  const

    // pipe policy types
    SHORT_PACKET_TERMINATE = $01;
    AUTO_CLEAR_STALL = $02;
    PIPE_TRANSFER_TIMEOUT = $03;
    IGNORE_SHORT_PACKETS = $04;
    ALLOW_PARTIAL_READS = $05;
    AUTO_FLUSH = $06;
    RAW_IO = $07;
    MAXIMUM_TRANSFER_SIZE = $08;
    RESET_PIPE_ON_RESUME = $09;

    // libusbK ISO pipe policy types
    ISO_START_LATENCY = $20;
    ISO_ALWAYS_START_ASAP = $21;
    ISO_NUM_FIXED_PACKETS = $22;

    // http://msdn.microsoft.com/en-us/library/windows/hardware/ff552359%28v=vs.85%29.aspx
    // Settings.Parallel.NumberOfPresentedRequests
    // Maximum number of transfers that can be asynchronously delivered at a
    // time. Available in version 1.9 and later versions of KMDF.
    SIMUL_PARALLEL_REQUESTS = $30;

    // Power policy types
    AUTO_SUSPEND = $81;
    SUSPEND_DELAY = $83;

    // Device Information types
    DEVICE_SPEED = $01;

    // Device Speeds
    LowSpeed = $01;
    FullSpeed = $02;
    HighSpeed = $03;

    USB_DESCRIPTOR_TYPE_DEVICE = $01;
    USB_DESCRIPTOR_TYPE_CONFIGURATION = $02;
    USB_DESCRIPTOR_TYPE_STRING = $03;
    USB_DESCRIPTOR_TYPE_INTERFACE = $04;
    USB_DESCRIPTOR_TYPE_ENDPOINT = $05;
    USB_DESCRIPTOR_TYPE_DEVICE_QUALIFIER = $06;
    USB_DESCRIPTOR_TYPE_CONFIG_POWER = $07;
    USB_DESCRIPTOR_TYPE_INTERFACE_POWER = $08;
    USB_DESCRIPTOR_TYPE_INTERFACE_ASSOCIATION = $0B;

    USB_REQUEST_GET_STATUS = $00;
    USB_REQUEST_CLEAR_FEATURE = $01;
    USB_REQUEST_SET_FEATURE = $03;
    USB_REQUEST_SET_ADDRESS = $05;
    USB_REQUEST_GET_DESCRIPTOR = $06;
    USB_REQUEST_SET_DESCRIPTOR = $07;
    USB_REQUEST_GET_CONFIGURATION = $08;
    USB_REQUEST_SET_CONFIGURATION = $09;
    USB_REQUEST_GET_INTERFACE = $0A;
    USB_REQUEST_SET_INTERFACE = $0B;
    USB_REQUEST_SYNC_FRAME = $0C;

  type

    USBD_PIPE_TYPE = (UsbdPipeTypeControl, UsbdPipeTypeIsochronous,
      UsbdPipeTypeBulk, UsbdPipeTypeInterrupt);

    PWINUSB_PIPE_INFORMATION = ^WINUSB_PIPE_INFORMATION;

    WINUSB_PIPE_INFORMATION = packed record
      PipeType: USBD_PIPE_TYPE;
      dummy0: array [0 .. 2] of Byte;
      PipeId: Byte;
      dummy1: Byte;
      MaximumPacketSize: Word;
      Interval: Byte;
      dummy2: array [0 .. 2] of Byte;
    end;

    WINUSB_SETUP_PACKET_INT64 = Int64;

    PWINUSB_SETUP_PACKET = ^WINUSB_SETUP_PACKET;

    WINUSB_SETUP_PACKET = packed record
      case Integer of
        0:
        (AsInt64: WINUSB_SETUP_PACKET_INT64);
        1:
        (RequestType: Byte;
          Request: Byte;
          Value: Word;
          Index: Word;
          Length: Word
        );
    end;

    // Structure describing an isochronous transfer packet.
    PKISO_PACKET = ^KISO_PACKET;

    KISO_PACKET = packed record
      Offset: Cardinal;
      Length: SmallInt;
      Status: Word;
    end;

    PKISO_PACKET_ARRAY = ^KISO_PACKET_ARRAY;

    KISO_PACKET_ARRAY = array [0 .. (MaxInt div SizeOf(KISO_PACKET)) - 1]
      of KISO_PACKET;

  const

    KISO_FLAG_NONE = 0;
    KISO_FLAG_SET_START_FRAME = $00000001;

  type

    KISO_FLAG = Cardinal;

    // Structure describing a user defined isochronous transfer.
    PKISO_CONTEXT = ^KISO_CONTEXT;

    KISO_CONTEXT = packed record
      Flags: Cardinal;
      StartFrame: Cardinal;
      ErrorCount: SmallInt;
      NumberOfPackets: SmallInt;
      UrbHdrStatus: Cardinal;
      // Contains a variable-length array of KISO_PACKET structures that
      // describe the isochronous transfer packets to be transferred on the
      // USB bus.
      // note This field is assigned by the user application, used by the driver
      // upon transfer submission, and updated by the driver upon transfer
      // completion.
      // Translation to Delphi is difficult, since you can not declare array
      // with the length of zero, so you must use a Type cast to access the
      // (optional) array members PKISO_PACKET_ARRAY(@x.IsoPackets)^[n]
      // I made the function GetIsoPacketFromIsoContext that returns a pointer
      // to a specific packet.
      IsoPackets: record end;
    end;

    KLIB_USER_CONTEXT = pointer;

    // pointer to a \c KISO_CONTEXT structure
    KLIB_HANDLE = pointer;

    // Opaque UsbK handle, see \ref UsbK_Init.
    KUSB_HANDLE = KLIB_HANDLE;

    // Opaque LstK handle, see \ref LstK_Init.
    KLST_HANDLE = KLIB_HANDLE;

    // Opaque HotK handle, see \ref HotK_Init.
    KHOT_HANDLE = KLIB_HANDLE;

    // Opaque OvlK handle, see \ref OvlK_Acquire.
    KOVL_HANDLE = KLIB_HANDLE;

    // Opaque OvlPoolK handle, see \ref OvlK_Init.
    KOVL_POOL_HANDLE = KLIB_HANDLE;

    // Opaque StmK handle, see \ref StmK_Init.
    KSTM_HANDLE = KLIB_HANDLE;

    // Handle type enumeration.
    KLIB_HANDLE_TYPE = (KLIB_HANDLE_TYPE_HOTK, KLIB_HANDLE_TYPE_USBK,
      KLIB_HANDLE_TYPE_USBSHAREDK, KLIB_HANDLE_TYPE_LSTK,
      KLIB_HANDLE_TYPE_LSTINFOK, KLIB_HANDLE_TYPE_OVLK,
      KLIB_HANDLE_TYPE_OVLPOOLK, KLIB_HANDLE_TYPE_STMK, KLIB_HANDLE_TYPE_COUNT);

    PKLIB_VERSION = ^KLIB_VERSION;

    KLIB_VERSION = record
      Major: Integer;
      Minor: Integer;
      Micro: Integer;
      Nano: Integer;
    end;

    // Callback function typedef for \ref IsoK_EnumPackets
    KISO_ENUM_PACKETS_CB = function(const PacketIndex: Cardinal;
      const IsoPacket: PKISO_PACKET; const UserState: pointer): Bool; stdcall;

  const

    KLST_STRING_MAX_LEN = 256;

    KLST_SYNC_FLAG_NONE = $0000;
    KLST_SYNC_FLAG_UNCHANGED = $0001;
    KLST_SYNC_FLAG_ADDED = $0002;
    KLST_SYNC_FLAG_REMOVED = $0004;
    KLST_SYNC_FLAG_CONNECT_CHANGE = $0008;
    KLST_SYNC_FLAG_MASK = $000F;

  type

    KLST_SYNC_FLAG = Cardinal;

    // Common usb device information structure
    PKLST_DEV_COMMON_INFO = ^KLST_DEV_COMMON_INFO;

    KLST_DEV_COMMON_INFO = packed record
      Vid: Integer;
      Pid: Integer;
      MI: Integer;
      InstanceID: array [0 .. KLST_STRING_MAX_LEN - 1] of AnsiChar;
    end;

    KLST_DEVINFO_HANDLE = ^KLST_DEVINFO;

    KLST_DEVINFO = packed record
      Common: KLST_DEV_COMMON_INFO;
      DriverID: Integer;
      DeviceInterfaceGUID: array [0 .. KLST_STRING_MAX_LEN - 1] of AnsiChar;
      InstanceID: array [0 .. KLST_STRING_MAX_LEN - 1] of AnsiChar;
      ClassGUID: array [0 .. KLST_STRING_MAX_LEN - 1] of AnsiChar;
      Mfg: array [0 .. KLST_STRING_MAX_LEN - 1] of AnsiChar;
      DeviceDesc: array [0 .. KLST_STRING_MAX_LEN - 1] of AnsiChar;
      Service: array [0 .. KLST_STRING_MAX_LEN - 1] of AnsiChar;
      SymbolicLink: array [0 .. KLST_STRING_MAX_LEN - 1] of AnsiChar;
      DevicePath: array [0 .. KLST_STRING_MAX_LEN - 1] of AnsiChar;
      LUsb0FilterIndex: Integer;
      Connected: Bool;
      SyncFlags: KLST_SYNC_FLAG;
    end;

  const

    KLST_FLAG_NONE = $0000;
    KLST_FLAG_INCLUDE_RAWGUID = $0001;
    KLST_FLAG_INCLUDE_DISCONNECT = $0002;

  type

    KLST_FLAG = Cardinal;

    KLST_ENUM_DEVINFO_CB = function(const DeviceList: KLST_HANDLE;
      const DeviceInfo: KLST_DEVINFO_HANDLE; const Contex: pointer)
      : Bool; stdcall;

    PUSB_INTERFACE_DESCRIPTOR = ^USB_INTERFACE_DESCRIPTOR;

    USB_INTERFACE_DESCRIPTOR = packed record
      bLength: Byte;
      bDescriptorType: Byte;
      bInterfaceNumber: Byte;
      bAlternateSetting: Byte;
      bNumEndpoints: Byte;
      bInterfaceClass: Byte;
      bInterfaceSubClass: Byte;
      bInterfaceProtocol: Byte;
      iInterface: Byte;
    end;

    PUSB_DEVICE_DESCRIPTOR = ^USB_DEVICE_DESCRIPTOR;

    USB_DEVICE_DESCRIPTOR = packed record
      bLength: Byte;
      bDescriptorType: Byte;
      bcdUSB: Word;
      bDeviceClass: Byte;
      bDeviceSubClass: Byte;
      bDeviceProtocol: Byte;
      bMaxPacketSize0: Byte;
      idVendor: Word;
      idProduct: Word;
      bcdDevice: Word;
      iManufacturer: Byte;
      iProduct: Byte;
      iSerialNumber: Byte;
      bNumConfigurations: Byte;
    end;

    PUSB_ENDPOINT_DESCRIPTOR = ^USB_ENDPOINT_DESCRIPTOR;

    USB_ENDPOINT_DESCRIPTOR = packed record
      bLength: Byte;
      bDescriptorType: Byte;
      bEndpointAddress: Byte;
      bmAttributes: Byte;
      wMaxPacketSize: SmallInt;
      bInterval: Byte;
    end;

    KUSB_PROPERTY = (KUSB_PROPERTY_DEVICE_FILE_HANDLE, KUSB_PROPERTY_COUNT);

  const

    KHOT_FLAG_NONE: UINT = 0;
    KHOT_FLAG_PLUG_ALL_ON_INIT: UINT = $0001;
    KHOT_FLAG_PASS_DUPE_INSTANCE: UINT = $0002;
    KHOT_FLAG_POST_USER_MESSAGE: UINT = $0004;

  type

    KLST_PATTERN_MATCH = packed record
      InstanceID: array [0 .. KLST_STRING_MAX_LEN - 1] of AnsiChar;
      DeviceInterfaceGUID: array [0 .. KLST_STRING_MAX_LEN - 1] of AnsiChar;
      SymbolicLink: array [0 .. KLST_STRING_MAX_LEN - 1] of AnsiChar;
      z_F_i_x_e_d: array [0 .. (1024 - (KLST_STRING_MAX_LEN * 3)) - 1] of Byte;
    end;

    PKLST_PATTERN_MATCH = ^KLST_PATTERN_MATCH;

    KHOT_PLUG_CB = procedure(HotHandle: KHOT_HANDLE;
      DeviceInfo: KLST_DEVINFO_HANDLE; PlugType: KLST_SYNC_FLAG); stdcall;

    KHOT_PARAMS = packed record
      UserHwnd: HWND;
      UserMessage: UINT;
      Flags: UINT;
      PatternMatch: KLST_PATTERN_MATCH;
      OnHotPlug: KHOT_PLUG_CB;
      z_F_i_x_e_d: array [0 .. (2048 - SizeOf(KLST_PATTERN_MATCH) -
        SizeOf(PUINT) * 2 - (SizeOf(UINT) * 2)) - 1] of Byte;
    end;

    PKHOT_PARAMS = ^KHOT_PARAMS;

  const

    USBD_ISO_START_FRAME_RANGE = 1024;

  type

    KUSB_DRIVER_API_INFO = packed record
      DriverID: Integer;
      FunctionCount: Integer;
    end;

    //  Supported function id enumeration.
    KUSB_FNID = (KUSB_FNID_Init, KUSB_FNID_Free, KUSB_FNID_ClaimInterface,
      KUSB_FNID_ReleaseInterface, KUSB_FNID_SetAltInterface,
      KUSB_FNID_GetAltInterface, KUSB_FNID_GetDescriptor,
      KUSB_FNID_ControlTransfer, KUSB_FNID_SetPowerPolicy,
      KUSB_FNID_GetPowerPolicy, KUSB_FNID_SetConfiguration,
      KUSB_FNID_GetConfiguration, KUSB_FNID_ResetDevice, KUSB_FNID_Initialize,
      KUSB_FNID_SelectInterface, KUSB_FNID_GetAssociatedInterface,
      KUSB_FNID_Clone, KUSB_FNID_QueryInterfaceSettings,
      KUSB_FNID_QueryDeviceInformation, KUSB_FNID_SetCurrentAlternateSetting,
      KUSB_FNID_GetCurrentAlternateSetting, KUSB_FNID_QueryPipe,
      KUSB_FNID_SetPipePolicy, KUSB_FNID_GetPipePolicy, KUSB_FNID_ReadPipe,
      KUSB_FNID_WritePipe, KUSB_FNID_ResetPipe, KUSB_FNID_AbortPipe,
      KUSB_FNID_FlushPipe, KUSB_FNID_IsoReadPipe, KUSB_FNID_IsoWritePipe,
      KUSB_FNID_GetCurrentFrameNumber, KUSB_FNID_GetOverlappedResult,
      KUSB_FNID_GetProperty,
      // Supported function count
      KUSB_FNID_COUNT);

    KUSB_Init = function(var InterfaceHandle: KUSB_HANDLE;
      const DevInfo: KLST_DEVINFO_HANDLE): Bool; stdcall;

    KUSB_Free = function(const InterfaceHandle: KUSB_HANDLE): Bool; stdcall;

    KUSB_ClaimInterface = function(const InterfaceHandle: KUSB_HANDLE;
      const NumberOrIndex: Byte; const IsIndex: Bool): Bool; stdcall;

    KUSB_ReleaseInterface = function(const InterfaceHandle: KUSB_HANDLE;
      const NumberOrIndex: Byte; const IsIndex: Bool): Bool; stdcall;

    KUSB_SetAltInterface = function(const InterfaceHandle: KUSB_HANDLE;
      const NumberOrIndex: Byte; const IsIndex: Bool;
      const AltSettingNumber: Byte): Bool; stdcall;

    KUSB_GetAltInterface = function(const InterfaceHandle: KUSB_HANDLE;
      const NumberOrIndex: Byte; const IsIndex: Bool;
      var AltSettingNumber: Byte): Bool; stdcall;

    KUSB_GetDescriptor = function(const InterfaceHandle: KUSB_HANDLE;
      const DescriptorType: Byte; const Index: Byte; const LanguageID: Word;
      var Buffer; const BufferLength: Cardinal; var LengthTransferred: Cardinal)
      : Bool; stdcall;

    KUSB_ControlTransfer = function(const InterfaceHandle: KUSB_HANDLE;
      const SetupPacket: WINUSB_SETUP_PACKET_INT64; const PBuffer: PByte;
      //optional may be Nil
      const BufferLength: Cardinal; const LengthTransferred: PCardinal;
      //Optional may be Nil
      const Overlapped: POverlapped //Optional
      ): Bool; stdcall;

    KUSB_SetPowerPolicy = function(const InterfaceHandle: KUSB_HANDLE;
      const PolicyType: Cardinal; const ValueLength: Cardinal; const Value)
      : Bool; stdcall;

    KUSB_GetPowerPolicy = function(const InterfaceHandle: KUSB_HANDLE;
      const PolicyType: Cardinal; var ValueLength: Cardinal;
      //Input: Size of Value, output : copied bytes
      var Value): Bool; stdcall;

    KUSB_SetConfiguration = function(const InterfaceHandle: KUSB_HANDLE;
      const ConfigurationNumber: Byte): Bool; stdcall;

    KUSB_GetConfiguration = function(const InterfaceHandle: KUSB_HANDLE;
      var ConfigurationNumber: Byte): Bool; stdcall;

    KUSB_ResetDevice = function(const InterfaceHandle: KUSB_HANDLE)
      : Bool; stdcall;

    KUSB_Initialize = function(const DeviceHandle: KUSB_HANDLE;
      var InterfaceHandle: KUSB_HANDLE): Bool; stdcall;

    KUSB_SelectInterface = function(const InterfaceHandle: KUSB_HANDLE;
      const NumberOrIndex: Byte; const IsIndex: Bool): Bool; stdcall;

    KUSB_GetAssociatedInterface = function(const InterfaceHandle: KUSB_HANDLE;
      const AssociatedInterfaceIndex: Byte;
      var AssociatedInterfaceHandle: KUSB_HANDLE): Bool; stdcall;

    KUSB_Clone = function(const InterfaceHandle: KUSB_HANDLE;
      var DstInterfaceHandle: KUSB_HANDLE): Bool; stdcall;

    KUSB_QueryInterfaceSettings = function(const InterfaceHandle: KUSB_HANDLE;
      const AltSettingNumber: Byte;
      var UsbAltInterfaceDescriptor: USB_INTERFACE_DESCRIPTOR): Bool; stdcall;

    KUSB_QueryDeviceInformation = function(const InterfaceHandle: KUSB_HANDLE;
      const InformationType: Cardinal; var BufferLength: Cardinal;
      // Input: Length of Buffer, copied Bytes in Buffer
      var Buffer): Bool; stdcall;

    KUSB_SetCurrentAlternateSetting = function(const InterfaceHandle
      : KUSB_HANDLE; const AltSettingNumber: Byte): Bool; stdcall;

    KUSB_GetCurrentAlternateSetting = function(const InterfaceHandle
      : KUSB_HANDLE; var AltSettingNumber: Byte): Bool; stdcall;

    KUSB_QueryPipe = function(const InterfaceHandle: KUSB_HANDLE;
      const AltSettingNumber: Byte; const PipeIndex: Byte;
      var PipeInformation: WINUSB_PIPE_INFORMATION): Bool; stdcall;

    KUSB_SetPipePolicy = function(const InterfaceHandle: KUSB_HANDLE;
      const PipeId: Byte; const PolicyType: Cardinal;
      const ValueLength: Cardinal; const Value): Bool; stdcall;

    KUSB_GetPipePolicy = function(const InterfaceHandle: KUSB_HANDLE;
      const PipeId: Byte; const PolicyType: Cardinal; var ValueLength: Cardinal;
      // Input: Length of Value, copied Bytes in Value
      var Value): Bool; stdcall;

    KUSB_ReadPipe = function(const InterfaceHandle: KUSB_HANDLE;
      const PipeId: Byte; var Buffer; const BufferLength: Cardinal;
      const LengthTransferred: PCardinal; // optional may be Nil
      const Overlapped: POverlapped //Optional
      ): Bool; stdcall;

    KUSB_WritePipe = function(const InterfaceHandle: KUSB_HANDLE;
      const PipeId: Byte; const Buffer; const BufferLength: Cardinal;
      const LengthTransferred: PCardinal; // optional may be Nil
      const Overlapped: POverlapped //Optional
      ): Bool; stdcall;

    KUSB_ResetPipe = function(const InterfaceHandle: KUSB_HANDLE;
      const PipeId: Byte): Bool; stdcall;

    KUSB_AbortPipe = function(const InterfaceHandle: KUSB_HANDLE;
      const PipeId: Byte): Bool; stdcall;

    KUSB_FlushPipe = function(const InterfaceHandle: KUSB_HANDLE;
      const PipeId: Byte): Bool; stdcall;

    KUSB_IsoReadPipe = function(const InterfaceHandle: KUSB_HANDLE;
      const PipeId: Byte; var Buffer; const BufferLength: Cardinal;
      const Overlapped: POverlapped; //Optional
      const IsoContext: PKISO_CONTEXT // optional
      ): Bool; stdcall;

    KUSB_IsoWritePipe = function(const InterfaceHandle: KUSB_HANDLE;
      const PipeId: Byte; const Buffer; const BufferLength: Cardinal;
      const Overlapped: POverlapped; //Optional
      const IsoContext: PKISO_CONTEXT // optional
      ): Bool; stdcall;

    KUSB_GetCurrentFrameNumber = function(const InterfaceHandle: KUSB_HANDLE;
      var FrameNumber: Cardinal): Bool; stdcall;

    KUSB_GetOverlappedResult = function(const InterfaceHandle: KUSB_HANDLE;
      const lpOverlapped: POverlapped; //Optional
      var lpNumberOfBytesTransferred: Cardinal; const bWait: Bool)
      : Bool; stdcall;

    KUSB_GetProperty = function(const InterfaceHandle: KUSB_HANDLE;
      const PropertyType: KUSB_PROPERTY; var PropertySize: Cardinal;
      // Input: Length of Property Buffer, copied Bytes in Property Buffer
      var TheProperty
      // Parameter name changed, since "property" is a reserved word in Delphi
      ): Bool; stdcall;

    // Driver API function set structure.
    PKUSB_DRIVER_API = ^KUSB_DRIVER_API;

    KUSB_DRIVER_API = packed record
      Info: KUSB_DRIVER_API_INFO;
      Init: KUSB_Init;
      Free: KUSB_Free;
      ClaimInterface: KUSB_ClaimInterface;
      ReleaseInterface: KUSB_ReleaseInterface;
      SetAltInterface: KUSB_SetAltInterface;
      GetAltInterface: KUSB_GetAltInterface;
      GetDescriptor: KUSB_GetDescriptor;
      ControlTransfer: KUSB_ControlTransfer;
      SetPowerPolicy: KUSB_SetPowerPolicy;
      GetPowerPolicy: KUSB_GetPowerPolicy;
      SetConfiguration: KUSB_SetConfiguration;
      GetConfiguration: KUSB_GetConfiguration;
      ResetDevice: KUSB_ResetDevice;
      Initialize: KUSB_Initialize;
      SelectInterface: KUSB_SelectInterface;
      GetAssociatedInterface: KUSB_GetAssociatedInterface;
      Clone: KUSB_Clone;
      QueryInterfaceSettings: KUSB_QueryInterfaceSettings;
      QueryDeviceInformation: KUSB_QueryDeviceInformation;
      SetCurrentAlternateSetting: KUSB_SetCurrentAlternateSetting;
      GetCurrentAlternateSetting: KUSB_GetCurrentAlternateSetting;
      QueryPipe: KUSB_QueryPipe;
      SetPipePolicy: KUSB_SetPipePolicy;
      GetPipePolicy: KUSB_GetPipePolicy;
      ReadPipe: KUSB_ReadPipe;
      WritePipe: KUSB_WritePipe;
      ResetPipe: KUSB_ResetPipe;
      AbortPipe: KUSB_AbortPipe;
      FlushPipe: KUSB_FlushPipe;
      IsoReadPipe: KUSB_IsoReadPipe;
      IsoWritePipe: KUSB_IsoWritePipe;
      GetCurrentFrameNumber: KUSB_GetCurrentFrameNumber;
      GetOverlappedResult: KUSB_GetOverlappedResult;
      GetProperty: KUSB_GetProperty;
      // fixed structure padding.
      z_F_i_x_e_d: array [0 .. 512 - SizeOf(KUSB_DRIVER_API_INFO) -
        (SizeOf(pointer) * Ord(KUSB_FNID_COUNT)) - 1] of Byte;
    end;

    // StmK

  type

    KSTM_FLAG = Cardinal;

    KSTM_COMPLETE_RESULT = Cardinal;

  const

    KSTM_FLAG_NONE = 0;
    KSTM_FLAG_USE_TIMEOUT = $80000000;
    KSTM_FLAG_NO_PARTIAL_XFERS = $00100000;
    KSTM_FLAG_TIMEOUT_MASK = $0001FFFF;

    KSTM_COMPLETE_RESULT_VALID = 0;
    KSTM_COMPLETE_RESULT_INVALID = 1;

  type

    PKSTM_XFER_CONTEXT = ^KSTM_XFER_CONTEXT;

    KSTM_XFER_CONTEXT = packed record
      Buffer: PByte;
      BufferSize: Integer;
      TransferLength: Integer;
      UserState: pointer;
    end;

    PKSTM_INFO = ^KSTM_INFO;

    KSTM_INFO = packed record
      UsbHandle: KUSB_HANDLE;
      PipeId: Byte;
      MaxPendingTransfers: Integer;
      MaxTransferSize: Integer;
      MaxPendingIO: Integer;
      EndpointDescriptor: USB_ENDPOINT_DESCRIPTOR;
      DriverAPI: KUSB_DRIVER_API;
      DeviceHandle: THandle;
      StreamHandle: KSTM_HANDLE;
      UserState: pointer;
    end;

    PInteger = ^Integer;

    KSTM_ERROR_CB = function(const StreamInfo: PKSTM_INFO;
      const XferContext: PKSTM_XFER_CONTEXT; const XferContextIndex: Integer;
      const ErrorCode: Integer): Integer; stdcall;
    KSTM_SUBMIT_CB = function(const StreamInfo: PKSTM_INFO;
      const XferContext: PKSTM_XFER_CONTEXT; const XferContextIndex: Integer;
      Overlapped: POverlapped): Integer; stdcall;
    KSTM_STARTED_CB = function(const StreamInfo: PKSTM_INFO;
      const XferContext: PKSTM_XFER_CONTEXT; const XferContextIndex: Integer)
      : Integer; stdcall;
    KSTM_STOPPED_CB = function(const StreamInfo: PKSTM_INFO;
      const XferContext: PKSTM_XFER_CONTEXT; const XferContextIndex: Integer)
      : Integer; stdcall;
    KSTM_COMPLETE_CB = function(const StreamInfo: PKSTM_INFO;
      const XferContext: PKSTM_XFER_CONTEXT; const XferContextIndex: Integer;
      const ErrorCode: Integer): Integer; stdcall;
    KSTM_BEFORE_COMPLETE_CB = function(const StreamInfo: PKSTM_INFO;
      const XferContext: PKSTM_XFER_CONTEXT; const XferContextIndex: Integer;
      const ErrorCode: PInteger): KSTM_COMPLETE_RESULT; stdcall;

    PKSTM_CALLBACK = ^KSTM_CALLBACK;

    KSTM_CALLBACK = packed record
      Error: KSTM_ERROR_CB;
      Submit: KSTM_SUBMIT_CB;
      Complete: KSTM_COMPLETE_CB;
      Started: KSTM_STARTED_CB;
      Stopped: KSTM_STOPPED_CB;
      BeforeComplete: KSTM_BEFORE_COMPLETE_CB;
      z_F_i_x_e_d: array [0 .. (64 - SizeOf(pointer) * 6) - 1] of Byte;
    end;

    KOVL_POOL_FLAG = (KOVL_POOL_FLAG_NONE);
    KOVL_WAIT_FLAG = Cardinal;

  const

    KOVL_WAIT_FLAG_NONE = 0;
    KOVL_WAIT_FLAG_RELEASE_ON_SUCCESS = $0001;
    KOVL_WAIT_FLAG_RELEASE_ON_FAIL = $0002;
    KOVL_WAIT_FLAG_RELEASE_ON_SUCCESS_FAIL = $0003;
    KOVL_WAIT_FLAG_CANCEL_ON_TIMEOUT = $0004;
    KOVL_WAIT_FLAG_RELEASE_ON_TIMEOUT = $000C;
    KOVL_WAIT_FLAG_RELEASE_ALWAYS = $000F;
    KOVL_WAIT_FLAG_ALERTABLE = $0010;

  var

    DllAvailable: Boolean;

    {$IFDEF DynamicLink}

  var

    HLIBUSBKDll: THandle;

    HotK_Init: function(var Handle: KHOT_HANDLE; const InitParams: PKHOT_PARAMS)
      : Bool; stdcall;
    HotK_Free: function(const Handle: KHOT_HANDLE): Bool; stdcall;
    HotK_FreeAll: procedure; stdcall;
    IsoK_EnumPackets: function(const IsoContext: PKISO_CONTEXT;
      const EnumPackets: KISO_ENUM_PACKETS_CB; const StartPacketIndex: Integer;
      const UserState): Bool; stdcall;
    IsoK_Free: function(const IsoContext: PKISO_CONTEXT): Bool; stdcall;
    IsoK_GetPacket: function(const IsoContext: PKISO_CONTEXT;
      const PacketIndex: Integer; const IsoPacket: PKISO_PACKET): Bool; stdcall;
    IsoK_Init: function(var IsoContext: PKISO_CONTEXT;
      const NumberOfPackets: Integer; const StartFrame: Integer): Bool; stdcall;
    IsoK_ReUse: function(const IsoContext: PKISO_CONTEXT): Bool; stdcall;
    IsoK_SetPacket: function(const IsoContext: PKISO_CONTEXT;
      const PacketIndex: Integer; const IsoPacket: PKISO_PACKET): Bool; stdcall;
    IsoK_SetPackets: function(const IsoContext: PKISO_CONTEXT;
      const PacketSize: Integer): Bool; stdcall;
    LibK_CopyDriverAPI: function: Bool; stdcall;
    LibK_GetContext: function(const Handle: KLIB_HANDLE;
      const HandleType: KLIB_HANDLE_TYPE): KLIB_USER_CONTEXT; stdcall;
    LibK_GetProcAddress: function: Bool; stdcall;
    LibK_GetVersion: function: Bool; stdcall;
    LibK_LoadDriverAPI: function(var DriverAPI: KUSB_DRIVER_API;
      const DriverID: Integer): Bool; stdcall;
    LibK_SetCleanupCallback: function: Bool; stdcall;
    LibK_SetContext: function(const Handle: KLIB_HANDLE;
      const HandleType: KLIB_HANDLE_TYPE; const ContextValue: KLIB_USER_CONTEXT)
      : Bool; stdcall;
    LibK_SetDefaultContext: function(const HandleType: KLIB_HANDLE_TYPE;
      const UserContext: KLIB_USER_CONTEXT): Bool; stdcall;
    LibK_GetDefaultContext: function(const HandleType: KLIB_HANDLE_TYPE)
      : KLIB_USER_CONTEXT; stdcall;
    LstK_AttachInfo: function: Bool; stdcall;
    LstK_Clone: function(const InterfaceHandle: KUSB_HANDLE;
      var DstInterfaceHandle: KUSB_HANDLE): Bool; stdcall;
    LstK_CloneInfo: function: Bool; stdcall;
    LstK_Count: function(const DeviceList: KLST_HANDLE; var Count: Cardinal)
      : Bool; stdcall;
    LstK_Current: function: Bool; stdcall;
    LstK_DetachInfo: function: Bool; stdcall;
    LstK_Enumerate: function: Bool; stdcall;
    LstK_FindByVidPid: function(const DeviceList: KLST_HANDLE;
      const Vid: Integer; const Pid: Integer;
      var DeviceInfo: KLST_DEVINFO_HANDLE): Bool; stdcall;
    LstK_Free: function(const DeviceList: KLST_HANDLE): Bool; stdcall;
    LstK_FreeInfo: function: Bool; stdcall;
    LstK_Init: function(var DeviceList: KLST_HANDLE; const Flags: KLST_FLAG)
      : Bool; stdcall;
    LstK_InitEx: function(var DeviceList: KLST_HANDLE; const Flags: KLST_FLAG;
      const PatternMatch: PKLST_PATTERN_MATCH): Bool; stdcall;
    LstK_MoveNext: function(const DeviceList: KLST_HANDLE;
      var DevInfo: KLST_DEVINFO_HANDLE): Bool; stdcall;
    LstK_MoveReset: function(const DeviceList: KLST_HANDLE): Bool; stdcall;
    LstK_Sync: function: Bool; stdcall;
    OvlK_Acquire: function(var OverlappedK: KOVL_HANDLE;
      const PoolHandle: KOVL_POOL_HANDLE): Bool; stdcall;
    OvlK_Free: function(const PoolHandle: KOVL_POOL_HANDLE): Bool; stdcall;
    OvlK_GetEventHandle: function: Bool; stdcall;
    OvlK_Init: function(var PoolHandle: KOVL_POOL_HANDLE;
      const UsbHandle: KUSB_HANDLE; const MaxOverlappedCount: Integer;
      const Flags: KOVL_POOL_FLAG): Bool; stdcall;
    OvlK_IsComplete: function: Bool; stdcall;
    OvlK_ReUse: function(const OverlappedK: KOVL_HANDLE): Bool; stdcall;
    OvlK_Release: function(const OverlappedK: KOVL_HANDLE): Bool; stdcall;
    OvlK_Wait: function(const OverlappedK: KOVL_HANDLE;
      const TimeoutMS: Integer; const WaitFlags: KOVL_WAIT_FLAG;
      var TransferredLength: Cardinal): Bool; stdcall;
    OvlK_WaitOldest: function(const PoolHandle: KOVL_POOL_HANDLE;
      var OverlappedK: KOVL_HANDLE; const TimeoutMS: Integer;
      const WaitFlags: KOVL_WAIT_FLAG; var TransferredLength: Cardinal)
      : Bool; stdcall;
    OvlK_WaitAndRelease: function(const OverlappedK: KOVL_HANDLE;
      const TimeoutMS: Integer; var TransferredLength: Cardinal): Bool; stdcall;
    OvlK_WaitOrCancel: function(const OverlappedK: KOVL_HANDLE;
      const TimeoutMS: Integer; var TransferredLength: Cardinal): Bool; stdcall;
    StmK_Free: function(const StreamHandle: KSTM_HANDLE): Bool; stdcall;
    StmK_Init: function(var StreamHandle: KSTM_HANDLE;
      const UsbHandle: KUSB_HANDLE; const PipeId: Byte;
      const MaxTransferSize: Integer; const MaxPendingTransfers: Integer;
      const MaxPendingIO: Integer; const Callbacks: PKSTM_CALLBACK;
      const Flags: KSTM_FLAG): Bool; stdcall;
    StmK_Read: function(const StreamHandle: KSTM_HANDLE; var Buffer;
      const Offset: Integer; const Length: Integer;
      var TransferredLength: Cardinal): Bool; stdcall;
    StmK_Start: function(const StreamHandle: KSTM_HANDLE): Bool; stdcall;
    StmK_Stop: function(const StreamHandle: KSTM_HANDLE;
      const TimeoutCancelMS: Integer): Bool; stdcall;
    StmK_Write: function(const StreamHandle: KSTM_HANDLE; const Buffer;
      const Offset: Integer; const Length: Integer;
      var TransferredLength: Cardinal): Bool; stdcall;
    UsbK_AbortPipe: function(const InterfaceHandle: KUSB_HANDLE;
      const PipeId: Byte): Bool; stdcall;
    UsbK_ClaimInterface: function(const InterfaceHandle: KUSB_HANDLE;
      const NumberOrIndex: Byte; const IsIndex: Bool): Bool; stdcall;
    UsbK_Clone: function(const InterfaceHandle: KUSB_HANDLE;
      var DstInterfaceHandle: KUSB_HANDLE): Bool; stdcall;
    UsbK_ControlTransfer: function(const InterfaceHandle: KUSB_HANDLE;
      const SetupPacket: WINUSB_SETUP_PACKET_INT64; var Buffer;
      const BufferLength: Cardinal; const LengthTransferred: PCardinal;
      //Optional may be Nil
      const Overlapped: POverlapped): Bool; stdcall;
    UsbK_FlushPipe: function: Bool; stdcall;
    UsbK_Free: function(const InterfaceHandle: KUSB_HANDLE): Bool; stdcall;
    UsbK_GetAltInterface: function(const InterfaceHandle: KUSB_HANDLE;
      const NumberOrIndex: Byte; const IsIndex: Bool;
      var AltSettingNumber: Byte): Bool; stdcall;
    UsbK_GetAssociatedInterface: function: Bool; stdcall;
    UsbK_GetConfiguration: function: Bool; stdcall;
    UsbK_GetCurrentAlternateSetting: function: Bool; stdcall;
    UsbK_GetCurrentFrameNumber: function(const InterfaceHandle: KUSB_HANDLE;
      var FrameNumber: Cardinal): Bool; stdcall;
    UsbK_GetDescriptor: function(const InterfaceHandle: KUSB_HANDLE;
      const DescriptorType: Byte; const Index: Byte; const LanguageID: Word;
      var Buffer; const BufferLength: Cardinal; var LengthTransferred: Cardinal)
      : Bool; stdcall;
    UsbK_GetOverlappedResult: function: Bool; stdcall;
    UsbK_GetPipePolicy: function: Bool; stdcall;
    UsbK_GetPowerPolicy: function: Bool; stdcall;
    UsbK_GetProperty: function: Bool; stdcall;
    UsbK_Init: function(var InterfaceHandle: KUSB_HANDLE;
      const DevInfo: KLST_DEVINFO_HANDLE): Bool; stdcall;
    UsbK_Initialize: function: Bool; stdcall;
    UsbK_IsoReadPipe: function(const InterfaceHandle: KUSB_HANDLE;
      const PipeId: Byte; var Buffer; const BufferLength: Cardinal;
      const Overlapped: POverlapped; const IsoContext: PKISO_CONTEXT)
      : Bool; stdcall;
    UsbK_IsoWritePipe: function: Bool; stdcall;
    UsbK_QueryDeviceInformation: function: Bool; stdcall;
    UsbK_QueryInterfaceSettings: function(const InterfaceHandle: KUSB_HANDLE;
      const AltSettingNumber: Byte;
      var UsbAltInterfaceDescriptor: USB_INTERFACE_DESCRIPTOR): Bool; stdcall;
    UsbK_QueryPipe: function(const InterfaceHandle: KUSB_HANDLE;
      const AltSettingNumber: Byte; const PipeIndex: Byte;
      var PipeInformation: WINUSB_PIPE_INFORMATION): Bool; stdcall;
    UsbK_ReadPipe: function(const InterfaceHandle: KUSB_HANDLE;
      const PipeId: Byte; var Buffer; const BufferLength: Cardinal;
      const LengthTransferred: PCardinal; //Optional may be Nil
      const Overlapped: POverlapped): Bool; stdcall;
    UsbK_ReleaseInterface: function(const InterfaceHandle: KUSB_HANDLE;
      const NumberOrIndex: Byte; const IsIndex: Bool): Bool; stdcall;
    UsbK_ResetDevice: function: Bool; stdcall;
    UsbK_ResetPipe: function(const InterfaceHandle: KUSB_HANDLE;
      const PipeId: Byte): Bool; stdcall;
    UsbK_SelectInterface: function(const InterfaceHandle: KUSB_HANDLE;
      const NumberOrIndex: Byte; const IsIndex: Bool): Bool; stdcall;
    UsbK_SetAltInterface: function(const InterfaceHandle: KUSB_HANDLE;
      const NumberOrIndex: Byte; const IsIndex: Bool;
      const AltSettingNumber: Byte): Bool; stdcall;
    UsbK_SetConfiguration: function(const InterfaceHandle: KUSB_HANDLE;
      const ConfigurationNumber: Byte): Bool; stdcall;
    UsbK_SetCurrentAlternateSetting
      : function(const InterfaceHandle: KUSB_HANDLE;
      const AltSettingNumber: Byte): Bool; stdcall;
    UsbK_SetPipePolicy: function(const InterfaceHandle: KUSB_HANDLE;
      const PipeId: Byte; const PolicyType: Cardinal;
      const ValueLength: Cardinal; const Value): Bool; stdcall;
    UsbK_SetPowerPolicy: function: Bool; stdcall;
	
    UsbK_WritePipe: function(const InterfaceHandle: KUSB_HANDLE;
      const PipeId: Byte; var Buffer; const BufferLength: Cardinal;
      const LengthTransferred: PCardinal;
      const Overlapped: POverlapped): Bool; stdcall;

    WinUsb_AbortPipe: function: Bool; stdcall;
    WinUsb_ControlTransfer: function: Bool; stdcall;
    WinUsb_FlushPipe: function: Bool; stdcall;
    WinUsb_Free: function: Bool; stdcall;
    WinUsb_GetAssociatedInterface: function: Bool; stdcall;
    WinUsb_GetCurrentAlternateSetting: function: Bool; stdcall;
    WinUsb_GetDescriptor: function: Bool; stdcall;
    WinUsb_GetOverlappedResult: function: Bool; stdcall;
    WinUsb_GetPipePolicy: function: Bool; stdcall;
    WinUsb_GetPowerPolicy: function: Bool; stdcall;
    WinUsb_Initialize: function: Bool; stdcall;
    WinUsb_QueryDeviceInformation: function: Bool; stdcall;
    WinUsb_QueryInterfaceSettings: function: Bool; stdcall;
    WinUsb_QueryPipe: function: Bool; stdcall;
    WinUsb_ReadPipe: function: Bool; stdcall;
    WinUsb_ResetPipe: function: Bool; stdcall;
    WinUsb_SetCurrentAlternateSetting: function: Bool; stdcall;
    WinUsb_SetPipePolicy: function: Bool; stdcall;
    WinUsb_SetPowerPolicy: function: Bool; stdcall;
    WinUsb_WritePipe: function: Bool; stdcall;

    {$ELSE}
  function HotK_Init(var Handle: KHOT_HANDLE; const InitParams: PKHOT_PARAMS)
    : Bool; stdcall; external LIBUSBK_DLL name 'HotK_Init';
  function HotK_Free(const Handle: KHOT_HANDLE): Bool; stdcall;
    external LIBUSBK_DLL name 'HotK_Free';
  procedure HotK_FreeAll; stdcall; external LIBUSBK_DLL name 'HotK_FreeAll';
  function IsoK_EnumPackets(const IsoContext: PKISO_CONTEXT;
    const EnumPackets: KISO_ENUM_PACKETS_CB; const StartPacketIndex: Integer;
    const UserState): Bool; stdcall;
    external LIBUSBK_DLL name 'IsoK_EnumPackets';
  function IsoK_Free(const IsoContext: PKISO_CONTEXT): Bool; stdcall;
    external LIBUSBK_DLL name 'IsoK_Free';
  function IsoK_GetPacket(const IsoContext: PKISO_CONTEXT;
    const PacketIndex: Integer; const IsoPacket: PKISO_PACKET): Bool; stdcall;
    external LIBUSBK_DLL name 'IsoK_GetPacket';
  function IsoK_Init(var IsoContext: PKISO_CONTEXT;
    const NumberOfPackets: Integer; const StartFrame: Integer): Bool; stdcall;
    external LIBUSBK_DLL name 'IsoK_Init';
  function IsoK_ReUse(const IsoContext: PKISO_CONTEXT): Bool; stdcall;
    external LIBUSBK_DLL name 'IsoK_ReUse';
  function IsoK_SetPacket(const IsoContext: PKISO_CONTEXT;
    const PacketIndex: Integer; const IsoPacket: PKISO_PACKET): Bool; stdcall;
    external LIBUSBK_DLL name 'IsoK_SetPacket';
  function IsoK_SetPackets(const IsoContext: PKISO_CONTEXT;
    const PacketSize: Integer): Bool; stdcall;
    external LIBUSBK_DLL name 'IsoK_SetPackets';
  function LibK_CopyDriverAPI: Bool; stdcall;
    external LIBUSBK_DLL name 'LibK_CopyDriverAPI';
  function LibK_GetContext(const Handle: KLIB_HANDLE;
    const HandleType: KLIB_HANDLE_TYPE): KLIB_USER_CONTEXT; stdcall;
    external LIBUSBK_DLL name 'LibK_GetContext';
  function LibK_GetProcAddress: Bool; stdcall;
    external LIBUSBK_DLL name 'LibK_GetProcAddress';
  function LibK_GetVersion: Bool; stdcall;
    external LIBUSBK_DLL name 'LibK_GetVersion';
  function LibK_LoadDriverAPI(var DriverAPI: KUSB_DRIVER_API;
    const DriverID: Integer): Bool; stdcall;
    external LIBUSBK_DLL name 'LibK_LoadDriverAPI';
  function LibK_SetCleanupCallback: Bool; stdcall;
    external LIBUSBK_DLL name 'LibK_SetCleanupCallback';
  function LibK_SetContext(const Handle: KLIB_HANDLE;
    const HandleType: KLIB_HANDLE_TYPE; const ContextValue: KLIB_USER_CONTEXT)
    : Bool; stdcall; external LIBUSBK_DLL name 'LibK_SetContext';
  function LibK_SetDefaultContext(const HandleType: KLIB_HANDLE_TYPE;
    const UserContext: KLIB_USER_CONTEXT): Bool; stdcall;
    external LIBUSBK_DLL name 'LibK_SetDefaultContext';
  function LibK_GetDefaultContext(const HandleType: KLIB_HANDLE_TYPE)
    : KLIB_USER_CONTEXT; stdcall;
    external LIBUSBK_DLL name 'LibK_GetDefaultContext';
  function LstK_AttachInfo: Bool; stdcall;
    external LIBUSBK_DLL name 'LstK_AttachInfo';
  function LstK_Clone(const InterfaceHandle: KUSB_HANDLE;
    var DstInterfaceHandle: KUSB_HANDLE): Bool; stdcall;
    external LIBUSBK_DLL name 'LstK_Clone';
  function LstK_CloneInfo: Bool; stdcall;
    external LIBUSBK_DLL name 'LstK_CloneInfo';
  function LstK_Count(const DeviceList: KLST_HANDLE; var Count: Cardinal): Bool;
    stdcall; external LIBUSBK_DLL name 'LstK_Count';
  function LstK_Current: Bool; stdcall;
    external LIBUSBK_DLL name 'LstK_Current';
  function LstK_DetachInfo: Bool; stdcall;
    external LIBUSBK_DLL name 'LstK_Current';
  function LstK_Enumerate: Bool; stdcall;
    external LIBUSBK_DLL name 'LstK_Enumerate';
  function LstK_FindByVidPid(const DeviceList: KLST_HANDLE; const Vid: Integer;
    const Pid: Integer; var DeviceInfo: KLST_DEVINFO_HANDLE): Bool; stdcall;
    external LIBUSBK_DLL name 'LstK_FindByVidPid';
  function LstK_Free(const DeviceList: KLST_HANDLE): Bool; stdcall;
    external LIBUSBK_DLL name 'LstK_Free';
  function LstK_FreeInfo: Bool; stdcall;
    external LIBUSBK_DLL name 'LstK_FreeInfo';
  function LstK_Init(var DeviceList: KLST_HANDLE; const Flags: KLST_FLAG): Bool;
    stdcall; external LIBUSBK_DLL name 'LstK_Init';
  function LstK_InitEx(var DeviceList: KLST_HANDLE; const Flags: KLST_FLAG;
    const PatternMatch: PKLST_PATTERN_MATCH): Bool; stdcall;
    external LIBUSBK_DLL name 'LstK_InitEx';
  function LstK_MoveNext(const DeviceList: KLST_HANDLE;
    var DevInfo: KLST_DEVINFO_HANDLE): Bool; stdcall;
    external LIBUSBK_DLL name 'LstK_MoveNext';
  function LstK_MoveReset(const DeviceList: KLST_HANDLE): Bool; stdcall;
    external LIBUSBK_DLL name 'LstK_MoveReset';
  function LstK_Sync: Bool; stdcall; external LIBUSBK_DLL name 'LstK_Sync';
  function OvlK_Acquire(var OverlappedK: KOVL_HANDLE;
    const PoolHandle: KOVL_POOL_HANDLE): Bool; stdcall;
    external LIBUSBK_DLL name 'OvlK_Acquire';
  function OvlK_Free(const PoolHandle: KOVL_POOL_HANDLE): Bool; stdcall;
    external LIBUSBK_DLL name 'OvlK_Free';
  function OvlK_GetEventHandle: Bool; stdcall;
    external LIBUSBK_DLL name 'OvlK_GetEventHandle';
  function OvlK_Init(var PoolHandle: KOVL_POOL_HANDLE;
    const UsbHandle: KUSB_HANDLE; const MaxOverlappedCount: Integer;
    const Flags: KOVL_POOL_FLAG): Bool; stdcall;
    external LIBUSBK_DLL name 'OvlK_Init';
  function OvlK_IsComplete: Bool; stdcall;
    external LIBUSBK_DLL name 'OvlK_IsComplete';
  function OvlK_ReUse(const OverlappedK: KOVL_HANDLE): Bool; stdcall;
    external LIBUSBK_DLL name 'OvlK_ReUse';
  function OvlK_Release(const OverlappedK: KOVL_HANDLE): Bool; stdcall;
    external LIBUSBK_DLL name 'OvlK_Release';
  function OvlK_Wait(const OverlappedK: KOVL_HANDLE; const TimeoutMS: Integer;
    const WaitFlags: KOVL_WAIT_FLAG; var TransferredLength: Cardinal): Bool;
    stdcall; external LIBUSBK_DLL name 'OvlK_Wait';
  function OvlK_WaitOldest(const PoolHandle: KOVL_POOL_HANDLE;
    var OverlappedK: KOVL_HANDLE; const TimeoutMS: Integer;
    const WaitFlags: KOVL_WAIT_FLAG; var TransferredLength: Cardinal): Bool;
    stdcall; external LIBUSBK_DLL name 'OvlK_WaitOldest';
  function OvlK_WaitAndRelease(const OverlappedK: KOVL_HANDLE;
    const TimeoutMS: Integer; var TransferredLength: Cardinal): Bool; stdcall;
    external LIBUSBK_DLL name 'OvlK_WaitAndRelease';
  function OvlK_WaitOrCancel(const OverlappedK: KOVL_HANDLE;
    const TimeoutMS: Integer; var TransferredLength: Cardinal): Bool; stdcall;
    external LIBUSBK_DLL name 'OvlK_WaitOrCancel';
  function StmK_Free(const StreamHandle: KSTM_HANDLE): Bool; stdcall;
    external LIBUSBK_DLL name 'StmK_Free';
  function StmK_Init(var StreamHandle: KSTM_HANDLE;
    const UsbHandle: KUSB_HANDLE; const PipeId: Byte;
    const MaxTransferSize: Integer; const MaxPendingTransfers: Integer;
    const MaxPendingIO: Integer; const Callbacks: PKSTM_CALLBACK;
    const Flags: KSTM_FLAG): Bool; stdcall;
    external LIBUSBK_DLL name 'StmK_Init';
  function StmK_Read(const StreamHandle: KSTM_HANDLE; var Buffer;
    const Offset: Integer; const Length: Integer;
    var TransferredLength: Cardinal): Bool; stdcall;
    external LIBUSBK_DLL name 'StmK_Read';
  function StmK_Start(const StreamHandle: KSTM_HANDLE): Bool; stdcall;
    external LIBUSBK_DLL name 'StmK_Start';
  function StmK_Stop(const StreamHandle: KSTM_HANDLE;
    const TimeoutCancelMS: Integer): Bool; stdcall;
    external LIBUSBK_DLL name 'StmK_Stop';
  function StmK_Write(const StreamHandle: KSTM_HANDLE; const Buffer;
    const Offset: Integer; const Length: Integer;
    var TransferredLength: Cardinal): Bool; stdcall;
    external LIBUSBK_DLL name 'StmK_Write';
  function UsbK_AbortPipe(const InterfaceHandle: KUSB_HANDLE;
    const PipeId: Byte): Bool; stdcall;
    external LIBUSBK_DLL name 'UsbK_AbortPipe';
  function UsbK_ClaimInterface(const InterfaceHandle: KUSB_HANDLE;
    const NumberOrIndex: Byte; const IsIndex: Bool): Bool; stdcall;
    external LIBUSBK_DLL name 'UsbK_ClaimInterface';
  function UsbK_Clone(const InterfaceHandle: KUSB_HANDLE;
    var DstInterfaceHandle: KUSB_HANDLE): Bool; stdcall;
    external LIBUSBK_DLL name 'UsbK_Clone';
  function UsbK_ControlTransfer(const InterfaceHandle: KUSB_HANDLE;
    const SetupPacket: WINUSB_SETUP_PACKET_INT64; var Buffer;
    const BufferLength: Cardinal; const LengthTransferred: PCardinal;
    //Optional may be Nil
    const Overlapped: POverlapped): Bool; stdcall;
    external LIBUSBK_DLL name 'UsbK_ControlTransfer';
  function UsbK_FlushPipe: Bool; stdcall;
    external LIBUSBK_DLL name 'UsbK_FlushPipe';
  function UsbK_Free(const InterfaceHandle: KUSB_HANDLE): Bool; stdcall;
    external LIBUSBK_DLL name 'UsbK_Free';
  function UsbK_GetAltInterface(const InterfaceHandle: KUSB_HANDLE;
    const NumberOrIndex: Byte; const IsIndex: Bool; var AltSettingNumber: Byte)
    : Bool; stdcall; external LIBUSBK_DLL name 'UsbK_GetAltInterface';
  function UsbK_GetAssociatedInterface: Bool; stdcall;
    external LIBUSBK_DLL name 'UsbK_GetAssociatedInterface';
  function UsbK_GetConfiguration: Bool; stdcall;
    external LIBUSBK_DLL name 'UsbK_GetConfiguration';
  function UsbK_GetCurrentAlternateSetting: Bool; stdcall;
    external LIBUSBK_DLL name 'UsbK_GetCurrentAlternateSetting';
  function UsbK_GetCurrentFrameNumber(const InterfaceHandle: KUSB_HANDLE;
    var FrameNumber: Cardinal): Bool; stdcall;
    external LIBUSBK_DLL name 'UsbK_GetCurrentFrameNumber';
  function UsbK_GetDescriptor(const InterfaceHandle: KUSB_HANDLE;
    const DescriptorType: Byte; const Index: Byte; const LanguageID: Word;
    var Buffer; const BufferLength: Cardinal; var LengthTransferred: Cardinal)
    : Bool; stdcall; external LIBUSBK_DLL name 'UsbK_GetDescriptor';
  function UsbK_GetOverlappedResult: Bool; stdcall;
    external LIBUSBK_DLL name 'UsbK_GetOverlappedResult';
  function UsbK_GetPipePolicy: Bool; stdcall;
    external LIBUSBK_DLL name 'UsbK_GetPipePolicy';
  function UsbK_GetPowerPolicy: Bool; stdcall;
    external LIBUSBK_DLL name 'UsbK_GetPowerPolicy';
  function UsbK_GetProperty: Bool; stdcall;
    external LIBUSBK_DLL name 'UsbK_GetProperty';
  function UsbK_Init(var InterfaceHandle: KUSB_HANDLE;
    const DevInfo: KLST_DEVINFO_HANDLE): Bool; stdcall;
    external LIBUSBK_DLL name 'UsbK_Init';
  function UsbK_Initialize: Bool; stdcall;
    external LIBUSBK_DLL name 'UsbK_Initialize';
  function UsbK_IsoReadPipe(const InterfaceHandle: KUSB_HANDLE;
    const PipeId: Byte; var Buffer; const BufferLength: Cardinal;
    const Overlapped: POverlapped; const IsoContext: PKISO_CONTEXT): Bool;
    stdcall; external LIBUSBK_DLL name 'UsbK_IsoReadPipe';
  function UsbK_IsoWritePipe: Bool; stdcall;
    external LIBUSBK_DLL name 'UsbK_IsoWritePipe';
  function UsbK_QueryDeviceInformation: Bool; stdcall;
    external LIBUSBK_DLL name 'UsbK_QueryDeviceInformation';
  function UsbK_QueryInterfaceSettings(const InterfaceHandle: KUSB_HANDLE;
    const AltSettingNumber: Byte;
    var UsbAltInterfaceDescriptor: USB_INTERFACE_DESCRIPTOR): Bool; stdcall;
    external LIBUSBK_DLL name 'UsbK_QueryInterfaceSettings';
  function UsbK_QueryPipe(const InterfaceHandle: KUSB_HANDLE;
    const AltSettingNumber: Byte; const PipeIndex: Byte;
    var PipeInformation: WINUSB_PIPE_INFORMATION): Bool; stdcall;
    external LIBUSBK_DLL name 'UsbK_QueryPipe';
  function UsbK_ReadPipe(const InterfaceHandle: KUSB_HANDLE; const PipeId: Byte;
    var Buffer; const BufferLength: Cardinal;
    const LengthTransferred: PCardinal; //Optional may be Nil
    const Overlapped: POverlapped): Bool; stdcall;
    external LIBUSBK_DLL name 'UsbK_ReadPipe';
  function UsbK_ReleaseInterface(const InterfaceHandle: KUSB_HANDLE;
    const NumberOrIndex: Byte; const IsIndex: Bool): Bool; stdcall;
    external LIBUSBK_DLL name 'UsbK_ReleaseInterface';
  function UsbK_ResetDevice: Bool; stdcall;
    external LIBUSBK_DLL name 'UsbK_ResetDevice';
  function UsbK_ResetPipe(const InterfaceHandle: KUSB_HANDLE;
    const PipeId: Byte): Bool; stdcall;
    external LIBUSBK_DLL name 'UsbK_ResetPipe';
  function UsbK_SelectInterface(const InterfaceHandle: KUSB_HANDLE;
    const NumberOrIndex: Byte; const IsIndex: Bool): Bool; stdcall;
    external LIBUSBK_DLL name 'UsbK_SelectInterface';
  function UsbK_SetAltInterface(const InterfaceHandle: KUSB_HANDLE;
    const NumberOrIndex: Byte; const IsIndex: Bool;
    const AltSettingNumber: Byte): Bool; stdcall;
    external LIBUSBK_DLL name 'UsbK_SetAltInterface';
  function UsbK_SetConfiguration(const InterfaceHandle: KUSB_HANDLE;
    const ConfigurationNumber: Byte): Bool; stdcall;
    external LIBUSBK_DLL name 'UsbK_SetConfiguration';
  function UsbK_SetCurrentAlternateSetting(const InterfaceHandle: KUSB_HANDLE;
    const AltSettingNumber: Byte): Bool; stdcall;
    external LIBUSBK_DLL name 'UsbK_SetCurrentAlternateSetting';
  function UsbK_SetPipePolicy(const InterfaceHandle: KUSB_HANDLE;
    const PipeId: Byte; const PolicyType: Cardinal; const ValueLength: Cardinal;
    const Value): Bool; stdcall; external LIBUSBK_DLL name 'UsbK_SetPipePolicy';

  function UsbK_SetPowerPolicy: Bool; stdcall;
    external LIBUSBK_DLL name 'UsbK_SetPowerPolicy';

  function UsbK_WritePipe(const InterfaceHandle: KUSB_HANDLE; const PipeId: Byte;
    var Buffer; const BufferLength: Cardinal;
    const LengthTransferred: PCardinal;
    const Overlapped: POverlapped): Bool; stdcall;
    external LIBUSBK_DLL name 'UsbK_WritePipe';
	
  function WinUsb_AbortPipe: Bool; stdcall;
    external LIBUSBK_DLL name 'WinUsb_AbortPipe';
  function WinUsb_ControlTransfer: Bool; stdcall;
    external LIBUSBK_DLL name 'WinUsb_ControlTransfer';
  function WinUsb_FlushPipe: Bool; stdcall;
    external LIBUSBK_DLL name 'WinUsb_FlushPipe';
  function WinUsb_Free: Bool; stdcall; external LIBUSBK_DLL name 'WinUsb_Free';
  function WinUsb_GetAssociatedInterface: Bool; stdcall;
    external LIBUSBK_DLL name 'WinUsb_GetAssociatedInterface';
  function WinUsb_GetCurrentAlternateSetting: Bool; stdcall;
    external LIBUSBK_DLL name 'WinUsb_GetCurrentAlternateSetting';
  function WinUsb_GetDescriptor: Bool; stdcall;
    external LIBUSBK_DLL name 'WinUsb_GetDescriptor';
  function WinUsb_GetOverlappedResult: Bool; stdcall;
    external LIBUSBK_DLL name 'WinUsb_GetOverlappedResult';
  function WinUsb_GetPipePolicy: Bool; stdcall;
    external LIBUSBK_DLL name 'WinUsb_GetPipePolicy';
  function WinUsb_GetPowerPolicy: Bool; stdcall;
    external LIBUSBK_DLL name 'WinUsb_GetPowerPolicy';
  function WinUsb_Initialize: Bool; stdcall;
    external LIBUSBK_DLL name 'WinUsb_Initialize';
  function WinUsb_QueryDeviceInformation: Bool; stdcall;
    external LIBUSBK_DLL name 'WinUsb_QueryDeviceInformation';
  function WinUsb_QueryInterfaceSettings: Bool; stdcall;
    external LIBUSBK_DLL name 'WinUsb_QueryInterfaceSettings';
  function WinUsb_QueryPipe: Bool; stdcall;
    external LIBUSBK_DLL name 'WinUsb_QueryPipe';
  function WinUsb_ReadPipe: Bool; stdcall;
    external LIBUSBK_DLL name 'WinUsb_ReadPipe';
  function WinUsb_ResetPipe: Bool; stdcall;
    external LIBUSBK_DLL name 'WinUsb_ResetPipe';
  function WinUsb_SetCurrentAlternateSetting: Bool; stdcall;
    external LIBUSBK_DLL name 'WinUsb_SetCurrentAlternateSetting';
  function WinUsb_SetPipePolicy: Bool; stdcall;
    external LIBUSBK_DLL name 'WinUsb_SetPipePolicy';
  function WinUsb_SetPowerPolicy: Bool; stdcall;
    external LIBUSBK_DLL name 'WinUsb_SetPowerPolicy';
  function WinUsb_WritePipe: Bool; stdcall;
    external LIBUSBK_DLL name 'WinUsb_WritePipe';

  {$ENDIF}
  function GetIsoPacketFromIsoContext(const AIsoContext: PKISO_CONTEXT;
    const AIndex: Integer): PKISO_PACKET;

  function UsbK_InitFromDevicePath(const ADevicePath: String;
    var InterfaceHandle: KUSB_HANDLE): Boolean;

  function USB_DESCRIPTOR_MAKE_TYPE_AND_INDEX(const DescriptorType: Byte;
    const Index: Byte): Word;

implementation

  function GetIsoPacketFromIsoContext(const AIsoContext: PKISO_CONTEXT;
    const AIndex: Integer): PKISO_PACKET;
  begin
    if not Assigned(AIsoContext) or (AIndex < 0) or
      (AIndex >= AIsoContext.NumberOfPackets) then
      Result:= Nil
    else
      Result:= @PKISO_PACKET_ARRAY(@AIsoContext.IsoPackets)^[AIndex];
    // isoCtx.IsoPackets[posPacket];
  end;

  function UsbK_InitFromDevicePath(const ADevicePath: String;
    var InterfaceHandle: KUSB_HANDLE): Boolean;
  var
    deviceCount: Cardinal;
    lDeviceList: KLST_HANDLE;
    lDeviceInfo: KLST_DEVINFO_HANDLE;
  begin
    Result:= False;
    if not DllAvailable then
      Exit;
    InterfaceHandle:= Nil;
    deviceCount:= 0;
    lDeviceList:= Nil;
    lDeviceInfo:= Nil;
    // Get the device list
    if (not LstK_Init(lDeviceList, 0)) then
      Exit;
    try
      LstK_Count(lDeviceList, deviceCount);
      if (deviceCount = 0) then
        Exit; // List is freed in finally
      while LstK_MoveNext(lDeviceList, lDeviceInfo) do
      begin
        if Assigned(lDeviceInfo) then
        begin
          if ADevicePath = lDeviceInfo.DevicePath then
          begin
            if UsbK_Init(InterfaceHandle, lDeviceInfo) then
            begin
              Result:= True;
              Exit;
            end;
            InterfaceHandle:= Nil;
          end;
        end;
      end;
    finally
      // If lDeviceList is still assigned than free
      if Assigned(lDeviceList) then
        LstK_Free(lDeviceList);
    end;
  end;

  function USB_DESCRIPTOR_MAKE_TYPE_AND_INDEX(const DescriptorType: Byte;
    const Index: Byte): Word;
  begin
    Result:= (Word(DescriptorType) shl 8) or Index;
  end;

  function InitDllImport: Boolean;
  begin
    Result:= False;
    {$IFDEF DynamicLink}
    HLIBUSBKDll:= LoadLibrary(LIBUSBK_DLL);
    if HLIBUSBKDll >= 32 then { success }
    begin
      HotK_Init:= GetProcAddress(HLIBUSBKDll, 'HotK_Init');
      HotK_Free:= GetProcAddress(HLIBUSBKDll, 'HotK_Free');
      HotK_FreeAll:= GetProcAddress(HLIBUSBKDll, 'HotK_FreeAll');
      IsoK_EnumPackets:= GetProcAddress(HLIBUSBKDll, 'IsoK_EnumPackets');
      IsoK_Free:= GetProcAddress(HLIBUSBKDll, 'IsoK_Free');
      IsoK_GetPacket:= GetProcAddress(HLIBUSBKDll, 'IsoK_GetPacket');
      IsoK_Init:= GetProcAddress(HLIBUSBKDll, 'IsoK_Init');
      IsoK_ReUse:= GetProcAddress(HLIBUSBKDll, 'IsoK_ReUse');
      IsoK_SetPacket:= GetProcAddress(HLIBUSBKDll, 'IsoK_SetPacket');
      IsoK_SetPackets:= GetProcAddress(HLIBUSBKDll, 'IsoK_SetPackets');
      LibK_CopyDriverAPI:= GetProcAddress(HLIBUSBKDll, 'LibK_CopyDriverAPI');
      LibK_GetContext:= GetProcAddress(HLIBUSBKDll, 'LibK_GetContext');
      LibK_GetProcAddress:= GetProcAddress(HLIBUSBKDll, 'LibK_GetProcAddress');
      LibK_GetVersion:= GetProcAddress(HLIBUSBKDll, 'LibK_GetVersion');
      LibK_LoadDriverAPI:= GetProcAddress(HLIBUSBKDll, 'LibK_LoadDriverAPI');
      LibK_SetCleanupCallback:= GetProcAddress(HLIBUSBKDll,
        'LibK_SetCleanupCallback');
      LibK_SetContext:= GetProcAddress(HLIBUSBKDll, 'LibK_SetContext');
      LibK_SetDefaultContext:= GetProcAddress(HLIBUSBKDll,
        'LibK_SetDefaultContext');
      LibK_GetDefaultContext:= GetProcAddress(HLIBUSBKDll,
        'LibK_GetDefaultContext');
      LstK_AttachInfo:= GetProcAddress(HLIBUSBKDll, 'LstK_AttachInfo');
      LstK_Clone:= GetProcAddress(HLIBUSBKDll, 'LstK_Clone');
      LstK_CloneInfo:= GetProcAddress(HLIBUSBKDll, 'LstK_CloneInfo');
      LstK_Count:= GetProcAddress(HLIBUSBKDll, 'LstK_Count');
      LstK_Current:= GetProcAddress(HLIBUSBKDll, 'LstK_Current');
      LstK_DetachInfo:= GetProcAddress(HLIBUSBKDll, 'LstK_DetachInfo');
      LstK_Enumerate:= GetProcAddress(HLIBUSBKDll, 'LstK_Enumerate');
      LstK_FindByVidPid:= GetProcAddress(HLIBUSBKDll, 'LstK_FindByVidPid');
      LstK_Free:= GetProcAddress(HLIBUSBKDll, 'LstK_Free');
      LstK_FreeInfo:= GetProcAddress(HLIBUSBKDll, 'LstK_FreeInfo');
      LstK_Init:= GetProcAddress(HLIBUSBKDll, 'LstK_Init');
      LstK_InitEx:= GetProcAddress(HLIBUSBKDll, 'LstK_InitEx');
      LstK_MoveNext:= GetProcAddress(HLIBUSBKDll, 'LstK_MoveNext');
      LstK_MoveReset:= GetProcAddress(HLIBUSBKDll, 'LstK_MoveReset');
      LstK_Sync:= GetProcAddress(HLIBUSBKDll, 'LstK_Sync');
      OvlK_Acquire:= GetProcAddress(HLIBUSBKDll, 'OvlK_Acquire');
      OvlK_Free:= GetProcAddress(HLIBUSBKDll, 'OvlK_Free');
      OvlK_GetEventHandle:= GetProcAddress(HLIBUSBKDll, 'OvlK_GetEventHandle');
      OvlK_Init:= GetProcAddress(HLIBUSBKDll, 'OvlK_Init');
      OvlK_IsComplete:= GetProcAddress(HLIBUSBKDll, 'OvlK_IsComplete');
      OvlK_ReUse:= GetProcAddress(HLIBUSBKDll, 'OvlK_ReUse');
      OvlK_Release:= GetProcAddress(HLIBUSBKDll, 'OvlK_Release');
      OvlK_Wait:= GetProcAddress(HLIBUSBKDll, 'OvlK_Wait');
      OvlK_WaitOldest:= GetProcAddress(HLIBUSBKDll, 'OvlK_WaitOldest');
      OvlK_WaitAndRelease:= GetProcAddress(HLIBUSBKDll, 'OvlK_WaitAndRelease');
      OvlK_WaitOrCancel:= GetProcAddress(HLIBUSBKDll, 'OvlK_WaitOrCancel');
      StmK_Free:= GetProcAddress(HLIBUSBKDll, 'StmK_Free');
      StmK_Init:= GetProcAddress(HLIBUSBKDll, 'StmK_Init');
      StmK_Read:= GetProcAddress(HLIBUSBKDll, 'StmK_Read');
      StmK_Start:= GetProcAddress(HLIBUSBKDll, 'StmK_Start');
      StmK_Stop:= GetProcAddress(HLIBUSBKDll, 'StmK_Stop');
      StmK_Write:= GetProcAddress(HLIBUSBKDll, 'StmK_Write');
      UsbK_AbortPipe:= GetProcAddress(HLIBUSBKDll, 'UsbK_AbortPipe');
      UsbK_ClaimInterface:= GetProcAddress(HLIBUSBKDll, 'UsbK_ClaimInterface');
      UsbK_Clone:= GetProcAddress(HLIBUSBKDll, 'UsbK_Clone');
      UsbK_ControlTransfer:= GetProcAddress(HLIBUSBKDll,
        'UsbK_ControlTransfer');
      UsbK_FlushPipe:= GetProcAddress(HLIBUSBKDll, 'UsbK_FlushPipe');
      UsbK_Free:= GetProcAddress(HLIBUSBKDll, 'UsbK_Free');
      UsbK_GetAltInterface:= GetProcAddress(HLIBUSBKDll,
        'UsbK_GetAltInterface');
      UsbK_GetAssociatedInterface:= GetProcAddress(HLIBUSBKDll,
        'UsbK_GetAssociatedInterface');
      UsbK_GetConfiguration:= GetProcAddress(HLIBUSBKDll,
        'UsbK_GetConfiguration');
      UsbK_GetCurrentAlternateSetting:= GetProcAddress(HLIBUSBKDll,
        'UsbK_GetCurrentAlternateSetting');
      UsbK_GetCurrentFrameNumber:= GetProcAddress(HLIBUSBKDll,
        'UsbK_GetCurrentFrameNumber');
      UsbK_GetDescriptor:= GetProcAddress(HLIBUSBKDll, 'UsbK_GetDescriptor');
      UsbK_GetOverlappedResult:= GetProcAddress(HLIBUSBKDll,
        'UsbK_GetOverlappedResult');
      UsbK_GetPipePolicy:= GetProcAddress(HLIBUSBKDll, 'UsbK_GetPipePolicy');
      UsbK_GetPowerPolicy:= GetProcAddress(HLIBUSBKDll, 'UsbK_GetPowerPolicy');
      UsbK_GetProperty:= GetProcAddress(HLIBUSBKDll, 'UsbK_GetProperty');
      UsbK_Init:= GetProcAddress(HLIBUSBKDll, 'UsbK_Init');
      UsbK_Initialize:= GetProcAddress(HLIBUSBKDll, 'UsbK_Initialize');
      UsbK_IsoReadPipe:= GetProcAddress(HLIBUSBKDll, 'UsbK_IsoReadPipe');
      UsbK_IsoWritePipe:= GetProcAddress(HLIBUSBKDll, 'UsbK_IsoWritePipe');
      UsbK_QueryDeviceInformation:= GetProcAddress(HLIBUSBKDll,
        'UsbK_QueryDeviceInformation');
      UsbK_QueryInterfaceSettings:= GetProcAddress(HLIBUSBKDll,
        'UsbK_QueryInterfaceSettings');
      UsbK_QueryPipe:= GetProcAddress(HLIBUSBKDll, 'UsbK_QueryPipe');
      UsbK_ReadPipe:= GetProcAddress(HLIBUSBKDll, 'UsbK_ReadPipe');
      UsbK_ReleaseInterface:= GetProcAddress(HLIBUSBKDll,
        'UsbK_ReleaseInterface');
      UsbK_ResetDevice:= GetProcAddress(HLIBUSBKDll, 'UsbK_ResetDevice');
      UsbK_ResetPipe:= GetProcAddress(HLIBUSBKDll, 'UsbK_ResetPipe');
      UsbK_SelectInterface:= GetProcAddress(HLIBUSBKDll,
        'UsbK_SelectInterface');
      UsbK_SetAltInterface:= GetProcAddress(HLIBUSBKDll,
        'UsbK_SetAltInterface');
      UsbK_SetConfiguration:= GetProcAddress(HLIBUSBKDll,
        'UsbK_SetConfiguration');
      UsbK_SetCurrentAlternateSetting:= GetProcAddress(HLIBUSBKDll,
        'UsbK_SetCurrentAlternateSetting');
      UsbK_SetPipePolicy:= GetProcAddress(HLIBUSBKDll, 'UsbK_SetPipePolicy');
      UsbK_SetPowerPolicy:= GetProcAddress(HLIBUSBKDll, 'UsbK_SetPowerPolicy');
      UsbK_WritePipe:= GetProcAddress(HLIBUSBKDll, 'UsbK_WritePipe');
      WinUsb_AbortPipe:= GetProcAddress(HLIBUSBKDll, 'WinUsb_AbortPipe');
      WinUsb_ControlTransfer:= GetProcAddress(HLIBUSBKDll,
        'WinUsb_ControlTransfer');
      WinUsb_FlushPipe:= GetProcAddress(HLIBUSBKDll, 'WinUsb_FlushPipe');
      WinUsb_Free:= GetProcAddress(HLIBUSBKDll, 'WinUsb_Free');
      WinUsb_GetAssociatedInterface:= GetProcAddress(HLIBUSBKDll,
        'WinUsb_GetAssociatedInterface');
      WinUsb_GetCurrentAlternateSetting:= GetProcAddress(HLIBUSBKDll,
        'WinUsb_GetCurrentAlternateSetting');
      WinUsb_GetDescriptor:= GetProcAddress(HLIBUSBKDll,
        'WinUsb_GetDescriptor');
      WinUsb_GetOverlappedResult:= GetProcAddress(HLIBUSBKDll,
        'WinUsb_GetOverlappedResult');
      WinUsb_GetPipePolicy:= GetProcAddress(HLIBUSBKDll,
        'WinUsb_GetPipePolicy');
      WinUsb_GetPowerPolicy:= GetProcAddress(HLIBUSBKDll,
        'WinUsb_GetPowerPolicy');
      WinUsb_Initialize:= GetProcAddress(HLIBUSBKDll, 'WinUsb_Initialize');
      WinUsb_QueryDeviceInformation:= GetProcAddress(HLIBUSBKDll,
        'WinUsb_QueryDeviceInformation');
      WinUsb_QueryInterfaceSettings:= GetProcAddress(HLIBUSBKDll,
        'WinUsb_QueryInterfaceSettings');
      WinUsb_QueryPipe:= GetProcAddress(HLIBUSBKDll, 'WinUsb_QueryPipe');
      WinUsb_ReadPipe:= GetProcAddress(HLIBUSBKDll, 'WinUsb_ReadPipe');
      WinUsb_ResetPipe:= GetProcAddress(HLIBUSBKDll, 'WinUsb_ResetPipe');
      WinUsb_SetCurrentAlternateSetting:= GetProcAddress(HLIBUSBKDll,
        'WinUsb_SetCurrentAlternateSetting');
      WinUsb_SetPipePolicy:= GetProcAddress(HLIBUSBKDll,
        'WinUsb_SetPipePolicy');
      WinUsb_SetPowerPolicy:= GetProcAddress(HLIBUSBKDll,
        'WinUsb_SetPowerPolicy');
      WinUsb_WritePipe:= GetProcAddress(HLIBUSBKDll, 'WinUsb_WritePipe');
      Result:= True;
      Result:= Result and Assigned(HotK_Init);
      Result:= Result and Assigned(HotK_Free);
      Result:= Result and Assigned(HotK_FreeAll);
      Result:= Result and Assigned(IsoK_EnumPackets);
      Result:= Result and Assigned(IsoK_Free);
      Result:= Result and Assigned(IsoK_GetPacket);
      Result:= Result and Assigned(IsoK_Init);
      Result:= Result and Assigned(IsoK_ReUse);
      Result:= Result and Assigned(IsoK_SetPacket);
      Result:= Result and Assigned(IsoK_SetPackets);
      Result:= Result and Assigned(LibK_CopyDriverAPI);
      Result:= Result and Assigned(LibK_GetContext);
      Result:= Result and Assigned(LibK_GetProcAddress);
      Result:= Result and Assigned(LibK_GetVersion);
      Result:= Result and Assigned(LibK_LoadDriverAPI);
      Result:= Result and Assigned(LibK_SetCleanupCallback);
      Result:= Result and Assigned(LibK_SetContext);
      Result:= Result and Assigned(LibK_SetDefaultContext);
      Result:= Result and Assigned(LibK_GetDefaultContext);
      Result:= Result and Assigned(LstK_AttachInfo);
      Result:= Result and Assigned(LstK_Clone);
      Result:= Result and Assigned(LstK_CloneInfo);
      Result:= Result and Assigned(LstK_Count);
      Result:= Result and Assigned(LstK_Current);
      Result:= Result and Assigned(LstK_DetachInfo);
      Result:= Result and Assigned(LstK_Enumerate);
      Result:= Result and Assigned(LstK_FindByVidPid);
      Result:= Result and Assigned(LstK_Free);
      Result:= Result and Assigned(LstK_FreeInfo);
      Result:= Result and Assigned(LstK_Init);
      Result:= Result and Assigned(LstK_InitEx);
      Result:= Result and Assigned(LstK_MoveNext);
      Result:= Result and Assigned(LstK_MoveReset);
      Result:= Result and Assigned(LstK_Sync);
      Result:= Result and Assigned(OvlK_Acquire);
      Result:= Result and Assigned(OvlK_Free);
      Result:= Result and Assigned(OvlK_GetEventHandle);
      Result:= Result and Assigned(OvlK_Init);
      Result:= Result and Assigned(OvlK_IsComplete);
      Result:= Result and Assigned(OvlK_ReUse);
      Result:= Result and Assigned(OvlK_Release);
      Result:= Result and Assigned(OvlK_Wait);
      Result:= Result and Assigned(OvlK_WaitOldest);
      Result:= Result and Assigned(OvlK_WaitAndRelease);
      Result:= Result and Assigned(OvlK_WaitOrCancel);
      Result:= Result and Assigned(StmK_Free);
      Result:= Result and Assigned(StmK_Init);
      Result:= Result and Assigned(StmK_Read);
      Result:= Result and Assigned(StmK_Start);
      Result:= Result and Assigned(StmK_Stop);
      Result:= Result and Assigned(StmK_Write);
      Result:= Result and Assigned(UsbK_AbortPipe);
      Result:= Result and Assigned(UsbK_ClaimInterface);
      Result:= Result and Assigned(UsbK_Clone);
      Result:= Result and Assigned(UsbK_ControlTransfer);
      Result:= Result and Assigned(UsbK_FlushPipe);
      Result:= Result and Assigned(UsbK_Free);
      Result:= Result and Assigned(UsbK_GetAltInterface);
      Result:= Result and Assigned(UsbK_GetAssociatedInterface);
      Result:= Result and Assigned(UsbK_GetConfiguration);
      Result:= Result and Assigned(UsbK_GetCurrentAlternateSetting);
      Result:= Result and Assigned(UsbK_GetCurrentFrameNumber);
      Result:= Result and Assigned(UsbK_GetDescriptor);
      Result:= Result and Assigned(UsbK_GetOverlappedResult);
      Result:= Result and Assigned(UsbK_GetPipePolicy);
      Result:= Result and Assigned(UsbK_GetPowerPolicy);
      Result:= Result and Assigned(UsbK_GetProperty);
      Result:= Result and Assigned(UsbK_Init);
      Result:= Result and Assigned(UsbK_Initialize);
      Result:= Result and Assigned(UsbK_IsoReadPipe);
      Result:= Result and Assigned(UsbK_IsoWritePipe);
      Result:= Result and Assigned(UsbK_QueryDeviceInformation);
      Result:= Result and Assigned(UsbK_QueryInterfaceSettings);
      Result:= Result and Assigned(UsbK_QueryPipe);
      Result:= Result and Assigned(UsbK_ReadPipe);
      Result:= Result and Assigned(UsbK_ReleaseInterface);
      Result:= Result and Assigned(UsbK_ResetDevice);
      Result:= Result and Assigned(UsbK_ResetPipe);
      Result:= Result and Assigned(UsbK_SelectInterface);
      Result:= Result and Assigned(UsbK_SetAltInterface);
      Result:= Result and Assigned(UsbK_SetConfiguration);
      Result:= Result and Assigned(UsbK_SetCurrentAlternateSetting);
      Result:= Result and Assigned(UsbK_SetPipePolicy);
      Result:= Result and Assigned(UsbK_SetPowerPolicy);
      Result:= Result and Assigned(UsbK_WritePipe);
      Result:= Result and Assigned(WinUsb_AbortPipe);
      Result:= Result and Assigned(WinUsb_ControlTransfer);
      Result:= Result and Assigned(WinUsb_FlushPipe);
      Result:= Result and Assigned(WinUsb_Free);
      Result:= Result and Assigned(WinUsb_GetAssociatedInterface);
      Result:= Result and Assigned(WinUsb_GetCurrentAlternateSetting);
      Result:= Result and Assigned(WinUsb_GetDescriptor);
      Result:= Result and Assigned(WinUsb_GetOverlappedResult);
      Result:= Result and Assigned(WinUsb_GetPipePolicy);
      Result:= Result and Assigned(WinUsb_GetPowerPolicy);
      Result:= Result and Assigned(WinUsb_Initialize);
      Result:= Result and Assigned(WinUsb_QueryDeviceInformation);
      Result:= Result and Assigned(WinUsb_QueryInterfaceSettings);
      Result:= Result and Assigned(WinUsb_QueryPipe);
      Result:= Result and Assigned(WinUsb_ReadPipe);
      Result:= Result and Assigned(WinUsb_ResetPipe);
      Result:= Result and Assigned(WinUsb_SetCurrentAlternateSetting);
      Result:= Result and Assigned(WinUsb_SetPipePolicy);
      Result:= Result and Assigned(WinUsb_SetPowerPolicy);
      Result:= Result and Assigned(WinUsb_WritePipe);
    end
    else
    begin
      HotK_Init:= Nil;
      HotK_Free:= Nil;
      HotK_FreeAll:= Nil;
      IsoK_EnumPackets:= Nil;
      IsoK_Free:= Nil;
      IsoK_GetPacket:= Nil;
      IsoK_Init:= Nil;
      IsoK_ReUse:= Nil;
      IsoK_SetPacket:= Nil;
      IsoK_SetPackets:= Nil;
      LibK_CopyDriverAPI:= Nil;
      LibK_GetContext:= Nil;
      LibK_GetProcAddress:= Nil;
      LibK_GetVersion:= Nil;
      LibK_LoadDriverAPI:= Nil;
      LibK_SetCleanupCallback:= Nil;
      LibK_SetContext:= Nil;
      LibK_SetDefaultContext:= Nil;
      LibK_GetDefaultContext:= Nil;
      LstK_AttachInfo:= Nil;
      LstK_Clone:= Nil;
      LstK_CloneInfo:= Nil;
      LstK_Count:= Nil;
      LstK_Current:= Nil;
      LstK_DetachInfo:= Nil;
      LstK_Enumerate:= Nil;
      LstK_FindByVidPid:= Nil;
      LstK_Free:= Nil;
      LstK_FreeInfo:= Nil;
      LstK_Init:= Nil;
      LstK_InitEx:= Nil;
      LstK_MoveNext:= Nil;
      LstK_MoveReset:= Nil;
      LstK_Sync:= Nil;
      OvlK_Acquire:= Nil;
      OvlK_Free:= Nil;
      OvlK_GetEventHandle:= Nil;
      OvlK_Init:= Nil;
      OvlK_IsComplete:= Nil;
      OvlK_ReUse:= Nil;
      OvlK_Release:= Nil;
      OvlK_Wait:= Nil;
      OvlK_WaitOldest:= Nil;
      OvlK_WaitAndRelease:= Nil;
      OvlK_WaitOrCancel:= Nil;
      StmK_Free:= Nil;
      StmK_Init:= Nil;
      StmK_Read:= Nil;
      StmK_Start:= Nil;
      StmK_Stop:= Nil;
      StmK_Write:= Nil;
      UsbK_AbortPipe:= Nil;
      UsbK_ClaimInterface:= Nil;
      UsbK_Clone:= Nil;
      UsbK_ControlTransfer:= Nil;
      UsbK_FlushPipe:= Nil;
      UsbK_Free:= Nil;
      UsbK_GetAltInterface:= Nil;
      UsbK_GetAssociatedInterface:= Nil;
      UsbK_GetConfiguration:= Nil;
      UsbK_GetCurrentAlternateSetting:= Nil;
      UsbK_GetCurrentFrameNumber:= Nil;
      UsbK_GetDescriptor:= Nil;
      UsbK_GetOverlappedResult:= Nil;
      UsbK_GetPipePolicy:= Nil;
      UsbK_GetPowerPolicy:= Nil;
      UsbK_GetProperty:= Nil;
      UsbK_Init:= Nil;
      UsbK_Initialize:= Nil;
      UsbK_IsoReadPipe:= Nil;
      UsbK_IsoWritePipe:= Nil;
      UsbK_QueryDeviceInformation:= Nil;
      UsbK_QueryInterfaceSettings:= Nil;
      UsbK_QueryPipe:= Nil;
      UsbK_ReadPipe:= Nil;
      UsbK_ReleaseInterface:= Nil;
      UsbK_ResetDevice:= Nil;
      UsbK_ResetPipe:= Nil;
      UsbK_SelectInterface:= Nil;
      UsbK_SetAltInterface:= Nil;
      UsbK_SetConfiguration:= Nil;
      UsbK_SetCurrentAlternateSetting:= Nil;
      UsbK_SetPipePolicy:= Nil;
      UsbK_SetPowerPolicy:= Nil;
      UsbK_WritePipe:= Nil;
      WinUsb_AbortPipe:= Nil;
      WinUsb_ControlTransfer:= Nil;
      WinUsb_FlushPipe:= Nil;
      WinUsb_Free:= Nil;
      WinUsb_GetAssociatedInterface:= Nil;
      WinUsb_GetCurrentAlternateSetting:= Nil;
      WinUsb_GetDescriptor:= Nil;
      WinUsb_GetOverlappedResult:= Nil;
      WinUsb_GetPipePolicy:= Nil;
      WinUsb_GetPowerPolicy:= Nil;
      WinUsb_Initialize:= Nil;
      WinUsb_QueryDeviceInformation:= Nil;
      WinUsb_QueryInterfaceSettings:= Nil;
      WinUsb_QueryPipe:= Nil;
      WinUsb_ReadPipe:= Nil;
      WinUsb_ResetPipe:= Nil;
      WinUsb_SetCurrentAlternateSetting:= Nil;
      WinUsb_SetPipePolicy:= Nil;
      WinUsb_SetPowerPolicy:= Nil;
      WinUsb_WritePipe:= Nil;
    end;
    {$ELSE}
    Result:= True;
    {$ENDIF}
  end;

  procedure DoneDllImport;
  begin
    {$IFDEF DynamicLink}
    if DllAvailable then
      FreeLibrary(HLIBUSBKDll);
    {$ENDIF}
  end;

initialization

  {$IFDEF DynamicLink}
    DllAvailable:= InitDllImport;
  {$ELSE}
  // Anyway the program will not start if the DLL is not available
  DllAvailable:= True;
  {$ENDIF}
  // Delphi will show a Breakpoint if Assert violates, if no violation is
  // detected by the compiler, the linker will eliminate the calls
  Assert((SizeOf(WINUSB_PIPE_INFORMATION) = 12),
    'WINUSB_PIPE_INFORMATION size violation');
  Assert((SizeOf(WINUSB_SETUP_PACKET) = 8),
    'WINUSB_SETUP_PACKET size violation');
  Assert((SizeOf(KISO_CONTEXT) = 16), 'KISO_CONTEXT size violation');
  Assert((SizeOf(KUSB_DRIVER_API) = 512), 'KUSB_DRIVER_API size violation');
  Assert((SizeOf(KSTM_CALLBACK) = 64), 'KSTM_CALLBACK size violation');
  Assert((SizeOf(KLST_PATTERN_MATCH) = 1024),
    'KLST_PATTERN_MATCH size violation');
  Assert((SizeOf(KHOT_PARAMS) = 2048), 'KHOT_PARAMS size violation');

finalization

  {$IFDEF DynamicLink}
    DoneDllImport;
  {$ENDIF}

end.
