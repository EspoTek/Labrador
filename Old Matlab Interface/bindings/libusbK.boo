ERROR: Z:\SVNMAIN\GoogleCode\usb-travis\trunk\libusbK\bindings\libusbK.cs(1281,9): BCE0000: enum member initializer must be integer value

#region Copyright (c) Travis Robinson

// Copyright (c) 2012 Travis Robinson <libusbdotnet@gmail.com>
// All rights reserved.
//
// C# libusbK Bindings
// Auto-generated on: 04.28.2011
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


// ReSharper disable InconsistentNaming
// ReSharper disable CheckNamespace
// ReSharper disable UnassignedReadonlyField

namespace libusbK

import System
import System.Diagnostics
import System.Runtime.InteropServices

public static class AllKOptions:

	#region Public Members
	
	public static LIBUSBK_FULLPATH_TO_ALTERNATE_DLL as string
	
	#endregion


public static class AllKConstants:

	#region Public Members
	
	public static final KLST_STRING_MAX_LEN = 256

	
	public static final LIBUSBK_DLL = 'libusbK.dll'

	
	public static final USB_CONFIG_POWERED_MASK as byte = 192

	
	public static final USB_ENDPOINT_ADDRESS_MASK as byte = 15

	
	public static final USB_ENDPOINT_DIRECTION_MASK as byte = 128
	
	#endregion


public enum PipePolicyType:

	SHORT_PACKET_TERMINATE = 1

	AUTO_CLEAR_STALL = 2

	PIPE_TRANSFER_TIMEOUT = 3

	IGNORE_SHORT_PACKETS = 4

	ALLOW_PARTIAL_READS = 5

	AUTO_FLUSH = 6

	RAW_IO = 7

	MAXIMUM_TRANSFER_SIZE = 8

	RESET_PIPE_ON_RESUME = 9

	
	ISO_START_LATENCY = 32

	ISO_ALWAYS_START_ASAP = 33

	ISO_NUM_FIXED_PACKETS = 34

	
	SIMUL_PARALLEL_REQUESTS = 48


public enum PowerPolicyType:

	AUTO_SUSPEND = 129

	SUSPEND_DELAY = 131


public enum DeviceInformationType:

	DEVICE_SPEED = 1


public enum EndpointType:

	CONTROL = 0

	
	ISOCHRONOUS = 1

	
	BULK = 2

	
	INTERRUPT = 3

	
	MASK = 3


public static class ErrorCodes:

	#region Public Members
	
	public static final AccessDenied = 5

	
	public static final Busy = 170

	
	public static final Cancelled = 1223

	
	public static final Empty = 4306

	
	public static final InvalidHandle = 6

	
	public static final InvalidParameter = 87

	
	public static final IoIncomplete = 996

	
	public static final IoPending = 997

	
	public static final MoreData = 234

	
	public static final NoMoreItems = 259

	
	public static final NotEnoughMemory = 8

	
	public static final NotFound = 1168

	
	public static final NotSupported = 50

	
	public static final OperationAborted = 995

	
	public static final ResourceNotAvailable = 5006

	
	public static final ResourceNotFound = 5007

	
	public static final SemTimeout = 121

	
	public static final Success = 0

	
	public static final ThreadNotInProcess = 566

	
	public static final ThreadWasSuspended = 699

	
	public static final TooManyModules = 214
	
	#endregion


public interface IKLIB_HANDLE:

	#region Public Members
	
	def GetContext() as IntPtr

	HandleType as KLIB_HANDLE_TYPE:
		get

	Pointer as IntPtr:
		get

	def SetCleanupCallback(CleanupCallback as KLIB_HANDLE_CLEANUP_CB) as bool

	def SetContext(UserContext as IntPtr) as bool
	
	#endregion


#region Opaque library handles

public struct KLST_HANDLE(IKLIB_HANDLE):

	#region IKLIB_HANDLE Members
	
	public Pointer as IntPtr:
		get:
			return mHandlePtr

	
	public HandleType as KLIB_HANDLE_TYPE:
		get:
			return KLIB_HANDLE_TYPE.LSTK

	
	public def GetContext() as IntPtr:
		return AllKFunctions.LibK_GetContext(mHandlePtr, HandleType)

	
	public def SetContext(UserContext as IntPtr) as bool:
		return AllKFunctions.LibK_SetContext(mHandlePtr, HandleType, UserContext)

	
	public def SetCleanupCallback(CleanupCallback as KLIB_HANDLE_CLEANUP_CB) as bool:
		return AllKFunctions.LibK_SetCleanupCallback(mHandlePtr, HandleType, CleanupCallback)

	
	#endregion
	
	#region Public Members
	
	public def constructor(Handle as IntPtr):
		mHandlePtr = Handle

	
	#endregion
	
	#region Private Members
	
	private final mHandlePtr as IntPtr
	
	#endregion


public struct KHOT_HANDLE(IKLIB_HANDLE):

	#region IKLIB_HANDLE Members
	
	public Pointer as IntPtr:
		get:
			return mHandlePtr

	
	public HandleType as KLIB_HANDLE_TYPE:
		get:
			return KLIB_HANDLE_TYPE.HOTK

	
	public def GetContext() as IntPtr:
		return AllKFunctions.LibK_GetContext(mHandlePtr, HandleType)

	
	public def SetContext(UserContext as IntPtr) as bool:
		return AllKFunctions.LibK_SetContext(mHandlePtr, HandleType, UserContext)

	
	public def SetCleanupCallback(CleanupCallback as KLIB_HANDLE_CLEANUP_CB) as bool:
		return AllKFunctions.LibK_SetCleanupCallback(mHandlePtr, HandleType, CleanupCallback)

	
	#endregion
	
	#region Public Members
	
	public def constructor(Handle as IntPtr):
		mHandlePtr = Handle

	
	#endregion
	
	#region Private Members
	
	private final mHandlePtr as IntPtr
	
	#endregion


public struct KUSB_HANDLE(IKLIB_HANDLE):

	#region IKLIB_HANDLE Members
	
	public Pointer as IntPtr:
		get:
			return mHandlePtr

	
	public HandleType as KLIB_HANDLE_TYPE:
		get:
			return KLIB_HANDLE_TYPE.USBK

	
	public def GetContext() as IntPtr:
		return AllKFunctions.LibK_GetContext(mHandlePtr, HandleType)

	
	public def SetContext(UserContext as IntPtr) as bool:
		return AllKFunctions.LibK_SetContext(mHandlePtr, HandleType, UserContext)

	
	public def SetCleanupCallback(CleanupCallback as KLIB_HANDLE_CLEANUP_CB) as bool:
		return AllKFunctions.LibK_SetCleanupCallback(mHandlePtr, HandleType, CleanupCallback)

	
	#endregion
	
	#region USB Shared Device Context
	
	public def GetSharedContext() as IntPtr:
		return AllKFunctions.LibK_GetContext(mHandlePtr, KLIB_HANDLE_TYPE.USBSHAREDK)

	
	public def SetSharedCleanupCallback(CleanupCallback as KLIB_HANDLE_CLEANUP_CB) as bool:
		return AllKFunctions.LibK_SetCleanupCallback(mHandlePtr, KLIB_HANDLE_TYPE.USBSHAREDK, CleanupCallback)

	
	public def SetSharedContext(UserContext as IntPtr) as bool:
		return AllKFunctions.LibK_SetContext(mHandlePtr, KLIB_HANDLE_TYPE.USBSHAREDK, UserContext)

	
	#endregion
	
	#region Public Members
	
	public def constructor(Handle as IntPtr):
		mHandlePtr = Handle

	
	#endregion
	
	#region Private Members
	
	private final mHandlePtr as IntPtr
	
	#endregion


public struct KOVL_POOL_HANDLE(IKLIB_HANDLE):

	#region IKLIB_HANDLE Members
	
	public Pointer as IntPtr:
		get:
			return mHandlePtr

	
	public HandleType as KLIB_HANDLE_TYPE:
		get:
			return KLIB_HANDLE_TYPE.OVLPOOLK

	
	public def GetContext() as IntPtr:
		return AllKFunctions.LibK_GetContext(mHandlePtr, HandleType)

	
	public def SetContext(UserContext as IntPtr) as bool:
		return AllKFunctions.LibK_SetContext(mHandlePtr, HandleType, UserContext)

	
	public def SetCleanupCallback(CleanupCallback as KLIB_HANDLE_CLEANUP_CB) as bool:
		return AllKFunctions.LibK_SetCleanupCallback(mHandlePtr, HandleType, CleanupCallback)

	
	#endregion
	
	#region Public Members
	
	public def constructor(Handle as IntPtr):
		mHandlePtr = Handle

	
	#endregion
	
	#region Private Members
	
	private final mHandlePtr as IntPtr
	
	#endregion


public struct KOVL_HANDLE(IKLIB_HANDLE):

	#region IKLIB_HANDLE Members
	
	public Pointer as IntPtr:
		get:
			return mHandlePtr

	
	public HandleType as KLIB_HANDLE_TYPE:
		get:
			return KLIB_HANDLE_TYPE.OVLK

	
	public def GetContext() as IntPtr:
		return AllKFunctions.LibK_GetContext(mHandlePtr, HandleType)

	
	public def SetContext(UserContext as IntPtr) as bool:
		return AllKFunctions.LibK_SetContext(mHandlePtr, HandleType, UserContext)

	
	public def SetCleanupCallback(CleanupCallback as KLIB_HANDLE_CLEANUP_CB) as bool:
		return AllKFunctions.LibK_SetCleanupCallback(mHandlePtr, HandleType, CleanupCallback)

	
	#endregion
	
	#region Public Members
	
	public def constructor(Handle as IntPtr):
		mHandlePtr = Handle

	
	#endregion
	
	#region Private Members
	
	private final mHandlePtr as IntPtr
	
	#endregion


public struct KSTM_HANDLE(IKLIB_HANDLE):

	#region IKLIB_HANDLE Members
	
	public Pointer as IntPtr:
		get:
			return mHandlePtr

	
	public HandleType as KLIB_HANDLE_TYPE:
		get:
			return KLIB_HANDLE_TYPE.STMK

	
	public def GetContext() as IntPtr:
		return AllKFunctions.LibK_GetContext(mHandlePtr, HandleType)

	
	public def SetContext(UserContext as IntPtr) as bool:
		return AllKFunctions.LibK_SetContext(mHandlePtr, HandleType, UserContext)

	
	public def SetCleanupCallback(CleanupCallback as KLIB_HANDLE_CLEANUP_CB) as bool:
		return AllKFunctions.LibK_SetCleanupCallback(mHandlePtr, HandleType, CleanupCallback)

	
	#endregion
	
	#region Public Members
	
	public def constructor(Handle as IntPtr):
		mHandlePtr = Handle

	
	#endregion
	
	#region Private Members
	
	private final mHandlePtr as IntPtr
	
	#endregion


#endregion

#region Internal Function Imports

