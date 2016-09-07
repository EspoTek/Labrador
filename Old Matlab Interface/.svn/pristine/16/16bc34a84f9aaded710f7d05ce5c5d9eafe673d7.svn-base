#Region "Copyright (c) Travis Robinson"

' Copyright (c) 2012 Travis Robinson <libusbdotnet@gmail.com>
' All rights reserved.
'
' C# libusbK Bindings
' Auto-generated on: 04.28.2011
'
' Redistribution and use in source and binary forms, with or without
' modification, are permitted provided that the following conditions are met:
'
'     * Redistributions of source code must retain the above copyright
'       notice, this list of conditions and the following disclaimer.
'
' THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
' IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
' TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
' PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TRAVIS LEE ROBINSON
' BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
' CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
' SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
' INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
' CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
' ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
' THE POSSIBILITY OF SUCH DAMAGE.

#End Region

Imports System
Imports System.Diagnostics
Imports System.Runtime.InteropServices

' ReSharper disable InconsistentNaming
' ReSharper disable CheckNamespace
' ReSharper disable UnassignedReadonlyField

Namespace libusbK
	Public NotInheritable Class AllKOptions
		Private Sub New()
		End Sub
		#Region "Public Members"

		''' <summary>
		'''   Alternate libusbK library to use.  This must be assigned before any libusbK functions are called and it must be the full path and file name to a libusbK.dll.
		''' </summary>
		Public Shared LIBUSBK_FULLPATH_TO_ALTERNATE_DLL As String

		#End Region
	End Class

	Public NotInheritable Class AllKConstants
		Private Sub New()
		End Sub
		#Region "Public Members"

		''' <summary>
		''' Allocated length for all strings in a \ref KLST_DEVINFO structure.
		''' </summary>
		Public Const KLST_STRING_MAX_LEN As Integer = 256

		''' <summary>
		''' libusbK library
		''' </summary>
		Public Const LIBUSBK_DLL As String = "libusbK.dll"

		''' <summary>
		''' Config power mask for the \c bmAttributes field of a \ref USB_CONFIGURATION_DESCRIPTOR
		''' </summary>
		Public Const USB_CONFIG_POWERED_MASK As Byte = &Hc0

		''' <summary>
		''' Endpoint address mask for the \c bEndpointAddress field of a \ref USB_ENDPOINT_DESCRIPTOR
		''' </summary>
		Public Const USB_ENDPOINT_ADDRESS_MASK As Byte = &Hf

		''' <summary>
		''' Endpoint direction mask for the \c bEndpointAddress field of a \ref USB_ENDPOINT_DESCRIPTOR
		''' </summary>
		Public Const USB_ENDPOINT_DIRECTION_MASK As Byte = &H80

		#End Region
	End Class

	Public Enum PipePolicyType
		SHORT_PACKET_TERMINATE = &H1
		AUTO_CLEAR_STALL = &H2
		PIPE_TRANSFER_TIMEOUT = &H3
		IGNORE_SHORT_PACKETS = &H4
		ALLOW_PARTIAL_READS = &H5
		AUTO_FLUSH = &H6
		RAW_IO = &H7
		MAXIMUM_TRANSFER_SIZE = &H8
		RESET_PIPE_ON_RESUME = &H9

		ISO_START_LATENCY = &H20
		ISO_ALWAYS_START_ASAP = &H21
		ISO_NUM_FIXED_PACKETS = &H22

		SIMUL_PARALLEL_REQUESTS = &H30
	End Enum

	Public Enum PowerPolicyType
		AUTO_SUSPEND = &H81
		SUSPEND_DELAY = &H83
	End Enum

	Public Enum DeviceInformationType
		DEVICE_SPEED = &H1
	End Enum

	Public Enum EndpointType
		''' <summary>
		''' Indicates a control endpoint
		''' </summary>
		CONTROL = &H0

		''' <summary>
		''' Indicates an isochronous endpoint
		''' </summary>
		ISOCHRONOUS = &H1

		''' <summary>
		''' Indicates a bulk endpoint
		''' </summary>
		BULK = &H2

		''' <summary>
		''' Indicates an interrupt endpoint
		''' </summary>
		INTERRUPT = &H3

		''' <summary>
		''' Endpoint type mask for the \c bmAttributes field of a \ref USB_ENDPOINT_DESCRIPTOR
		''' </summary>
		MASK = &H3
	End Enum

	Public NotInheritable Class ErrorCodes
		Private Sub New()
		End Sub
		#Region "Public Members"

		''' <summary>
		'''   Access is denied.
		''' </summary>
		Public Const AccessDenied As Integer = 5

		''' <summary>
		'''   The requested resource is in use.
		''' </summary>
		Public Const Busy As Integer = 170

		''' <summary>
		'''   The operation was canceled by the user.
		''' </summary>
		Public Const Cancelled As Integer = 1223

		''' <summary>
		'''   The library, drive, or media pool is empty.
		''' </summary>
		Public Const Empty As Integer = 4306

		''' <summary>
		'''   The handle is invalid.
		''' </summary>
		Public Const InvalidHandle As Integer = 6

		''' <summary>
		'''   The parameter is incorrect.
		''' </summary>
		Public Const InvalidParameter As Integer = 87

		''' <summary>
		'''   Overlapped I/O event is not in a signaled state.
		''' </summary>
		Public Const IoIncomplete As Integer = 996

		''' <summary>
		'''   Overlapped I/O operation is in progress.
		''' </summary>
		Public Const IoPending As Integer = 997

		''' <summary>
		'''   More data is available.
		''' </summary>
		Public Const MoreData As Integer = 234

		''' <summary>
		'''   No more data is available.
		''' </summary>
		Public Const NoMoreItems As Integer = 259

		''' <summary>
		'''   Not enough storage is available to process this command.
		''' </summary>
		Public Const NotEnoughMemory As Integer = 8

		''' <summary>
		'''   Element not found.
		''' </summary>
		Public Const NotFound As Integer = 1168

		''' <summary>
		'''   The request is not supported.
		''' </summary>
		Public Const NotSupported As Integer = 50

		''' <summary>
		'''   The I/O operation has been aborted because of either a thread exit or an application request.
		''' </summary>
		Public Const OperationAborted As Integer = 995

		''' <summary>
		'''   The cluster resource is not available.
		''' </summary>
		Public Const ResourceNotAvailable As Integer = 5006

		''' <summary>
		'''   The cluster resource could not be found.
		''' </summary>
		Public Const ResourceNotFound As Integer = 5007

		''' <summary>
		'''   The semaphore timeout period has expired.
		''' </summary>
		Public Const SemTimeout As Integer = 121

		''' <summary>
		'''   The operation completed successfully.
		''' </summary>
		Public Const Success As Integer = 0

		''' <summary>
		'''   An attempt was made to operate on a thread within a specific process, but the thread specified is not in the process specified.
		''' </summary>
		Public Const ThreadNotInProcess As Integer = 566

		''' <summary>
		'''   A thread termination occurred while the thread was suspended. The thread was resumed, and termination proceeded.
		''' </summary>
		Public Const ThreadWasSuspended As Integer = 699

		''' <summary>
		'''   Too many dynamic-link modules are attached to this program or dynamic-link module.
		''' </summary>
		Public Const TooManyModules As Integer = 214

		#End Region
	End Class

	Public Interface IKLIB_HANDLE
		#Region "Public Members"

		Function GetContext() As IntPtr
		ReadOnly Property HandleType() As KLIB_HANDLE_TYPE
		ReadOnly Property Pointer() As IntPtr
		Function SetCleanupCallback(CleanupCallback As KLIB_HANDLE_CLEANUP_CB) As Boolean
		Function SetContext(UserContext As IntPtr) As Boolean

		#End Region
	End Interface

	#Region "Opaque library handles"

	Public Structure KLST_HANDLE
		Implements IKLIB_HANDLE
		#Region "IKLIB_HANDLE Members"

		Public ReadOnly Property Pointer() As IntPtr Implements IKLIB_HANDLE.Pointer
			Get
				Return mHandlePtr
			End Get
		End Property

		Public ReadOnly Property HandleType() As KLIB_HANDLE_TYPE Implements IKLIB_HANDLE.HandleType
			Get
				Return KLIB_HANDLE_TYPE.LSTK
			End Get
		End Property

		Public Function GetContext() As IntPtr Implements IKLIB_HANDLE.GetContext
			Return AllKFunctions.LibK_GetContext(mHandlePtr, HandleType)
		End Function

		Public Function SetContext(UserContext As IntPtr) As Boolean Implements IKLIB_HANDLE.SetContext
			Return AllKFunctions.LibK_SetContext(mHandlePtr, HandleType, UserContext)
		End Function

		Public Function SetCleanupCallback(CleanupCallback As KLIB_HANDLE_CLEANUP_CB) As Boolean Implements IKLIB_HANDLE.SetCleanupCallback
			Return AllKFunctions.LibK_SetCleanupCallback(mHandlePtr, HandleType, CleanupCallback)
		End Function

		#End Region

		#Region "Public Members"

		Public Sub New(Handle As IntPtr)
			mHandlePtr = Handle
		End Sub

		#End Region

		#Region "Private Members"

		Private ReadOnly mHandlePtr As IntPtr

		#End Region
	End Structure

	Public Structure KHOT_HANDLE
		Implements IKLIB_HANDLE
		#Region "IKLIB_HANDLE Members"

		Public ReadOnly Property Pointer() As IntPtr Implements IKLIB_HANDLE.Pointer
			Get
				Return mHandlePtr
			End Get
		End Property

		Public ReadOnly Property HandleType() As KLIB_HANDLE_TYPE Implements IKLIB_HANDLE.HandleType
			Get
				Return KLIB_HANDLE_TYPE.HOTK
			End Get
		End Property

		Public Function GetContext() As IntPtr Implements IKLIB_HANDLE.GetContext
			Return AllKFunctions.LibK_GetContext(mHandlePtr, HandleType)
		End Function

		Public Function SetContext(UserContext As IntPtr) As Boolean Implements IKLIB_HANDLE.SetContext
			Return AllKFunctions.LibK_SetContext(mHandlePtr, HandleType, UserContext)
		End Function

		Public Function SetCleanupCallback(CleanupCallback As KLIB_HANDLE_CLEANUP_CB) As Boolean Implements IKLIB_HANDLE.SetCleanupCallback
			Return AllKFunctions.LibK_SetCleanupCallback(mHandlePtr, HandleType, CleanupCallback)
		End Function

		#End Region

		#Region "Public Members"

		Public Sub New(Handle As IntPtr)
			mHandlePtr = Handle
		End Sub

		#End Region

		#Region "Private Members"

		Private ReadOnly mHandlePtr As IntPtr

		#End Region
	End Structure

	Public Structure KUSB_HANDLE
		Implements IKLIB_HANDLE
		#Region "IKLIB_HANDLE Members"

		Public ReadOnly Property Pointer() As IntPtr Implements IKLIB_HANDLE.Pointer
			Get
				Return mHandlePtr
			End Get
		End Property

		Public ReadOnly Property HandleType() As KLIB_HANDLE_TYPE Implements IKLIB_HANDLE.HandleType
			Get
				Return KLIB_HANDLE_TYPE.USBK
			End Get
		End Property

		Public Function GetContext() As IntPtr Implements IKLIB_HANDLE.GetContext
			Return AllKFunctions.LibK_GetContext(mHandlePtr, HandleType)
		End Function

		Public Function SetContext(UserContext As IntPtr) As Boolean Implements IKLIB_HANDLE.SetContext
			Return AllKFunctions.LibK_SetContext(mHandlePtr, HandleType, UserContext)
		End Function

		Public Function SetCleanupCallback(CleanupCallback As KLIB_HANDLE_CLEANUP_CB) As Boolean Implements IKLIB_HANDLE.SetCleanupCallback
			Return AllKFunctions.LibK_SetCleanupCallback(mHandlePtr, HandleType, CleanupCallback)
		End Function

		#End Region

		#Region "USB Shared Device Context"

		Public Function GetSharedContext() As IntPtr
			Return AllKFunctions.LibK_GetContext(mHandlePtr, KLIB_HANDLE_TYPE.USBSHAREDK)
		End Function

		Public Function SetSharedCleanupCallback(CleanupCallback As KLIB_HANDLE_CLEANUP_CB) As Boolean
			Return AllKFunctions.LibK_SetCleanupCallback(mHandlePtr, KLIB_HANDLE_TYPE.USBSHAREDK, CleanupCallback)
		End Function

		Public Function SetSharedContext(UserContext As IntPtr) As Boolean
			Return AllKFunctions.LibK_SetContext(mHandlePtr, KLIB_HANDLE_TYPE.USBSHAREDK, UserContext)
		End Function

		#End Region

		#Region "Public Members"

		Public Sub New(Handle As IntPtr)
			mHandlePtr = Handle
		End Sub

		#End Region

		#Region "Private Members"

		Private ReadOnly mHandlePtr As IntPtr

		#End Region
	End Structure

	Public Structure KOVL_POOL_HANDLE
		Implements IKLIB_HANDLE
		#Region "IKLIB_HANDLE Members"

		Public ReadOnly Property Pointer() As IntPtr Implements IKLIB_HANDLE.Pointer
			Get
				Return mHandlePtr
			End Get
		End Property

		Public ReadOnly Property HandleType() As KLIB_HANDLE_TYPE Implements IKLIB_HANDLE.HandleType
			Get
				Return KLIB_HANDLE_TYPE.OVLPOOLK
			End Get
		End Property

		Public Function GetContext() As IntPtr Implements IKLIB_HANDLE.GetContext
			Return AllKFunctions.LibK_GetContext(mHandlePtr, HandleType)
		End Function

		Public Function SetContext(UserContext As IntPtr) As Boolean Implements IKLIB_HANDLE.SetContext
			Return AllKFunctions.LibK_SetContext(mHandlePtr, HandleType, UserContext)
		End Function

		Public Function SetCleanupCallback(CleanupCallback As KLIB_HANDLE_CLEANUP_CB) As Boolean Implements IKLIB_HANDLE.SetCleanupCallback
			Return AllKFunctions.LibK_SetCleanupCallback(mHandlePtr, HandleType, CleanupCallback)
		End Function

		#End Region

		#Region "Public Members"

		Public Sub New(Handle As IntPtr)
			mHandlePtr = Handle
		End Sub

		#End Region

		#Region "Private Members"

		Private ReadOnly mHandlePtr As IntPtr

		#End Region
	End Structure

	Public Structure KOVL_HANDLE
		Implements IKLIB_HANDLE
		#Region "IKLIB_HANDLE Members"

		Public ReadOnly Property Pointer() As IntPtr Implements IKLIB_HANDLE.Pointer
			Get
				Return mHandlePtr
			End Get
		End Property

		Public ReadOnly Property HandleType() As KLIB_HANDLE_TYPE Implements IKLIB_HANDLE.HandleType
			Get
				Return KLIB_HANDLE_TYPE.OVLK
			End Get
		End Property

		Public Function GetContext() As IntPtr Implements IKLIB_HANDLE.GetContext
			Return AllKFunctions.LibK_GetContext(mHandlePtr, HandleType)
		End Function

		Public Function SetContext(UserContext As IntPtr) As Boolean Implements IKLIB_HANDLE.SetContext
			Return AllKFunctions.LibK_SetContext(mHandlePtr, HandleType, UserContext)
		End Function

		Public Function SetCleanupCallback(CleanupCallback As KLIB_HANDLE_CLEANUP_CB) As Boolean Implements IKLIB_HANDLE.SetCleanupCallback
			Return AllKFunctions.LibK_SetCleanupCallback(mHandlePtr, HandleType, CleanupCallback)
		End Function

		#End Region

		#Region "Public Members"

		Public Sub New(Handle As IntPtr)
			mHandlePtr = Handle
		End Sub

		#End Region

		#Region "Private Members"

		Private ReadOnly mHandlePtr As IntPtr

		#End Region
	End Structure

	Public Structure KSTM_HANDLE
		Implements IKLIB_HANDLE
		#Region "IKLIB_HANDLE Members"

		Public ReadOnly Property Pointer() As IntPtr Implements IKLIB_HANDLE.Pointer
			Get
				Return mHandlePtr
			End Get
		End Property

		Public ReadOnly Property HandleType() As KLIB_HANDLE_TYPE Implements IKLIB_HANDLE.HandleType
			Get
				Return KLIB_HANDLE_TYPE.STMK
			End Get
		End Property

		Public Function GetContext() As IntPtr Implements IKLIB_HANDLE.GetContext
			Return AllKFunctions.LibK_GetContext(mHandlePtr, HandleType)
		End Function

		Public Function SetContext(UserContext As IntPtr) As Boolean Implements IKLIB_HANDLE.SetContext
			Return AllKFunctions.LibK_SetContext(mHandlePtr, HandleType, UserContext)
		End Function

		Public Function SetCleanupCallback(CleanupCallback As KLIB_HANDLE_CLEANUP_CB) As Boolean Implements IKLIB_HANDLE.SetCleanupCallback
			Return AllKFunctions.LibK_SetCleanupCallback(mHandlePtr, HandleType, CleanupCallback)
		End Function

		#End Region

		#Region "Public Members"

		Public Sub New(Handle As IntPtr)
			mHandlePtr = Handle
		End Sub

		#End Region

		#Region "Private Members"

		Private ReadOnly mHandlePtr As IntPtr

		#End Region
	End Structure

	#End Region

	#Region "Internal Function Imports"

	Friend NotInheritable Class AllKFunctions
		Private Sub New()
		End Sub
		#Region "Delegates"

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Sub HotK_FreeAllDelegate()

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function HotK_FreeDelegate(<[In]> Handle As KHOT_HANDLE) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function HotK_InitDelegate(<Out> ByRef Handle As KHOT_HANDLE, <[In], Out> ByRef InitParams As KHOT_PARAMS) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function IsoK_EnumPacketsDelegate(<[In]> IsoContext As KISO_CONTEXT, EnumPackets As KISO_ENUM_PACKETS_CB, StartPacketIndex As Integer, UserState As IntPtr) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function IsoK_FreeDelegate(<[In]> IsoContext As KISO_CONTEXT) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function IsoK_GetPacketDelegate(<[In]> IsoContext As KISO_CONTEXT, PacketIndex As Integer, <Out> ByRef IsoPacket As KISO_PACKET) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function IsoK_InitDelegate(<Out> ByRef IsoContext As KISO_CONTEXT, NumberOfPackets As Integer, StartFrame As Integer) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function IsoK_ReUseDelegate(<[In]> IsoContext As KISO_CONTEXT) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function IsoK_SetPacketDelegate(<[In]> IsoContext As KISO_CONTEXT, PacketIndex As Integer, <[In]> ByRef IsoPacket As KISO_PACKET) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function IsoK_SetPacketsDelegate(<[In]> IsoContext As KISO_CONTEXT, PacketSize As Integer) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Sub LibK_Context_FreeDelegate()

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function LibK_Context_InitDelegate(Heap As IntPtr, Reserved As IntPtr) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function LibK_CopyDriverAPIDelegate(<Out> ByRef DriverAPI As KUSB_DRIVER_API, <[In]> UsbHandle As KUSB_HANDLE) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function LibK_GetContextDelegate(<[In]> Handle As IntPtr, HandleType As KLIB_HANDLE_TYPE) As IntPtr

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function LibK_GetDefaultContextDelegate(HandleType As KLIB_HANDLE_TYPE) As IntPtr

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function LibK_GetProcAddressDelegate(ProcAddress As IntPtr, DriverID As Integer, FunctionID As Integer) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Sub LibK_GetVersionDelegate(<Out> ByRef Version As KLIB_VERSION)

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function LibK_LoadDriverAPIDelegate(<Out> ByRef DriverAPI As KUSB_DRIVER_API, DriverID As Integer) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function LibK_SetCleanupCallbackDelegate(<[In]> Handle As IntPtr, HandleType As KLIB_HANDLE_TYPE, CleanupCB As KLIB_HANDLE_CLEANUP_CB) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function LibK_SetContextDelegate(<[In]> Handle As IntPtr, HandleType As KLIB_HANDLE_TYPE, ContextValue As IntPtr) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function LibK_SetDefaultContextDelegate(HandleType As KLIB_HANDLE_TYPE, ContextValue As IntPtr) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function LstK_CountDelegate(<[In]> DeviceList As KLST_HANDLE, ByRef Count As Integer) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function LstK_CurrentDelegate(<[In]> DeviceList As KLST_HANDLE, <Out> ByRef DeviceInfo As KLST_DEVINFO_HANDLE) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function LstK_EnumerateDelegate(<[In]> DeviceList As KLST_HANDLE, EnumDevListCB As KLST_ENUM_DEVINFO_CB, Context As IntPtr) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function LstK_FindByVidPidDelegate(<[In]> DeviceList As KLST_HANDLE, Vid As Integer, Pid As Integer, <Out> ByRef DeviceInfo As KLST_DEVINFO_HANDLE) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function LstK_FreeDelegate(<[In]> DeviceList As KLST_HANDLE) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function LstK_InitDelegate(<Out> ByRef DeviceList As KLST_HANDLE, Flags As KLST_FLAG) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function LstK_InitExDelegate(<Out> ByRef DeviceList As KLST_HANDLE, Flags As KLST_FLAG, <[In]> ByRef PatternMatch As KLST_PATTERN_MATCH) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function LstK_MoveNextDelegate(<[In]> DeviceList As KLST_HANDLE, <Out> ByRef DeviceInfo As KLST_DEVINFO_HANDLE) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Sub LstK_MoveResetDelegate(<[In]> DeviceList As KLST_HANDLE)

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function OvlK_AcquireDelegate(<Out> ByRef OverlappedK As KOVL_HANDLE, <[In]> PoolHandle As KOVL_POOL_HANDLE) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function OvlK_FreeDelegate(<[In]> PoolHandle As KOVL_POOL_HANDLE) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function OvlK_GetEventHandleDelegate(<[In]> OverlappedK As KOVL_HANDLE) As IntPtr

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function OvlK_InitDelegate(<Out> ByRef PoolHandle As KOVL_POOL_HANDLE, <[In]> UsbHandle As KUSB_HANDLE, MaxOverlappedCount As Integer, Flags As KOVL_POOL_FLAG) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function OvlK_IsCompleteDelegate(<[In]> OverlappedK As KOVL_HANDLE) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function OvlK_ReUseDelegate(<[In]> OverlappedK As KOVL_HANDLE) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function OvlK_ReleaseDelegate(<[In]> OverlappedK As KOVL_HANDLE) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function OvlK_WaitAndReleaseDelegate(<[In]> OverlappedK As KOVL_HANDLE, TimeoutMS As Integer, ByRef TransferredLength As Integer) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function OvlK_WaitDelegate(<[In]> OverlappedK As KOVL_HANDLE, TimeoutMS As Integer, WaitFlags As KOVL_WAIT_FLAG, ByRef TransferredLength As Integer) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function OvlK_WaitOldestDelegate(<[In]> PoolHandle As KOVL_POOL_HANDLE, <Out> ByRef OverlappedK As KOVL_HANDLE, TimeoutMS As Integer, WaitFlags As KOVL_WAIT_FLAG, ByRef TransferredLength As Integer) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function OvlK_WaitOrCancelDelegate(<[In]> OverlappedK As KOVL_HANDLE, TimeoutMS As Integer, ByRef TransferredLength As Integer) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function StmK_FreeDelegate(<[In]> StreamHandle As KSTM_HANDLE) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function StmK_InitDelegate(<Out> ByRef StreamHandle As KSTM_HANDLE, <[In]> UsbHandle As KUSB_HANDLE, PipeID As Byte, MaxTransferSize As Integer, MaxPendingTransfers As Integer, MaxPendingIO As Integer, _
			<[In]> ByRef Callbacks As KSTM_CALLBACK, Flags As KSTM_FLAG) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function StmK_ReadDelegate(<[In]> StreamHandle As KSTM_HANDLE, Buffer As IntPtr, Offset As Integer, Length As Integer, ByRef TransferredLength As Integer) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function StmK_StartDelegate(<[In]> StreamHandle As KSTM_HANDLE) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function StmK_StopDelegate(<[In]> StreamHandle As KSTM_HANDLE, TimeoutCancelMS As Integer) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function StmK_WriteDelegate(<[In]> StreamHandle As KSTM_HANDLE, Buffer As IntPtr, Offset As Integer, Length As Integer, ByRef TransferredLength As Integer) As Boolean

		<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
		Public Delegate Function UsbK_FreeDelegate(<[In]> InterfaceHandle As KUSB_HANDLE) As Boolean

		#End Region

		Shared Sub New()
			If [String].IsNullOrEmpty(AllKOptions.LIBUSBK_FULLPATH_TO_ALTERNATE_DLL) Then
				mModuleLibusbK = LoadLibraryEx(AllKConstants.LIBUSBK_DLL, IntPtr.Zero, LoadLibraryFlags.NONE)
			Else
				mModuleLibusbK = LoadLibraryEx(AllKOptions.LIBUSBK_FULLPATH_TO_ALTERNATE_DLL, IntPtr.Zero, LoadLibraryFlags.LOAD_WITH_ALTERED_SEARCH_PATH)
			End If

			If mModuleLibusbK = IntPtr.Zero Then
				Throw New DllNotFoundException("libusbK.dll not found.  Please install drivers/applications and retry.")
			End If

			LoadDynamicFunctions()
		End Sub

		#Region "Nested Enumerations"

		<Flags> _
		Private Enum LoadLibraryFlags
			NONE = 0
			DONT_RESOLVE_DLL_REFERENCES = &H1
			LOAD_IGNORE_CODE_AUTHZ_LEVEL = &H10
			LOAD_LIBRARY_AS_DATAFILE = &H2
			LOAD_LIBRARY_AS_DATAFILE_EXCLUSIVE = &H40
			LOAD_LIBRARY_AS_IMAGE_RESOURCE = &H20
			LOAD_WITH_ALTERED_SEARCH_PATH = &H8
		End Enum

		#End Region

		#Region "Public Members"

		Public Shared HotK_Free As HotK_FreeDelegate
		Public Shared HotK_FreeAll As HotK_FreeAllDelegate
		Public Shared HotK_Init As HotK_InitDelegate
		Public Shared IsoK_EnumPackets As IsoK_EnumPacketsDelegate
		Public Shared IsoK_Free As IsoK_FreeDelegate
		Public Shared IsoK_GetPacket As IsoK_GetPacketDelegate
		Public Shared IsoK_Init As IsoK_InitDelegate
		Public Shared IsoK_ReUse As IsoK_ReUseDelegate
		Public Shared IsoK_SetPacket As IsoK_SetPacketDelegate
		Public Shared IsoK_SetPackets As IsoK_SetPacketsDelegate
		Public Shared LibK_Context_Free As LibK_Context_FreeDelegate
		Public Shared LibK_Context_Init As LibK_Context_InitDelegate

		Public Shared LibK_CopyDriverAPI As LibK_CopyDriverAPIDelegate
		Public Shared LibK_GetContext As LibK_GetContextDelegate
		Public Shared LibK_GetDefaultContext As LibK_GetDefaultContextDelegate
		Public Shared LibK_GetProcAddress As LibK_GetProcAddressDelegate
		Public Shared LibK_GetVersion As LibK_GetVersionDelegate
		Public Shared LibK_LoadDriverAPI As LibK_LoadDriverAPIDelegate
		Public Shared LibK_SetCleanupCallback As LibK_SetCleanupCallbackDelegate
		Public Shared LibK_SetContext As LibK_SetContextDelegate
		Public Shared LibK_SetDefaultContext As LibK_SetDefaultContextDelegate
		Public Shared LstK_Count As LstK_CountDelegate
		Public Shared LstK_Current As LstK_CurrentDelegate
		Public Shared LstK_Enumerate As LstK_EnumerateDelegate
		Public Shared LstK_FindByVidPid As LstK_FindByVidPidDelegate
		Public Shared LstK_Free As LstK_FreeDelegate
		Public Shared LstK_Init As LstK_InitDelegate
		Public Shared LstK_InitEx As LstK_InitExDelegate
		Public Shared LstK_MoveNext As LstK_MoveNextDelegate
		Public Shared LstK_MoveReset As LstK_MoveResetDelegate
		Public Shared OvlK_Acquire As OvlK_AcquireDelegate
		Public Shared OvlK_Free As OvlK_FreeDelegate
		Public Shared OvlK_GetEventHandle As OvlK_GetEventHandleDelegate
		Public Shared OvlK_Init As OvlK_InitDelegate
		Public Shared OvlK_IsComplete As OvlK_IsCompleteDelegate
		Public Shared OvlK_ReUse As OvlK_ReUseDelegate
		Public Shared OvlK_Release As OvlK_ReleaseDelegate
		Public Shared OvlK_Wait As OvlK_WaitDelegate
		Public Shared OvlK_WaitAndRelease As OvlK_WaitAndReleaseDelegate
		Public Shared OvlK_WaitOldest As OvlK_WaitOldestDelegate
		Public Shared OvlK_WaitOrCancel As OvlK_WaitOrCancelDelegate
		Public Shared StmK_Free As StmK_FreeDelegate
		Public Shared StmK_Init As StmK_InitDelegate
		Public Shared StmK_Read As StmK_ReadDelegate
		Public Shared StmK_Start As StmK_StartDelegate
		Public Shared StmK_Stop As StmK_StopDelegate
		Public Shared StmK_Write As StmK_WriteDelegate
		Public Shared UsbK_Free As UsbK_FreeDelegate

		#End Region

		#Region "Private Members"

		Private Declare Ansi Function GetProcAddress Lib "kernel32.dll" (hModule As IntPtr, procName As String) As IntPtr

		Private Shared Sub LoadDynamicFunctions()
			LibK_GetVersion = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "LibK_GetVersion"), GetType(LibK_GetVersionDelegate)), LibK_GetVersionDelegate)
			LibK_GetContext = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "LibK_GetContext"), GetType(LibK_GetContextDelegate)), LibK_GetContextDelegate)
			LibK_SetContext = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "LibK_SetContext"), GetType(LibK_SetContextDelegate)), LibK_SetContextDelegate)
			LibK_SetCleanupCallback = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "LibK_SetCleanupCallback"), GetType(LibK_SetCleanupCallbackDelegate)), LibK_SetCleanupCallbackDelegate)
			LibK_LoadDriverAPI = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "LibK_LoadDriverAPI"), GetType(LibK_LoadDriverAPIDelegate)), LibK_LoadDriverAPIDelegate)
			LibK_CopyDriverAPI = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "LibK_CopyDriverAPI"), GetType(LibK_CopyDriverAPIDelegate)), LibK_CopyDriverAPIDelegate)
			LibK_GetProcAddress = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "LibK_GetProcAddress"), GetType(LibK_GetProcAddressDelegate)), LibK_GetProcAddressDelegate)
			LibK_SetDefaultContext = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "LibK_SetDefaultContext"), GetType(LibK_SetDefaultContextDelegate)), LibK_SetDefaultContextDelegate)
			LibK_GetDefaultContext = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "LibK_GetDefaultContext"), GetType(LibK_GetDefaultContextDelegate)), LibK_GetDefaultContextDelegate)
			LibK_Context_Init = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "LibK_Context_Init"), GetType(LibK_Context_InitDelegate)), LibK_Context_InitDelegate)
			LibK_Context_Free = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "LibK_Context_Free"), GetType(LibK_Context_FreeDelegate)), LibK_Context_FreeDelegate)
			UsbK_Free = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "UsbK_Free"), GetType(UsbK_FreeDelegate)), UsbK_FreeDelegate)
			LstK_Init = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "LstK_Init"), GetType(LstK_InitDelegate)), LstK_InitDelegate)
			LstK_InitEx = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "LstK_InitEx"), GetType(LstK_InitExDelegate)), LstK_InitExDelegate)
			LstK_Free = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "LstK_Free"), GetType(LstK_FreeDelegate)), LstK_FreeDelegate)
			LstK_Enumerate = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "LstK_Enumerate"), GetType(LstK_EnumerateDelegate)), LstK_EnumerateDelegate)
			LstK_Current = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "LstK_Current"), GetType(LstK_CurrentDelegate)), LstK_CurrentDelegate)
			LstK_MoveNext = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "LstK_MoveNext"), GetType(LstK_MoveNextDelegate)), LstK_MoveNextDelegate)
			LstK_MoveReset = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "LstK_MoveReset"), GetType(LstK_MoveResetDelegate)), LstK_MoveResetDelegate)
			LstK_FindByVidPid = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "LstK_FindByVidPid"), GetType(LstK_FindByVidPidDelegate)), LstK_FindByVidPidDelegate)
			LstK_Count = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "LstK_Count"), GetType(LstK_CountDelegate)), LstK_CountDelegate)
			HotK_Init = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "HotK_Init"), GetType(HotK_InitDelegate)), HotK_InitDelegate)
			HotK_Free = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "HotK_Free"), GetType(HotK_FreeDelegate)), HotK_FreeDelegate)
			HotK_FreeAll = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "HotK_FreeAll"), GetType(HotK_FreeAllDelegate)), HotK_FreeAllDelegate)
			OvlK_Acquire = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "OvlK_Acquire"), GetType(OvlK_AcquireDelegate)), OvlK_AcquireDelegate)
			OvlK_Release = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "OvlK_Release"), GetType(OvlK_ReleaseDelegate)), OvlK_ReleaseDelegate)
			OvlK_Init = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "OvlK_Init"), GetType(OvlK_InitDelegate)), OvlK_InitDelegate)
			OvlK_Free = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "OvlK_Free"), GetType(OvlK_FreeDelegate)), OvlK_FreeDelegate)
			OvlK_GetEventHandle = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "OvlK_GetEventHandle"), GetType(OvlK_GetEventHandleDelegate)), OvlK_GetEventHandleDelegate)
			OvlK_Wait = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "OvlK_Wait"), GetType(OvlK_WaitDelegate)), OvlK_WaitDelegate)
			OvlK_WaitOldest = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "OvlK_WaitOldest"), GetType(OvlK_WaitOldestDelegate)), OvlK_WaitOldestDelegate)
			OvlK_WaitOrCancel = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "OvlK_WaitOrCancel"), GetType(OvlK_WaitOrCancelDelegate)), OvlK_WaitOrCancelDelegate)
			OvlK_WaitAndRelease = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "OvlK_WaitAndRelease"), GetType(OvlK_WaitAndReleaseDelegate)), OvlK_WaitAndReleaseDelegate)
			OvlK_IsComplete = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "OvlK_IsComplete"), GetType(OvlK_IsCompleteDelegate)), OvlK_IsCompleteDelegate)
			OvlK_ReUse = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "OvlK_ReUse"), GetType(OvlK_ReUseDelegate)), OvlK_ReUseDelegate)
			StmK_Init = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "StmK_Init"), GetType(StmK_InitDelegate)), StmK_InitDelegate)
			StmK_Free = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "StmK_Free"), GetType(StmK_FreeDelegate)), StmK_FreeDelegate)
			StmK_Start = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "StmK_Start"), GetType(StmK_StartDelegate)), StmK_StartDelegate)
			StmK_Stop = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "StmK_Stop"), GetType(StmK_StopDelegate)), StmK_StopDelegate)
			StmK_Read = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "StmK_Read"), GetType(StmK_ReadDelegate)), StmK_ReadDelegate)
			StmK_Write = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "StmK_Write"), GetType(StmK_WriteDelegate)), StmK_WriteDelegate)
			IsoK_Init = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "IsoK_Init"), GetType(IsoK_InitDelegate)), IsoK_InitDelegate)
			IsoK_Free = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "IsoK_Free"), GetType(IsoK_FreeDelegate)), IsoK_FreeDelegate)
			IsoK_SetPackets = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "IsoK_SetPackets"), GetType(IsoK_SetPacketsDelegate)), IsoK_SetPacketsDelegate)
			IsoK_SetPacket = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "IsoK_SetPacket"), GetType(IsoK_SetPacketDelegate)), IsoK_SetPacketDelegate)
			IsoK_GetPacket = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "IsoK_GetPacket"), GetType(IsoK_GetPacketDelegate)), IsoK_GetPacketDelegate)
			IsoK_EnumPackets = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "IsoK_EnumPackets"), GetType(IsoK_EnumPacketsDelegate)), IsoK_EnumPacketsDelegate)
			IsoK_ReUse = DirectCast(Marshal.GetDelegateForFunctionPointer(GetProcAddress(mModuleLibusbK, "IsoK_ReUse"), GetType(IsoK_ReUseDelegate)), IsoK_ReUseDelegate)
		End Sub

		<DllImport("kernel32.dll")> _
		Private Shared Function LoadLibraryEx(lpFileName As String, hReservedNull As IntPtr, dwFlags As LoadLibraryFlags) As IntPtr
		End Function

		Private Shared ReadOnly mModuleLibusbK As IntPtr = IntPtr.Zero

		#End Region
	End Class

	#End Region

	#Region "Enumerations"

	''' <Summary>Values used in the \c bmAttributes field of a \ref USB_ENDPOINT_DESCRIPTOR</Summary>
	Public Enum USBD_PIPE_TYPE
		''' <Summary>Indicates a control endpoint</Summary>
		UsbdPipeTypeControl

		''' <Summary>Indicates an isochronous endpoint</Summary>
		UsbdPipeTypeIsochronous

		''' <Summary>Indicates a bulk endpoint</Summary>
		UsbdPipeTypeBulk

		''' <Summary>Indicates an interrupt endpoint</Summary>
		UsbdPipeTypeInterrupt
	End Enum

	''' <Summary>Additional ISO transfer flags.</Summary>
	<Flags> _
	Public Enum KISO_FLAG
		NONE = 0

		''' <Summary>Do not start the transfer immediately, instead use \ref KISO_CONTEXT::StartFrame.</Summary>
		SET_START_FRAME = &H1
	End Enum

	''' <Summary>Handle type enumeration.</Summary>
	Public Enum KLIB_HANDLE_TYPE
		''' <Summary>Hot plug handle. \ref KHOT_HANDLE</Summary>
		HOTK

		''' <Summary>USB handle. \ref KUSB_HANDLE</Summary>
		USBK

		''' <Summary>Shared USB handle. \ref KUSB_HANDLE</Summary>
		USBSHAREDK

		''' <Summary>Device list handle. \ref KLST_HANDLE</Summary>
		LSTK

		''' <Summary>Device info handle. \ref KLST_DEVINFO_HANDLE</Summary>
		LSTINFOK

		''' <Summary>Overlapped handle. \ref KOVL_HANDLE</Summary>
		OVLK

		''' <Summary>Overlapped pool handle. \ref KOVL_POOL_HANDLE</Summary>
		OVLPOOLK

		''' <Summary>Pipe stream handle. \ref KSTM_HANDLE</Summary>
		STMK

		''' <Summary>Max handle type count.</Summary>
		COUNT
	End Enum

	''' <Summary>Device list sync flags.</Summary>
	<Flags> _
	Public Enum KLST_SYNC_FLAG
		''' <Summary>Cleared/invalid state.</Summary>
		NONE = 0

		''' <Summary>Unchanged state,</Summary>
		UNCHANGED = &H1

		''' <Summary>Added (Arrival) state,</Summary>
		ADDED = &H2

		''' <Summary>Removed (Unplugged) state,</Summary>
		REMOVED = &H4

		''' <Summary>Connect changed state.</Summary>
		CONNECT_CHANGE = &H8

		''' <Summary>All states.</Summary>
		MASK = &Hf
	End Enum

	''' <Summary>Device list initialization flags.</Summary>
	<Flags> _
	Public Enum KLST_FLAG
		''' <Summary>No flags (or 0)</Summary>
		NONE = 0

		''' <Summary>Enable listings for the raw device interface GUID \b only. {A5DCBF10-6530-11D2-901F-00C04FB951ED}</Summary>
		INCLUDE_RAWGUID = &H1

		''' <Summary>List all libusbK devices including those not currently connected.</Summary>
		INCLUDE_DISCONNECT = &H2
	End Enum

	''' <Summary>bmRequest.Dir</Summary>
	Public Enum BMREQUEST_DIR
		HOST_TO_DEVICE = 0
		DEVICE_TO_HOST = 1
	End Enum

	''' <Summary>bmRequest.Type</Summary>
	Public Enum BMREQUEST_TYPE
		''' <Summary>Standard request. See \ref USB_REQUEST_ENUM</Summary>
		STANDARD = 0

		''' <Summary>Class-specific request.</Summary>
		[CLASS] = 1

		''' <Summary>Vendor-specific request</Summary>
		VENDOR = 2
	End Enum

	''' <Summary>bmRequest.Recipient</Summary>
	Public Enum BMREQUEST_RECIPIENT
		''' <Summary>Request is for a device.</Summary>
		DEVICE = 0

		''' <Summary>Request is for an interface of a device.</Summary>
		[INTERFACE] = 1

		''' <Summary>Request is for an endpoint of a device.</Summary>
		ENDPOINT = 2

		''' <Summary>Request is for a vendor-specific purpose.</Summary>
		OTHER = 3
	End Enum

	''' <Summary>Values for the bits returned by the \ref USB_REQUEST_GET_STATUS request.</Summary>
	Public Enum USB_GETSTATUS
		''' <Summary>Device is self powered</Summary>
		SELF_POWERED = &H1

		''' <Summary>Device can wake the system from a low power/sleeping state.</Summary>
		REMOTE_WAKEUP_ENABLED = &H2
	End Enum

	''' <Summary>Standard USB descriptor types. For more information, see section 9-5 of the USB 3.0 specifications.</Summary>
	Public Enum USB_DESCRIPTOR_TYPE
		''' <Summary>Device descriptor type.</Summary>
		DEVICE = &H1

		''' <Summary>Configuration descriptor type.</Summary>
		CONFIGURATION = &H2

		''' <Summary>String descriptor type.</Summary>
		[STRING] = &H3

		''' <Summary>Interface descriptor type.</Summary>
		[INTERFACE] = &H4

		''' <Summary>Endpoint descriptor type.</Summary>
		ENDPOINT = &H5

		''' <Summary>Device qualifier descriptor type.</Summary>
		DEVICE_QUALIFIER = &H6

		''' <Summary>Config power descriptor type.</Summary>
		CONFIG_POWER = &H7

		''' <Summary>Interface power descriptor type.</Summary>
		INTERFACE_POWER = &H8

		''' <Summary>Interface association descriptor type.</Summary>
		INTERFACE_ASSOCIATION = &Hb
	End Enum

	''' <Summary>Usb handle specific properties that can be retrieved with \ref UsbK_GetProperty.</Summary>
	Public Enum KUSB_PROPERTY
		''' <Summary>Get the internal device file handle used for operations such as GetOverlappedResult or DeviceIoControl.</Summary>
		DEVICE_FILE_HANDLE

		COUNT
	End Enum

	''' <Summary>Supported driver id enumeration.</Summary>
	Public Enum KUSB_DRVID
		''' <Summary>libusbK.sys driver ID</Summary>
		LIBUSBK

		''' <Summary>libusb0.sys driver ID</Summary>
		LIBUSB0

		''' <Summary>WinUSB.sys driver ID</Summary>
		WINUSB

		''' <Summary>libusb0.sys filter driver ID</Summary>
		LIBUSB0_FILTER

		''' <Summary>Supported driver count</Summary>
		COUNT
	End Enum

	''' <Summary>Supported function id enumeration.</Summary>
	Public Enum KUSB_FNID
		''' <Summary>\ref UsbK_Init dynamic driver function id.</Summary>
		Init

		''' <Summary>\ref UsbK_Free dynamic driver function id.</Summary>
		Free

		''' <Summary>\ref UsbK_ClaimInterface dynamic driver function id.</Summary>
		ClaimInterface

		''' <Summary>\ref UsbK_ReleaseInterface dynamic driver function id.</Summary>
		ReleaseInterface

		''' <Summary>\ref UsbK_SetAltInterface dynamic driver function id.</Summary>
		SetAltInterface

		''' <Summary>\ref UsbK_GetAltInterface dynamic driver function id.</Summary>
		GetAltInterface

		''' <Summary>\ref UsbK_GetDescriptor dynamic driver function id.</Summary>
		GetDescriptor

		''' <Summary>\ref UsbK_ControlTransfer dynamic driver function id.</Summary>
		ControlTransfer

		''' <Summary>\ref UsbK_SetPowerPolicy dynamic driver function id.</Summary>
		SetPowerPolicy

		''' <Summary>\ref UsbK_GetPowerPolicy dynamic driver function id.</Summary>
		GetPowerPolicy

		''' <Summary>\ref UsbK_SetConfiguration dynamic driver function id.</Summary>
		SetConfiguration

		''' <Summary>\ref UsbK_GetConfiguration dynamic driver function id.</Summary>
		GetConfiguration

		''' <Summary>\ref UsbK_ResetDevice dynamic driver function id.</Summary>
		ResetDevice

		''' <Summary>\ref UsbK_Initialize dynamic driver function id.</Summary>
		Initialize

		''' <Summary>\ref UsbK_SelectInterface dynamic driver function id.</Summary>
		SelectInterface

		''' <Summary>\ref UsbK_GetAssociatedInterface dynamic driver function id.</Summary>
		GetAssociatedInterface

		''' <Summary>\ref UsbK_Clone dynamic driver function id.</Summary>
		Clone

		''' <Summary>\ref UsbK_QueryInterfaceSettings dynamic driver function id.</Summary>
		QueryInterfaceSettings

		''' <Summary>\ref UsbK_QueryDeviceInformation dynamic driver function id.</Summary>
		QueryDeviceInformation

		''' <Summary>\ref UsbK_SetCurrentAlternateSetting dynamic driver function id.</Summary>
		SetCurrentAlternateSetting

		''' <Summary>\ref UsbK_GetCurrentAlternateSetting dynamic driver function id.</Summary>
		GetCurrentAlternateSetting

		''' <Summary>\ref UsbK_QueryPipe dynamic driver function id.</Summary>
		QueryPipe

		''' <Summary>\ref UsbK_SetPipePolicy dynamic driver function id.</Summary>
		SetPipePolicy

		''' <Summary>\ref UsbK_GetPipePolicy dynamic driver function id.</Summary>
		GetPipePolicy

		''' <Summary>\ref UsbK_ReadPipe dynamic driver function id.</Summary>
		ReadPipe

		''' <Summary>\ref UsbK_WritePipe dynamic driver function id.</Summary>
		WritePipe

		''' <Summary>\ref UsbK_ResetPipe dynamic driver function id.</Summary>
		ResetPipe

		''' <Summary>\ref UsbK_AbortPipe dynamic driver function id.</Summary>
		AbortPipe

		''' <Summary>\ref UsbK_FlushPipe dynamic driver function id.</Summary>
		FlushPipe

		''' <Summary>\ref UsbK_IsoReadPipe dynamic driver function id.</Summary>
		IsoReadPipe

		''' <Summary>\ref UsbK_IsoWritePipe dynamic driver function id.</Summary>
		IsoWritePipe

		''' <Summary>\ref UsbK_GetCurrentFrameNumber dynamic driver function id.</Summary>
		GetCurrentFrameNumber

		''' <Summary>\ref UsbK_GetOverlappedResult dynamic driver function id.</Summary>
		GetOverlappedResult

		''' <Summary>\ref UsbK_GetProperty dynamic driver function id.</Summary>
		GetProperty


		''' <Summary>Supported function count</Summary>
		COUNT
	End Enum

	''' <Summary>Hot plug config flags.</Summary>
	<Flags> _
	Public Enum KHOT_FLAG
		''' <Summary>No flags (or 0)</Summary>
		NONE

		''' <Summary>Notify all devices which match upon a succuessful call to \ref HotK_Init.</Summary>
		PLUG_ALL_ON_INIT = &H1

		''' <Summary>Allow other \ref KHOT_HANDLE instances to consume this match.</Summary>
		PASS_DUPE_INSTANCE = &H2

		''' <Summary>If a \c UserHwnd is specified, use \c PostMessage instead of \c SendMessage.</Summary>
		POST_USER_MESSAGE = &H4
	End Enum

	''' <Summary>\c WaitFlags used by \ref OvlK_Wait.</Summary>
	<Flags> _
	Public Enum KOVL_WAIT_FLAG
		''' <Summary>Do not perform any additional actions upon exiting \ref OvlK_Wait.</Summary>
		NONE = 0

		''' <Summary>If the i/o operation completes successfully, release the OverlappedK back to it's pool.</Summary>
		RELEASE_ON_SUCCESS = &H1

		''' <Summary>If the i/o operation fails, release the OverlappedK back to it's pool.</Summary>
		RELEASE_ON_FAIL = &H2

		''' <Summary>If the i/o operation fails or completes successfully, release the OverlappedK back to its pool. Perform no actions if it times-out.</Summary>
		RELEASE_ON_SUCCESS_FAIL = &H3

		''' <Summary>If the i/o operation times-out cancel it, but do not release the OverlappedK back to its pool.</Summary>
		CANCEL_ON_TIMEOUT = &H4

		''' <Summary>If the i/o operation times-out, cancel it and release the OverlappedK back to its pool.</Summary>
		RELEASE_ON_TIMEOUT = &Hc

		''' <Summary>Always release the OverlappedK back to its pool.  If the operation timed-out, cancel it before releasing back to its pool.</Summary>
		RELEASE_ALWAYS = &Hf

		''' <Summary>Uses alterable wait functions.  See http://msdn.microsoft.com/en-us/library/windows/desktop/ms687036%28v=vs.85%29.aspx</Summary>
		ALERTABLE = &H10
	End Enum

	''' <Summary>\c Overlapped pool config flags.</Summary>
	<Flags> _
	Public Enum KOVL_POOL_FLAG
		NONE = 0
	End Enum

	''' <Summary>Stream config flags.</Summary>
	<Flags> _
	Public Enum KSTM_FLAG As UInteger
		''' <Summary>None</Summary>
		NONE = 0
		NO_PARTIAL_XFERS = &H100000
		USE_TIMEOUT = &H80000000UI
		TIMEOUT_MASK = &H1ffff
	End Enum

	''' <Summary>Stream config flags.</Summary>
	Public Enum KSTM_COMPLETE_RESULT
		''' <Summary>Valid</Summary>
		VALID = 0

		''' <Summary>Invalid</Summary>
		INVALID
	End Enum

	#End Region

	#Region "Structs"

	''' <Summary>The \c WINUSB_PIPE_INFORMATION structure contains pipe information that the \ref UsbK_QueryPipe routine retrieves.</Summary>
	<StructLayout(LayoutKind.Sequential, CharSet := CharSet.Ansi)> _
	Public Structure WINUSB_PIPE_INFORMATION
		''' <Summary>A \c USBD_PIPE_TYPE enumeration value that specifies the pipe type</Summary>
		Public PipeType As USBD_PIPE_TYPE

		''' <Summary>The pipe identifier (ID)</Summary>
		Public PipeId As Byte

		''' <Summary>The maximum size, in bytes, of the packets that are transmitted on the pipe</Summary>
		Public MaximumPacketSize As UShort

		''' <Summary>The pipe interval</Summary>
		Public Interval As Byte


		Public Overrides Function ToString() As String
			Return String.Format("PipeType: {0}" & vbLf & "PipeId: {1}" & vbLf & "MaximumPacketSize: {2}" & vbLf & "Interval: {3}" & vbLf, PipeType, PipeId.ToString("X2") & "h", MaximumPacketSize, Interval.ToString("X2") & "h")
		End Function
	End Structure

	''' <Summary>The \c WINUSB_SETUP_PACKET structure describes a USB setup packet.</Summary>
	<StructLayout(LayoutKind.Sequential, CharSet := CharSet.Ansi, Pack := 1)> _
	Public Structure WINUSB_SETUP_PACKET
		''' <Summary>The request type. The values that are assigned to this member are defined in Table 9.2 of section 9.3 of the Universal Serial Bus (USB) specification (www.usb.org).</Summary>
		Public RequestType As Byte

		''' <Summary>The device request. The values that are assigned to this member are defined in Table 9.3 of section 9.4 of the Universal Serial Bus (USB) specification.</Summary>
		Public Request As Byte

		''' <Summary>The meaning of this member varies according to the request. For an explanation of this member, see the Universal Serial Bus (USB) specification.</Summary>
		Public Value As UShort

		''' <Summary>The meaning of this member varies according to the request. For an explanation of this member, see the Universal Serial Bus (USB) specification.</Summary>
		Public Index As UShort

		''' <Summary>The number of bytes to transfer. (not including the \c WINUSB_SETUP_PACKET itself)</Summary>
		Public Length As UShort


		Public Overrides Function ToString() As String
			Return String.Format("RequestType: {0}" & vbLf & "Request: {1}" & vbLf & "Value: {2}" & vbLf & "Index: {3}" & vbLf & "Length: {4}" & vbLf, RequestType.ToString("X2") & "h", Request.ToString("X2") & "h", Value.ToString("X4") & "h", Index.ToString("X4") & "h", Length)
		End Function
	End Structure

	''' <Summary>Structure describing an isochronous transfer packet.</Summary>
	<StructLayout(LayoutKind.Sequential, CharSet := CharSet.Ansi, Pack := 1)> _
	Public Structure KISO_PACKET
		''' <Summary>Specifies the offset, in bytes, of the buffer for this packet from the beginning of the entire isochronous transfer data buffer.</Summary>
		Public Offset As Integer

		''' <Summary>Set by the host controller to indicate the actual number of bytes received by the device for isochronous IN transfers. Length not used for isochronous OUT transfers.</Summary>
		Public Length As UShort

		''' <Summary>Contains the 16 least significant USBD status bits, on return from the host controller driver, of this transfer packet.</Summary>
		Public Status As UShort


		Public Overrides Function ToString() As String
			Return String.Format("Offset: {0}" & vbLf & "Length: {1}" & vbLf & "Status: {2}" & vbLf, Offset, Length, Status.ToString("X4") & "h")
		End Function
	End Structure

	<StructLayout(LayoutKind.Sequential)> _
	Public Structure KISO_CONTEXT
		Private ReadOnly mHandlePtr As IntPtr

		Public Sub New(Handle As IntPtr)
			mHandlePtr = Handle
		End Sub

		Public ReadOnly Property Pointer() As IntPtr
			Get
				Return mHandlePtr
			End Get
		End Property

		''' <summary>KISO_CONTEXT_MAP is used for calculating field offsets only</summary>
		<StructLayout(LayoutKind.Sequential, CharSet := CharSet.Ansi, Pack := 1)> _
		Private Structure KISO_CONTEXT_MAP
			''' <Summary>Additional ISO transfer flags. See \ref KISO_FLAG.</Summary>
			Private ReadOnly Flags As KISO_FLAG

			''' <Summary>Specifies the frame number that the transfer should begin on (0 for ASAP).</Summary>
			Private ReadOnly StartFrame As Integer

			''' <Summary>Contains the number of packets that completed with an error condition on return from the host controller driver.</Summary>
			Private ReadOnly ErrorCount As Short

			''' <Summary>Specifies the number of packets that are described by the variable-length array member \c IsoPacket.</Summary>
			Private ReadOnly NumberOfPackets As Short

			''' <Summary>Contains the URB Hdr.Status value on return from the host controller driver.</Summary>
			Private ReadOnly UrbHdrStatus As Integer
		End Structure

		Private Shared ReadOnly ofsFlags As Integer = Marshal.OffsetOf(GetType(KISO_CONTEXT_MAP), "Flags").ToInt32()
		Private Shared ReadOnly ofsStartFrame As Integer = Marshal.OffsetOf(GetType(KISO_CONTEXT_MAP), "StartFrame").ToInt32()
		Private Shared ReadOnly ofsErrorCount As Integer = Marshal.OffsetOf(GetType(KISO_CONTEXT_MAP), "ErrorCount").ToInt32()
		Private Shared ReadOnly ofsNumberOfPackets As Integer = Marshal.OffsetOf(GetType(KISO_CONTEXT_MAP), "NumberOfPackets").ToInt32()
		Private Shared ReadOnly ofsUrbHdrStatus As Integer = Marshal.OffsetOf(GetType(KISO_CONTEXT_MAP), "UrbHdrStatus").ToInt32()


		''' <Summary>Additional ISO transfer flags. See \ref KISO_FLAG.</Summary>
		Public ReadOnly Property Flags() As KISO_FLAG
			Get
				Return CType(Marshal.ReadInt32(mHandlePtr, ofsFlags), KISO_FLAG)
			End Get
		End Property


		''' <Summary>Specifies the frame number that the transfer should begin on (0 for ASAP).</Summary>
		Public ReadOnly Property StartFrame() As Integer
			Get
				Return Marshal.ReadInt32(mHandlePtr, ofsStartFrame)
			End Get
		End Property


		''' <Summary>Contains the number of packets that completed with an error condition on return from the host controller driver.</Summary>
		Public ReadOnly Property ErrorCount() As Short
			Get
				Return Marshal.ReadInt16(mHandlePtr, ofsErrorCount)
			End Get
		End Property


		''' <Summary>Specifies the number of packets that are described by the variable-length array member \c IsoPacket.</Summary>
		Public ReadOnly Property NumberOfPackets() As Short
			Get
				Return Marshal.ReadInt16(mHandlePtr, ofsNumberOfPackets)
			End Get
		End Property


		''' <Summary>Contains the URB Hdr.Status value on return from the host controller driver.</Summary>
		Public ReadOnly Property UrbHdrStatus() As Integer
			Get
				Return Marshal.ReadInt32(mHandlePtr, ofsUrbHdrStatus)
			End Get
		End Property


		Public Overrides Function ToString() As String
			Return String.Format("Flags: {0}" & vbLf & "StartFrame: {1}" & vbLf & "ErrorCount: {2}" & vbLf & "NumberOfPackets: {3}" & vbLf & "UrbHdrStatus: {4}" & vbLf, Flags.ToString(), StartFrame, ErrorCount, NumberOfPackets, UrbHdrStatus.ToString("X8") & "h")
		End Function
	End Structure

	''' <Summary>libusbK verson information structure.</Summary>
	<StructLayout(LayoutKind.Sequential, CharSet := CharSet.Ansi)> _
	Public Structure KLIB_VERSION
		''' <Summary>Major version number.</Summary>
		Public Major As Integer

		''' <Summary>Minor version number.</Summary>
		Public Minor As Integer

		''' <Summary>Micro version number.</Summary>
		Public Micro As Integer

		''' <Summary>Nano version number.</Summary>
		Public Nano As Integer

		Public Overrides Function ToString() As String
			Return String.Format("Major: {0}" & vbLf & "Minor: {1}" & vbLf & "Micro: {2}" & vbLf & "Nano: {3}" & vbLf, Major, Minor, Micro, Nano)
		End Function
	End Structure

	''' <Summary>Common usb device information structure</Summary>
	<StructLayout(LayoutKind.Sequential, CharSet := CharSet.Ansi)> _
	Public Structure KLST_DEV_COMMON_INFO
		''' <Summary>VendorID parsed from \ref KLST_DEVINFO::DeviceID</Summary>
		Public Vid As Integer

		''' <Summary>ProductID parsed from \ref KLST_DEVINFO::DeviceID</Summary>
		Public Pid As Integer

		''' <Summary>Composite interface number parsed from \ref KLST_DEVINFO::DeviceID.  Set to \b -1 for devices that do not have the composite parent driver.</Summary>
		Public MI As Integer

		' An ID that uniquely identifies a USB device.
		<MarshalAs(UnmanagedType.ByValTStr, SizeConst := AllKConstants.KLST_STRING_MAX_LEN)> _
		Public InstanceID As String


		Public Overrides Function ToString() As String
			Return String.Format("Vid: {0}" & vbLf & "Pid: {1}" & vbLf & "MI: {2}" & vbLf & "InstanceID: {3}" & vbLf, Vid.ToString("X4") & "h", Pid.ToString("X4") & "h", MI.ToString("X2") & "h", InstanceID)
		End Function
	End Structure

	<StructLayout(LayoutKind.Sequential)> _
	Public Structure KLST_DEVINFO_HANDLE
		Implements IKLIB_HANDLE
		Private ReadOnly mHandlePtr As IntPtr

		Public Sub New(Handle As IntPtr)
			mHandlePtr = Handle
		End Sub

		Public ReadOnly Property Pointer() As IntPtr Implements IKLIB_HANDLE.Pointer
			Get
				Return mHandlePtr
			End Get
		End Property

		Public ReadOnly Property HandleType() As KLIB_HANDLE_TYPE Implements IKLIB_HANDLE.HandleType
			Get
				Return KLIB_HANDLE_TYPE.LSTINFOK
			End Get
		End Property

		Public Function GetContext() As IntPtr Implements IKLIB_HANDLE.GetContext
			Return AllKFunctions.LibK_GetContext(mHandlePtr, HandleType)
		End Function

		Public Function SetContext(UserContext As IntPtr) As Boolean Implements IKLIB_HANDLE.SetContext
			Return AllKFunctions.LibK_SetContext(mHandlePtr, HandleType, UserContext)
		End Function

		Public Function SetCleanupCallback(CleanupCallback As KLIB_HANDLE_CLEANUP_CB) As Boolean Implements IKLIB_HANDLE.SetCleanupCallback
			Return AllKFunctions.LibK_SetCleanupCallback(mHandlePtr, HandleType, CleanupCallback)
		End Function

		''' <summary>KLST_DEVINFO_MAP is used for calculating field offsets only</summary>
		<StructLayout(LayoutKind.Sequential, CharSet := CharSet.Ansi)> _
		Private Structure KLST_DEVINFO_MAP
			''' <Summary>Common usb device information</Summary>
			Private ReadOnly Common As KLST_DEV_COMMON_INFO

			''' <Summary>Driver id this device element is using</Summary>
			Private ReadOnly DriverID As Integer

			''' <Summary>Device interface GUID</Summary>
			<MarshalAs(UnmanagedType.ByValTStr, SizeConst := AllKConstants.KLST_STRING_MAX_LEN)> _
			Private ReadOnly DeviceInterfaceGUID As String

			''' <Summary>Device instance ID.</Summary>
			<MarshalAs(UnmanagedType.ByValTStr, SizeConst := AllKConstants.KLST_STRING_MAX_LEN)> _
			Private ReadOnly DeviceID As String

			''' <Summary>Class GUID.</Summary>
			<MarshalAs(UnmanagedType.ByValTStr, SizeConst := AllKConstants.KLST_STRING_MAX_LEN)> _
			Private ReadOnly ClassGUID As String

			''' <Summary>Manufacturer name as specified in the INF file.</Summary>
			<MarshalAs(UnmanagedType.ByValTStr, SizeConst := AllKConstants.KLST_STRING_MAX_LEN)> _
			Private ReadOnly Mfg As String

			''' <Summary>Device description as specified in the INF file.</Summary>
			<MarshalAs(UnmanagedType.ByValTStr, SizeConst := AllKConstants.KLST_STRING_MAX_LEN)> _
			Private ReadOnly DeviceDesc As String

			''' <Summary>Driver service name.</Summary>
			<MarshalAs(UnmanagedType.ByValTStr, SizeConst := AllKConstants.KLST_STRING_MAX_LEN)> _
			Private ReadOnly Service As String

			''' <Summary>Unique identifier.</Summary>
			<MarshalAs(UnmanagedType.ByValTStr, SizeConst := AllKConstants.KLST_STRING_MAX_LEN)> _
			Private ReadOnly SymbolicLink As String

			''' <Summary>physical device filename used with the Windows \c CreateFile()</Summary>
			<MarshalAs(UnmanagedType.ByValTStr, SizeConst := AllKConstants.KLST_STRING_MAX_LEN)> _
			Private ReadOnly DevicePath As String

			''' <Summary>libusb-win32 filter index id.</Summary>
			Private ReadOnly LUsb0FilterIndex As Integer

			''' <Summary>Indicates the devices connection state.</Summary>
			Private ReadOnly Connected As Boolean

			''' <Summary>Synchronization flags. (internal use only)</Summary>
			Private ReadOnly SyncFlags As KLST_SYNC_FLAG

			Private ReadOnly BusNumber As Integer

			Private ReadOnly DeviceAddress As Integer

			''' <Summary>If the the device is serialized, represents the string value of \ref USB_DEVICE_DESCRIPTOR::iSerialNumber. For Devices without a \b iSerialNumber, represents the unique \b InstanceID assigned by \b Windows.</Summary>
			<MarshalAs(UnmanagedType.ByValTStr, SizeConst := AllKConstants.KLST_STRING_MAX_LEN)> _
			Private ReadOnly SerialNumber As String
		End Structure

		Private Shared ReadOnly ofsCommon As Integer = Marshal.OffsetOf(GetType(KLST_DEVINFO_MAP), "Common").ToInt32()
		Private Shared ReadOnly ofsDriverID As Integer = Marshal.OffsetOf(GetType(KLST_DEVINFO_MAP), "DriverID").ToInt32()
		Private Shared ReadOnly ofsDeviceInterfaceGUID As Integer = Marshal.OffsetOf(GetType(KLST_DEVINFO_MAP), "DeviceInterfaceGUID").ToInt32()
		Private Shared ReadOnly ofsDeviceID As Integer = Marshal.OffsetOf(GetType(KLST_DEVINFO_MAP), "DeviceID").ToInt32()
		Private Shared ReadOnly ofsClassGUID As Integer = Marshal.OffsetOf(GetType(KLST_DEVINFO_MAP), "ClassGUID").ToInt32()
		Private Shared ReadOnly ofsMfg As Integer = Marshal.OffsetOf(GetType(KLST_DEVINFO_MAP), "Mfg").ToInt32()
		Private Shared ReadOnly ofsDeviceDesc As Integer = Marshal.OffsetOf(GetType(KLST_DEVINFO_MAP), "DeviceDesc").ToInt32()
		Private Shared ReadOnly ofsService As Integer = Marshal.OffsetOf(GetType(KLST_DEVINFO_MAP), "Service").ToInt32()
		Private Shared ReadOnly ofsSymbolicLink As Integer = Marshal.OffsetOf(GetType(KLST_DEVINFO_MAP), "SymbolicLink").ToInt32()
		Private Shared ReadOnly ofsDevicePath As Integer = Marshal.OffsetOf(GetType(KLST_DEVINFO_MAP), "DevicePath").ToInt32()
		Private Shared ReadOnly ofsLUsb0FilterIndex As Integer = Marshal.OffsetOf(GetType(KLST_DEVINFO_MAP), "LUsb0FilterIndex").ToInt32()
		Private Shared ReadOnly ofsConnected As Integer = Marshal.OffsetOf(GetType(KLST_DEVINFO_MAP), "Connected").ToInt32()
		Private Shared ReadOnly ofsSyncFlags As Integer = Marshal.OffsetOf(GetType(KLST_DEVINFO_MAP), "SyncFlags").ToInt32()
		Private Shared ReadOnly ofsBusNumber As Integer = Marshal.OffsetOf(GetType(KLST_DEVINFO_MAP), "BusNumber").ToInt32()
		Private Shared ReadOnly ofsDeviceAddress As Integer = Marshal.OffsetOf(GetType(KLST_DEVINFO_MAP), "DeviceAddress").ToInt32()
		Private Shared ReadOnly ofsSerialNumber As Integer = Marshal.OffsetOf(GetType(KLST_DEVINFO_MAP), "SerialNumber").ToInt32()


		''' <Summary>Common usb device information</Summary>
		Public ReadOnly Property Common() As KLST_DEV_COMMON_INFO
			Get
				Return CType(Marshal.PtrToStructure(New IntPtr(mHandlePtr.ToInt64() + ofsCommon), GetType(KLST_DEV_COMMON_INFO)), KLST_DEV_COMMON_INFO)
			End Get
		End Property


		''' <Summary>Driver id this device element is using</Summary>
		Public ReadOnly Property DriverID() As Integer
			Get
				Return Marshal.ReadInt32(mHandlePtr, ofsDriverID)
			End Get
		End Property


		''' <Summary>Device interface GUID</Summary>
		Public ReadOnly Property DeviceInterfaceGUID() As String
			Get
				Return Marshal.PtrToStringAnsi(New IntPtr(mHandlePtr.ToInt64() + ofsDeviceInterfaceGUID))
			End Get
		End Property


		''' <Summary>Device instance ID.</Summary>
		Public ReadOnly Property DeviceID() As String
			Get
				Return Marshal.PtrToStringAnsi(New IntPtr(mHandlePtr.ToInt64() + ofsDeviceID))
			End Get
		End Property


		''' <Summary>Class GUID.</Summary>
		Public ReadOnly Property ClassGUID() As String
			Get
				Return Marshal.PtrToStringAnsi(New IntPtr(mHandlePtr.ToInt64() + ofsClassGUID))
			End Get
		End Property


		''' <Summary>Manufacturer name as specified in the INF file.</Summary>
		Public ReadOnly Property Mfg() As String
			Get
				Return Marshal.PtrToStringAnsi(New IntPtr(mHandlePtr.ToInt64() + ofsMfg))
			End Get
		End Property


		''' <Summary>Device description as specified in the INF file.</Summary>
		Public ReadOnly Property DeviceDesc() As String
			Get
				Return Marshal.PtrToStringAnsi(New IntPtr(mHandlePtr.ToInt64() + ofsDeviceDesc))
			End Get
		End Property


		''' <Summary>Driver service name.</Summary>
		Public ReadOnly Property Service() As String
			Get
				Return Marshal.PtrToStringAnsi(New IntPtr(mHandlePtr.ToInt64() + ofsService))
			End Get
		End Property


		''' <Summary>Unique identifier.</Summary>
		Public ReadOnly Property SymbolicLink() As String
			Get
				Return Marshal.PtrToStringAnsi(New IntPtr(mHandlePtr.ToInt64() + ofsSymbolicLink))
			End Get
		End Property


		''' <Summary>physical device filename used with the Windows \c CreateFile()</Summary>
		Public ReadOnly Property DevicePath() As String
			Get
				Return Marshal.PtrToStringAnsi(New IntPtr(mHandlePtr.ToInt64() + ofsDevicePath))
			End Get
		End Property


		''' <Summary>libusb-win32 filter index id.</Summary>
		Public ReadOnly Property LUsb0FilterIndex() As Integer
			Get
				Return Marshal.ReadInt32(mHandlePtr, ofsLUsb0FilterIndex)
			End Get
		End Property


		''' <Summary>Indicates the devices connection state.</Summary>
		Public ReadOnly Property Connected() As Boolean
			Get
				Return Marshal.ReadInt32(mHandlePtr, ofsConnected) <> 0
			End Get
		End Property


		''' <Summary>Synchronization flags. (internal use only)</Summary>
		Public ReadOnly Property SyncFlags() As KLST_SYNC_FLAG
			Get
				Return CType(Marshal.ReadInt32(mHandlePtr, ofsSyncFlags), KLST_SYNC_FLAG)
			End Get
		End Property


		Public ReadOnly Property BusNumber() As Integer
			Get
				Return Marshal.ReadInt32(mHandlePtr, ofsBusNumber)
			End Get
		End Property


		Public ReadOnly Property DeviceAddress() As Integer
			Get
				Return Marshal.ReadInt32(mHandlePtr, ofsDeviceAddress)
			End Get
		End Property


		''' <Summary>If the the device is serialized, represents the string value of \ref USB_DEVICE_DESCRIPTOR::iSerialNumber. For Devices without a \b iSerialNumber, represents the unique \b InstanceID assigned by \b Windows.</Summary>
		Public ReadOnly Property SerialNumber() As String
			Get
				Return Marshal.PtrToStringAnsi(New IntPtr(mHandlePtr.ToInt64() + ofsSerialNumber))
			End Get
		End Property


		Public Overrides Function ToString() As String
			Return String.Format("DriverID: {0}" & vbLf & "DeviceInterfaceGUID: {1}" & vbLf & "DeviceID: {2}" & vbLf & "ClassGUID: {3}" & vbLf & "Mfg: {4}" & vbLf & "DeviceDesc: {5}" & vbLf & "Service: {6}" & vbLf & "SymbolicLink: {7}" & vbLf & "DevicePath: {8}" & vbLf & "LUsb0FilterIndex: {9}" & vbLf & "Connected: {10}" & vbLf & "SyncFlags: {11}" & vbLf & "BusNumber: {12}" & vbLf & "DeviceAddress: {13}" & vbLf & "SerialNumber: {14}" & vbLf, DriverID, DeviceInterfaceGUID, DeviceID, ClassGUID, Mfg, _
				DeviceDesc, Service, SymbolicLink, DevicePath, LUsb0FilterIndex, Connected, _
				SyncFlags.ToString(), BusNumber, DeviceAddress, SerialNumber)
		End Function
	End Structure

	''' <Summary>Device list/hot-plug pattern match structure.</Summary>
	<StructLayout(LayoutKind.Sequential, CharSet := CharSet.Ansi, Size := 1024)> _
	Public Structure KLST_PATTERN_MATCH
		''' <Summary>Pattern match a device instance id.</Summary>
		<MarshalAs(UnmanagedType.ByValTStr, SizeConst := AllKConstants.KLST_STRING_MAX_LEN)> _
		Public DeviceID As String

		''' <Summary>Pattern match a device interface guid.</Summary>
		<MarshalAs(UnmanagedType.ByValTStr, SizeConst := AllKConstants.KLST_STRING_MAX_LEN)> _
		Public DeviceInterfaceGUID As String

		''' <Summary>Pattern match a symbolic link.</Summary>
		<MarshalAs(UnmanagedType.ByValTStr, SizeConst := AllKConstants.KLST_STRING_MAX_LEN)> _
		Public ClassGUID As String


		Public Overrides Function ToString() As String
			Return String.Format("DeviceID: {0}" & vbLf & "DeviceInterfaceGUID: {1}" & vbLf & "ClassGUID: {2}" & vbLf, DeviceID, DeviceInterfaceGUID, ClassGUID)
		End Function
	End Structure

	''' <Summary>A structure representing the standard USB device descriptor.</Summary>
	<StructLayout(LayoutKind.Sequential, CharSet := CharSet.Ansi, Pack := 1)> _
	Public Structure USB_DEVICE_DESCRIPTOR
		''' <Summary>Size of this descriptor (in bytes)</Summary>
		Public bLength As Byte

		''' <Summary>Descriptor type</Summary>
		Public bDescriptorType As Byte

		''' <Summary>USB specification release number in binary-coded decimal.</Summary>
		Public bcdUSB As UShort

		''' <Summary>USB-IF class code for the device</Summary>
		Public bDeviceClass As Byte

		''' <Summary>USB-IF subclass code for the device</Summary>
		Public bDeviceSubClass As Byte

		''' <Summary>USB-IF protocol code for the device</Summary>
		Public bDeviceProtocol As Byte

		''' <Summary>Maximum packet size for control endpoint 0</Summary>
		Public bMaxPacketSize0 As Byte

		''' <Summary>USB-IF vendor ID</Summary>
		Public idVendor As UShort

		''' <Summary>USB-IF product ID</Summary>
		Public idProduct As UShort

		''' <Summary>Device release number in binary-coded decimal</Summary>
		Public bcdDevice As UShort

		''' <Summary>Index of string descriptor describing manufacturer</Summary>
		Public iManufacturer As Byte

		''' <Summary>Index of string descriptor describing product</Summary>
		Public iProduct As Byte

		''' <Summary>Index of string descriptor containing device serial number</Summary>
		Public iSerialNumber As Byte

		''' <Summary>Number of possible configurations</Summary>
		Public bNumConfigurations As Byte


		Public Overrides Function ToString() As String
			Return String.Format("bLength: {0}" & vbLf & "bDescriptorType: {1}" & vbLf & "bcdUSB: {2}" & vbLf & "bDeviceClass: {3}" & vbLf & "bDeviceSubClass: {4}" & vbLf & "bDeviceProtocol: {5}" & vbLf & "bMaxPacketSize0: {6}" & vbLf & "idVendor: {7}" & vbLf & "idProduct: {8}" & vbLf & "bcdDevice: {9}" & vbLf & "iManufacturer: {10}" & vbLf & "iProduct: {11}" & vbLf & "iSerialNumber: {12}" & vbLf & "bNumConfigurations: {13}" & vbLf, bLength, bDescriptorType.ToString("X2") & "h", bcdUSB.ToString("X4") & "h", bDeviceClass.ToString("X2") & "h", bDeviceSubClass.ToString("X2") & "h", _
				bDeviceProtocol.ToString("X2") & "h", bMaxPacketSize0, idVendor.ToString("X4") & "h", idProduct.ToString("X4") & "h", bcdDevice.ToString("X4") & "h", iManufacturer, _
				iProduct, iSerialNumber, bNumConfigurations)
		End Function
	End Structure

	''' <Summary>A structure representing the standard USB endpoint descriptor.</Summary>
	<StructLayout(LayoutKind.Sequential, CharSet := CharSet.Ansi, Pack := 1)> _
	Public Structure USB_ENDPOINT_DESCRIPTOR
		''' <Summary>Size of this descriptor (in bytes)</Summary>
		Public bLength As Byte

		''' <Summary>Descriptor type</Summary>
		Public bDescriptorType As Byte

		''' <Summary>The address of the endpoint described by this descriptor.</Summary>
		Public bEndpointAddress As Byte

		''' <Summary>Attributes which apply to the endpoint when it is configured using the bConfigurationValue.</Summary>
		Public bmAttributes As Byte

		''' <Summary>Maximum packet size this endpoint is capable of sending/receiving.</Summary>
		Public wMaxPacketSize As UShort

		''' <Summary>Interval for polling endpoint for data transfers.</Summary>
		Public bInterval As Byte


		Public Overrides Function ToString() As String
			Return String.Format("bLength: {0}" & vbLf & "bDescriptorType: {1}" & vbLf & "bEndpointAddress: {2}" & vbLf & "bmAttributes: {3}" & vbLf & "wMaxPacketSize: {4}" & vbLf & "bInterval: {5}" & vbLf, bLength, bDescriptorType.ToString("X2") & "h", bEndpointAddress.ToString("X2") & "h", bmAttributes.ToString("X2") & "h", wMaxPacketSize, _
				bInterval)
		End Function
	End Structure

	''' <Summary>A structure representing the standard USB configuration descriptor.</Summary>
	<StructLayout(LayoutKind.Sequential, CharSet := CharSet.Ansi, Pack := 1)> _
	Public Structure USB_CONFIGURATION_DESCRIPTOR
		''' <Summary>Size of this descriptor (in bytes)</Summary>
		Public bLength As Byte

		''' <Summary>Descriptor type</Summary>
		Public bDescriptorType As Byte

		''' <Summary>Total length of data returned for this configuration</Summary>
		Public wTotalLength As UShort

		''' <Summary>Number of interfaces supported by this configuration</Summary>
		Public bNumInterfaces As Byte

		''' <Summary>Identifier value for this configuration</Summary>
		Public bConfigurationValue As Byte

		''' <Summary>Index of string descriptor describing this configuration</Summary>
		Public iConfiguration As Byte

		''' <Summary>Configuration characteristics</Summary>
		Public bmAttributes As Byte

		''' <Summary>Maximum power consumption of the USB device from this bus in this configuration when the device is fully operation.</Summary>
		Public MaxPower As Byte

		Public Overrides Function ToString() As String
			Return String.Format("bLength: {0}" & vbLf & "bDescriptorType: {1}" & vbLf & "wTotalLength: {2}" & vbLf & "bNumInterfaces: {3}" & vbLf & "bConfigurationValue: {4}" & vbLf & "iConfiguration: {5}" & vbLf & "bmAttributes: {6}" & vbLf & "MaxPower: {7}" & vbLf, bLength, bDescriptorType.ToString("X2") & "h", wTotalLength, bNumInterfaces, bConfigurationValue, _
				iConfiguration, bmAttributes.ToString("X2") & "h", MaxPower)
		End Function
	End Structure

	''' <Summary>A structure representing the standard USB interface descriptor.</Summary>
	<StructLayout(LayoutKind.Sequential, CharSet := CharSet.Ansi, Pack := 1)> _
	Public Structure USB_INTERFACE_DESCRIPTOR
		''' <Summary>Size of this descriptor (in bytes)</Summary>
		Public bLength As Byte

		''' <Summary>Descriptor type</Summary>
		Public bDescriptorType As Byte

		''' <Summary>Number of this interface</Summary>
		Public bInterfaceNumber As Byte

		''' <Summary>Value used to select this alternate setting for this interface</Summary>
		Public bAlternateSetting As Byte

		''' <Summary>Number of endpoints used by this interface (excluding the control endpoint)</Summary>
		Public bNumEndpoints As Byte

		''' <Summary>USB-IF class code for this interface</Summary>
		Public bInterfaceClass As Byte

		''' <Summary>USB-IF subclass code for this interface</Summary>
		Public bInterfaceSubClass As Byte

		''' <Summary>USB-IF protocol code for this interface</Summary>
		Public bInterfaceProtocol As Byte

		''' <Summary>Index of string descriptor describing this interface</Summary>
		Public iInterface As Byte


		Public Overrides Function ToString() As String
			Return String.Format("bLength: {0}" & vbLf & "bDescriptorType: {1}" & vbLf & "bInterfaceNumber: {2}" & vbLf & "bAlternateSetting: {3}" & vbLf & "bNumEndpoints: {4}" & vbLf & "bInterfaceClass: {5}" & vbLf & "bInterfaceSubClass: {6}" & vbLf & "bInterfaceProtocol: {7}" & vbLf & "iInterface: {8}" & vbLf, bLength, bDescriptorType.ToString("X2") & "h", bInterfaceNumber, bAlternateSetting, bNumEndpoints, _
				bInterfaceClass.ToString("X2") & "h", bInterfaceSubClass.ToString("X2") & "h", bInterfaceProtocol.ToString("X2") & "h", iInterface)
		End Function
	End Structure

	''' <Summary>A structure representing the standard USB string descriptor.</Summary>
	<StructLayout(LayoutKind.Sequential, CharSet := CharSet.Unicode, Pack := 1)> _
	Public Structure USB_STRING_DESCRIPTOR
		''' <Summary>Size of this descriptor (in bytes)</Summary>
		Public bLength As Byte

		''' <Summary>Descriptor type</Summary>
		Public bDescriptorType As Byte

		''' <Summary>Content of the string</Summary>
		<MarshalAs(UnmanagedType.ByValTStr, SizeConst := AllKConstants.KLST_STRING_MAX_LEN)> _
		Public bString As String


		Public Overrides Function ToString() As String
			Return String.Format("bLength: {0}" & vbLf & "bDescriptorType: {1}" & vbLf & "bString: {2}" & vbLf, bLength, bDescriptorType.ToString("X2") & "h", bString)
		End Function
	End Structure

	''' <Summary>A structure representing the common USB descriptor.</Summary>
	<StructLayout(LayoutKind.Sequential, CharSet := CharSet.Ansi, Pack := 1)> _
	Public Structure USB_COMMON_DESCRIPTOR
		''' <Summary>Size of this descriptor (in bytes)</Summary>
		Public bLength As Byte

		''' <Summary>Descriptor type</Summary>
		Public bDescriptorType As Byte


		Public Overrides Function ToString() As String
			Return String.Format("bLength: {0}" & vbLf & "bDescriptorType: {1}" & vbLf, bLength, bDescriptorType.ToString("X2") & "h")
		End Function
	End Structure

	''' <Summary>Allows hardware manufacturers to define groupings of interfaces.</Summary>
	<StructLayout(LayoutKind.Sequential, CharSet := CharSet.Ansi, Pack := 1)> _
	Public Structure USB_INTERFACE_ASSOCIATION_DESCRIPTOR
		''' <Summary>Size of this descriptor (in bytes)</Summary>
		Public bLength As Byte

		''' <Summary>Descriptor type</Summary>
		Public bDescriptorType As Byte

		''' <Summary>First interface number of the set of interfaces that follow this descriptor</Summary>
		Public bFirstInterface As Byte

		''' <Summary>The Number of interfaces follow this descriptor that are considered "associated"</Summary>
		Public bInterfaceCount As Byte

		''' <Summary>\c bInterfaceClass used for this associated interfaces</Summary>
		Public bFunctionClass As Byte

		''' <Summary>\c bInterfaceSubClass used for the associated interfaces</Summary>
		Public bFunctionSubClass As Byte

		''' <Summary>\c bInterfaceProtocol used for the associated interfaces</Summary>
		Public bFunctionProtocol As Byte

		''' <Summary>Index of string descriptor describing the associated interfaces</Summary>
		Public iFunction As Byte


		Public Overrides Function ToString() As String
			Return String.Format("bLength: {0}" & vbLf & "bDescriptorType: {1}" & vbLf & "bFirstInterface: {2}" & vbLf & "bInterfaceCount: {3}" & vbLf & "bFunctionClass: {4}" & vbLf & "bFunctionSubClass: {5}" & vbLf & "bFunctionProtocol: {6}" & vbLf & "iFunction: {7}" & vbLf, bLength, bDescriptorType.ToString("X2") & "h", bFirstInterface, bInterfaceCount, bFunctionClass.ToString("X2") & "h", _
				bFunctionSubClass.ToString("X2") & "h", bFunctionProtocol.ToString("X2") & "h", iFunction)
		End Function
	End Structure

	''' <Summary>USB core driver API information structure.</Summary>
	<StructLayout(LayoutKind.Sequential, CharSet := CharSet.Ansi)> _
	Public Structure KUSB_DRIVER_API_INFO
		''' <Summary>\readonly Driver id of the driver api.</Summary>
		Public DriverID As Integer

		''' <Summary>\readonly Number of valid functions contained in the driver API.</Summary>
		Public FunctionCount As Integer


		Public Overrides Function ToString() As String
			Return String.Format("DriverID: {0}" & vbLf & "FunctionCount: {1}" & vbLf, DriverID, FunctionCount)
		End Function
	End Structure

	''' <Summary>Driver API function set structure.</Summary>
	<StructLayout(LayoutKind.Sequential, CharSet := CharSet.Ansi, Size := 512)> _
	Public Structure KUSB_DRIVER_API
		''' <Summary>Driver API information.</Summary>
		Public Info As KUSB_DRIVER_API_INFO


		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public Init As KUSB_InitDelegate


		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public Free As KUSB_FreeDelegate


		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public ClaimInterface As KUSB_ClaimInterfaceDelegate


		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public ReleaseInterface As KUSB_ReleaseInterfaceDelegate


		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public SetAltInterface As KUSB_SetAltInterfaceDelegate


		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public GetAltInterface As KUSB_GetAltInterfaceDelegate


		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public GetDescriptor As KUSB_GetDescriptorDelegate


		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public ControlTransfer As KUSB_ControlTransferDelegate


		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public SetPowerPolicy As KUSB_SetPowerPolicyDelegate


		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public GetPowerPolicy As KUSB_GetPowerPolicyDelegate


		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public SetConfiguration As KUSB_SetConfigurationDelegate


		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public GetConfiguration As KUSB_GetConfigurationDelegate


		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public ResetDevice As KUSB_ResetDeviceDelegate


		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public Initialize As KUSB_InitializeDelegate


		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public SelectInterface As KUSB_SelectInterfaceDelegate


		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public GetAssociatedInterface As KUSB_GetAssociatedInterfaceDelegate


		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public Clone As KUSB_CloneDelegate


		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public QueryInterfaceSettings As KUSB_QueryInterfaceSettingsDelegate


		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public QueryDeviceInformation As KUSB_QueryDeviceInformationDelegate


		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public SetCurrentAlternateSetting As KUSB_SetCurrentAlternateSettingDelegate


		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public GetCurrentAlternateSetting As KUSB_GetCurrentAlternateSettingDelegate


		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public QueryPipe As KUSB_QueryPipeDelegate


		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public SetPipePolicy As KUSB_SetPipePolicyDelegate


		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public GetPipePolicy As KUSB_GetPipePolicyDelegate


		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public ReadPipe As KUSB_ReadPipeDelegate


		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public WritePipe As KUSB_WritePipeDelegate


		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public ResetPipe As KUSB_ResetPipeDelegate


		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public AbortPipe As KUSB_AbortPipeDelegate


		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public FlushPipe As KUSB_FlushPipeDelegate


		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public IsoReadPipe As KUSB_IsoReadPipeDelegate


		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public IsoWritePipe As KUSB_IsoWritePipeDelegate


		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public GetCurrentFrameNumber As KUSB_GetCurrentFrameNumberDelegate


		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public GetOverlappedResult As KUSB_GetOverlappedResultDelegate


		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public GetProperty As KUSB_GetPropertyDelegate
	End Structure

	''' <Summary>Hot plug parameter structure.</Summary>
	<StructLayout(LayoutKind.Sequential, CharSet := CharSet.Ansi, Size := 2048)> _
	Public Structure KHOT_PARAMS
		''' <Summary>Hot plug event window handle to send/post messages when notifications occur.</Summary>
		Public UserHwnd As IntPtr

		''' <Summary>WM_USER message start offset used when sending/posting messages, See details.</Summary>
		Public UserMessage As Integer

		''' <Summary>Additional init/config parameters</Summary>
		Public Flags As KHOT_FLAG

		''' <Summary>File pattern matches for restricting notifcations to a single/group or all supported usb devices.</Summary>
		Public PatternMatch As KLST_PATTERN_MATCH

		''' <Summary>Hot plug event callback function invoked when notifications occur.</Summary>
		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public OnHotPlug As KHOT_PLUG_CB


		Public Overrides Function ToString() As String
			Return String.Format("UserHwnd: {0}" & vbLf & "UserMessage: {1}" & vbLf & "Flags: {2}" & vbLf, UserHwnd.ToString("X16") & "h", UserMessage.ToString("X8") & "h", Flags.ToString())
		End Function
	End Structure

	<StructLayout(LayoutKind.Sequential)> _
	Public Structure KSTM_XFER_CONTEXT
		Private ReadOnly mHandlePtr As IntPtr

		Public Sub New(Handle As IntPtr)
			mHandlePtr = Handle
		End Sub

		Public ReadOnly Property Pointer() As IntPtr
			Get
				Return mHandlePtr
			End Get
		End Property

		''' <summary>KSTM_XFER_CONTEXT_MAP is used for calculating field offsets only</summary>
		<StructLayout(LayoutKind.Sequential, CharSet := CharSet.Ansi)> _
		Private Structure KSTM_XFER_CONTEXT_MAP
			''' <Summary>Internal stream buffer.</Summary>
			Private ReadOnly Buffer As IntPtr

			''' <Summary>Size of internal stream buffer.</Summary>
			Private ReadOnly BufferSize As Integer

			''' <Summary>Number of bytes to write or number of bytes read.</Summary>
			Private ReadOnly TransferLength As Integer

			''' <Summary>User defined state.</Summary>
			Private ReadOnly UserState As IntPtr
		End Structure

		Private Shared ReadOnly ofsBuffer As Integer = Marshal.OffsetOf(GetType(KSTM_XFER_CONTEXT_MAP), "Buffer").ToInt32()
		Private Shared ReadOnly ofsBufferSize As Integer = Marshal.OffsetOf(GetType(KSTM_XFER_CONTEXT_MAP), "BufferSize").ToInt32()
		Private Shared ReadOnly ofsTransferLength As Integer = Marshal.OffsetOf(GetType(KSTM_XFER_CONTEXT_MAP), "TransferLength").ToInt32()
		Private Shared ReadOnly ofsUserState As Integer = Marshal.OffsetOf(GetType(KSTM_XFER_CONTEXT_MAP), "UserState").ToInt32()


		''' <Summary>Internal stream buffer.</Summary>
		Public ReadOnly Property Buffer() As IntPtr
			Get
				Return Marshal.ReadIntPtr(mHandlePtr, ofsBuffer)
			End Get
		End Property


		''' <Summary>Size of internal stream buffer.</Summary>
		Public ReadOnly Property BufferSize() As Integer
			Get
				Return Marshal.ReadInt32(mHandlePtr, ofsBufferSize)
			End Get
		End Property


		''' <Summary>Number of bytes to write or number of bytes read.</Summary>
		Public ReadOnly Property TransferLength() As Integer
			Get
				Return Marshal.ReadInt32(mHandlePtr, ofsTransferLength)
			End Get
		End Property


		''' <Summary>User defined state.</Summary>
		Public Property UserState() As IntPtr
			Get
				Return Marshal.ReadIntPtr(mHandlePtr, ofsUserState)
			End Get
			Set
				Marshal.WriteIntPtr(mHandlePtr, ofsUserState, value)
			End Set
		End Property


		Public Overrides Function ToString() As String
			Return String.Format("Buffer: {0}" & vbLf & "BufferSize: {1}" & vbLf & "TransferLength: {2}" & vbLf & "UserState: {3}" & vbLf, Buffer.ToString("X16") & "h", BufferSize, TransferLength, UserState.ToString("X16") & "h")
		End Function
	End Structure

	<StructLayout(LayoutKind.Sequential)> _
	Public Structure KSTM_INFO
		Private ReadOnly mHandlePtr As IntPtr

		Public Sub New(Handle As IntPtr)
			mHandlePtr = Handle
		End Sub

		Public ReadOnly Property Pointer() As IntPtr
			Get
				Return mHandlePtr
			End Get
		End Property

		''' <summary>KSTM_INFO_MAP is used for calculating field offsets only</summary>
		<StructLayout(LayoutKind.Sequential, CharSet := CharSet.Ansi)> _
		Private Structure KSTM_INFO_MAP
			''' <Summary>\ref KUSB_HANDLE this stream uses.</Summary>
			Private ReadOnly UsbHandle As IntPtr

			''' <Summary>This parameter corresponds to the bEndpointAddress field in the endpoint descriptor.</Summary>
			Private ReadOnly PipeID As Byte

			''' <Summary>Maximum transfer read/write request allowed pending.</Summary>
			Private ReadOnly MaxPendingTransfers As Integer

			''' <Summary>Maximum transfer sage size.</Summary>
			Private ReadOnly MaxTransferSize As Integer

			''' <Summary>Maximum number of I/O request allowed pending.</Summary>
			Private ReadOnly MaxPendingIO As Integer

			''' <Summary>Populated with the endpoint descriptor for the specified \c PipeID.</Summary>
			Private ReadOnly EndpointDescriptor As USB_ENDPOINT_DESCRIPTOR

			''' <Summary>Populated with the driver api for the specified \c UsbHandle.</Summary>
			Private ReadOnly DriverAPI As KUSB_DRIVER_API

			''' <Summary>Populated with the device file handle for the specified \c UsbHandle.</Summary>
			Private ReadOnly DeviceHandle As IntPtr

			''' <Summary>Stream handle.</Summary>
			Private ReadOnly StreamHandle As IntPtr

			''' <Summary>Stream info user defined state.</Summary>
			Private ReadOnly UserState As IntPtr
		End Structure

		Private Shared ReadOnly ofsUsbHandle As Integer = Marshal.OffsetOf(GetType(KSTM_INFO_MAP), "UsbHandle").ToInt32()
		Private Shared ReadOnly ofsPipeID As Integer = Marshal.OffsetOf(GetType(KSTM_INFO_MAP), "PipeID").ToInt32()
		Private Shared ReadOnly ofsMaxPendingTransfers As Integer = Marshal.OffsetOf(GetType(KSTM_INFO_MAP), "MaxPendingTransfers").ToInt32()
		Private Shared ReadOnly ofsMaxTransferSize As Integer = Marshal.OffsetOf(GetType(KSTM_INFO_MAP), "MaxTransferSize").ToInt32()
		Private Shared ReadOnly ofsMaxPendingIO As Integer = Marshal.OffsetOf(GetType(KSTM_INFO_MAP), "MaxPendingIO").ToInt32()
		Private Shared ReadOnly ofsEndpointDescriptor As Integer = Marshal.OffsetOf(GetType(KSTM_INFO_MAP), "EndpointDescriptor").ToInt32()
		Private Shared ReadOnly ofsDriverAPI As Integer = Marshal.OffsetOf(GetType(KSTM_INFO_MAP), "DriverAPI").ToInt32()
		Private Shared ReadOnly ofsDeviceHandle As Integer = Marshal.OffsetOf(GetType(KSTM_INFO_MAP), "DeviceHandle").ToInt32()
		Private Shared ReadOnly ofsStreamHandle As Integer = Marshal.OffsetOf(GetType(KSTM_INFO_MAP), "StreamHandle").ToInt32()
		Private Shared ReadOnly ofsUserState As Integer = Marshal.OffsetOf(GetType(KSTM_INFO_MAP), "UserState").ToInt32()


		''' <Summary>\ref KUSB_HANDLE this stream uses.</Summary>
		Public ReadOnly Property UsbHandle() As IntPtr
			Get
				Return Marshal.ReadIntPtr(mHandlePtr, ofsUsbHandle)
			End Get
		End Property


		''' <Summary>This parameter corresponds to the bEndpointAddress field in the endpoint descriptor.</Summary>
		Public ReadOnly Property PipeID() As Byte
			Get
				Return Marshal.ReadByte(mHandlePtr, ofsPipeID)
			End Get
		End Property


		''' <Summary>Maximum transfer read/write request allowed pending.</Summary>
		Public ReadOnly Property MaxPendingTransfers() As Integer
			Get
				Return Marshal.ReadInt32(mHandlePtr, ofsMaxPendingTransfers)
			End Get
		End Property


		''' <Summary>Maximum transfer sage size.</Summary>
		Public ReadOnly Property MaxTransferSize() As Integer
			Get
				Return Marshal.ReadInt32(mHandlePtr, ofsMaxTransferSize)
			End Get
		End Property


		''' <Summary>Maximum number of I/O request allowed pending.</Summary>
		Public ReadOnly Property MaxPendingIO() As Integer
			Get
				Return Marshal.ReadInt32(mHandlePtr, ofsMaxPendingIO)
			End Get
		End Property


		''' <Summary>Populated with the endpoint descriptor for the specified \c PipeID.</Summary>
		Public ReadOnly Property EndpointDescriptor() As USB_ENDPOINT_DESCRIPTOR
			Get
				Return CType(Marshal.PtrToStructure(New IntPtr(mHandlePtr.ToInt64() + ofsEndpointDescriptor), GetType(USB_ENDPOINT_DESCRIPTOR)), USB_ENDPOINT_DESCRIPTOR)
			End Get
		End Property


		''' <Summary>Populated with the driver api for the specified \c UsbHandle.</Summary>
		Public ReadOnly Property DriverAPI() As KUSB_DRIVER_API
			Get
				Return CType(Marshal.PtrToStructure(New IntPtr(mHandlePtr.ToInt64() + ofsDriverAPI), GetType(KUSB_DRIVER_API)), KUSB_DRIVER_API)
			End Get
		End Property


		''' <Summary>Populated with the device file handle for the specified \c UsbHandle.</Summary>
		Public ReadOnly Property DeviceHandle() As IntPtr
			Get
				Return Marshal.ReadIntPtr(mHandlePtr, ofsDeviceHandle)
			End Get
		End Property


		''' <Summary>Stream handle.</Summary>
		Public ReadOnly Property StreamHandle() As IntPtr
			Get
				Return Marshal.ReadIntPtr(mHandlePtr, ofsStreamHandle)
			End Get
		End Property


		''' <Summary>Stream info user defined state.</Summary>
		Public Property UserState() As IntPtr
			Get
				Return Marshal.ReadIntPtr(mHandlePtr, ofsUserState)
			End Get
			Set
				Marshal.WriteIntPtr(mHandlePtr, ofsUserState, value)
			End Set
		End Property


		Public Overrides Function ToString() As String
			Return String.Format("UsbHandle: {0}" & vbLf & "PipeID: {1}" & vbLf & "MaxPendingTransfers: {2}" & vbLf & "MaxTransferSize: {3}" & vbLf & "MaxPendingIO: {4}" & vbLf & "DeviceHandle: {5}" & vbLf & "StreamHandle: {6}" & vbLf & "UserState: {7}" & vbLf, UsbHandle.ToString("X16") & "h", PipeID.ToString("X2") & "h", MaxPendingTransfers, MaxTransferSize, MaxPendingIO, _
				DeviceHandle.ToString("X16") & "h", StreamHandle.ToString("X16") & "h", UserState.ToString("X16") & "h")
		End Function
	End Structure

	''' <Summary>Stream callback structure.</Summary>
	<StructLayout(LayoutKind.Sequential, CharSet := CharSet.Ansi, Size := 64)> _
	Public Structure KSTM_CALLBACK
		''' <Summary>Executed when a transfer error occurs.</Summary>
		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public [Error] As KSTM_ERROR_CB

		''' <Summary>Executed to submit a transfer.</Summary>
		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public Submit As KSTM_SUBMIT_CB

		''' <Summary>Executed when a valid transfer completes.</Summary>
		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public Complete As KSTM_COMPLETE_CB

		''' <Summary>Executed for every transfer context when the stream is started with \ref StmK_Start.</Summary>
		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public Started As KSTM_STARTED_CB

		''' <Summary>Executed for every transfer context when the stream is stopped with \ref StmK_Stop.</Summary>
		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public Stopped As KSTM_STOPPED_CB

		''' <Summary>Executed immediately after a transfer completes.</Summary>
		<MarshalAs(UnmanagedType.FunctionPtr)> _
		Public BeforeComplete As KSTM_BEFORE_COMPLETE_CB
	End Structure

	#End Region

	#Region "Delegates"

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KLIB_HANDLE_CLEANUP_CB(<[In]> Handle As IntPtr, HandleType As KLIB_HANDLE_TYPE, UserContext As IntPtr) As Integer

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KISO_ENUM_PACKETS_CB(PacketIndex As Integer, <[In]> ByRef IsoPacket As KISO_PACKET, UserState As IntPtr) As Boolean

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KLST_ENUM_DEVINFO_CB(<[In]> DeviceList As KLST_HANDLE, <[In]> DeviceInfo As KLST_DEVINFO_HANDLE, Context As IntPtr) As Boolean

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KUSB_InitDelegate(<Out> ByRef InterfaceHandle As KUSB_HANDLE, <[In]> DevInfo As KLST_DEVINFO_HANDLE) As Boolean

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KUSB_FreeDelegate(<[In]> InterfaceHandle As KUSB_HANDLE) As Boolean

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KUSB_ClaimInterfaceDelegate(<[In]> InterfaceHandle As KUSB_HANDLE, NumberOrIndex As Byte, IsIndex As Boolean) As Boolean

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KUSB_ReleaseInterfaceDelegate(<[In]> InterfaceHandle As KUSB_HANDLE, NumberOrIndex As Byte, IsIndex As Boolean) As Boolean

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KUSB_SetAltInterfaceDelegate(<[In]> InterfaceHandle As KUSB_HANDLE, NumberOrIndex As Byte, IsIndex As Boolean, AltSettingNumber As Byte) As Boolean

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KUSB_GetAltInterfaceDelegate(<[In]> InterfaceHandle As KUSB_HANDLE, NumberOrIndex As Byte, IsIndex As Boolean, ByRef AltSettingNumber As Byte) As Boolean

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KUSB_GetDescriptorDelegate(<[In]> InterfaceHandle As KUSB_HANDLE, DescriptorType As Byte, Index As Byte, LanguageID As UShort, Buffer As IntPtr, BufferLength As Integer, _
		ByRef LengthTransferred As Integer) As Boolean

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KUSB_ControlTransferDelegate(<[In]> InterfaceHandle As KUSB_HANDLE, SetupPacket As WINUSB_SETUP_PACKET, Buffer As IntPtr, BufferLength As Integer, ByRef LengthTransferred As Integer, Overlapped As IntPtr) As Boolean

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KUSB_SetPowerPolicyDelegate(<[In]> InterfaceHandle As KUSB_HANDLE, PolicyType As Integer, ValueLength As Integer, Value As IntPtr) As Boolean

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KUSB_GetPowerPolicyDelegate(<[In]> InterfaceHandle As KUSB_HANDLE, PolicyType As Integer, ByRef ValueLength As Integer, Value As IntPtr) As Boolean

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KUSB_SetConfigurationDelegate(<[In]> InterfaceHandle As KUSB_HANDLE, ConfigurationNumber As Byte) As Boolean

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KUSB_GetConfigurationDelegate(<[In]> InterfaceHandle As KUSB_HANDLE, ByRef ConfigurationNumber As Byte) As Boolean

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KUSB_ResetDeviceDelegate(<[In]> InterfaceHandle As KUSB_HANDLE) As Boolean

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KUSB_InitializeDelegate(DeviceHandle As IntPtr, <Out> ByRef InterfaceHandle As KUSB_HANDLE) As Boolean

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KUSB_SelectInterfaceDelegate(<[In]> InterfaceHandle As KUSB_HANDLE, NumberOrIndex As Byte, IsIndex As Boolean) As Boolean

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KUSB_GetAssociatedInterfaceDelegate(<[In]> InterfaceHandle As KUSB_HANDLE, AssociatedInterfaceIndex As Byte, <Out> ByRef AssociatedInterfaceHandle As KUSB_HANDLE) As Boolean

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KUSB_CloneDelegate(<[In]> InterfaceHandle As KUSB_HANDLE, <Out> ByRef DstInterfaceHandle As KUSB_HANDLE) As Boolean

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KUSB_QueryInterfaceSettingsDelegate(<[In]> InterfaceHandle As KUSB_HANDLE, AltSettingIndex As Byte, <Out> ByRef UsbAltInterfaceDescriptor As USB_INTERFACE_DESCRIPTOR) As Boolean

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KUSB_QueryDeviceInformationDelegate(<[In]> InterfaceHandle As KUSB_HANDLE, InformationType As Integer, ByRef BufferLength As Integer, Buffer As IntPtr) As Boolean

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KUSB_SetCurrentAlternateSettingDelegate(<[In]> InterfaceHandle As KUSB_HANDLE, AltSettingNumber As Byte) As Boolean

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KUSB_GetCurrentAlternateSettingDelegate(<[In]> InterfaceHandle As KUSB_HANDLE, ByRef AltSettingNumber As Byte) As Boolean

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KUSB_QueryPipeDelegate(<[In]> InterfaceHandle As KUSB_HANDLE, AltSettingNumber As Byte, PipeIndex As Byte, <Out> ByRef PipeInformation As WINUSB_PIPE_INFORMATION) As Boolean

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KUSB_SetPipePolicyDelegate(<[In]> InterfaceHandle As KUSB_HANDLE, PipeID As Byte, PolicyType As Integer, ValueLength As Integer, Value As IntPtr) As Boolean

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KUSB_GetPipePolicyDelegate(<[In]> InterfaceHandle As KUSB_HANDLE, PipeID As Byte, PolicyType As Integer, ByRef ValueLength As Integer, Value As IntPtr) As Boolean

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KUSB_ReadPipeDelegate(<[In]> InterfaceHandle As KUSB_HANDLE, PipeID As Byte, Buffer As IntPtr, BufferLength As Integer, ByRef LengthTransferred As Integer, Overlapped As IntPtr) As Boolean

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KUSB_WritePipeDelegate(<[In]> InterfaceHandle As KUSB_HANDLE, PipeID As Byte, Buffer As IntPtr, BufferLength As Integer, ByRef LengthTransferred As Integer, Overlapped As IntPtr) As Boolean

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KUSB_ResetPipeDelegate(<[In]> InterfaceHandle As KUSB_HANDLE, PipeID As Byte) As Boolean

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KUSB_AbortPipeDelegate(<[In]> InterfaceHandle As KUSB_HANDLE, PipeID As Byte) As Boolean

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KUSB_FlushPipeDelegate(<[In]> InterfaceHandle As KUSB_HANDLE, PipeID As Byte) As Boolean

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KUSB_IsoReadPipeDelegate(<[In]> InterfaceHandle As KUSB_HANDLE, PipeID As Byte, Buffer As IntPtr, BufferLength As Integer, Overlapped As IntPtr, <[In]> IsoContext As KISO_CONTEXT) As Boolean

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KUSB_IsoWritePipeDelegate(<[In]> InterfaceHandle As KUSB_HANDLE, PipeID As Byte, Buffer As IntPtr, BufferLength As Integer, Overlapped As IntPtr, <[In]> IsoContext As KISO_CONTEXT) As Boolean

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KUSB_GetCurrentFrameNumberDelegate(<[In]> InterfaceHandle As KUSB_HANDLE, ByRef FrameNumber As Integer) As Boolean

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KUSB_GetOverlappedResultDelegate(<[In]> InterfaceHandle As KUSB_HANDLE, Overlapped As IntPtr, ByRef lpNumberOfBytesTransferred As Integer, bWait As Boolean) As Boolean

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KUSB_GetPropertyDelegate(<[In]> InterfaceHandle As KUSB_HANDLE, PropertyType As KUSB_PROPERTY, ByRef PropertySize As Integer, Value As IntPtr) As Boolean

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Sub KHOT_PLUG_CB(<[In]> HotHandle As KHOT_HANDLE, <[In]> DeviceInfo As KLST_DEVINFO_HANDLE, PlugType As KLST_SYNC_FLAG)

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KSTM_ERROR_CB(<[In]> StreamInfo As KSTM_INFO, <[In]> XferContext As KSTM_XFER_CONTEXT, XferContextIndex As Integer, ErrorCode As Integer) As Integer

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KSTM_SUBMIT_CB(<[In]> StreamInfo As KSTM_INFO, <[In]> XferContext As KSTM_XFER_CONTEXT, XferContextIndex As Integer, Overlapped As IntPtr) As Integer

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KSTM_STARTED_CB(<[In]> StreamInfo As KSTM_INFO, <[In]> XferContext As KSTM_XFER_CONTEXT, XferContextIndex As Integer) As Integer

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KSTM_STOPPED_CB(<[In]> StreamInfo As KSTM_INFO, <[In]> XferContext As KSTM_XFER_CONTEXT, XferContextIndex As Integer) As Integer

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KSTM_COMPLETE_CB(<[In]> StreamInfo As KSTM_INFO, <[In]> XferContext As KSTM_XFER_CONTEXT, XferContextIndex As Integer, ErrorCode As Integer) As Integer

	<UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet := CharSet.Ansi, SetLastError := True)> _
	Public Delegate Function KSTM_BEFORE_COMPLETE_CB(<[In]> StreamInfo As KSTM_INFO, <[In]> XferContext As KSTM_XFER_CONTEXT, XferContextIndex As Integer, ByRef ErrorCode As Integer) As KSTM_COMPLETE_RESULT

	#End Region

	Public Class LstK
		Implements IDisposable
		Protected mHandleStruct As KLST_HANDLE
		Protected mbDisposed As Boolean

		Protected Sub New()
		End Sub

		#Region "IDisposable Members"

		''' <summary>Explicitly closes and frees the handle.</summary>
		Public Overridable Sub Dispose() Implements IDisposable.Dispose
			Dispose(True)
			GC.SuppressFinalize(Me)
		End Sub

		#End Region

		Protected Overrides Sub Finalize()
			Try
				Dispose(False)
			Finally
				MyBase.Finalize()
			End Try
		End Sub

		Protected Overridable Sub Dispose(disposing As Boolean)
			If Not mbDisposed Then
				If mHandleStruct.Pointer <> IntPtr.Zero Then
					AllKFunctions.LstK_Free(mHandleStruct)
					Debug.Print("{0} Dispose: Freed Handle:{1:X16}h Explicit:{2}", [GetType]().Name, mHandleStruct.Pointer.ToInt64(), disposing)
				Else
					Debug.Print("{0} Dispose: [WARNING] Handle is null", [GetType]().Name)
				End If

				mHandleStruct = New KLST_HANDLE(IntPtr.Zero)
				mbDisposed = True
			End If
		End Sub

		''' <Summary>Initializes a new usb device list containing all supported devices.</Summary>
		Protected Function Init(Flags As KLST_FLAG) As Boolean
			Dim success As Boolean = AllKFunctions.LstK_Init(mHandleStruct, Flags)

			If Not success Then
				Throw New Exception(String.Format("{0} failed initializing. ErrorCode={1:X8}h", [GetType]().Name, Marshal.GetLastWin32Error()))
			End If

			Debug.Print("{0} Init: handle 0x{1:X16}", [GetType]().Name, mHandleStruct.Pointer.ToInt64())
			Return True
		End Function

		''' <Summary>Initializes a new usb device list containing only devices matching a specific class GUID.</Summary>
		Protected Function InitEx(Flags As KLST_FLAG, ByRef PatternMatch As KLST_PATTERN_MATCH) As Boolean
			Dim success As Boolean = AllKFunctions.LstK_InitEx(mHandleStruct, Flags, PatternMatch)

			If Not success Then
				Throw New Exception(String.Format("{0} failed initializing. ErrorCode={1:X8}h", [GetType]().Name, Marshal.GetLastWin32Error()))
			End If

			Debug.Print("{0} Init: handle 0x{1:X16}", [GetType]().Name, mHandleStruct.Pointer.ToInt64())
			Return True
		End Function

		#Region "Public Members"

		''' <Summary>Initializes a new usb device list containing all supported devices.</Summary>
		Public Sub New(Flags As KLST_FLAG)
			Dim success As Boolean = AllKFunctions.LstK_Init(mHandleStruct, Flags)

			If Not success Then
				Throw New Exception(String.Format("{0} failed initializing. ErrorCode={1:X8}h", [GetType]().Name, Marshal.GetLastWin32Error()))
			End If

			Debug.Print("{0} Init: handle 0x{1:X16}", [GetType]().Name, mHandleStruct.Pointer.ToInt64())
		End Sub

		''' <Summary>Initializes a new usb device list containing only devices matching a specific class GUID.</Summary>
		Public Sub New(Flags As KLST_FLAG, ByRef PatternMatch As KLST_PATTERN_MATCH)
			Dim success As Boolean = AllKFunctions.LstK_InitEx(mHandleStruct, Flags, PatternMatch)

			If Not success Then
				Throw New Exception(String.Format("{0} failed initializing. ErrorCode={1:X8}h", [GetType]().Name, Marshal.GetLastWin32Error()))
			End If

			Debug.Print("{0} Init: handle 0x{1:X16}", [GetType]().Name, mHandleStruct.Pointer.ToInt64())
		End Sub

		''' <Summary>Counts the number of device info elements in a device list.</Summary>
		Public Overridable Function Count(ByRef Count As Integer) As Boolean
			Return AllKFunctions.LstK_Count(mHandleStruct, Count)
		End Function

		''' <Summary>Gets the \ref KLST_DEVINFO element for the current position.</Summary>
		Public Overridable Function Current(ByRef DeviceInfo As KLST_DEVINFO_HANDLE) As Boolean
			Return AllKFunctions.LstK_Current(mHandleStruct, DeviceInfo)
		End Function

		''' <Summary>Enumerates \ref KLST_DEVINFO elements of a \ref KLST_HANDLE.</Summary>
		Public Overridable Function Enumerate(EnumDevListCB As KLST_ENUM_DEVINFO_CB, Context As IntPtr) As Boolean
			Return AllKFunctions.LstK_Enumerate(mHandleStruct, EnumDevListCB, Context)
		End Function

		''' <Summary>Find a device by vendor and product id</Summary>
		Public Overridable Function FindByVidPid(Vid As Integer, Pid As Integer, ByRef DeviceInfo As KLST_DEVINFO_HANDLE) As Boolean
			Return AllKFunctions.LstK_FindByVidPid(mHandleStruct, Vid, Pid, DeviceInfo)
		End Function

		''' <summary>Calls the dispose method.</summary>
		Public Overridable Sub Free()
			Dispose()
		End Sub

		''' <summary>Gets the handle class structure.</summary>
		Public ReadOnly Property Handle() As KLST_HANDLE
			Get
				Return mHandleStruct
			End Get
		End Property

		''' <Summary>Advances the device list current \ref KLST_DEVINFO position.</Summary>
		Public Overridable Function MoveNext(ByRef DeviceInfo As KLST_DEVINFO_HANDLE) As Boolean
			Return AllKFunctions.LstK_MoveNext(mHandleStruct, DeviceInfo)
		End Function

		''' <Summary>Sets the device list to its initial position, which is before the first element in the list.</Summary>
		Public Overridable Sub MoveReset()
			AllKFunctions.LstK_MoveReset(mHandleStruct)
		End Sub

		#End Region
	End Class

	Public Class HotK
		Implements IDisposable
		Protected mHandleStruct As KHOT_HANDLE
		Protected mbDisposed As Boolean

		Protected Sub New()
		End Sub

		#Region "IDisposable Members"

		''' <summary>Explicitly closes and frees the handle.</summary>
		Public Overridable Sub Dispose() Implements IDisposable.Dispose
			Dispose(True)
			GC.SuppressFinalize(Me)
		End Sub

		#End Region

		Protected Overrides Sub Finalize()
			Try
				Dispose(False)
			Finally
				MyBase.Finalize()
			End Try
		End Sub

		Protected Overridable Sub Dispose(disposing As Boolean)
			If Not mbDisposed Then
				If mHandleStruct.Pointer <> IntPtr.Zero Then
					AllKFunctions.HotK_Free(mHandleStruct)
					Debug.Print("{0} Dispose: Freed Handle:{1:X16}h Explicit:{2}", [GetType]().Name, mHandleStruct.Pointer.ToInt64(), disposing)
				Else
					Debug.Print("{0} Dispose: [WARNING] Handle is null", [GetType]().Name)
				End If

				mHandleStruct = New KHOT_HANDLE(IntPtr.Zero)
				mbDisposed = True
			End If
		End Sub

		''' <Summary>Creates a new hot-plug handle for USB device arrival/removal event monitoring.</Summary>
		Protected Function Init(ByRef InitParams As KHOT_PARAMS) As Boolean
			Dim success As Boolean = AllKFunctions.HotK_Init(mHandleStruct, InitParams)

			If Not success Then
				Throw New Exception(String.Format("{0} failed initializing. ErrorCode={1:X8}h", [GetType]().Name, Marshal.GetLastWin32Error()))
			End If

			Debug.Print("{0} Init: handle 0x{1:X16}", [GetType]().Name, mHandleStruct.Pointer.ToInt64())
			Return True
		End Function

		#Region "Public Members"

		''' <Summary>Creates a new hot-plug handle for USB device arrival/removal event monitoring.</Summary>
		Public Sub New(ByRef InitParams As KHOT_PARAMS)
			Dim success As Boolean = AllKFunctions.HotK_Init(mHandleStruct, InitParams)

			If Not success Then
				Throw New Exception(String.Format("{0} failed initializing. ErrorCode={1:X8}h", [GetType]().Name, Marshal.GetLastWin32Error()))
			End If

			Debug.Print("{0} Init: handle 0x{1:X16}", [GetType]().Name, mHandleStruct.Pointer.ToInt64())
		End Sub

		''' <summary>Calls the dispose method.</summary>
		Public Overridable Sub Free()
			Dispose()
		End Sub

		''' <Summary>Frees all hot-plug handles initialized with \ref HotK_Init.</Summary>
		Public Overridable Sub FreeAll()
			AllKFunctions.HotK_FreeAll()
		End Sub

		''' <summary>Gets the handle class structure.</summary>
		Public ReadOnly Property Handle() As KHOT_HANDLE
			Get
				Return mHandleStruct
			End Get
		End Property

		#End Region
	End Class

	Public Class UsbK
		Implements IDisposable
		Protected driverAPI As KUSB_DRIVER_API
		Protected mHandleStruct As KUSB_HANDLE
		Protected mbDisposed As Boolean

		Protected Sub New()
		End Sub

		#Region "IDisposable Members"

		''' <summary>Explicitly closes and frees the handle.</summary>
		Public Overridable Sub Dispose() Implements IDisposable.Dispose
			Dispose(True)
			GC.SuppressFinalize(Me)
		End Sub

		#End Region

		Protected Overrides Sub Finalize()
			Try
				Dispose(False)
			Finally
				MyBase.Finalize()
			End Try
		End Sub

		Protected Overridable Sub Dispose(disposing As Boolean)
			If Not mbDisposed Then
				If mHandleStruct.Pointer <> IntPtr.Zero Then
					AllKFunctions.UsbK_Free(mHandleStruct)
					Debug.Print("{0} Dispose: Freed Handle:{1:X16}h Explicit:{2}", [GetType]().Name, mHandleStruct.Pointer.ToInt64(), disposing)
				Else
					Debug.Print("{0} Dispose: [WARNING] Handle is null", [GetType]().Name)
				End If

				mHandleStruct = New KUSB_HANDLE(IntPtr.Zero)
				mbDisposed = True
			End If
		End Sub

		''' <Summary>Creates/opens a libusbK interface handle from the device list. This is a preferred method.</Summary>
		Protected Function Init(DevInfo As KLST_DEVINFO_HANDLE) As Boolean
			Dim success As Boolean = AllKFunctions.LibK_LoadDriverAPI(driverAPI, DevInfo.DriverID)

			If Not success Then
				Throw New Exception(String.Format("{0} failed loading Driver API. ErrorCode={1:X8}h", [GetType]().Name, Marshal.GetLastWin32Error()))
			End If

			success = driverAPI.Init(mHandleStruct, DevInfo)

			If Not success Then
				Throw New Exception(String.Format("{0} failed initializing usb device. ErrorCode={1:X8}h", [GetType]().Name, Marshal.GetLastWin32Error()))
			End If

			Debug.Print("{0} Init: handle 0x{1:X16}", [GetType]().Name, mHandleStruct.Pointer.ToInt64())
			Return True
		End Function

		''' <Summary>Creates a libusbK handle for the device specified by a file handle.</Summary>
		Protected Function Initialize(DeviceHandle As IntPtr, driverID As KUSB_DRVID) As Boolean
			Dim success As Boolean = AllKFunctions.LibK_LoadDriverAPI(driverAPI, CInt(driverID))

			If Not success Then
				Throw New Exception(String.Format("{0} failed loading Driver API. ErrorCode={1:X8}h", [GetType]().Name, Marshal.GetLastWin32Error()))
			End If

			success = driverAPI.Initialize(DeviceHandle, mHandleStruct)

			If Not success Then
				Throw New Exception(String.Format("{0} failed initializing usb device. ErrorCode={1:X8}h", [GetType]().Name, Marshal.GetLastWin32Error()))
			End If

			Debug.Print("{0} Init: handle 0x{1:X16}", [GetType]().Name, mHandleStruct.Pointer.ToInt64())
			Return True
		End Function

		#Region "Public Members"

		''' <Summary>Creates/opens a libusbK interface handle from the device list. This is a preferred method.</Summary>
		Public Sub New(DevInfo As KLST_DEVINFO_HANDLE)
			Dim success As Boolean = AllKFunctions.LibK_LoadDriverAPI(driverAPI, DevInfo.DriverID)

			If Not success Then
				Throw New Exception(String.Format("{0} failed loading Driver API. ErrorCode={1:X8}h", [GetType]().Name, Marshal.GetLastWin32Error()))
			End If

			success = driverAPI.Init(mHandleStruct, DevInfo)

			If Not success Then
				Throw New Exception(String.Format("{0} failed initializing usb device. ErrorCode={1:X8}h", [GetType]().Name, Marshal.GetLastWin32Error()))
			End If

			Debug.Print("{0} Init: handle 0x{1:X16}", [GetType]().Name, mHandleStruct.Pointer.ToInt64())
		End Sub

		''' <Summary>Creates a libusbK handle for the device specified by a file handle.</Summary>
		Public Sub New(DeviceHandle As IntPtr, driverID As KUSB_DRVID)
			Dim success As Boolean = AllKFunctions.LibK_LoadDriverAPI(driverAPI, CInt(driverID))

			If Not success Then
				Throw New Exception(String.Format("{0} failed loading Driver API. ErrorCode={1:X8}h", [GetType]().Name, Marshal.GetLastWin32Error()))
			End If

			success = driverAPI.Initialize(DeviceHandle, mHandleStruct)

			If Not success Then
				Throw New Exception(String.Format("{0} failed initializing usb device. ErrorCode={1:X8}h", [GetType]().Name, Marshal.GetLastWin32Error()))
			End If

			Debug.Print("{0} Init: handle 0x{1:X16}", [GetType]().Name, mHandleStruct.Pointer.ToInt64())
		End Sub

		''' <Summary>Aborts all of the pending transfers for a pipe.</Summary>
		Public Overridable Function AbortPipe(PipeID As Byte) As Boolean
			Return driverAPI.AbortPipe(mHandleStruct, PipeID)
		End Function

		''' <Summary>Claims the specified interface by number or index.</Summary>
		Public Overridable Function ClaimInterface(NumberOrIndex As Byte, IsIndex As Boolean) As Boolean
			Return driverAPI.ClaimInterface(mHandleStruct, NumberOrIndex, IsIndex)
		End Function

		''' <Summary>Clones the specified interface handle.</Summary>
		Public Overridable Function Clone(ByRef DstInterfaceHandle As KUSB_HANDLE) As Boolean
			Return driverAPI.Clone(mHandleStruct, DstInterfaceHandle)
		End Function

		''' <Summary>Transmits control data over a default control endpoint.</Summary>
		Public Overridable Function ControlTransfer(SetupPacket As WINUSB_SETUP_PACKET, Buffer As IntPtr, BufferLength As Integer, ByRef LengthTransferred As Integer, Overlapped As IntPtr) As Boolean
			Return driverAPI.ControlTransfer(mHandleStruct, SetupPacket, Buffer, BufferLength, LengthTransferred, Overlapped)
		End Function

		''' <Summary>Transmits control data over a default control endpoint.</Summary>
		Public Overridable Function ControlTransfer(SetupPacket As WINUSB_SETUP_PACKET, Buffer As Array, BufferLength As Integer, ByRef LengthTransferred As Integer, Overlapped As IntPtr) As Boolean
			Return driverAPI.ControlTransfer(mHandleStruct, SetupPacket, Marshal.UnsafeAddrOfPinnedArrayElement(Buffer, 0), BufferLength, LengthTransferred, Overlapped)
		End Function

		''' <Summary>Transmits control data over a default control endpoint.</Summary>
		Public Overridable Function ControlTransfer(SetupPacket As WINUSB_SETUP_PACKET, Buffer As Array, BufferLength As Integer, ByRef LengthTransferred As Integer, Overlapped As KOVL_HANDLE) As Boolean
			Return driverAPI.ControlTransfer(mHandleStruct, SetupPacket, Marshal.UnsafeAddrOfPinnedArrayElement(Buffer, 0), BufferLength, LengthTransferred, Overlapped.Pointer)
		End Function

		''' <Summary>Transmits control data over a default control endpoint.</Summary>
		Public Overridable Function ControlTransfer(SetupPacket As WINUSB_SETUP_PACKET, Buffer As IntPtr, BufferLength As Integer, ByRef LengthTransferred As Integer, Overlapped As KOVL_HANDLE) As Boolean
			Return driverAPI.ControlTransfer(mHandleStruct, SetupPacket, Buffer, BufferLength, LengthTransferred, Overlapped.Pointer)
		End Function

		''' <Summary>Discards any data that is cached in a pipe.</Summary>
		Public Overridable Function FlushPipe(PipeID As Byte) As Boolean
			Return driverAPI.FlushPipe(mHandleStruct, PipeID)
		End Function

		''' <summary>Calls the dispose method.</summary>
		Public Overridable Sub Free()
			Dispose()
		End Sub

		''' <Summary>Gets the alternate setting for the specified interface.</Summary>
		Public Overridable Function GetAltInterface(NumberOrIndex As Byte, IsIndex As Boolean, ByRef AltSettingNumber As Byte) As Boolean
			Return driverAPI.GetAltInterface(mHandleStruct, NumberOrIndex, IsIndex, AltSettingNumber)
		End Function

		''' <Summary>Retrieves a handle for an associated interface.</Summary>
		Public Overridable Function GetAssociatedInterface(AssociatedInterfaceIndex As Byte, ByRef AssociatedInterfaceHandle As KUSB_HANDLE) As Boolean
			Return driverAPI.GetAssociatedInterface(mHandleStruct, AssociatedInterfaceIndex, AssociatedInterfaceHandle)
		End Function

		''' <Summary>Gets the device current configuration number.</Summary>
		Public Overridable Function GetConfiguration(ByRef ConfigurationNumber As Byte) As Boolean
			Return driverAPI.GetConfiguration(mHandleStruct, ConfigurationNumber)
		End Function

		''' <Summary>Gets the current alternate interface setting for an interface.</Summary>
		Public Overridable Function GetCurrentAlternateSetting(ByRef AltSettingNumber As Byte) As Boolean
			Return driverAPI.GetCurrentAlternateSetting(mHandleStruct, AltSettingNumber)
		End Function

		''' <Summary>Retrieves the current USB frame number.</Summary>
		Public Overridable Function GetCurrentFrameNumber(ByRef FrameNumber As Integer) As Boolean
			Return driverAPI.GetCurrentFrameNumber(mHandleStruct, FrameNumber)
		End Function

		''' <Summary>Gets the requested descriptor. This is a synchronous operation.</Summary>
		Public Overridable Function GetDescriptor(DescriptorType As Byte, Index As Byte, LanguageID As Integer, Buffer As IntPtr, BufferLength As Integer, ByRef LengthTransferred As Integer) As Boolean
			Return driverAPI.GetDescriptor(mHandleStruct, DescriptorType, Index, CUShort(LanguageID), Buffer, BufferLength, _
				LengthTransferred)
		End Function

		''' <Summary>Gets the requested descriptor. This is a synchronous operation.</Summary>
		Public Overridable Function GetDescriptor(DescriptorType As Byte, Index As Byte, LanguageID As Integer, Buffer As Array, BufferLength As Integer, ByRef LengthTransferred As Integer) As Boolean
			Return driverAPI.GetDescriptor(mHandleStruct, DescriptorType, Index, CUShort(LanguageID), Marshal.UnsafeAddrOfPinnedArrayElement(Buffer, 0), BufferLength, _
				LengthTransferred)
		End Function

		''' <Summary>Retrieves the results of an overlapped operation on the specified libusbK handle.</Summary>
		Public Overridable Function GetOverlappedResult(Overlapped As IntPtr, ByRef lpNumberOfBytesTransferred As Integer, bWait As Boolean) As Boolean
			Return driverAPI.GetOverlappedResult(mHandleStruct, Overlapped, lpNumberOfBytesTransferred, bWait)
		End Function

		''' <Summary>Retrieves the results of an overlapped operation on the specified libusbK handle.</Summary>
		Public Overridable Function GetOverlappedResult(Overlapped As KOVL_HANDLE, ByRef lpNumberOfBytesTransferred As Integer, bWait As Boolean) As Boolean
			Return driverAPI.GetOverlappedResult(mHandleStruct, Overlapped.Pointer, lpNumberOfBytesTransferred, bWait)
		End Function

		''' <Summary>Gets the policy for a specific pipe (endpoint).</Summary>
		Public Overridable Function GetPipePolicy(PipeID As Byte, PolicyType As Integer, ByRef ValueLength As Integer, Value As IntPtr) As Boolean
			Return driverAPI.GetPipePolicy(mHandleStruct, PipeID, PolicyType, ValueLength, Value)
		End Function

		''' <Summary>Gets the policy for a specific pipe (endpoint).</Summary>
		Public Overridable Function GetPipePolicy(PipeID As Byte, PolicyType As Integer, ByRef ValueLength As Integer, Value As Array) As Boolean
			Return driverAPI.GetPipePolicy(mHandleStruct, PipeID, PolicyType, ValueLength, Marshal.UnsafeAddrOfPinnedArrayElement(Value, 0))
		End Function

		''' <Summary>Gets the power policy for a device.</Summary>
		Public Overridable Function GetPowerPolicy(PolicyType As Integer, ByRef ValueLength As Integer, Value As IntPtr) As Boolean
			Return driverAPI.GetPowerPolicy(mHandleStruct, PolicyType, ValueLength, Value)
		End Function

		''' <Summary>Gets the power policy for a device.</Summary>
		Public Overridable Function GetPowerPolicy(PolicyType As Integer, ByRef ValueLength As Integer, Value As Array) As Boolean
			Return driverAPI.GetPowerPolicy(mHandleStruct, PolicyType, ValueLength, Marshal.UnsafeAddrOfPinnedArrayElement(Value, 0))
		End Function

		''' <Summary>Gets a USB device (driver specific) property from usb handle.</Summary>
		Public Overridable Function GetProperty(PropertyType As KUSB_PROPERTY, ByRef PropertySize As Integer, Value As IntPtr) As Boolean
			Return driverAPI.GetProperty(mHandleStruct, PropertyType, PropertySize, Value)
		End Function

		''' <Summary>Gets a USB device (driver specific) property from usb handle.</Summary>
		Public Overridable Function GetProperty(PropertyType As KUSB_PROPERTY, ByRef PropertySize As Integer, Value As Array) As Boolean
			Return driverAPI.GetProperty(mHandleStruct, PropertyType, PropertySize, Marshal.UnsafeAddrOfPinnedArrayElement(Value, 0))
		End Function

		''' <summary>Gets the handle class structure.</summary>
		Public ReadOnly Property Handle() As KUSB_HANDLE
			Get
				Return mHandleStruct
			End Get
		End Property

		''' <Summary>Reads from an isochronous pipe.</Summary>
		Public Overridable Function IsoReadPipe(PipeID As Byte, Buffer As IntPtr, BufferLength As Integer, Overlapped As IntPtr, IsoContext As KISO_CONTEXT) As Boolean
			Return driverAPI.IsoReadPipe(mHandleStruct, PipeID, Buffer, BufferLength, Overlapped, IsoContext)
		End Function

		''' <Summary>Reads from an isochronous pipe.</Summary>
		Public Overridable Function IsoReadPipe(PipeID As Byte, Buffer As Array, BufferLength As Integer, Overlapped As IntPtr, IsoContext As KISO_CONTEXT) As Boolean
			Return driverAPI.IsoReadPipe(mHandleStruct, PipeID, Marshal.UnsafeAddrOfPinnedArrayElement(Buffer, 0), BufferLength, Overlapped, IsoContext)
		End Function

		''' <Summary>Reads from an isochronous pipe.</Summary>
		Public Overridable Function IsoReadPipe(PipeID As Byte, Buffer As Array, BufferLength As Integer, Overlapped As KOVL_HANDLE, IsoContext As KISO_CONTEXT) As Boolean
			Return driverAPI.IsoReadPipe(mHandleStruct, PipeID, Marshal.UnsafeAddrOfPinnedArrayElement(Buffer, 0), BufferLength, Overlapped.Pointer, IsoContext)
		End Function

		''' <Summary>Reads from an isochronous pipe.</Summary>
		Public Overridable Function IsoReadPipe(PipeID As Byte, Buffer As IntPtr, BufferLength As Integer, Overlapped As KOVL_HANDLE, IsoContext As KISO_CONTEXT) As Boolean
			Return driverAPI.IsoReadPipe(mHandleStruct, PipeID, Buffer, BufferLength, Overlapped.Pointer, IsoContext)
		End Function

		''' <Summary>Writes to an isochronous pipe.</Summary>
		Public Overridable Function IsoWritePipe(PipeID As Byte, Buffer As IntPtr, BufferLength As Integer, Overlapped As IntPtr, IsoContext As KISO_CONTEXT) As Boolean
			Return driverAPI.IsoWritePipe(mHandleStruct, PipeID, Buffer, BufferLength, Overlapped, IsoContext)
		End Function

		''' <Summary>Writes to an isochronous pipe.</Summary>
		Public Overridable Function IsoWritePipe(PipeID As Byte, Buffer As Array, BufferLength As Integer, Overlapped As IntPtr, IsoContext As KISO_CONTEXT) As Boolean
			Return driverAPI.IsoWritePipe(mHandleStruct, PipeID, Marshal.UnsafeAddrOfPinnedArrayElement(Buffer, 0), BufferLength, Overlapped, IsoContext)
		End Function

		''' <Summary>Writes to an isochronous pipe.</Summary>
		Public Overridable Function IsoWritePipe(PipeID As Byte, Buffer As Array, BufferLength As Integer, Overlapped As KOVL_HANDLE, IsoContext As KISO_CONTEXT) As Boolean
			Return driverAPI.IsoWritePipe(mHandleStruct, PipeID, Marshal.UnsafeAddrOfPinnedArrayElement(Buffer, 0), BufferLength, Overlapped.Pointer, IsoContext)
		End Function

		''' <Summary>Writes to an isochronous pipe.</Summary>
		Public Overridable Function IsoWritePipe(PipeID As Byte, Buffer As IntPtr, BufferLength As Integer, Overlapped As KOVL_HANDLE, IsoContext As KISO_CONTEXT) As Boolean
			Return driverAPI.IsoWritePipe(mHandleStruct, PipeID, Buffer, BufferLength, Overlapped.Pointer, IsoContext)
		End Function

		''' <Summary>Retrieves information about the physical device that is associated with a libusbK handle.</Summary>
		Public Overridable Function QueryDeviceInformation(InformationType As Integer, ByRef BufferLength As Integer, Buffer As IntPtr) As Boolean
			Return driverAPI.QueryDeviceInformation(mHandleStruct, InformationType, BufferLength, Buffer)
		End Function

		''' <Summary>Retrieves the interface descriptor for the specified alternate interface settings for a particular interface handle.</Summary>
		Public Overridable Function QueryInterfaceSettings(AltSettingIndex As Byte, ByRef UsbAltInterfaceDescriptor As USB_INTERFACE_DESCRIPTOR) As Boolean
			Return driverAPI.QueryInterfaceSettings(mHandleStruct, AltSettingIndex, UsbAltInterfaceDescriptor)
		End Function

		''' <Summary>Retrieves information about a pipe that is associated with an interface.</Summary>
		Public Overridable Function QueryPipe(AltSettingNumber As Byte, PipeIndex As Byte, ByRef PipeInformation As WINUSB_PIPE_INFORMATION) As Boolean
			Return driverAPI.QueryPipe(mHandleStruct, AltSettingNumber, PipeIndex, PipeInformation)
		End Function

		''' <Summary>Reads data from the specified pipe.</Summary>
		Public Overridable Function ReadPipe(PipeID As Byte, Buffer As IntPtr, BufferLength As Integer, ByRef LengthTransferred As Integer, Overlapped As IntPtr) As Boolean
			Return driverAPI.ReadPipe(mHandleStruct, PipeID, Buffer, BufferLength, LengthTransferred, Overlapped)
		End Function

		''' <Summary>Reads data from the specified pipe.</Summary>
		Public Overridable Function ReadPipe(PipeID As Byte, Buffer As Array, BufferLength As Integer, ByRef LengthTransferred As Integer, Overlapped As IntPtr) As Boolean
			Return driverAPI.ReadPipe(mHandleStruct, PipeID, Marshal.UnsafeAddrOfPinnedArrayElement(Buffer, 0), BufferLength, LengthTransferred, Overlapped)
		End Function

		''' <Summary>Reads data from the specified pipe.</Summary>
		Public Overridable Function ReadPipe(PipeID As Byte, Buffer As Array, BufferLength As Integer, ByRef LengthTransferred As Integer, Overlapped As KOVL_HANDLE) As Boolean
			Return driverAPI.ReadPipe(mHandleStruct, PipeID, Marshal.UnsafeAddrOfPinnedArrayElement(Buffer, 0), BufferLength, LengthTransferred, Overlapped.Pointer)
		End Function

		''' <Summary>Reads data from the specified pipe.</Summary>
		Public Overridable Function ReadPipe(PipeID As Byte, Buffer As IntPtr, BufferLength As Integer, ByRef LengthTransferred As Integer, Overlapped As KOVL_HANDLE) As Boolean
			Return driverAPI.ReadPipe(mHandleStruct, PipeID, Buffer, BufferLength, LengthTransferred, Overlapped.Pointer)
		End Function

		''' <Summary>Releases the specified interface by number or index.</Summary>
		Public Overridable Function ReleaseInterface(NumberOrIndex As Byte, IsIndex As Boolean) As Boolean
			Return driverAPI.ReleaseInterface(mHandleStruct, NumberOrIndex, IsIndex)
		End Function

		''' <Summary>Resets the usb device of the specified interface handle. (port cycle).</Summary>
		Public Overridable Function ResetDevice() As Boolean
			Return driverAPI.ResetDevice(mHandleStruct)
		End Function

		''' <Summary>Resets the data toggle and clears the stall condition on a pipe.</Summary>
		Public Overridable Function ResetPipe(PipeID As Byte) As Boolean
			Return driverAPI.ResetPipe(mHandleStruct, PipeID)
		End Function

		''' <Summary>Selects the specified interface by number or index as the current interface.</Summary>
		Public Overridable Function SelectInterface(NumberOrIndex As Byte, IsIndex As Boolean) As Boolean
			Return driverAPI.SelectInterface(mHandleStruct, NumberOrIndex, IsIndex)
		End Function

		''' <Summary>Sets the alternate setting of the specified interface.</Summary>
		Public Overridable Function SetAltInterface(NumberOrIndex As Byte, IsIndex As Boolean, AltSettingNumber As Byte) As Boolean
			Return driverAPI.SetAltInterface(mHandleStruct, NumberOrIndex, IsIndex, AltSettingNumber)
		End Function

		''' <Summary>Sets the device configuration number.</Summary>
		Public Overridable Function SetConfiguration(ConfigurationNumber As Byte) As Boolean
			Return driverAPI.SetConfiguration(mHandleStruct, ConfigurationNumber)
		End Function

		''' <Summary>Sets the alternate setting of an interface.</Summary>
		Public Overridable Function SetCurrentAlternateSetting(AltSettingNumber As Byte) As Boolean
			Return driverAPI.SetCurrentAlternateSetting(mHandleStruct, AltSettingNumber)
		End Function

		''' <Summary>Sets the policy for a specific pipe associated with an endpoint on the device. This is a synchronous operation.</Summary>
		Public Overridable Function SetPipePolicy(PipeID As Byte, PolicyType As Integer, ValueLength As Integer, Value As IntPtr) As Boolean
			Return driverAPI.SetPipePolicy(mHandleStruct, PipeID, PolicyType, ValueLength, Value)
		End Function

		''' <Summary>Sets the policy for a specific pipe associated with an endpoint on the device. This is a synchronous operation.</Summary>
		Public Overridable Function SetPipePolicy(PipeID As Byte, PolicyType As Integer, ValueLength As Integer, Value As Array) As Boolean
			Return driverAPI.SetPipePolicy(mHandleStruct, PipeID, PolicyType, ValueLength, Marshal.UnsafeAddrOfPinnedArrayElement(Value, 0))
		End Function

		''' <Summary>Sets the power policy for a device.</Summary>
		Public Overridable Function SetPowerPolicy(PolicyType As Integer, ValueLength As Integer, Value As IntPtr) As Boolean
			Return driverAPI.SetPowerPolicy(mHandleStruct, PolicyType, ValueLength, Value)
		End Function

		''' <Summary>Sets the power policy for a device.</Summary>
		Public Overridable Function SetPowerPolicy(PolicyType As Integer, ValueLength As Integer, Value As Array) As Boolean
			Return driverAPI.SetPowerPolicy(mHandleStruct, PolicyType, ValueLength, Marshal.UnsafeAddrOfPinnedArrayElement(Value, 0))
		End Function

		''' <Summary>Writes data to a pipe.</Summary>
		Public Overridable Function WritePipe(PipeID As Byte, Buffer As IntPtr, BufferLength As Integer, ByRef LengthTransferred As Integer, Overlapped As IntPtr) As Boolean
			Return driverAPI.WritePipe(mHandleStruct, PipeID, Buffer, BufferLength, LengthTransferred, Overlapped)
		End Function

		''' <Summary>Writes data to a pipe.</Summary>
		Public Overridable Function WritePipe(PipeID As Byte, Buffer As Array, BufferLength As Integer, ByRef LengthTransferred As Integer, Overlapped As IntPtr) As Boolean
			Return driverAPI.WritePipe(mHandleStruct, PipeID, Marshal.UnsafeAddrOfPinnedArrayElement(Buffer, 0), BufferLength, LengthTransferred, Overlapped)
		End Function

		''' <Summary>Writes data to a pipe.</Summary>
		Public Overridable Function WritePipe(PipeID As Byte, Buffer As Array, BufferLength As Integer, ByRef LengthTransferred As Integer, Overlapped As KOVL_HANDLE) As Boolean
			Return driverAPI.WritePipe(mHandleStruct, PipeID, Marshal.UnsafeAddrOfPinnedArrayElement(Buffer, 0), BufferLength, LengthTransferred, Overlapped.Pointer)
		End Function

		''' <Summary>Writes data to a pipe.</Summary>
		Public Overridable Function WritePipe(PipeID As Byte, Buffer As IntPtr, BufferLength As Integer, ByRef LengthTransferred As Integer, Overlapped As KOVL_HANDLE) As Boolean
			Return driverAPI.WritePipe(mHandleStruct, PipeID, Buffer, BufferLength, LengthTransferred, Overlapped.Pointer)
		End Function

		#End Region
	End Class

	Public Class OvlK
		Implements IDisposable
		Protected mHandleStruct As KOVL_POOL_HANDLE
		Protected mbDisposed As Boolean

		Protected Sub New()
		End Sub

		#Region "IDisposable Members"

		''' <summary>Explicitly closes and frees the handle.</summary>
		Public Overridable Sub Dispose() Implements IDisposable.Dispose
			Dispose(True)
			GC.SuppressFinalize(Me)
		End Sub

		#End Region

		Protected Overrides Sub Finalize()
			Try
				Dispose(False)
			Finally
				MyBase.Finalize()
			End Try
		End Sub

		Protected Overridable Sub Dispose(disposing As Boolean)
			If Not mbDisposed Then
				If mHandleStruct.Pointer <> IntPtr.Zero Then
					AllKFunctions.OvlK_Free(mHandleStruct)
					Debug.Print("{0} Dispose: Freed Handle:{1:X16}h Explicit:{2}", [GetType]().Name, mHandleStruct.Pointer.ToInt64(), disposing)
				Else
					Debug.Print("{0} Dispose: [WARNING] Handle is null", [GetType]().Name)
				End If

				mHandleStruct = New KOVL_POOL_HANDLE(IntPtr.Zero)
				mbDisposed = True
			End If
		End Sub

		''' <Summary>Creates a new overlapped pool.</Summary>
		Protected Function Init(UsbHandle As KUSB_HANDLE, MaxOverlappedCount As Integer, Flags As KOVL_POOL_FLAG) As Boolean
			Dim success As Boolean = AllKFunctions.OvlK_Init(mHandleStruct, UsbHandle, MaxOverlappedCount, Flags)

			If Not success Then
				Throw New Exception(String.Format("{0} failed initializing. ErrorCode={1:X8}h", [GetType]().Name, Marshal.GetLastWin32Error()))
			End If

			Debug.Print("{0} Init: handle 0x{1:X16}", [GetType]().Name, mHandleStruct.Pointer.ToInt64())
			Return True
		End Function

		#Region "Public Members"

		''' <Summary>Creates a new overlapped pool.</Summary>
		Public Sub New(UsbHandle As KUSB_HANDLE, MaxOverlappedCount As Integer, Flags As KOVL_POOL_FLAG)
			Dim success As Boolean = AllKFunctions.OvlK_Init(mHandleStruct, UsbHandle, MaxOverlappedCount, Flags)

			If Not success Then
				Throw New Exception(String.Format("{0} failed initializing. ErrorCode={1:X8}h", [GetType]().Name, Marshal.GetLastWin32Error()))
			End If

			Debug.Print("{0} Init: handle 0x{1:X16}", [GetType]().Name, mHandleStruct.Pointer.ToInt64())
		End Sub

		''' <Summary>Gets a preallocated \c OverlappedK structure from the specified/default pool.</Summary>
		Public Overridable Function Acquire(ByRef OverlappedK As KOVL_HANDLE) As Boolean
			Return AllKFunctions.OvlK_Acquire(OverlappedK, mHandleStruct)
		End Function

		''' <summary>Calls the dispose method.</summary>
		Public Overridable Sub Free()
			Dispose()
		End Sub

		''' <Summary>Returns the internal event handle used to signal IO operations.</Summary>
		Public Overridable Function GetEventHandle(OverlappedK As KOVL_HANDLE) As IntPtr
			Return AllKFunctions.OvlK_GetEventHandle(OverlappedK)
		End Function

		''' <summary>Gets the handle class structure.</summary>
		Public ReadOnly Property Handle() As KOVL_POOL_HANDLE
			Get
				Return mHandleStruct
			End Get
		End Property

		''' <Summary>Checks for i/o completion; returns immediately. (polling)</Summary>
		Public Overridable Function IsComplete(OverlappedK As KOVL_HANDLE) As Boolean
			Return AllKFunctions.OvlK_IsComplete(OverlappedK)
		End Function

		''' <Summary>Initializes an overlappedK for re-use. The overlappedK is not return to its pool.</Summary>
		Public Overridable Function ReUse(OverlappedK As KOVL_HANDLE) As Boolean
			Return AllKFunctions.OvlK_ReUse(OverlappedK)
		End Function

		''' <Summary>Returns an \c OverlappedK structure to it's pool.</Summary>
		Public Overridable Function Release(OverlappedK As KOVL_HANDLE) As Boolean
			Return AllKFunctions.OvlK_Release(OverlappedK)
		End Function

		''' <Summary>Waits for overlapped I/O completion, and performs actions specified in \c WaitFlags.</Summary>
		Public Overridable Function Wait(OverlappedK As KOVL_HANDLE, TimeoutMS As Integer, WaitFlags As KOVL_WAIT_FLAG, ByRef TransferredLength As Integer) As Boolean
			Return AllKFunctions.OvlK_Wait(OverlappedK, TimeoutMS, WaitFlags, TransferredLength)
		End Function

		''' <Summary>Waits for overlapped I/O completion, cancels on a timeout error and always releases the OvlK handle back to its pool.</Summary>
		Public Overridable Function WaitAndRelease(OverlappedK As KOVL_HANDLE, TimeoutMS As Integer, ByRef TransferredLength As Integer) As Boolean
			Return AllKFunctions.OvlK_WaitAndRelease(OverlappedK, TimeoutMS, TransferredLength)
		End Function

		''' <Summary>Waits for overlapped I/O completion on the oldest acquired OverlappedK handle and performs actions specified in \c WaitFlags.</Summary>
		Public Overridable Function WaitOldest(ByRef OverlappedK As KOVL_HANDLE, TimeoutMS As Integer, WaitFlags As KOVL_WAIT_FLAG, ByRef TransferredLength As Integer) As Boolean
			Return AllKFunctions.OvlK_WaitOldest(mHandleStruct, OverlappedK, TimeoutMS, WaitFlags, TransferredLength)
		End Function

		''' <Summary>Waits for overlapped I/O completion, cancels on a timeout error.</Summary>
		Public Overridable Function WaitOrCancel(OverlappedK As KOVL_HANDLE, TimeoutMS As Integer, ByRef TransferredLength As Integer) As Boolean
			Return AllKFunctions.OvlK_WaitOrCancel(OverlappedK, TimeoutMS, TransferredLength)
		End Function

		#End Region
	End Class

	Public Class StmK
		Implements IDisposable
		Protected mHandleStruct As KSTM_HANDLE
		Protected mbDisposed As Boolean

		Protected Sub New()
		End Sub

		#Region "IDisposable Members"

		''' <summary>Explicitly closes and frees the handle.</summary>
		Public Overridable Sub Dispose() Implements IDisposable.Dispose
			Dispose(True)
			GC.SuppressFinalize(Me)
		End Sub

		#End Region

		Protected Overrides Sub Finalize()
			Try
				Dispose(False)
			Finally
				MyBase.Finalize()
			End Try
		End Sub

		Protected Overridable Sub Dispose(disposing As Boolean)
			If Not mbDisposed Then
				If mHandleStruct.Pointer <> IntPtr.Zero Then
					AllKFunctions.StmK_Free(mHandleStruct)
					Debug.Print("{0} Dispose: Freed Handle:{1:X16}h Explicit:{2}", [GetType]().Name, mHandleStruct.Pointer.ToInt64(), disposing)
				Else
					Debug.Print("{0} Dispose: [WARNING] Handle is null", [GetType]().Name)
				End If

				mHandleStruct = New KSTM_HANDLE(IntPtr.Zero)
				mbDisposed = True
			End If
		End Sub

		''' <Summary>Initializes a new uni-directional pipe stream.</Summary>
		Protected Function Init(UsbHandle As KUSB_HANDLE, PipeID As Byte, MaxTransferSize As Integer, MaxPendingTransfers As Integer, MaxPendingIO As Integer, ByRef Callbacks As KSTM_CALLBACK, _
			Flags As KSTM_FLAG) As Boolean
			Dim success As Boolean = AllKFunctions.StmK_Init(mHandleStruct, UsbHandle, PipeID, MaxTransferSize, MaxPendingTransfers, MaxPendingIO, _
				Callbacks, Flags)

			If Not success Then
				Throw New Exception(String.Format("{0} failed initializing. ErrorCode={1:X8}h", [GetType]().Name, Marshal.GetLastWin32Error()))
			End If

			Debug.Print("{0} Init: handle 0x{1:X16}", [GetType]().Name, mHandleStruct.Pointer.ToInt64())
			Return True
		End Function

		#Region "Public Members"

		''' <Summary>Initializes a new uni-directional pipe stream.</Summary>
		Public Sub New(UsbHandle As KUSB_HANDLE, PipeID As Byte, MaxTransferSize As Integer, MaxPendingTransfers As Integer, MaxPendingIO As Integer, ByRef Callbacks As KSTM_CALLBACK, _
			Flags As KSTM_FLAG)
			Dim success As Boolean = AllKFunctions.StmK_Init(mHandleStruct, UsbHandle, PipeID, MaxTransferSize, MaxPendingTransfers, MaxPendingIO, _
				Callbacks, Flags)

			If Not success Then
				Throw New Exception(String.Format("{0} failed initializing. ErrorCode={1:X8}h", [GetType]().Name, Marshal.GetLastWin32Error()))
			End If

			Debug.Print("{0} Init: handle 0x{1:X16}", [GetType]().Name, mHandleStruct.Pointer.ToInt64())
		End Sub

		''' <summary>Calls the dispose method.</summary>
		Public Overridable Sub Free()
			Dispose()
		End Sub

		''' <summary>Gets the handle class structure.</summary>
		Public ReadOnly Property Handle() As KSTM_HANDLE
			Get
				Return mHandleStruct
			End Get
		End Property

		''' <Summary>Reads data from the stream buffer.</Summary>
		Public Overridable Function Read(Buffer As IntPtr, Offset As Integer, Length As Integer, ByRef TransferredLength As Integer) As Boolean
			Return AllKFunctions.StmK_Read(mHandleStruct, Buffer, Offset, Length, TransferredLength)
		End Function

		''' <Summary>Reads data from the stream buffer.</Summary>
		Public Overridable Function Read(Buffer As Array, Offset As Integer, Length As Integer, ByRef TransferredLength As Integer) As Boolean
			Return AllKFunctions.StmK_Read(mHandleStruct, Marshal.UnsafeAddrOfPinnedArrayElement(Buffer, 0), Offset, Length, TransferredLength)
		End Function

		''' <Summary>Starts the internal stream thread.</Summary>
		Public Overridable Function Start() As Boolean
			Return AllKFunctions.StmK_Start(mHandleStruct)
		End Function

		''' <Summary>Stops the internal stream thread.</Summary>
		Public Overridable Function [Stop](TimeoutCancelMS As Integer) As Boolean
			Return AllKFunctions.StmK_Stop(mHandleStruct, TimeoutCancelMS)
		End Function

		''' <Summary>Writes data to the stream buffer.</Summary>
		Public Overridable Function Write(Buffer As IntPtr, Offset As Integer, Length As Integer, ByRef TransferredLength As Integer) As Boolean
			Return AllKFunctions.StmK_Write(mHandleStruct, Buffer, Offset, Length, TransferredLength)
		End Function

		''' <Summary>Writes data to the stream buffer.</Summary>
		Public Overridable Function Write(Buffer As Array, Offset As Integer, Length As Integer, ByRef TransferredLength As Integer) As Boolean
			Return AllKFunctions.StmK_Write(mHandleStruct, Marshal.UnsafeAddrOfPinnedArrayElement(Buffer, 0), Offset, Length, TransferredLength)
		End Function

		#End Region
	End Class

	Public Class IsoK
		Implements IDisposable
		Protected mHandleStruct As KISO_CONTEXT
		Protected mbDisposed As Boolean

		Protected Sub New()
		End Sub

		#Region "IDisposable Members"

		''' <summary>Explicitly closes and frees the handle.</summary>
		Public Overridable Sub Dispose() Implements IDisposable.Dispose
			Dispose(True)
			GC.SuppressFinalize(Me)
		End Sub

		#End Region

		Protected Overrides Sub Finalize()
			Try
				Dispose(False)
			Finally
				MyBase.Finalize()
			End Try
		End Sub

		Protected Overridable Sub Dispose(disposing As Boolean)
			If Not mbDisposed Then
				If mHandleStruct.Pointer <> IntPtr.Zero Then
					AllKFunctions.IsoK_Free(mHandleStruct)
					Debug.Print("{0} Dispose: Freed Handle:{1:X16}h Explicit:{2}", [GetType]().Name, mHandleStruct.Pointer.ToInt64(), disposing)
				Else
					Debug.Print("{0} Dispose: [WARNING] Handle is null", [GetType]().Name)
				End If

				mHandleStruct = New KISO_CONTEXT(IntPtr.Zero)
				mbDisposed = True
			End If
		End Sub

		''' <Summary>Creates a new isochronous transfer context.</Summary>
		Protected Function Init(NumberOfPackets As Integer, StartFrame As Integer) As Boolean
			Dim success As Boolean = AllKFunctions.IsoK_Init(mHandleStruct, NumberOfPackets, StartFrame)

			If Not success Then
				Throw New Exception(String.Format("{0} failed initializing. ErrorCode={1:X8}h", [GetType]().Name, Marshal.GetLastWin32Error()))
			End If

			Debug.Print("{0} Init: handle 0x{1:X16}", [GetType]().Name, mHandleStruct.Pointer.ToInt64())
			Return True
		End Function

		#Region "Nested Structs"

		<StructLayout(LayoutKind.Sequential, CharSet := CharSet.Ansi, Pack := 1)> _
		Private Structure KISO_CONTEXT_MAP
			''' <Summary>Additional ISO transfer flags. See \ref KISO_FLAG.</Summary>
			Private ReadOnly Flags As KISO_FLAG

			''' <Summary>Specifies the frame number that the transfer should begin on (0 for ASAP).</Summary>
			Private ReadOnly StartFrame As Integer

			''' <Summary>Contains the number of packets that completed with an error condition on return from the host controller driver.</Summary>
			Private ReadOnly ErrorCount As Short

			''' <Summary>Specifies the number of packets that are described by the variable-length array member \c IsoPacket.</Summary>
			Private ReadOnly NumberOfPackets As Short

			''' <Summary>Contains the URB Hdr.Status value on return from the host controller driver.</Summary>
			Private ReadOnly UrbHdrStatus As Integer
		End Structure

		#End Region

		#Region "Public Members"

		''' <Summary>Creates a new isochronous transfer context.</Summary>
		Public Sub New(NumberOfPackets As Integer, StartFrame As Integer)
			Dim success As Boolean = AllKFunctions.IsoK_Init(mHandleStruct, NumberOfPackets, StartFrame)

			If Not success Then
				Throw New Exception(String.Format("{0} failed initializing. ErrorCode={1:X8}h", [GetType]().Name, Marshal.GetLastWin32Error()))
			End If

			Debug.Print("{0} Init: handle 0x{1:X16}", [GetType]().Name, mHandleStruct.Pointer.ToInt64())
		End Sub

		''' <Summary>Convenience function for enumerating ISO packets of an isochronous transfer context.</Summary>
		Public Overridable Function EnumPackets(EnumPackets As KISO_ENUM_PACKETS_CB, StartPacketIndex As Integer, UserState As IntPtr) As Boolean
			Return AllKFunctions.IsoK_EnumPackets(mHandleStruct, EnumPackets, StartPacketIndex, UserState)
		End Function

		''' <Summary>Contains the number of packets that completed with an error condition on return from the host controller driver.</Summary>
		Public Property ErrorCount() As Short
			Get
				Return Marshal.ReadInt16(mHandleStruct.Pointer, ofsErrorCount)
			End Get
			Set
				Marshal.WriteInt16(mHandleStruct.Pointer, ofsErrorCount, value)
			End Set
		End Property

		''' <Summary>Additional ISO transfer flags. See \ref KISO_FLAG.</Summary>
		Public Property Flags() As KISO_FLAG
			Get
				Return CType(Marshal.ReadInt32(mHandleStruct.Pointer, ofsFlags), KISO_FLAG)
			End Get
			Set
				Marshal.WriteInt32(mHandleStruct.Pointer, ofsFlags, CInt(value))
			End Set
		End Property

		''' <summary>Calls the dispose method.</summary>
		Public Overridable Sub Free()
			Dispose()
		End Sub

		''' <Summary>Convenience function for getting all fields of a \ref KISO_PACKET.</Summary>
		Public Overridable Function GetPacket(PacketIndex As Integer, ByRef IsoPacket As KISO_PACKET) As Boolean
			Return AllKFunctions.IsoK_GetPacket(mHandleStruct, PacketIndex, IsoPacket)
		End Function

		''' <summary>Gets the handle class structure.</summary>
		Public ReadOnly Property Handle() As KISO_CONTEXT
			Get
				Return mHandleStruct
			End Get
		End Property

		''' <Summary>Specifies the number of packets that are described by the variable-length array member \c IsoPacket.</Summary>
		Public Property NumberOfPackets() As Short
			Get
				Return Marshal.ReadInt16(mHandleStruct.Pointer, ofsNumberOfPackets)
			End Get
			Set
				Marshal.WriteInt16(mHandleStruct.Pointer, ofsNumberOfPackets, value)
			End Set
		End Property

		''' <Summary>Convenience function for re-using an isochronous transfer context in a subsequent request.</Summary>
		Public Overridable Function ReUse() As Boolean
			Return AllKFunctions.IsoK_ReUse(mHandleStruct)
		End Function

		''' <Summary>Convenience function for setting all fields of a \ref KISO_PACKET.</Summary>
		Public Overridable Function SetPacket(PacketIndex As Integer, ByRef IsoPacket As KISO_PACKET) As Boolean
			Return AllKFunctions.IsoK_SetPacket(mHandleStruct, PacketIndex, IsoPacket)
		End Function

		''' <Summary>Convenience function for setting the offset of all ISO packets of an isochronous transfer context.</Summary>
		Public Overridable Function SetPackets(PacketSize As Integer) As Boolean
			Return AllKFunctions.IsoK_SetPackets(mHandleStruct, PacketSize)
		End Function

		''' <Summary>Specifies the frame number that the transfer should begin on (0 for ASAP).</Summary>
		Public Property StartFrame() As Integer
			Get
				Return Marshal.ReadInt32(mHandleStruct.Pointer, ofsStartFrame)
			End Get
			Set
				Marshal.WriteInt32(mHandleStruct.Pointer, ofsStartFrame, value)
			End Set
		End Property

		''' <Summary>Contains the URB Hdr.Status value on return from the host controller driver.</Summary>
		Public Property UrbHdrStatus() As Integer
			Get
				Return Marshal.ReadInt32(mHandleStruct.Pointer, ofsUrbHdrStatus)
			End Get
			Set
				Marshal.WriteInt32(mHandleStruct.Pointer, ofsUrbHdrStatus, value)
			End Set
		End Property

		#End Region

		#Region "Private Members"

		Private Shared ReadOnly ofsErrorCount As Integer = Marshal.OffsetOf(GetType(KISO_CONTEXT_MAP), "ErrorCount").ToInt32()
		Private Shared ReadOnly ofsFlags As Integer = Marshal.OffsetOf(GetType(KISO_CONTEXT_MAP), "Flags").ToInt32()
		Private Shared ReadOnly ofsNumberOfPackets As Integer = Marshal.OffsetOf(GetType(KISO_CONTEXT_MAP), "NumberOfPackets").ToInt32()
		Private Shared ReadOnly ofsStartFrame As Integer = Marshal.OffsetOf(GetType(KISO_CONTEXT_MAP), "StartFrame").ToInt32()
		Private Shared ReadOnly ofsUrbHdrStatus As Integer = Marshal.OffsetOf(GetType(KISO_CONTEXT_MAP), "UrbHdrStatus").ToInt32()

		#End Region
	End Class
End Namespace