internal static class AllKFunctions:

	#region Delegates
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable HotK_FreeAllDelegate() as void
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable HotK_FreeDelegate([In] Handle as KHOT_HANDLE) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable HotK_InitDelegate([Out] ref Handle as KHOT_HANDLE, [In] [Out] ref InitParams as KHOT_PARAMS) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable IsoK_EnumPacketsDelegate([In] IsoContext as KISO_CONTEXT, EnumPackets as KISO_ENUM_PACKETS_CB, StartPacketIndex as int, UserState as IntPtr) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable IsoK_FreeDelegate([In] IsoContext as KISO_CONTEXT) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable IsoK_GetPacketDelegate([In] IsoContext as KISO_CONTEXT, PacketIndex as int, [Out] ref IsoPacket as KISO_PACKET) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable IsoK_InitDelegate([Out] ref IsoContext as KISO_CONTEXT, NumberOfPackets as int, StartFrame as int) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable IsoK_ReUseDelegate([In] IsoContext as KISO_CONTEXT) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable IsoK_SetPacketDelegate([In] IsoContext as KISO_CONTEXT, PacketIndex as int, [In] ref IsoPacket as KISO_PACKET) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable IsoK_SetPacketsDelegate([In] IsoContext as KISO_CONTEXT, PacketSize as int) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable LibK_Context_FreeDelegate() as void
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable LibK_Context_InitDelegate(Heap as IntPtr, Reserved as IntPtr) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable LibK_CopyDriverAPIDelegate([Out] ref DriverAPI as KUSB_DRIVER_API, [In] UsbHandle as KUSB_HANDLE) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable LibK_GetContextDelegate([In] Handle as IntPtr, HandleType as KLIB_HANDLE_TYPE) as IntPtr
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable LibK_GetDefaultContextDelegate(HandleType as KLIB_HANDLE_TYPE) as IntPtr
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable LibK_GetProcAddressDelegate(ProcAddress as IntPtr, DriverID as int, FunctionID as int) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable LibK_GetVersionDelegate([Out] ref Version as KLIB_VERSION) as void
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable LibK_LoadDriverAPIDelegate([Out] ref DriverAPI as KUSB_DRIVER_API, DriverID as int) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable LibK_SetCleanupCallbackDelegate([In] Handle as IntPtr, HandleType as KLIB_HANDLE_TYPE, CleanupCB as KLIB_HANDLE_CLEANUP_CB) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable LibK_SetContextDelegate([In] Handle as IntPtr, HandleType as KLIB_HANDLE_TYPE, ContextValue as IntPtr) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable LibK_SetDefaultContextDelegate(HandleType as KLIB_HANDLE_TYPE, ContextValue as IntPtr) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable LstK_CountDelegate([In] DeviceList as KLST_HANDLE, ref Count as int) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable LstK_CurrentDelegate([In] DeviceList as KLST_HANDLE, [Out] ref DeviceInfo as KLST_DEVINFO_HANDLE) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable LstK_EnumerateDelegate([In] DeviceList as KLST_HANDLE, EnumDevListCB as KLST_ENUM_DEVINFO_CB, Context as IntPtr) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable LstK_FindByVidPidDelegate([In] DeviceList as KLST_HANDLE, Vid as int, Pid as int, [Out] ref DeviceInfo as KLST_DEVINFO_HANDLE) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable LstK_FreeDelegate([In] DeviceList as KLST_HANDLE) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable LstK_InitDelegate([Out] ref DeviceList as KLST_HANDLE, Flags as KLST_FLAG) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable LstK_InitExDelegate([Out] ref DeviceList as KLST_HANDLE, Flags as KLST_FLAG, [In] ref PatternMatch as KLST_PATTERN_MATCH) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable LstK_MoveNextDelegate([In] DeviceList as KLST_HANDLE, [Out] ref DeviceInfo as KLST_DEVINFO_HANDLE) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable LstK_MoveResetDelegate([In] DeviceList as KLST_HANDLE) as void
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable OvlK_AcquireDelegate([Out] ref OverlappedK as KOVL_HANDLE, [In] PoolHandle as KOVL_POOL_HANDLE) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable OvlK_FreeDelegate([In] PoolHandle as KOVL_POOL_HANDLE) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable OvlK_GetEventHandleDelegate([In] OverlappedK as KOVL_HANDLE) as IntPtr
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable OvlK_InitDelegate([Out] ref PoolHandle as KOVL_POOL_HANDLE, [In] UsbHandle as KUSB_HANDLE, MaxOverlappedCount as int, Flags as KOVL_POOL_FLAG) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable OvlK_IsCompleteDelegate([In] OverlappedK as KOVL_HANDLE) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable OvlK_ReUseDelegate([In] OverlappedK as KOVL_HANDLE) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable OvlK_ReleaseDelegate([In] OverlappedK as KOVL_HANDLE) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable OvlK_WaitAndReleaseDelegate([In] OverlappedK as KOVL_HANDLE, TimeoutMS as int, ref TransferredLength as int) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable OvlK_WaitDelegate([In] OverlappedK as KOVL_HANDLE, TimeoutMS as int, WaitFlags as KOVL_WAIT_FLAG, ref TransferredLength as int) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable OvlK_WaitOldestDelegate([In] PoolHandle as KOVL_POOL_HANDLE, [Out] ref OverlappedK as KOVL_HANDLE, TimeoutMS as int, WaitFlags as KOVL_WAIT_FLAG, ref TransferredLength as int) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable OvlK_WaitOrCancelDelegate([In] OverlappedK as KOVL_HANDLE, TimeoutMS as int, ref TransferredLength as int) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable StmK_FreeDelegate([In] StreamHandle as KSTM_HANDLE) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable StmK_InitDelegate([Out] ref StreamHandle as KSTM_HANDLE, [In] UsbHandle as KUSB_HANDLE, PipeID as byte, MaxTransferSize as int, MaxPendingTransfers as int, MaxPendingIO as int, [In] ref Callbacks as KSTM_CALLBACK, Flags as KSTM_FLAG) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable StmK_ReadDelegate([In] StreamHandle as KSTM_HANDLE, Buffer as IntPtr, Offset as int, Length as int, ref TransferredLength as int) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable StmK_StartDelegate([In] StreamHandle as KSTM_HANDLE) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable StmK_StopDelegate([In] StreamHandle as KSTM_HANDLE, TimeoutCancelMS as int) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable StmK_WriteDelegate([In] StreamHandle as KSTM_HANDLE, Buffer as IntPtr, Offset as int, Length as int, ref TransferredLength as int) as bool
	
	[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
	public static callable UsbK_FreeDelegate([In] InterfaceHandle as KUSB_HANDLE) as bool
	
	#endregion
	
	private static def constructor():
		if String.IsNullOrEmpty(AllKOptions.LIBUSBK_FULLPATH_TO_ALTERNATE_DLL):
			mModuleLibusbK = LoadLibraryEx(AllKConstants.LIBUSBK_DLL, IntPtr.Zero, LoadLibraryFlags.NONE)
		else:
			mModuleLibusbK = LoadLibraryEx(AllKOptions.LIBUSBK_FULLPATH_TO_ALTERNATE_DLL, IntPtr.Zero, LoadLibraryFlags.LOAD_WITH_ALTERED_SEARCH_PATH)
		
		if mModuleLibusbK == IntPtr.Zero:
			raise DllNotFoundException('libusbK.dll not found.  Please install drivers/applications and retry.')
		
		LoadDynamicFunctions()

	
	#region Nested Enumerations
	
	[Flags]
	private enum LoadLibraryFlags:

		NONE = 0

		DONT_RESOLVE_DLL_REFERENCES = 1

		LOAD_IGNORE_CODE_AUTHZ_LEVEL = 16

		LOAD_LIBRARY_AS_DATAFILE = 2

		LOAD_LIBRARY_AS_DATAFILE_EXCLUSIVE = 64

		LOAD_LIBRARY_AS_IMAGE_RESOURCE = 32

		LOAD_WITH_ALTERED_SEARCH_PATH = 8

	
	#endregion
	
	#region Public Members
	
	public static HotK_Free as HotK_FreeDelegate

	public static HotK_FreeAll as HotK_FreeAllDelegate

	public static HotK_Init as HotK_InitDelegate

	public static IsoK_EnumPackets as IsoK_EnumPacketsDelegate

	public static IsoK_Free as IsoK_FreeDelegate

	public static IsoK_GetPacket as IsoK_GetPacketDelegate

	public static IsoK_Init as IsoK_InitDelegate

	public static IsoK_ReUse as IsoK_ReUseDelegate

	public static IsoK_SetPacket as IsoK_SetPacketDelegate

	public static IsoK_SetPackets as IsoK_SetPacketsDelegate

	public static LibK_Context_Free as LibK_Context_FreeDelegate

	public static LibK_Context_Init as LibK_Context_InitDelegate

	
	public static LibK_CopyDriverAPI as LibK_CopyDriverAPIDelegate

	public static LibK_GetContext as LibK_GetContextDelegate

	public static LibK_GetDefaultContext as LibK_GetDefaultContextDelegate

	public static LibK_GetProcAddress as LibK_GetProcAddressDelegate

	public static LibK_GetVersion as LibK_GetVersionDelegate

	public static LibK_LoadDriverAPI as LibK_LoadDriverAPIDelegate

	public static LibK_SetCleanupCallback as LibK_SetCleanupCallbackDelegate

	public static LibK_SetContext as LibK_SetContextDelegate

	public static LibK_SetDefaultContext as LibK_SetDefaultContextDelegate

	public static LstK_Count as LstK_CountDelegate

	public static LstK_Current as LstK_CurrentDelegate

	public static LstK_Enumerate as LstK_EnumerateDelegate

	public static LstK_FindByVidPid as LstK_FindByVidPidDelegate

	public static LstK_Free as LstK_FreeDelegate

	public static LstK_Init as LstK_InitDelegate

	public static LstK_InitEx as LstK_InitExDelegate

	public static LstK_MoveNext as LstK_MoveNextDelegate

	public static LstK_MoveReset as LstK_MoveResetDelegate

	public static OvlK_Acquire as OvlK_AcquireDelegate

	public static OvlK_Free as OvlK_FreeDelegate

	public static OvlK_GetEventHandle as OvlK_GetEventHandleDelegate

	public static OvlK_Init as OvlK_InitDelegate

	public static OvlK_IsComplete as OvlK_IsCompleteDelegate

	public static OvlK_ReUse as OvlK_ReUseDelegate

	public static OvlK_Release as OvlK_ReleaseDelegate

	public static OvlK_Wait as OvlK_WaitDelegate

	public static OvlK_WaitAndRelease as OvlK_WaitAndReleaseDelegate

	public static OvlK_WaitOldest as OvlK_WaitOldestDelegate

	public static OvlK_WaitOrCancel as OvlK_WaitOrCancelDelegate

	public static StmK_Free as StmK_FreeDelegate

	public static StmK_Init as StmK_InitDelegate

	public static StmK_Read as StmK_ReadDelegate

	public static StmK_Start as StmK_StartDelegate

	public static StmK_Stop as StmK_StopDelegate

	public static StmK_Write as StmK_WriteDelegate

	public static UsbK_Free as UsbK_FreeDelegate

	
	#endregion
	
	#region Private Members
	
	[DllImport('kernel32.dll', CharSet: CharSet.Ansi, ExactSpelling: true, SetLastError: true)]
	private static def GetProcAddress(hModule as IntPtr, procName as string) as IntPtr:
		pass

	
	private static def LoadDynamicFunctions():
		LibK_GetVersion = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'LibK_GetVersion'), typeof(LibK_GetVersionDelegate)) cast LibK_GetVersionDelegate)
		LibK_GetContext = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'LibK_GetContext'), typeof(LibK_GetContextDelegate)) cast LibK_GetContextDelegate)
		LibK_SetContext = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'LibK_SetContext'), typeof(LibK_SetContextDelegate)) cast LibK_SetContextDelegate)
		LibK_SetCleanupCallback = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'LibK_SetCleanupCallback'), typeof(LibK_SetCleanupCallbackDelegate)) cast LibK_SetCleanupCallbackDelegate)
		LibK_LoadDriverAPI = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'LibK_LoadDriverAPI'), typeof(LibK_LoadDriverAPIDelegate)) cast LibK_LoadDriverAPIDelegate)
		LibK_CopyDriverAPI = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'LibK_CopyDriverAPI'), typeof(LibK_CopyDriverAPIDelegate)) cast LibK_CopyDriverAPIDelegate)
		LibK_GetProcAddress = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'LibK_GetProcAddress'), typeof(LibK_GetProcAddressDelegate)) cast LibK_GetProcAddressDelegate)
		LibK_SetDefaultContext = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'LibK_SetDefaultContext'), typeof(LibK_SetDefaultContextDelegate)) cast LibK_SetDefaultContextDelegate)
		LibK_GetDefaultContext = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'LibK_GetDefaultContext'), typeof(LibK_GetDefaultContextDelegate)) cast LibK_GetDefaultContextDelegate)
		LibK_Context_Init = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'LibK_Context_Init'), typeof(LibK_Context_InitDelegate)) cast LibK_Context_InitDelegate)
		LibK_Context_Free = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'LibK_Context_Free'), typeof(LibK_Context_FreeDelegate)) cast LibK_Context_FreeDelegate)
		UsbK_Free = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'UsbK_Free'), typeof(UsbK_FreeDelegate)) cast UsbK_FreeDelegate)
		LstK_Init = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'LstK_Init'), typeof(LstK_InitDelegate)) cast LstK_InitDelegate)
		LstK_InitEx = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'LstK_InitEx'), typeof(LstK_InitExDelegate)) cast LstK_InitExDelegate)
		LstK_Free = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'LstK_Free'), typeof(LstK_FreeDelegate)) cast LstK_FreeDelegate)
		LstK_Enumerate = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'LstK_Enumerate'), typeof(LstK_EnumerateDelegate)) cast LstK_EnumerateDelegate)
		LstK_Current = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'LstK_Current'), typeof(LstK_CurrentDelegate)) cast LstK_CurrentDelegate)
		LstK_MoveNext = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'LstK_MoveNext'), typeof(LstK_MoveNextDelegate)) cast LstK_MoveNextDelegate)
		LstK_MoveReset = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'LstK_MoveReset'), typeof(LstK_MoveResetDelegate)) cast LstK_MoveResetDelegate)
		LstK_FindByVidPid = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'LstK_FindByVidPid'), typeof(LstK_FindByVidPidDelegate)) cast LstK_FindByVidPidDelegate)
		LstK_Count = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'LstK_Count'), typeof(LstK_CountDelegate)) cast LstK_CountDelegate)
		HotK_Init = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'HotK_Init'), typeof(HotK_InitDelegate)) cast HotK_InitDelegate)
		HotK_Free = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'HotK_Free'), typeof(HotK_FreeDelegate)) cast HotK_FreeDelegate)
		HotK_FreeAll = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'HotK_FreeAll'), typeof(HotK_FreeAllDelegate)) cast HotK_FreeAllDelegate)
		OvlK_Acquire = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'OvlK_Acquire'), typeof(OvlK_AcquireDelegate)) cast OvlK_AcquireDelegate)
		OvlK_Release = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'OvlK_Release'), typeof(OvlK_ReleaseDelegate)) cast OvlK_ReleaseDelegate)
		OvlK_Init = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'OvlK_Init'), typeof(OvlK_InitDelegate)) cast OvlK_InitDelegate)
		OvlK_Free = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'OvlK_Free'), typeof(OvlK_FreeDelegate)) cast OvlK_FreeDelegate)
		OvlK_GetEventHandle = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'OvlK_GetEventHandle'), typeof(OvlK_GetEventHandleDelegate)) cast OvlK_GetEventHandleDelegate)
		OvlK_Wait = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'OvlK_Wait'), typeof(OvlK_WaitDelegate)) cast OvlK_WaitDelegate)
		OvlK_WaitOldest = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'OvlK_WaitOldest'), typeof(OvlK_WaitOldestDelegate)) cast OvlK_WaitOldestDelegate)
		OvlK_WaitOrCancel = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'OvlK_WaitOrCancel'), typeof(OvlK_WaitOrCancelDelegate)) cast OvlK_WaitOrCancelDelegate)
		OvlK_WaitAndRelease = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'OvlK_WaitAndRelease'), typeof(OvlK_WaitAndReleaseDelegate)) cast OvlK_WaitAndReleaseDelegate)
		OvlK_IsComplete = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'OvlK_IsComplete'), typeof(OvlK_IsCompleteDelegate)) cast OvlK_IsCompleteDelegate)
		OvlK_ReUse = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'OvlK_ReUse'), typeof(OvlK_ReUseDelegate)) cast OvlK_ReUseDelegate)
		StmK_Init = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'StmK_Init'), typeof(StmK_InitDelegate)) cast StmK_InitDelegate)
		StmK_Free = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'StmK_Free'), typeof(StmK_FreeDelegate)) cast StmK_FreeDelegate)
		StmK_Start = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'StmK_Start'), typeof(StmK_StartDelegate)) cast StmK_StartDelegate)
		StmK_Stop = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'StmK_Stop'), typeof(StmK_StopDelegate)) cast StmK_StopDelegate)
		StmK_Read = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'StmK_Read'), typeof(StmK_ReadDelegate)) cast StmK_ReadDelegate)
		StmK_Write = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'StmK_Write'), typeof(StmK_WriteDelegate)) cast StmK_WriteDelegate)
		IsoK_Init = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'IsoK_Init'), typeof(IsoK_InitDelegate)) cast IsoK_InitDelegate)
		IsoK_Free = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'IsoK_Free'), typeof(IsoK_FreeDelegate)) cast IsoK_FreeDelegate)
		IsoK_SetPackets = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'IsoK_SetPackets'), typeof(IsoK_SetPacketsDelegate)) cast IsoK_SetPacketsDelegate)
		IsoK_SetPacket = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'IsoK_SetPacket'), typeof(IsoK_SetPacketDelegate)) cast IsoK_SetPacketDelegate)
		IsoK_GetPacket = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'IsoK_GetPacket'), typeof(IsoK_GetPacketDelegate)) cast IsoK_GetPacketDelegate)
		IsoK_EnumPackets = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'IsoK_EnumPackets'), typeof(IsoK_EnumPacketsDelegate)) cast IsoK_EnumPacketsDelegate)
		IsoK_ReUse = (Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, 'IsoK_ReUse'), typeof(IsoK_ReUseDelegate)) cast IsoK_ReUseDelegate)

	
	[DllImport('kernel32.dll')]
	private static def LoadLibraryEx(lpFileName as string, hReservedNull as IntPtr, dwFlags as LoadLibraryFlags) as IntPtr:
		pass

	
	private static final mModuleLibusbK as IntPtr = IntPtr.Zero
	
	#endregion


#endregion

#region Enumerations

public enum USBD_PIPE_TYPE:

	UsbdPipeTypeControl

	
	UsbdPipeTypeIsochronous

	
	UsbdPipeTypeBulk

	
	UsbdPipeTypeInterrupt


[Flags]
public enum KISO_FLAG:

	NONE = 0

	
	SET_START_FRAME = 1


public enum KLIB_HANDLE_TYPE:

	HOTK

	
	USBK

	
	USBSHAREDK

	
	LSTK

	
	LSTINFOK

	
	OVLK

	
	OVLPOOLK

	
	STMK

	
	COUNT


[Flags]
public enum KLST_SYNC_FLAG:

	NONE = 0

	
	UNCHANGED = 1

	
	ADDED = 2

	
	REMOVED = 4

	
	CONNECT_CHANGE = 8

	
	MASK = 15


[Flags]
public enum KLST_FLAG:

	NONE = 0

	
	INCLUDE_RAWGUID = 1

	
	INCLUDE_DISCONNECT = 2


public enum BMREQUEST_DIR:

	HOST_TO_DEVICE = 0

	DEVICE_TO_HOST = 1


public enum BMREQUEST_TYPE:

	STANDARD = 0

	
	CLASS = 1

	
	VENDOR = 2


public enum BMREQUEST_RECIPIENT:

	DEVICE = 0

	
	INTERFACE = 1

	
	ENDPOINT = 2

	
	OTHER = 3


public enum USB_GETSTATUS:

	SELF_POWERED = 1

	
	REMOTE_WAKEUP_ENABLED = 2


public enum USB_DESCRIPTOR_TYPE:

	DEVICE = 1

	
	CONFIGURATION = 2

	
	STRING = 3

	
	INTERFACE = 4

	
	ENDPOINT = 5

	
	DEVICE_QUALIFIER = 6

	
	CONFIG_POWER = 7

	
	INTERFACE_POWER = 8

	
	INTERFACE_ASSOCIATION = 11


public enum KUSB_PROPERTY:

	DEVICE_FILE_HANDLE

	
	COUNT


public enum KUSB_DRVID:

	LIBUSBK

	
	LIBUSB0

	
	WINUSB

	
	LIBUSB0_FILTER

	
	COUNT


public enum KUSB_FNID:

	Init

	
	Free

	
	ClaimInterface

	
	ReleaseInterface

	
	SetAltInterface

	
	GetAltInterface

	
	GetDescriptor

	
	ControlTransfer

	
	SetPowerPolicy

	
	GetPowerPolicy

	
	SetConfiguration

	
	GetConfiguration

	
	ResetDevice

	
	Initialize

	
	SelectInterface

	
	GetAssociatedInterface

	
	Clone

	
	QueryInterfaceSettings

	
	QueryDeviceInformation

	
	SetCurrentAlternateSetting

	
	GetCurrentAlternateSetting

	
	QueryPipe

	
	SetPipePolicy

	
	GetPipePolicy

	
	ReadPipe

	
	WritePipe

	
	ResetPipe

	
	AbortPipe

	
	FlushPipe

	
	IsoReadPipe

	
	IsoWritePipe

	
	GetCurrentFrameNumber

	
	GetOverlappedResult

	
	GetProperty

	
	
	COUNT


[Flags]
public enum KHOT_FLAG:

	NONE

	
	PLUG_ALL_ON_INIT = 1

	
	PASS_DUPE_INSTANCE = 2

	
	POST_USER_MESSAGE = 4


[Flags]
public enum KOVL_WAIT_FLAG:

	NONE = 0

	
	RELEASE_ON_SUCCESS = 1

	
	RELEASE_ON_FAIL = 2

	
	RELEASE_ON_SUCCESS_FAIL = 3

	
	CANCEL_ON_TIMEOUT = 4

	
	RELEASE_ON_TIMEOUT = 12

	
	RELEASE_ALWAYS = 15

	
	ALERTABLE = 16


[Flags]
public enum KOVL_POOL_FLAG:

	NONE = 0


[Flags]
public enum KSTM_FLAG(uint):

	NONE = 0

	NO_PARTIAL_XFERS = 1048576

	TIMEOUT_MASK = 131071


public enum KSTM_COMPLETE_RESULT:

	VALID = 0

	
	INVALID


#endregion

#region Structs

[StructLayout(LayoutKind.Sequential, CharSet: CharSet.Ansi)]
public struct WINUSB_PIPE_INFORMATION:

	public PipeType as USBD_PIPE_TYPE

	
	public PipeId as byte

	
	public MaximumPacketSize as ushort

	
	public Interval as byte

	
	
	public override def ToString() as string:
		return string.Format('PipeType: {0}\nPipeId: {1}\nMaximumPacketSize: {2}\nInterval: {3}\n', PipeType, (PipeId.ToString('X2') + 'h'), MaximumPacketSize, (Interval.ToString('X2') + 'h'))


[StructLayout(LayoutKind.Sequential, CharSet: CharSet.Ansi, Pack: 1)]
public struct WINUSB_SETUP_PACKET:

	public RequestType as byte

	
	public Request as byte

	
	public Value as ushort

	
	public Index as ushort

	
	public Length as ushort

	
	
	public override def ToString() as string:
		return string.Format('RequestType: {0}\nRequest: {1}\nValue: {2}\nIndex: {3}\nLength: {4}\n', (RequestType.ToString('X2') + 'h'), (Request.ToString('X2') + 'h'), (Value.ToString('X4') + 'h'), (Index.ToString('X4') + 'h'), Length)


[StructLayout(LayoutKind.Sequential, CharSet: CharSet.Ansi, Pack: 1)]
public struct KISO_PACKET:

	public Offset as int

	
	public Length as ushort

	
	public Status as ushort

	
	
	public override def ToString() as string:
		return string.Format('Offset: {0}\nLength: {1}\nStatus: {2}\n', Offset, Length, (Status.ToString('X4') + 'h'))


[StructLayout(LayoutKind.Sequential)]
public struct KISO_CONTEXT:

	private final mHandlePtr as IntPtr

	
	public def constructor(Handle as IntPtr):
		mHandlePtr = Handle

	
	public Pointer as IntPtr:
		get:
			return mHandlePtr

	
	[StructLayout(LayoutKind.Sequential, CharSet: CharSet.Ansi, Pack: 1)]
	private struct KISO_CONTEXT_MAP:

		private final Flags as KISO_FLAG

		
		private final StartFrame as int

		
		private final ErrorCount as short

		
		private final NumberOfPackets as short

		
		private final UrbHdrStatus as int

	
	private static final ofsFlags as int = Marshal.OffsetOf(typeof(KISO_CONTEXT_MAP), 'Flags').ToInt32()

	private static final ofsStartFrame as int = Marshal.OffsetOf(typeof(KISO_CONTEXT_MAP), 'StartFrame').ToInt32()

	private static final ofsErrorCount as int = Marshal.OffsetOf(typeof(KISO_CONTEXT_MAP), 'ErrorCount').ToInt32()

	private static final ofsNumberOfPackets as int = Marshal.OffsetOf(typeof(KISO_CONTEXT_MAP), 'NumberOfPackets').ToInt32()

	private static final ofsUrbHdrStatus as int = Marshal.OffsetOf(typeof(KISO_CONTEXT_MAP), 'UrbHdrStatus').ToInt32()

	
	
	public Flags as KISO_FLAG:
		get:
			return (Marshal.ReadInt32(mHandlePtr, ofsFlags) cast KISO_FLAG)

	
	
	public StartFrame as int:
		get:
			return Marshal.ReadInt32(mHandlePtr, ofsStartFrame)

	
	
	public ErrorCount as short:
		get:
			return Marshal.ReadInt16(mHandlePtr, ofsErrorCount)

	
	
	public NumberOfPackets as short:
		get:
			return Marshal.ReadInt16(mHandlePtr, ofsNumberOfPackets)

	
	
	public UrbHdrStatus as int:
		get:
			return Marshal.ReadInt32(mHandlePtr, ofsUrbHdrStatus)

	
	
	public override def ToString() as string:
		return string.Format('Flags: {0}\nStartFrame: {1}\nErrorCount: {2}\nNumberOfPackets: {3}\nUrbHdrStatus: {4}\n', Flags.ToString(), StartFrame, ErrorCount, NumberOfPackets, (UrbHdrStatus.ToString('X8') + 'h'))


[StructLayout(LayoutKind.Sequential, CharSet: CharSet.Ansi)]
public struct KLIB_VERSION:

	public Major as int

	
	public Minor as int

	
	public Micro as int

	
	public Nano as int

	
	public override def ToString() as string:
		return string.Format('Major: {0}\nMinor: {1}\nMicro: {2}\nNano: {3}\n', Major, Minor, Micro, Nano)


[StructLayout(LayoutKind.Sequential, CharSet: CharSet.Ansi)]
public struct KLST_DEV_COMMON_INFO:

	public Vid as int

	
	public Pid as int

	
	public MI as int

	
	// An ID that uniquely identifies a USB device.
	[MarshalAs(UnmanagedType.ByValTStr, SizeConst: AllKConstants.KLST_STRING_MAX_LEN)]
	public InstanceID as string

	
	
	public override def ToString() as string:
		return string.Format('Vid: {0}\nPid: {1}\nMI: {2}\nInstanceID: {3}\n', (Vid.ToString('X4') + 'h'), (Pid.ToString('X4') + 'h'), (MI.ToString('X2') + 'h'), InstanceID)


[StructLayout(LayoutKind.Sequential)]
public struct KLST_DEVINFO_HANDLE(IKLIB_HANDLE):

	private final mHandlePtr as IntPtr

	
	public def constructor(Handle as IntPtr):
		mHandlePtr = Handle

	
	public Pointer as IntPtr:
		get:
			return mHandlePtr

	
	public HandleType as KLIB_HANDLE_TYPE:
		get:
			return KLIB_HANDLE_TYPE.LSTINFOK

	
	public def GetContext() as IntPtr:
		return AllKFunctions.LibK_GetContext(mHandlePtr, HandleType)

	
	public def SetContext(UserContext as IntPtr) as bool:
		return AllKFunctions.LibK_SetContext(mHandlePtr, HandleType, UserContext)

	
	public def SetCleanupCallback(CleanupCallback as KLIB_HANDLE_CLEANUP_CB) as bool:
		return AllKFunctions.LibK_SetCleanupCallback(mHandlePtr, HandleType, CleanupCallback)

	
	[StructLayout(LayoutKind.Sequential, CharSet: CharSet.Ansi)]
	private struct KLST_DEVINFO_MAP:

		private final Common as KLST_DEV_COMMON_INFO

		
		private final DriverID as int

		
		[MarshalAs(UnmanagedType.ByValTStr, SizeConst: AllKConstants.KLST_STRING_MAX_LEN)]
		private final DeviceInterfaceGUID as string

		
		[MarshalAs(UnmanagedType.ByValTStr, SizeConst: AllKConstants.KLST_STRING_MAX_LEN)]
		private final DeviceID as string

		
		[MarshalAs(UnmanagedType.ByValTStr, SizeConst: AllKConstants.KLST_STRING_MAX_LEN)]
		private final ClassGUID as string

		
		[MarshalAs(UnmanagedType.ByValTStr, SizeConst: AllKConstants.KLST_STRING_MAX_LEN)]
		private final Mfg as string

		
		[MarshalAs(UnmanagedType.ByValTStr, SizeConst: AllKConstants.KLST_STRING_MAX_LEN)]
		private final DeviceDesc as string

		
		[MarshalAs(UnmanagedType.ByValTStr, SizeConst: AllKConstants.KLST_STRING_MAX_LEN)]
		private final Service as string

		
		[MarshalAs(UnmanagedType.ByValTStr, SizeConst: AllKConstants.KLST_STRING_MAX_LEN)]
		private final SymbolicLink as string

		
		[MarshalAs(UnmanagedType.ByValTStr, SizeConst: AllKConstants.KLST_STRING_MAX_LEN)]
		private final DevicePath as string

		
		private final LUsb0FilterIndex as int

		
		private final Connected as bool

		
		private final SyncFlags as KLST_SYNC_FLAG

		
		private final BusNumber as int

		
		private final DeviceAddress as int

		
		[MarshalAs(UnmanagedType.ByValTStr, SizeConst: AllKConstants.KLST_STRING_MAX_LEN)]
		private final SerialNumber as string

	
	private static final ofsCommon as int = Marshal.OffsetOf(typeof(KLST_DEVINFO_MAP), 'Common').ToInt32()

	private static final ofsDriverID as int = Marshal.OffsetOf(typeof(KLST_DEVINFO_MAP), 'DriverID').ToInt32()

	private static final ofsDeviceInterfaceGUID as int = Marshal.OffsetOf(typeof(KLST_DEVINFO_MAP), 'DeviceInterfaceGUID').ToInt32()

	private static final ofsDeviceID as int = Marshal.OffsetOf(typeof(KLST_DEVINFO_MAP), 'DeviceID').ToInt32()

	private static final ofsClassGUID as int = Marshal.OffsetOf(typeof(KLST_DEVINFO_MAP), 'ClassGUID').ToInt32()

	private static final ofsMfg as int = Marshal.OffsetOf(typeof(KLST_DEVINFO_MAP), 'Mfg').ToInt32()

	private static final ofsDeviceDesc as int = Marshal.OffsetOf(typeof(KLST_DEVINFO_MAP), 'DeviceDesc').ToInt32()

	private static final ofsService as int = Marshal.OffsetOf(typeof(KLST_DEVINFO_MAP), 'Service').ToInt32()

	private static final ofsSymbolicLink as int = Marshal.OffsetOf(typeof(KLST_DEVINFO_MAP), 'SymbolicLink').ToInt32()

	private static final ofsDevicePath as int = Marshal.OffsetOf(typeof(KLST_DEVINFO_MAP), 'DevicePath').ToInt32()

	private static final ofsLUsb0FilterIndex as int = Marshal.OffsetOf(typeof(KLST_DEVINFO_MAP), 'LUsb0FilterIndex').ToInt32()

	private static final ofsConnected as int = Marshal.OffsetOf(typeof(KLST_DEVINFO_MAP), 'Connected').ToInt32()

	private static final ofsSyncFlags as int = Marshal.OffsetOf(typeof(KLST_DEVINFO_MAP), 'SyncFlags').ToInt32()

	private static final ofsBusNumber as int = Marshal.OffsetOf(typeof(KLST_DEVINFO_MAP), 'BusNumber').ToInt32()

	private static final ofsDeviceAddress as int = Marshal.OffsetOf(typeof(KLST_DEVINFO_MAP), 'DeviceAddress').ToInt32()

	private static final ofsSerialNumber as int = Marshal.OffsetOf(typeof(KLST_DEVINFO_MAP), 'SerialNumber').ToInt32()

	
	
	public Common as KLST_DEV_COMMON_INFO:
		get:
			return (Marshal.PtrToStructure(IntPtr((mHandlePtr.ToInt64() + ofsCommon)), typeof(KLST_DEV_COMMON_INFO)) cast KLST_DEV_COMMON_INFO)

	
	
	public DriverID as int:
		get:
			return Marshal.ReadInt32(mHandlePtr, ofsDriverID)

	
	
	public DeviceInterfaceGUID as string:
		get:
			return Marshal.PtrToStringAnsi(IntPtr((mHandlePtr.ToInt64() + ofsDeviceInterfaceGUID)))

	
	
	public DeviceID as string:
		get:
			return Marshal.PtrToStringAnsi(IntPtr((mHandlePtr.ToInt64() + ofsDeviceID)))

	
	
	public ClassGUID as string:
		get:
			return Marshal.PtrToStringAnsi(IntPtr((mHandlePtr.ToInt64() + ofsClassGUID)))

	
	
	public Mfg as string:
		get:
			return Marshal.PtrToStringAnsi(IntPtr((mHandlePtr.ToInt64() + ofsMfg)))

	
	
	public DeviceDesc as string:
		get:
			return Marshal.PtrToStringAnsi(IntPtr((mHandlePtr.ToInt64() + ofsDeviceDesc)))

	
	
	public Service as string:
		get:
			return Marshal.PtrToStringAnsi(IntPtr((mHandlePtr.ToInt64() + ofsService)))

	
	
	public SymbolicLink as string:
		get:
			return Marshal.PtrToStringAnsi(IntPtr((mHandlePtr.ToInt64() + ofsSymbolicLink)))

	
	
	public DevicePath as string:
		get:
			return Marshal.PtrToStringAnsi(IntPtr((mHandlePtr.ToInt64() + ofsDevicePath)))

	
	
	public LUsb0FilterIndex as int:
		get:
			return Marshal.ReadInt32(mHandlePtr, ofsLUsb0FilterIndex)

	
	
	public Connected as bool:
		get:
			return (Marshal.ReadInt32(mHandlePtr, ofsConnected) != 0)

	
	
	public SyncFlags as KLST_SYNC_FLAG:
		get:
			return (Marshal.ReadInt32(mHandlePtr, ofsSyncFlags) cast KLST_SYNC_FLAG)

	
	
	public BusNumber as int:
		get:
			return Marshal.ReadInt32(mHandlePtr, ofsBusNumber)

	
	
	public DeviceAddress as int:
		get:
			return Marshal.ReadInt32(mHandlePtr, ofsDeviceAddress)

	
	
	public SerialNumber as string:
		get:
			return Marshal.PtrToStringAnsi(IntPtr((mHandlePtr.ToInt64() + ofsSerialNumber)))

	
	
	public override def ToString() as string:
		return string.Format('DriverID: {0}\nDeviceInterfaceGUID: {1}\nDeviceID: {2}\nClassGUID: {3}\nMfg: {4}\nDeviceDesc: {5}\nService: {6}\nSymbolicLink: {7}\nDevicePath: {8}\nLUsb0FilterIndex: {9}\nConnected: {10}\nSyncFlags: {11}\nBusNumber: {12}\nDeviceAddress: {13}\nSerialNumber: {14}\n', DriverID, DeviceInterfaceGUID, DeviceID, ClassGUID, Mfg, DeviceDesc, Service, SymbolicLink, DevicePath, LUsb0FilterIndex, Connected, SyncFlags.ToString(), BusNumber, DeviceAddress, SerialNumber)


[StructLayout(LayoutKind.Sequential, CharSet: CharSet.Ansi, Size: 1024)]
public struct KLST_PATTERN_MATCH:

	[MarshalAs(UnmanagedType.ByValTStr, SizeConst: AllKConstants.KLST_STRING_MAX_LEN)]
	public DeviceID as string

	
	[MarshalAs(UnmanagedType.ByValTStr, SizeConst: AllKConstants.KLST_STRING_MAX_LEN)]
	public DeviceInterfaceGUID as string

	
	[MarshalAs(UnmanagedType.ByValTStr, SizeConst: AllKConstants.KLST_STRING_MAX_LEN)]
	public ClassGUID as string

	
	
	public override def ToString() as string:
		return string.Format('DeviceID: {0}\nDeviceInterfaceGUID: {1}\nClassGUID: {2}\n', DeviceID, DeviceInterfaceGUID, ClassGUID)


[StructLayout(LayoutKind.Sequential, CharSet: CharSet.Ansi, Pack: 1)]
public struct USB_DEVICE_DESCRIPTOR:

	public bLength as byte

	
	public bDescriptorType as byte

	
	public bcdUSB as ushort

	
	public bDeviceClass as byte

	
	public bDeviceSubClass as byte

	
	public bDeviceProtocol as byte

	
	public bMaxPacketSize0 as byte

	
	public idVendor as ushort

	
	public idProduct as ushort

	
	public bcdDevice as ushort

	
	public iManufacturer as byte

	
	public iProduct as byte

	
	public iSerialNumber as byte

	
	public bNumConfigurations as byte

	
	
	public override def ToString() as string:
		return string.Format('bLength: {0}\nbDescriptorType: {1}\nbcdUSB: {2}\nbDeviceClass: {3}\nbDeviceSubClass: {4}\nbDeviceProtocol: {5}\nbMaxPacketSize0: {6}\nidVendor: {7}\nidProduct: {8}\nbcdDevice: {9}\niManufacturer: {10}\niProduct: {11}\niSerialNumber: {12}\nbNumConfigurations: {13}\n', bLength, (bDescriptorType.ToString('X2') + 'h'), (bcdUSB.ToString('X4') + 'h'), (bDeviceClass.ToString('X2') + 'h'), (bDeviceSubClass.ToString('X2') + 'h'), (bDeviceProtocol.ToString('X2') + 'h'), bMaxPacketSize0, (idVendor.ToString('X4') + 'h'), (idProduct.ToString('X4') + 'h'), (bcdDevice.ToString('X4') + 'h'), iManufacturer, iProduct, iSerialNumber, bNumConfigurations)


[StructLayout(LayoutKind.Sequential, CharSet: CharSet.Ansi, Pack: 1)]
public struct USB_ENDPOINT_DESCRIPTOR:

	public bLength as byte

	
	public bDescriptorType as byte

	
	public bEndpointAddress as byte

	
	public bmAttributes as byte

	
	public wMaxPacketSize as ushort

	
	public bInterval as byte

	
	
	public override def ToString() as string:
		return string.Format('bLength: {0}\nbDescriptorType: {1}\nbEndpointAddress: {2}\nbmAttributes: {3}\nwMaxPacketSize: {4}\nbInterval: {5}\n', bLength, (bDescriptorType.ToString('X2') + 'h'), (bEndpointAddress.ToString('X2') + 'h'), (bmAttributes.ToString('X2') + 'h'), wMaxPacketSize, bInterval)


[StructLayout(LayoutKind.Sequential, CharSet: CharSet.Ansi, Pack: 1)]
public struct USB_CONFIGURATION_DESCRIPTOR:

	public bLength as byte

	
	public bDescriptorType as byte

	
	public wTotalLength as ushort

	
	public bNumInterfaces as byte

	
	public bConfigurationValue as byte

	
	public iConfiguration as byte

	
	public bmAttributes as byte

	
	public MaxPower as byte

	
	public override def ToString() as string:
		return string.Format('bLength: {0}\nbDescriptorType: {1}\nwTotalLength: {2}\nbNumInterfaces: {3}\nbConfigurationValue: {4}\niConfiguration: {5}\nbmAttributes: {6}\nMaxPower: {7}\n', bLength, (bDescriptorType.ToString('X2') + 'h'), wTotalLength, bNumInterfaces, bConfigurationValue, iConfiguration, (bmAttributes.ToString('X2') + 'h'), MaxPower)


[StructLayout(LayoutKind.Sequential, CharSet: CharSet.Ansi, Pack: 1)]
public struct USB_INTERFACE_DESCRIPTOR:

	public bLength as byte

	
	public bDescriptorType as byte

	
	public bInterfaceNumber as byte

	
	public bAlternateSetting as byte

	
	public bNumEndpoints as byte

	
	public bInterfaceClass as byte

	
	public bInterfaceSubClass as byte

	
	public bInterfaceProtocol as byte

	
	public iInterface as byte

	
	
	public override def ToString() as string:
		return string.Format('bLength: {0}\nbDescriptorType: {1}\nbInterfaceNumber: {2}\nbAlternateSetting: {3}\nbNumEndpoints: {4}\nbInterfaceClass: {5}\nbInterfaceSubClass: {6}\nbInterfaceProtocol: {7}\niInterface: {8}\n', bLength, (bDescriptorType.ToString('X2') + 'h'), bInterfaceNumber, bAlternateSetting, bNumEndpoints, (bInterfaceClass.ToString('X2') + 'h'), (bInterfaceSubClass.ToString('X2') + 'h'), (bInterfaceProtocol.ToString('X2') + 'h'), iInterface)


[StructLayout(LayoutKind.Sequential, CharSet: CharSet.Unicode, Pack: 1)]
public struct USB_STRING_DESCRIPTOR:

	public bLength as byte

	
	public bDescriptorType as byte

	
	[MarshalAs(UnmanagedType.ByValTStr, SizeConst: AllKConstants.KLST_STRING_MAX_LEN)]
	public bString as string

	
	
	public override def ToString() as string:
		return string.Format('bLength: {0}\nbDescriptorType: {1}\nbString: {2}\n', bLength, (bDescriptorType.ToString('X2') + 'h'), bString)


[StructLayout(LayoutKind.Sequential, CharSet: CharSet.Ansi, Pack: 1)]
public struct USB_COMMON_DESCRIPTOR:

	public bLength as byte

	
	public bDescriptorType as byte

	
	
	public override def ToString() as string:
		return string.Format('bLength: {0}\nbDescriptorType: {1}\n', bLength, (bDescriptorType.ToString('X2') + 'h'))


[StructLayout(LayoutKind.Sequential, CharSet: CharSet.Ansi, Pack: 1)]
public struct USB_INTERFACE_ASSOCIATION_DESCRIPTOR:

	public bLength as byte

	
	public bDescriptorType as byte

	
	public bFirstInterface as byte

	
	public bInterfaceCount as byte

	
	public bFunctionClass as byte

	
	public bFunctionSubClass as byte

	
	public bFunctionProtocol as byte

	
	public iFunction as byte

	
	
	public override def ToString() as string:
		return string.Format('bLength: {0}\nbDescriptorType: {1}\nbFirstInterface: {2}\nbInterfaceCount: {3}\nbFunctionClass: {4}\nbFunctionSubClass: {5}\nbFunctionProtocol: {6}\niFunction: {7}\n', bLength, (bDescriptorType.ToString('X2') + 'h'), bFirstInterface, bInterfaceCount, (bFunctionClass.ToString('X2') + 'h'), (bFunctionSubClass.ToString('X2') + 'h'), (bFunctionProtocol.ToString('X2') + 'h'), iFunction)


[StructLayout(LayoutKind.Sequential, CharSet: CharSet.Ansi)]
public struct KUSB_DRIVER_API_INFO:

	public DriverID as int

	
	public FunctionCount as int

	
	
	public override def ToString() as string:
		return string.Format('DriverID: {0}\nFunctionCount: {1}\n', DriverID, FunctionCount)


[StructLayout(LayoutKind.Sequential, CharSet: CharSet.Ansi, Size: 512)]
public struct KUSB_DRIVER_API:

	public Info as KUSB_DRIVER_API_INFO

	
	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public Init as KUSB_InitDelegate

	
	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public Free as KUSB_FreeDelegate

	
	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public ClaimInterface as KUSB_ClaimInterfaceDelegate

	
	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public ReleaseInterface as KUSB_ReleaseInterfaceDelegate

	
	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public SetAltInterface as KUSB_SetAltInterfaceDelegate

	
	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public GetAltInterface as KUSB_GetAltInterfaceDelegate

	
	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public GetDescriptor as KUSB_GetDescriptorDelegate

	
	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public ControlTransfer as KUSB_ControlTransferDelegate

	
	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public SetPowerPolicy as KUSB_SetPowerPolicyDelegate

	
	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public GetPowerPolicy as KUSB_GetPowerPolicyDelegate

	
	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public SetConfiguration as KUSB_SetConfigurationDelegate

	
	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public GetConfiguration as KUSB_GetConfigurationDelegate

	
	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public ResetDevice as KUSB_ResetDeviceDelegate

	
	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public Initialize as KUSB_InitializeDelegate

	
	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public SelectInterface as KUSB_SelectInterfaceDelegate

	
	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public GetAssociatedInterface as KUSB_GetAssociatedInterfaceDelegate

	
	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public Clone as KUSB_CloneDelegate

	
	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public QueryInterfaceSettings as KUSB_QueryInterfaceSettingsDelegate

	
	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public QueryDeviceInformation as KUSB_QueryDeviceInformationDelegate

	
	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public SetCurrentAlternateSetting as KUSB_SetCurrentAlternateSettingDelegate

	
	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public GetCurrentAlternateSetting as KUSB_GetCurrentAlternateSettingDelegate

	
	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public QueryPipe as KUSB_QueryPipeDelegate

	
	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public SetPipePolicy as KUSB_SetPipePolicyDelegate

	
	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public GetPipePolicy as KUSB_GetPipePolicyDelegate

	
	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public ReadPipe as KUSB_ReadPipeDelegate

	
	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public WritePipe as KUSB_WritePipeDelegate

	
	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public ResetPipe as KUSB_ResetPipeDelegate

	
	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public AbortPipe as KUSB_AbortPipeDelegate

	
	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public FlushPipe as KUSB_FlushPipeDelegate

	
	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public IsoReadPipe as KUSB_IsoReadPipeDelegate

	
	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public IsoWritePipe as KUSB_IsoWritePipeDelegate

	
	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public GetCurrentFrameNumber as KUSB_GetCurrentFrameNumberDelegate

	
	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public GetOverlappedResult as KUSB_GetOverlappedResultDelegate

	
	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public GetProperty as KUSB_GetPropertyDelegate


[StructLayout(LayoutKind.Sequential, CharSet: CharSet.Ansi, Size: 2048)]
public struct KHOT_PARAMS:

	public UserHwnd as IntPtr

	
	public UserMessage as int

	
	public Flags as KHOT_FLAG

	
	public PatternMatch as KLST_PATTERN_MATCH

	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public OnHotPlug as KHOT_PLUG_CB

	
	
	public override def ToString() as string:
		return string.Format('UserHwnd: {0}\nUserMessage: {1}\nFlags: {2}\n', (UserHwnd.ToString('X16') + 'h'), (UserMessage.ToString('X8') + 'h'), Flags.ToString())


[StructLayout(LayoutKind.Sequential)]
public struct KSTM_XFER_CONTEXT:

	private final mHandlePtr as IntPtr

	
	public def constructor(Handle as IntPtr):
		mHandlePtr = Handle

	
	public Pointer as IntPtr:
		get:
			return mHandlePtr

	
	[StructLayout(LayoutKind.Sequential, CharSet: CharSet.Ansi)]
	private struct KSTM_XFER_CONTEXT_MAP:

		private final Buffer as IntPtr

		
		private final BufferSize as int

		
		private final TransferLength as int

		
		private final UserState as IntPtr

	
	private static final ofsBuffer as int = Marshal.OffsetOf(typeof(KSTM_XFER_CONTEXT_MAP), 'Buffer').ToInt32()

	private static final ofsBufferSize as int = Marshal.OffsetOf(typeof(KSTM_XFER_CONTEXT_MAP), 'BufferSize').ToInt32()

	private static final ofsTransferLength as int = Marshal.OffsetOf(typeof(KSTM_XFER_CONTEXT_MAP), 'TransferLength').ToInt32()

	private static final ofsUserState as int = Marshal.OffsetOf(typeof(KSTM_XFER_CONTEXT_MAP), 'UserState').ToInt32()

	
	
	public Buffer as IntPtr:
		get:
			return Marshal.ReadIntPtr(mHandlePtr, ofsBuffer)

	
	
	public BufferSize as int:
		get:
			return Marshal.ReadInt32(mHandlePtr, ofsBufferSize)

	
	
	public TransferLength as int:
		get:
			return Marshal.ReadInt32(mHandlePtr, ofsTransferLength)

	
	
	public UserState as IntPtr:
		get:
			return Marshal.ReadIntPtr(mHandlePtr, ofsUserState)
		set:
			Marshal.WriteIntPtr(mHandlePtr, ofsUserState, value)

	
	
	public override def ToString() as string:
		return string.Format('Buffer: {0}\nBufferSize: {1}\nTransferLength: {2}\nUserState: {3}\n', (Buffer.ToString('X16') + 'h'), BufferSize, TransferLength, (UserState.ToString('X16') + 'h'))


[StructLayout(LayoutKind.Sequential)]
public struct KSTM_INFO:

	private final mHandlePtr as IntPtr

	
	public def constructor(Handle as IntPtr):
		mHandlePtr = Handle

	
	public Pointer as IntPtr:
		get:
			return mHandlePtr

	
	[StructLayout(LayoutKind.Sequential, CharSet: CharSet.Ansi)]
	private struct KSTM_INFO_MAP:

		private final UsbHandle as IntPtr

		
		private final PipeID as byte

		
		private final MaxPendingTransfers as int

		
		private final MaxTransferSize as int

		
		private final MaxPendingIO as int

		
		private final EndpointDescriptor as USB_ENDPOINT_DESCRIPTOR

		
		private final DriverAPI as KUSB_DRIVER_API

		
		private final DeviceHandle as IntPtr

		
		private final StreamHandle as IntPtr

		
		private final UserState as IntPtr

	
	private static final ofsUsbHandle as int = Marshal.OffsetOf(typeof(KSTM_INFO_MAP), 'UsbHandle').ToInt32()

	private static final ofsPipeID as int = Marshal.OffsetOf(typeof(KSTM_INFO_MAP), 'PipeID').ToInt32()

	private static final ofsMaxPendingTransfers as int = Marshal.OffsetOf(typeof(KSTM_INFO_MAP), 'MaxPendingTransfers').ToInt32()

	private static final ofsMaxTransferSize as int = Marshal.OffsetOf(typeof(KSTM_INFO_MAP), 'MaxTransferSize').ToInt32()

	private static final ofsMaxPendingIO as int = Marshal.OffsetOf(typeof(KSTM_INFO_MAP), 'MaxPendingIO').ToInt32()

	private static final ofsEndpointDescriptor as int = Marshal.OffsetOf(typeof(KSTM_INFO_MAP), 'EndpointDescriptor').ToInt32()

	private static final ofsDriverAPI as int = Marshal.OffsetOf(typeof(KSTM_INFO_MAP), 'DriverAPI').ToInt32()

	private static final ofsDeviceHandle as int = Marshal.OffsetOf(typeof(KSTM_INFO_MAP), 'DeviceHandle').ToInt32()

	private static final ofsStreamHandle as int = Marshal.OffsetOf(typeof(KSTM_INFO_MAP), 'StreamHandle').ToInt32()

	private static final ofsUserState as int = Marshal.OffsetOf(typeof(KSTM_INFO_MAP), 'UserState').ToInt32()

	
	
	public UsbHandle as IntPtr:
		get:
			return Marshal.ReadIntPtr(mHandlePtr, ofsUsbHandle)

	
	
	public PipeID as byte:
		get:
			return Marshal.ReadByte(mHandlePtr, ofsPipeID)

	
	
	public MaxPendingTransfers as int:
		get:
			return Marshal.ReadInt32(mHandlePtr, ofsMaxPendingTransfers)

	
	
	public MaxTransferSize as int:
		get:
			return Marshal.ReadInt32(mHandlePtr, ofsMaxTransferSize)

	
	
	public MaxPendingIO as int:
		get:
			return Marshal.ReadInt32(mHandlePtr, ofsMaxPendingIO)

	
	
	public EndpointDescriptor as USB_ENDPOINT_DESCRIPTOR:
		get:
			return (Marshal.PtrToStructure(IntPtr((mHandlePtr.ToInt64() + ofsEndpointDescriptor)), typeof(USB_ENDPOINT_DESCRIPTOR)) cast USB_ENDPOINT_DESCRIPTOR)

	
	
	public DriverAPI as KUSB_DRIVER_API:
		get:
			return (Marshal.PtrToStructure(IntPtr((mHandlePtr.ToInt64() + ofsDriverAPI)), typeof(KUSB_DRIVER_API)) cast KUSB_DRIVER_API)

	
	
	public DeviceHandle as IntPtr:
		get:
			return Marshal.ReadIntPtr(mHandlePtr, ofsDeviceHandle)

	
	
	public StreamHandle as IntPtr:
		get:
			return Marshal.ReadIntPtr(mHandlePtr, ofsStreamHandle)

	
	
	public UserState as IntPtr:
		get:
			return Marshal.ReadIntPtr(mHandlePtr, ofsUserState)
		set:
			Marshal.WriteIntPtr(mHandlePtr, ofsUserState, value)

	
	
	public override def ToString() as string:
		return string.Format('UsbHandle: {0}\nPipeID: {1}\nMaxPendingTransfers: {2}\nMaxTransferSize: {3}\nMaxPendingIO: {4}\nDeviceHandle: {5}\nStreamHandle: {6}\nUserState: {7}\n', (UsbHandle.ToString('X16') + 'h'), (PipeID.ToString('X2') + 'h'), MaxPendingTransfers, MaxTransferSize, MaxPendingIO, (DeviceHandle.ToString('X16') + 'h'), (StreamHandle.ToString('X16') + 'h'), (UserState.ToString('X16') + 'h'))


[StructLayout(LayoutKind.Sequential, CharSet: CharSet.Ansi, Size: 64)]
public struct KSTM_CALLBACK:

	[MarshalAs(UnmanagedType.FunctionPtr)]
	public Error as KSTM_ERROR_CB

	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public Submit as KSTM_SUBMIT_CB

	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public Complete as KSTM_COMPLETE_CB

	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public Started as KSTM_STARTED_CB

	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public Stopped as KSTM_STOPPED_CB

	
	[MarshalAs(UnmanagedType.FunctionPtr)]
	public BeforeComplete as KSTM_BEFORE_COMPLETE_CB


#endregion

#region Delegates

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KLIB_HANDLE_CLEANUP_CB([In] Handle as IntPtr, HandleType as KLIB_HANDLE_TYPE, UserContext as IntPtr) as int

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KISO_ENUM_PACKETS_CB(PacketIndex as int, [In] ref IsoPacket as KISO_PACKET, UserState as IntPtr) as bool

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KLST_ENUM_DEVINFO_CB([In] DeviceList as KLST_HANDLE, [In] DeviceInfo as KLST_DEVINFO_HANDLE, Context as IntPtr) as bool

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KUSB_InitDelegate([Out] ref InterfaceHandle as KUSB_HANDLE, [In] DevInfo as KLST_DEVINFO_HANDLE) as bool

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KUSB_FreeDelegate([In] InterfaceHandle as KUSB_HANDLE) as bool

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KUSB_ClaimInterfaceDelegate([In] InterfaceHandle as KUSB_HANDLE, NumberOrIndex as byte, IsIndex as bool) as bool

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KUSB_ReleaseInterfaceDelegate([In] InterfaceHandle as KUSB_HANDLE, NumberOrIndex as byte, IsIndex as bool) as bool

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KUSB_SetAltInterfaceDelegate([In] InterfaceHandle as KUSB_HANDLE, NumberOrIndex as byte, IsIndex as bool, AltSettingNumber as byte) as bool

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KUSB_GetAltInterfaceDelegate([In] InterfaceHandle as KUSB_HANDLE, NumberOrIndex as byte, IsIndex as bool, ref AltSettingNumber as byte) as bool

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KUSB_GetDescriptorDelegate([In] InterfaceHandle as KUSB_HANDLE, DescriptorType as byte, Index as byte, LanguageID as ushort, Buffer as IntPtr, BufferLength as int, ref LengthTransferred as int) as bool

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KUSB_ControlTransferDelegate([In] InterfaceHandle as KUSB_HANDLE, SetupPacket as WINUSB_SETUP_PACKET, Buffer as IntPtr, BufferLength as int, ref LengthTransferred as int, Overlapped as IntPtr) as bool

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KUSB_SetPowerPolicyDelegate([In] InterfaceHandle as KUSB_HANDLE, PolicyType as int, ValueLength as int, Value as IntPtr) as bool

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KUSB_GetPowerPolicyDelegate([In] InterfaceHandle as KUSB_HANDLE, PolicyType as int, ref ValueLength as int, Value as IntPtr) as bool

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KUSB_SetConfigurationDelegate([In] InterfaceHandle as KUSB_HANDLE, ConfigurationNumber as byte) as bool

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KUSB_GetConfigurationDelegate([In] InterfaceHandle as KUSB_HANDLE, ref ConfigurationNumber as byte) as bool

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KUSB_ResetDeviceDelegate([In] InterfaceHandle as KUSB_HANDLE) as bool

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KUSB_InitializeDelegate(DeviceHandle as IntPtr, [Out] ref InterfaceHandle as KUSB_HANDLE) as bool

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KUSB_SelectInterfaceDelegate([In] InterfaceHandle as KUSB_HANDLE, NumberOrIndex as byte, IsIndex as bool) as bool

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KUSB_GetAssociatedInterfaceDelegate([In] InterfaceHandle as KUSB_HANDLE, AssociatedInterfaceIndex as byte, [Out] ref AssociatedInterfaceHandle as KUSB_HANDLE) as bool

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KUSB_CloneDelegate([In] InterfaceHandle as KUSB_HANDLE, [Out] ref DstInterfaceHandle as KUSB_HANDLE) as bool

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KUSB_QueryInterfaceSettingsDelegate([In] InterfaceHandle as KUSB_HANDLE, AltSettingIndex as byte, [Out] ref UsbAltInterfaceDescriptor as USB_INTERFACE_DESCRIPTOR) as bool

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KUSB_QueryDeviceInformationDelegate([In] InterfaceHandle as KUSB_HANDLE, InformationType as int, ref BufferLength as int, Buffer as IntPtr) as bool

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KUSB_SetCurrentAlternateSettingDelegate([In] InterfaceHandle as KUSB_HANDLE, AltSettingNumber as byte) as bool

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KUSB_GetCurrentAlternateSettingDelegate([In] InterfaceHandle as KUSB_HANDLE, ref AltSettingNumber as byte) as bool

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KUSB_QueryPipeDelegate([In] InterfaceHandle as KUSB_HANDLE, AltSettingNumber as byte, PipeIndex as byte, [Out] ref PipeInformation as WINUSB_PIPE_INFORMATION) as bool

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KUSB_SetPipePolicyDelegate([In] InterfaceHandle as KUSB_HANDLE, PipeID as byte, PolicyType as int, ValueLength as int, Value as IntPtr) as bool

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KUSB_GetPipePolicyDelegate([In] InterfaceHandle as KUSB_HANDLE, PipeID as byte, PolicyType as int, ref ValueLength as int, Value as IntPtr) as bool

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KUSB_ReadPipeDelegate([In] InterfaceHandle as KUSB_HANDLE, PipeID as byte, Buffer as IntPtr, BufferLength as int, ref LengthTransferred as int, Overlapped as IntPtr) as bool

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KUSB_WritePipeDelegate([In] InterfaceHandle as KUSB_HANDLE, PipeID as byte, Buffer as IntPtr, BufferLength as int, ref LengthTransferred as int, Overlapped as IntPtr) as bool

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KUSB_ResetPipeDelegate([In] InterfaceHandle as KUSB_HANDLE, PipeID as byte) as bool

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KUSB_AbortPipeDelegate([In] InterfaceHandle as KUSB_HANDLE, PipeID as byte) as bool

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KUSB_FlushPipeDelegate([In] InterfaceHandle as KUSB_HANDLE, PipeID as byte) as bool

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KUSB_IsoReadPipeDelegate([In] InterfaceHandle as KUSB_HANDLE, PipeID as byte, Buffer as IntPtr, BufferLength as int, Overlapped as IntPtr, [In] IsoContext as KISO_CONTEXT) as bool

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KUSB_IsoWritePipeDelegate([In] InterfaceHandle as KUSB_HANDLE, PipeID as byte, Buffer as IntPtr, BufferLength as int, Overlapped as IntPtr, [In] IsoContext as KISO_CONTEXT) as bool

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KUSB_GetCurrentFrameNumberDelegate([In] InterfaceHandle as KUSB_HANDLE, ref FrameNumber as int) as bool

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KUSB_GetOverlappedResultDelegate([In] InterfaceHandle as KUSB_HANDLE, Overlapped as IntPtr, ref lpNumberOfBytesTransferred as int, bWait as bool) as bool

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KUSB_GetPropertyDelegate([In] InterfaceHandle as KUSB_HANDLE, PropertyType as KUSB_PROPERTY, ref PropertySize as int, Value as IntPtr) as bool

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KHOT_PLUG_CB([In] HotHandle as KHOT_HANDLE, [In] DeviceInfo as KLST_DEVINFO_HANDLE, PlugType as KLST_SYNC_FLAG) as void

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KSTM_ERROR_CB([In] StreamInfo as KSTM_INFO, [In] XferContext as KSTM_XFER_CONTEXT, XferContextIndex as int, ErrorCode as int) as int

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KSTM_SUBMIT_CB([In] StreamInfo as KSTM_INFO, [In] XferContext as KSTM_XFER_CONTEXT, XferContextIndex as int, Overlapped as IntPtr) as int

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KSTM_STARTED_CB([In] StreamInfo as KSTM_INFO, [In] XferContext as KSTM_XFER_CONTEXT, XferContextIndex as int) as int

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KSTM_STOPPED_CB([In] StreamInfo as KSTM_INFO, [In] XferContext as KSTM_XFER_CONTEXT, XferContextIndex as int) as int

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KSTM_COMPLETE_CB([In] StreamInfo as KSTM_INFO, [In] XferContext as KSTM_XFER_CONTEXT, XferContextIndex as int, ErrorCode as int) as int

[UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet: CharSet.Ansi, SetLastError: true)]
public callable KSTM_BEFORE_COMPLETE_CB([In] StreamInfo as KSTM_INFO, [In] XferContext as KSTM_XFER_CONTEXT, XferContextIndex as int, ref ErrorCode as int) as KSTM_COMPLETE_RESULT

#endregion

public class LstK(IDisposable):

	protected mHandleStruct as KLST_HANDLE

	protected mbDisposed as bool

	
	protected def constructor():
		pass

	
	#region IDisposable Members
	
	public virtual def Dispose():
		Dispose(true)
		GC.SuppressFinalize(self)

	
	#endregion
	
	def destructor():
		Dispose(false)

	
	protected virtual def Dispose(disposing as bool):
		if not mbDisposed:
			if mHandleStruct.Pointer != IntPtr.Zero:
				AllKFunctions.LstK_Free(mHandleStruct)
				Debug.Print('{0} Dispose: Freed Handle:{1:X16}h Explicit:{2}', GetType().Name, mHandleStruct.Pointer.ToInt64(), disposing)
			else:
				Debug.Print('{0} Dispose: [WARNING] Handle is null', GetType().Name)
			
			mHandleStruct = KLST_HANDLE(IntPtr.Zero)
			mbDisposed = true

	
	protected def Init(Flags as KLST_FLAG) as bool:
		success as bool = AllKFunctions.LstK_Init(mHandleStruct, Flags)
		
		if not success:
			raise Exception(string.Format('{0} failed initializing. ErrorCode={1:X8}h', GetType().Name, Marshal.GetLastWin32Error()))
		
		Debug.Print('{0} Init: handle 0x{1:X16}', GetType().Name, mHandleStruct.Pointer.ToInt64())
		return true

	
	protected def InitEx(Flags as KLST_FLAG, ref PatternMatch as KLST_PATTERN_MATCH) as bool:
		success as bool = AllKFunctions.LstK_InitEx(mHandleStruct, Flags, PatternMatch)
		
		if not success:
			raise Exception(string.Format('{0} failed initializing. ErrorCode={1:X8}h', GetType().Name, Marshal.GetLastWin32Error()))
		
		Debug.Print('{0} Init: handle 0x{1:X16}', GetType().Name, mHandleStruct.Pointer.ToInt64())
		return true

	
	#region Public Members
	
	public def constructor(Flags as KLST_FLAG):
		success as bool = AllKFunctions.LstK_Init(mHandleStruct, Flags)
		
		if not success:
			raise Exception(string.Format('{0} failed initializing. ErrorCode={1:X8}h', GetType().Name, Marshal.GetLastWin32Error()))
		
		Debug.Print('{0} Init: handle 0x{1:X16}', GetType().Name, mHandleStruct.Pointer.ToInt64())

	
	public def constructor(Flags as KLST_FLAG, ref PatternMatch as KLST_PATTERN_MATCH):
		success as bool = AllKFunctions.LstK_InitEx(mHandleStruct, Flags, PatternMatch)
		
		if not success:
			raise Exception(string.Format('{0} failed initializing. ErrorCode={1:X8}h', GetType().Name, Marshal.GetLastWin32Error()))
		
		Debug.Print('{0} Init: handle 0x{1:X16}', GetType().Name, mHandleStruct.Pointer.ToInt64())

	
	public virtual def Count(ref Count as int) as bool:
		return AllKFunctions.LstK_Count(mHandleStruct, Count)

	
	public virtual def Current(ref DeviceInfo as KLST_DEVINFO_HANDLE) as bool:
		return AllKFunctions.LstK_Current(mHandleStruct, DeviceInfo)

	
	public virtual def Enumerate(EnumDevListCB as KLST_ENUM_DEVINFO_CB, Context as IntPtr) as bool:
		return AllKFunctions.LstK_Enumerate(mHandleStruct, EnumDevListCB, Context)

	
	public virtual def FindByVidPid(Vid as int, Pid as int, ref DeviceInfo as KLST_DEVINFO_HANDLE) as bool:
		return AllKFunctions.LstK_FindByVidPid(mHandleStruct, Vid, Pid, DeviceInfo)

	
	public virtual def Free():
		Dispose()

	
	public Handle as KLST_HANDLE:
		get:
			return mHandleStruct

	
	public virtual def MoveNext(ref DeviceInfo as KLST_DEVINFO_HANDLE) as bool:
		return AllKFunctions.LstK_MoveNext(mHandleStruct, DeviceInfo)

	
	public virtual def MoveReset():
		AllKFunctions.LstK_MoveReset(mHandleStruct)
	
	#endregion


public class HotK(IDisposable):

	protected mHandleStruct as KHOT_HANDLE

	protected mbDisposed as bool

	
	protected def constructor():
		pass

	
	#region IDisposable Members
	
	public virtual def Dispose():
		Dispose(true)
		GC.SuppressFinalize(self)

	
	#endregion
	
	def destructor():
		Dispose(false)

	
	protected virtual def Dispose(disposing as bool):
		if not mbDisposed:
			if mHandleStruct.Pointer != IntPtr.Zero:
				AllKFunctions.HotK_Free(mHandleStruct)
				Debug.Print('{0} Dispose: Freed Handle:{1:X16}h Explicit:{2}', GetType().Name, mHandleStruct.Pointer.ToInt64(), disposing)
			else:
				Debug.Print('{0} Dispose: [WARNING] Handle is null', GetType().Name)
			
			mHandleStruct = KHOT_HANDLE(IntPtr.Zero)
			mbDisposed = true

	
	protected def Init(ref InitParams as KHOT_PARAMS) as bool:
		success as bool = AllKFunctions.HotK_Init(mHandleStruct, InitParams)
		
		if not success:
			raise Exception(string.Format('{0} failed initializing. ErrorCode={1:X8}h', GetType().Name, Marshal.GetLastWin32Error()))
		
		Debug.Print('{0} Init: handle 0x{1:X16}', GetType().Name, mHandleStruct.Pointer.ToInt64())
		return true

	
	#region Public Members
	
	public def constructor(ref InitParams as KHOT_PARAMS):
		success as bool = AllKFunctions.HotK_Init(mHandleStruct, InitParams)
		
		if not success:
			raise Exception(string.Format('{0} failed initializing. ErrorCode={1:X8}h', GetType().Name, Marshal.GetLastWin32Error()))
		
		Debug.Print('{0} Init: handle 0x{1:X16}', GetType().Name, mHandleStruct.Pointer.ToInt64())

	
	public virtual def Free():
		Dispose()

	
	public virtual def FreeAll():
		AllKFunctions.HotK_FreeAll()

	
	public Handle as KHOT_HANDLE:
		get:
			return mHandleStruct
	
	#endregion


public class UsbK(IDisposable):

	protected driverAPI as KUSB_DRIVER_API

	protected mHandleStruct as KUSB_HANDLE

	protected mbDisposed as bool

	
	protected def constructor():
		pass

	
	#region IDisposable Members
	
	public virtual def Dispose():
		Dispose(true)
		GC.SuppressFinalize(self)

	
	#endregion
	
	def destructor():
		Dispose(false)

	
	protected virtual def Dispose(disposing as bool):
		if not mbDisposed:
			if mHandleStruct.Pointer != IntPtr.Zero:
				AllKFunctions.UsbK_Free(mHandleStruct)
				Debug.Print('{0} Dispose: Freed Handle:{1:X16}h Explicit:{2}', GetType().Name, mHandleStruct.Pointer.ToInt64(), disposing)
			else:
				Debug.Print('{0} Dispose: [WARNING] Handle is null', GetType().Name)
			
			mHandleStruct = KUSB_HANDLE(IntPtr.Zero)
			mbDisposed = true

	
	protected def Init(DevInfo as KLST_DEVINFO_HANDLE) as bool:
		success as bool = AllKFunctions.LibK_LoadDriverAPI(driverAPI, DevInfo.DriverID)
		
		if not success:
			raise Exception(string.Format('{0} failed loading Driver API. ErrorCode={1:X8}h', GetType().Name, Marshal.GetLastWin32Error()))
		
		success = driverAPI.Init(mHandleStruct, DevInfo)
		
		if not success:
			raise Exception(string.Format('{0} failed initializing usb device. ErrorCode={1:X8}h', GetType().Name, Marshal.GetLastWin32Error()))
		
		Debug.Print('{0} Init: handle 0x{1:X16}', GetType().Name, mHandleStruct.Pointer.ToInt64())
		return true

	
	protected def Initialize(DeviceHandle as IntPtr, driverID as KUSB_DRVID) as bool:
		success as bool = AllKFunctions.LibK_LoadDriverAPI(driverAPI, (driverID cast int))
		
		if not success:
			raise Exception(string.Format('{0} failed loading Driver API. ErrorCode={1:X8}h', GetType().Name, Marshal.GetLastWin32Error()))
		
		success = driverAPI.Initialize(DeviceHandle, mHandleStruct)
		
		if not success:
			raise Exception(string.Format('{0} failed initializing usb device. ErrorCode={1:X8}h', GetType().Name, Marshal.GetLastWin32Error()))
		
		Debug.Print('{0} Init: handle 0x{1:X16}', GetType().Name, mHandleStruct.Pointer.ToInt64())
		return true

	
	#region Public Members
	
	public def constructor(DevInfo as KLST_DEVINFO_HANDLE):
		success as bool = AllKFunctions.LibK_LoadDriverAPI(driverAPI, DevInfo.DriverID)
		
		if not success:
			raise Exception(string.Format('{0} failed loading Driver API. ErrorCode={1:X8}h', GetType().Name, Marshal.GetLastWin32Error()))
		
		success = driverAPI.Init(mHandleStruct, DevInfo)
		
		if not success:
			raise Exception(string.Format('{0} failed initializing usb device. ErrorCode={1:X8}h', GetType().Name, Marshal.GetLastWin32Error()))
		
		Debug.Print('{0} Init: handle 0x{1:X16}', GetType().Name, mHandleStruct.Pointer.ToInt64())

	
	public def constructor(DeviceHandle as IntPtr, driverID as KUSB_DRVID):
		success as bool = AllKFunctions.LibK_LoadDriverAPI(driverAPI, (driverID cast int))
		
		if not success:
			raise Exception(string.Format('{0} failed loading Driver API. ErrorCode={1:X8}h', GetType().Name, Marshal.GetLastWin32Error()))
		
		success = driverAPI.Initialize(DeviceHandle, mHandleStruct)
		
		if not success:
			raise Exception(string.Format('{0} failed initializing usb device. ErrorCode={1:X8}h', GetType().Name, Marshal.GetLastWin32Error()))
		
		Debug.Print('{0} Init: handle 0x{1:X16}', GetType().Name, mHandleStruct.Pointer.ToInt64())

	
	public virtual def AbortPipe(PipeID as byte) as bool:
		return driverAPI.AbortPipe(mHandleStruct, PipeID)

	
	public virtual def ClaimInterface(NumberOrIndex as byte, IsIndex as bool) as bool:
		return driverAPI.ClaimInterface(mHandleStruct, NumberOrIndex, IsIndex)

	
	public virtual def Clone(ref DstInterfaceHandle as KUSB_HANDLE) as bool:
		return driverAPI.Clone(mHandleStruct, DstInterfaceHandle)

	
	public virtual def ControlTransfer(SetupPacket as WINUSB_SETUP_PACKET, Buffer as IntPtr, BufferLength as int, ref LengthTransferred as int, Overlapped as IntPtr) as bool:
		return driverAPI.ControlTransfer(mHandleStruct, SetupPacket, Buffer, BufferLength, LengthTransferred, Overlapped)

	
	public virtual def ControlTransfer(SetupPacket as WINUSB_SETUP_PACKET, Buffer as Array, BufferLength as int, ref LengthTransferred as int, Overlapped as IntPtr) as bool:
		return driverAPI.ControlTransfer(mHandleStruct, SetupPacket, Marshal.UnsafeAddrOfPinnedArrayElement(Buffer, 0), BufferLength, LengthTransferred, Overlapped)

	
	public virtual def ControlTransfer(SetupPacket as WINUSB_SETUP_PACKET, Buffer as Array, BufferLength as int, ref LengthTransferred as int, Overlapped as KOVL_HANDLE) as bool:
		return driverAPI.ControlTransfer(mHandleStruct, SetupPacket, Marshal.UnsafeAddrOfPinnedArrayElement(Buffer, 0), BufferLength, LengthTransferred, Overlapped.Pointer)

	
	public virtual def ControlTransfer(SetupPacket as WINUSB_SETUP_PACKET, Buffer as IntPtr, BufferLength as int, ref LengthTransferred as int, Overlapped as KOVL_HANDLE) as bool:
		return driverAPI.ControlTransfer(mHandleStruct, SetupPacket, Buffer, BufferLength, LengthTransferred, Overlapped.Pointer)

	
	public virtual def FlushPipe(PipeID as byte) as bool:
		return driverAPI.FlushPipe(mHandleStruct, PipeID)

	
	public virtual def Free():
		Dispose()

	
	public virtual def GetAltInterface(NumberOrIndex as byte, IsIndex as bool, ref AltSettingNumber as byte) as bool:
		return driverAPI.GetAltInterface(mHandleStruct, NumberOrIndex, IsIndex, AltSettingNumber)

	
	public virtual def GetAssociatedInterface(AssociatedInterfaceIndex as byte, ref AssociatedInterfaceHandle as KUSB_HANDLE) as bool:
		return driverAPI.GetAssociatedInterface(mHandleStruct, AssociatedInterfaceIndex, AssociatedInterfaceHandle)

	
	public virtual def GetConfiguration(ref ConfigurationNumber as byte) as bool:
		return driverAPI.GetConfiguration(mHandleStruct, ConfigurationNumber)

	
	public virtual def GetCurrentAlternateSetting(ref AltSettingNumber as byte) as bool:
		return driverAPI.GetCurrentAlternateSetting(mHandleStruct, AltSettingNumber)

	
	public virtual def GetCurrentFrameNumber(ref FrameNumber as int) as bool:
		return driverAPI.GetCurrentFrameNumber(mHandleStruct, FrameNumber)

	
	public virtual def GetDescriptor(DescriptorType as byte, Index as byte, LanguageID as int, Buffer as IntPtr, BufferLength as int, ref LengthTransferred as int) as bool:
		return driverAPI.GetDescriptor(mHandleStruct, DescriptorType, Index, (LanguageID cast ushort), Buffer, BufferLength, LengthTransferred)

	
	public virtual def GetDescriptor(DescriptorType as byte, Index as byte, LanguageID as int, Buffer as Array, BufferLength as int, ref LengthTransferred as int) as bool:
		return driverAPI.GetDescriptor(mHandleStruct, DescriptorType, Index, (LanguageID cast ushort), Marshal.UnsafeAddrOfPinnedArrayElement(Buffer, 0), BufferLength, LengthTransferred)

	
	public virtual def GetOverlappedResult(Overlapped as IntPtr, ref lpNumberOfBytesTransferred as int, bWait as bool) as bool:
		return driverAPI.GetOverlappedResult(mHandleStruct, Overlapped, lpNumberOfBytesTransferred, bWait)

	
	public virtual def GetOverlappedResult(Overlapped as KOVL_HANDLE, ref lpNumberOfBytesTransferred as int, bWait as bool) as bool:
		return driverAPI.GetOverlappedResult(mHandleStruct, Overlapped.Pointer, lpNumberOfBytesTransferred, bWait)

	
	public virtual def GetPipePolicy(PipeID as byte, PolicyType as int, ref ValueLength as int, Value as IntPtr) as bool:
		return driverAPI.GetPipePolicy(mHandleStruct, PipeID, PolicyType, ValueLength, Value)

	
	public virtual def GetPipePolicy(PipeID as byte, PolicyType as int, ref ValueLength as int, Value as Array) as bool:
		return driverAPI.GetPipePolicy(mHandleStruct, PipeID, PolicyType, ValueLength, Marshal.UnsafeAddrOfPinnedArrayElement(Value, 0))

	
	public virtual def GetPowerPolicy(PolicyType as int, ref ValueLength as int, Value as IntPtr) as bool:
		return driverAPI.GetPowerPolicy(mHandleStruct, PolicyType, ValueLength, Value)

	
	public virtual def GetPowerPolicy(PolicyType as int, ref ValueLength as int, Value as Array) as bool:
		return driverAPI.GetPowerPolicy(mHandleStruct, PolicyType, ValueLength, Marshal.UnsafeAddrOfPinnedArrayElement(Value, 0))

	
	public virtual def GetProperty(PropertyType as KUSB_PROPERTY, ref PropertySize as int, Value as IntPtr) as bool:
		return driverAPI.GetProperty(mHandleStruct, PropertyType, PropertySize, Value)

	
	public virtual def GetProperty(PropertyType as KUSB_PROPERTY, ref PropertySize as int, Value as Array) as bool:
		return driverAPI.GetProperty(mHandleStruct, PropertyType, PropertySize, Marshal.UnsafeAddrOfPinnedArrayElement(Value, 0))

	
	public Handle as KUSB_HANDLE:
		get:
			return mHandleStruct

	
	public virtual def IsoReadPipe(PipeID as byte, Buffer as IntPtr, BufferLength as int, Overlapped as IntPtr, IsoContext as KISO_CONTEXT) as bool:
		return driverAPI.IsoReadPipe(mHandleStruct, PipeID, Buffer, BufferLength, Overlapped, IsoContext)

	
	public virtual def IsoReadPipe(PipeID as byte, Buffer as Array, BufferLength as int, Overlapped as IntPtr, IsoContext as KISO_CONTEXT) as bool:
		return driverAPI.IsoReadPipe(mHandleStruct, PipeID, Marshal.UnsafeAddrOfPinnedArrayElement(Buffer, 0), BufferLength, Overlapped, IsoContext)

	
	public virtual def IsoReadPipe(PipeID as byte, Buffer as Array, BufferLength as int, Overlapped as KOVL_HANDLE, IsoContext as KISO_CONTEXT) as bool:
		return driverAPI.IsoReadPipe(mHandleStruct, PipeID, Marshal.UnsafeAddrOfPinnedArrayElement(Buffer, 0), BufferLength, Overlapped.Pointer, IsoContext)

	
	public virtual def IsoReadPipe(PipeID as byte, Buffer as IntPtr, BufferLength as int, Overlapped as KOVL_HANDLE, IsoContext as KISO_CONTEXT) as bool:
		return driverAPI.IsoReadPipe(mHandleStruct, PipeID, Buffer, BufferLength, Overlapped.Pointer, IsoContext)

	
	public virtual def IsoWritePipe(PipeID as byte, Buffer as IntPtr, BufferLength as int, Overlapped as IntPtr, IsoContext as KISO_CONTEXT) as bool:
		return driverAPI.IsoWritePipe(mHandleStruct, PipeID, Buffer, BufferLength, Overlapped, IsoContext)

	
	public virtual def IsoWritePipe(PipeID as byte, Buffer as Array, BufferLength as int, Overlapped as IntPtr, IsoContext as KISO_CONTEXT) as bool:
		return driverAPI.IsoWritePipe(mHandleStruct, PipeID, Marshal.UnsafeAddrOfPinnedArrayElement(Buffer, 0), BufferLength, Overlapped, IsoContext)

	
	public virtual def IsoWritePipe(PipeID as byte, Buffer as Array, BufferLength as int, Overlapped as KOVL_HANDLE, IsoContext as KISO_CONTEXT) as bool:
		return driverAPI.IsoWritePipe(mHandleStruct, PipeID, Marshal.UnsafeAddrOfPinnedArrayElement(Buffer, 0), BufferLength, Overlapped.Pointer, IsoContext)

	
	public virtual def IsoWritePipe(PipeID as byte, Buffer as IntPtr, BufferLength as int, Overlapped as KOVL_HANDLE, IsoContext as KISO_CONTEXT) as bool:
		return driverAPI.IsoWritePipe(mHandleStruct, PipeID, Buffer, BufferLength, Overlapped.Pointer, IsoContext)

	
	public virtual def QueryDeviceInformation(InformationType as int, ref BufferLength as int, Buffer as IntPtr) as bool:
		return driverAPI.QueryDeviceInformation(mHandleStruct, InformationType, BufferLength, Buffer)

	
	public virtual def QueryInterfaceSettings(AltSettingIndex as byte, ref UsbAltInterfaceDescriptor as USB_INTERFACE_DESCRIPTOR) as bool:
		return driverAPI.QueryInterfaceSettings(mHandleStruct, AltSettingIndex, UsbAltInterfaceDescriptor)

	
	public virtual def QueryPipe(AltSettingNumber as byte, PipeIndex as byte, ref PipeInformation as WINUSB_PIPE_INFORMATION) as bool:
		return driverAPI.QueryPipe(mHandleStruct, AltSettingNumber, PipeIndex, PipeInformation)

	
	public virtual def ReadPipe(PipeID as byte, Buffer as IntPtr, BufferLength as int, ref LengthTransferred as int, Overlapped as IntPtr) as bool:
		return driverAPI.ReadPipe(mHandleStruct, PipeID, Buffer, BufferLength, LengthTransferred, Overlapped)

	
	public virtual def ReadPipe(PipeID as byte, Buffer as Array, BufferLength as int, ref LengthTransferred as int, Overlapped as IntPtr) as bool:
		return driverAPI.ReadPipe(mHandleStruct, PipeID, Marshal.UnsafeAddrOfPinnedArrayElement(Buffer, 0), BufferLength, LengthTransferred, Overlapped)

	
	public virtual def ReadPipe(PipeID as byte, Buffer as Array, BufferLength as int, ref LengthTransferred as int, Overlapped as KOVL_HANDLE) as bool:
		return driverAPI.ReadPipe(mHandleStruct, PipeID, Marshal.UnsafeAddrOfPinnedArrayElement(Buffer, 0), BufferLength, LengthTransferred, Overlapped.Pointer)

	
	public virtual def ReadPipe(PipeID as byte, Buffer as IntPtr, BufferLength as int, ref LengthTransferred as int, Overlapped as KOVL_HANDLE) as bool:
		return driverAPI.ReadPipe(mHandleStruct, PipeID, Buffer, BufferLength, LengthTransferred, Overlapped.Pointer)

	
	public virtual def ReleaseInterface(NumberOrIndex as byte, IsIndex as bool) as bool:
		return driverAPI.ReleaseInterface(mHandleStruct, NumberOrIndex, IsIndex)

	
	public virtual def ResetDevice() as bool:
		return driverAPI.ResetDevice(mHandleStruct)

	
	public virtual def ResetPipe(PipeID as byte) as bool:
		return driverAPI.ResetPipe(mHandleStruct, PipeID)

	
	public virtual def SelectInterface(NumberOrIndex as byte, IsIndex as bool) as bool:
		return driverAPI.SelectInterface(mHandleStruct, NumberOrIndex, IsIndex)

	
	public virtual def SetAltInterface(NumberOrIndex as byte, IsIndex as bool, AltSettingNumber as byte) as bool:
		return driverAPI.SetAltInterface(mHandleStruct, NumberOrIndex, IsIndex, AltSettingNumber)

	
	public virtual def SetConfiguration(ConfigurationNumber as byte) as bool:
		return driverAPI.SetConfiguration(mHandleStruct, ConfigurationNumber)

	
	public virtual def SetCurrentAlternateSetting(AltSettingNumber as byte) as bool:
		return driverAPI.SetCurrentAlternateSetting(mHandleStruct, AltSettingNumber)

	
	public virtual def SetPipePolicy(PipeID as byte, PolicyType as int, ValueLength as int, Value as IntPtr) as bool:
		return driverAPI.SetPipePolicy(mHandleStruct, PipeID, PolicyType, ValueLength, Value)

	
	public virtual def SetPipePolicy(PipeID as byte, PolicyType as int, ValueLength as int, Value as Array) as bool:
		return driverAPI.SetPipePolicy(mHandleStruct, PipeID, PolicyType, ValueLength, Marshal.UnsafeAddrOfPinnedArrayElement(Value, 0))

	
	public virtual def SetPowerPolicy(PolicyType as int, ValueLength as int, Value as IntPtr) as bool:
		return driverAPI.SetPowerPolicy(mHandleStruct, PolicyType, ValueLength, Value)

	
	public virtual def SetPowerPolicy(PolicyType as int, ValueLength as int, Value as Array) as bool:
		return driverAPI.SetPowerPolicy(mHandleStruct, PolicyType, ValueLength, Marshal.UnsafeAddrOfPinnedArrayElement(Value, 0))

	
	public virtual def WritePipe(PipeID as byte, Buffer as IntPtr, BufferLength as int, ref LengthTransferred as int, Overlapped as IntPtr) as bool:
		return driverAPI.WritePipe(mHandleStruct, PipeID, Buffer, BufferLength, LengthTransferred, Overlapped)

	
	public virtual def WritePipe(PipeID as byte, Buffer as Array, BufferLength as int, ref LengthTransferred as int, Overlapped as IntPtr) as bool:
		return driverAPI.WritePipe(mHandleStruct, PipeID, Marshal.UnsafeAddrOfPinnedArrayElement(Buffer, 0), BufferLength, LengthTransferred, Overlapped)

	
	public virtual def WritePipe(PipeID as byte, Buffer as Array, BufferLength as int, ref LengthTransferred as int, Overlapped as KOVL_HANDLE) as bool:
		return driverAPI.WritePipe(mHandleStruct, PipeID, Marshal.UnsafeAddrOfPinnedArrayElement(Buffer, 0), BufferLength, LengthTransferred, Overlapped.Pointer)

	
	public virtual def WritePipe(PipeID as byte, Buffer as IntPtr, BufferLength as int, ref LengthTransferred as int, Overlapped as KOVL_HANDLE) as bool:
		return driverAPI.WritePipe(mHandleStruct, PipeID, Buffer, BufferLength, LengthTransferred, Overlapped.Pointer)
	
	#endregion


public class OvlK(IDisposable):

	protected mHandleStruct as KOVL_POOL_HANDLE

	protected mbDisposed as bool

	
	protected def constructor():
		pass

	
	#region IDisposable Members
	
	public virtual def Dispose():
		Dispose(true)
		GC.SuppressFinalize(self)

	
	#endregion
	
	def destructor():
		Dispose(false)

	
	protected virtual def Dispose(disposing as bool):
		if not mbDisposed:
			if mHandleStruct.Pointer != IntPtr.Zero:
				AllKFunctions.OvlK_Free(mHandleStruct)
				Debug.Print('{0} Dispose: Freed Handle:{1:X16}h Explicit:{2}', GetType().Name, mHandleStruct.Pointer.ToInt64(), disposing)
			else:
				Debug.Print('{0} Dispose: [WARNING] Handle is null', GetType().Name)
			
			mHandleStruct = KOVL_POOL_HANDLE(IntPtr.Zero)
			mbDisposed = true

	
	protected def Init(UsbHandle as KUSB_HANDLE, MaxOverlappedCount as int, Flags as KOVL_POOL_FLAG) as bool:
		success as bool = AllKFunctions.OvlK_Init(mHandleStruct, UsbHandle, MaxOverlappedCount, Flags)
		
		if not success:
			raise Exception(string.Format('{0} failed initializing. ErrorCode={1:X8}h', GetType().Name, Marshal.GetLastWin32Error()))
		
		Debug.Print('{0} Init: handle 0x{1:X16}', GetType().Name, mHandleStruct.Pointer.ToInt64())
		return true

	
	#region Public Members
	
	public def constructor(UsbHandle as KUSB_HANDLE, MaxOverlappedCount as int, Flags as KOVL_POOL_FLAG):
		success as bool = AllKFunctions.OvlK_Init(mHandleStruct, UsbHandle, MaxOverlappedCount, Flags)
		
		if not success:
			raise Exception(string.Format('{0} failed initializing. ErrorCode={1:X8}h', GetType().Name, Marshal.GetLastWin32Error()))
		
		Debug.Print('{0} Init: handle 0x{1:X16}', GetType().Name, mHandleStruct.Pointer.ToInt64())

	
	public virtual def Acquire(ref OverlappedK as KOVL_HANDLE) as bool:
		return AllKFunctions.OvlK_Acquire(OverlappedK, mHandleStruct)

	
	public virtual def Free():
		Dispose()

	
	public virtual def GetEventHandle(OverlappedK as KOVL_HANDLE) as IntPtr:
		return AllKFunctions.OvlK_GetEventHandle(OverlappedK)

	
	public Handle as KOVL_POOL_HANDLE:
		get:
			return mHandleStruct

	
	public virtual def IsComplete(OverlappedK as KOVL_HANDLE) as bool:
		return AllKFunctions.OvlK_IsComplete(OverlappedK)

	
	public virtual def ReUse(OverlappedK as KOVL_HANDLE) as bool:
		return AllKFunctions.OvlK_ReUse(OverlappedK)

	
	public virtual def Release(OverlappedK as KOVL_HANDLE) as bool:
		return AllKFunctions.OvlK_Release(OverlappedK)

	
	public virtual def Wait(OverlappedK as KOVL_HANDLE, TimeoutMS as int, WaitFlags as KOVL_WAIT_FLAG, ref TransferredLength as int) as bool:
		return AllKFunctions.OvlK_Wait(OverlappedK, TimeoutMS, WaitFlags, TransferredLength)

	
	public virtual def WaitAndRelease(OverlappedK as KOVL_HANDLE, TimeoutMS as int, ref TransferredLength as int) as bool:
		return AllKFunctions.OvlK_WaitAndRelease(OverlappedK, TimeoutMS, TransferredLength)

	
	public virtual def WaitOldest(ref OverlappedK as KOVL_HANDLE, TimeoutMS as int, WaitFlags as KOVL_WAIT_FLAG, ref TransferredLength as int) as bool:
		return AllKFunctions.OvlK_WaitOldest(mHandleStruct, OverlappedK, TimeoutMS, WaitFlags, TransferredLength)

	
	public virtual def WaitOrCancel(OverlappedK as KOVL_HANDLE, TimeoutMS as int, ref TransferredLength as int) as bool:
		return AllKFunctions.OvlK_WaitOrCancel(OverlappedK, TimeoutMS, TransferredLength)
	
	#endregion


public class StmK(IDisposable):

	protected mHandleStruct as KSTM_HANDLE

	protected mbDisposed as bool

	
	protected def constructor():
		pass

	
	#region IDisposable Members
	
	public virtual def Dispose():
		Dispose(true)
		GC.SuppressFinalize(self)

	
	#endregion
	
	def destructor():
		Dispose(false)

	
	protected virtual def Dispose(disposing as bool):
		if not mbDisposed:
			if mHandleStruct.Pointer != IntPtr.Zero:
				AllKFunctions.StmK_Free(mHandleStruct)
				Debug.Print('{0} Dispose: Freed Handle:{1:X16}h Explicit:{2}', GetType().Name, mHandleStruct.Pointer.ToInt64(), disposing)
			else:
				Debug.Print('{0} Dispose: [WARNING] Handle is null', GetType().Name)
			
			mHandleStruct = KSTM_HANDLE(IntPtr.Zero)
			mbDisposed = true

	
	protected def Init(UsbHandle as KUSB_HANDLE, PipeID as byte, MaxTransferSize as int, MaxPendingTransfers as int, MaxPendingIO as int, ref Callbacks as KSTM_CALLBACK, Flags as KSTM_FLAG) as bool:
		success as bool = AllKFunctions.StmK_Init(mHandleStruct, UsbHandle, PipeID, MaxTransferSize, MaxPendingTransfers, MaxPendingIO, Callbacks, Flags)
		
		if not success:
			raise Exception(string.Format('{0} failed initializing. ErrorCode={1:X8}h', GetType().Name, Marshal.GetLastWin32Error()))
		
		Debug.Print('{0} Init: handle 0x{1:X16}', GetType().Name, mHandleStruct.Pointer.ToInt64())
		return true

	
	#region Public Members
	
	public def constructor(UsbHandle as KUSB_HANDLE, PipeID as byte, MaxTransferSize as int, MaxPendingTransfers as int, MaxPendingIO as int, ref Callbacks as KSTM_CALLBACK, Flags as KSTM_FLAG):
		success as bool = AllKFunctions.StmK_Init(mHandleStruct, UsbHandle, PipeID, MaxTransferSize, MaxPendingTransfers, MaxPendingIO, Callbacks, Flags)
		
		if not success:
			raise Exception(string.Format('{0} failed initializing. ErrorCode={1:X8}h', GetType().Name, Marshal.GetLastWin32Error()))
		
		Debug.Print('{0} Init: handle 0x{1:X16}', GetType().Name, mHandleStruct.Pointer.ToInt64())

	
	public virtual def Free():
		Dispose()

	
	public Handle as KSTM_HANDLE:
		get:
			return mHandleStruct

	
	public virtual def Read(Buffer as IntPtr, Offset as int, Length as int, ref TransferredLength as int) as bool:
		return AllKFunctions.StmK_Read(mHandleStruct, Buffer, Offset, Length, TransferredLength)

	
	public virtual def Read(Buffer as Array, Offset as int, Length as int, ref TransferredLength as int) as bool:
		return AllKFunctions.StmK_Read(mHandleStruct, Marshal.UnsafeAddrOfPinnedArrayElement(Buffer, 0), Offset, Length, TransferredLength)

	
	public virtual def Start() as bool:
		return AllKFunctions.StmK_Start(mHandleStruct)

	
	public virtual def Stop(TimeoutCancelMS as int) as bool:
		return AllKFunctions.StmK_Stop(mHandleStruct, TimeoutCancelMS)

	
	public virtual def Write(Buffer as IntPtr, Offset as int, Length as int, ref TransferredLength as int) as bool:
		return AllKFunctions.StmK_Write(mHandleStruct, Buffer, Offset, Length, TransferredLength)

	
	public virtual def Write(Buffer as Array, Offset as int, Length as int, ref TransferredLength as int) as bool:
		return AllKFunctions.StmK_Write(mHandleStruct, Marshal.UnsafeAddrOfPinnedArrayElement(Buffer, 0), Offset, Length, TransferredLength)
	
	#endregion


public class IsoK(IDisposable):

	protected mHandleStruct as KISO_CONTEXT

	protected mbDisposed as bool

	
	protected def constructor():
		pass

	
	#region IDisposable Members
	
	public virtual def Dispose():
		Dispose(true)
		GC.SuppressFinalize(self)

	
	#endregion
	
	def destructor():
		Dispose(false)

	
	protected virtual def Dispose(disposing as bool):
		if not mbDisposed:
			if mHandleStruct.Pointer != IntPtr.Zero:
				AllKFunctions.IsoK_Free(mHandleStruct)
				Debug.Print('{0} Dispose: Freed Handle:{1:X16}h Explicit:{2}', GetType().Name, mHandleStruct.Pointer.ToInt64(), disposing)
			else:
				Debug.Print('{0} Dispose: [WARNING] Handle is null', GetType().Name)
			
			mHandleStruct = KISO_CONTEXT(IntPtr.Zero)
			mbDisposed = true

	
	protected def Init(NumberOfPackets as int, StartFrame as int) as bool:
		success as bool = AllKFunctions.IsoK_Init(mHandleStruct, NumberOfPackets, StartFrame)
		
		if not success:
			raise Exception(string.Format('{0} failed initializing. ErrorCode={1:X8}h', GetType().Name, Marshal.GetLastWin32Error()))
		
		Debug.Print('{0} Init: handle 0x{1:X16}', GetType().Name, mHandleStruct.Pointer.ToInt64())
		return true

	
	#region Nested Structs
	
	[StructLayout(LayoutKind.Sequential, CharSet: CharSet.Ansi, Pack: 1)]
	private struct KISO_CONTEXT_MAP:

		private final Flags as KISO_FLAG

		
		private final StartFrame as int

		
		private final ErrorCount as short

		
		private final NumberOfPackets as short

		
		private final UrbHdrStatus as int

	
	#endregion
	
	#region Public Members
	
	public def constructor(NumberOfPackets as int, StartFrame as int):
		success as bool = AllKFunctions.IsoK_Init(mHandleStruct, NumberOfPackets, StartFrame)
		
		if not success:
			raise Exception(string.Format('{0} failed initializing. ErrorCode={1:X8}h', GetType().Name, Marshal.GetLastWin32Error()))
		
		Debug.Print('{0} Init: handle 0x{1:X16}', GetType().Name, mHandleStruct.Pointer.ToInt64())

	
	public virtual def EnumPackets(EnumPackets as KISO_ENUM_PACKETS_CB, StartPacketIndex as int, UserState as IntPtr) as bool:
		return AllKFunctions.IsoK_EnumPackets(mHandleStruct, EnumPackets, StartPacketIndex, UserState)

	
	public ErrorCount as short:
		get:
			return Marshal.ReadInt16(mHandleStruct.Pointer, ofsErrorCount)
		set:
			Marshal.WriteInt16(mHandleStruct.Pointer, ofsErrorCount, value)

	
	public Flags as KISO_FLAG:
		get:
			return (Marshal.ReadInt32(mHandleStruct.Pointer, ofsFlags) cast KISO_FLAG)
		set:
			Marshal.WriteInt32(mHandleStruct.Pointer, ofsFlags, (value cast int))

	
	public virtual def Free():
		Dispose()

	
	public virtual def GetPacket(PacketIndex as int, ref IsoPacket as KISO_PACKET) as bool:
		return AllKFunctions.IsoK_GetPacket(mHandleStruct, PacketIndex, IsoPacket)

	
	public Handle as KISO_CONTEXT:
		get:
			return mHandleStruct

	
	public NumberOfPackets as short:
		get:
			return Marshal.ReadInt16(mHandleStruct.Pointer, ofsNumberOfPackets)
		set:
			Marshal.WriteInt16(mHandleStruct.Pointer, ofsNumberOfPackets, value)

	
	public virtual def ReUse() as bool:
		return AllKFunctions.IsoK_ReUse(mHandleStruct)

	
	public virtual def SetPacket(PacketIndex as int, ref IsoPacket as KISO_PACKET) as bool:
		return AllKFunctions.IsoK_SetPacket(mHandleStruct, PacketIndex, IsoPacket)

	
	public virtual def SetPackets(PacketSize as int) as bool:
		return AllKFunctions.IsoK_SetPackets(mHandleStruct, PacketSize)

	
	public StartFrame as int:
		get:
			return Marshal.ReadInt32(mHandleStruct.Pointer, ofsStartFrame)
		set:
			Marshal.WriteInt32(mHandleStruct.Pointer, ofsStartFrame, value)

	
	public UrbHdrStatus as int:
		get:
			return Marshal.ReadInt32(mHandleStruct.Pointer, ofsUrbHdrStatus)
		set:
			Marshal.WriteInt32(mHandleStruct.Pointer, ofsUrbHdrStatus, value)

	
	#endregion
	
	#region Private Members
	
	private static final ofsErrorCount as int = Marshal.OffsetOf(typeof(KISO_CONTEXT_MAP), 'ErrorCount').ToInt32()

	private static final ofsFlags as int = Marshal.OffsetOf(typeof(KISO_CONTEXT_MAP), 'Flags').ToInt32()

	private static final ofsNumberOfPackets as int = Marshal.OffsetOf(typeof(KISO_CONTEXT_MAP), 'NumberOfPackets').ToInt32()

	private static final ofsStartFrame as int = Marshal.OffsetOf(typeof(KISO_CONTEXT_MAP), 'StartFrame').ToInt32()

	private static final ofsUrbHdrStatus as int = Marshal.OffsetOf(typeof(KISO_CONTEXT_MAP), 'UrbHdrStatus').ToInt32()
	
	#endregion

