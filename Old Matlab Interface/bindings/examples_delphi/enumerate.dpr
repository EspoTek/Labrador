program enumerate;

{$APPTYPE CONSOLE}
uses
  SysUtils,
  libusbK in '..\libusbK.pas';

procedure EnumerateAttachedDevices;
var
	deviceCount : Cardinal;
  lDeviceList : KLST_HANDLE;
  lDeviceInfo : KLST_DEVINFO_HANDLE;
  i : Integer;
begin
	deviceCount := 0;
  lDeviceList := Nil;
  lDeviceInfo := Nil;
	// Get the device list
  if (not LstK_Init(lDeviceList, 0)) then
  begin
    WriteLn('Error in LstK_Init!');
    Exit;
  end;
  try // make sure list is freed under all circumstances
    LstK_Count(lDeviceList, deviceCount);
    if (deviceCount = 0) then
    begin
      WriteLn('No devices found!');
      Exit; // lDeviceList is freed in finally
    end;
    i := -1;
    while LstK_MoveNext(lDeviceList, lDeviceInfo) do
    begin
      Inc(i);
      if Assigned(lDeviceInfo) then
      begin
        WriteLn('Device ',i,' ---------------------------------');
        WriteLn('VID: ',lDeviceInfo.Common.Vid);
        WriteLn('PID: ',lDeviceInfo.Common.Pid);
        WriteLn('MI: ',lDeviceInfo.Common.MI);
        WriteLn('InstanceID: ',lDeviceInfo.Common.InstanceID);
        WriteLn('DriverID: ',lDeviceInfo.DriverID);
        WriteLn('DeviceInterfaceGUID: ',lDeviceInfo.DeviceInterfaceGUID);
        WriteLn('InstanceID: ',lDeviceInfo.InstanceID);
        WriteLn('ClassGUID: ',lDeviceInfo.ClassGUID);
        WriteLn('Mfg: ',lDeviceInfo.Mfg);
        WriteLn('DeviceDesc: ',lDeviceInfo.DeviceDesc);
        WriteLn('Service: ',lDeviceInfo.Service);
        WriteLn('SymbolicLink: ',lDeviceInfo.SymbolicLink);
        WriteLn('DevicePath: ',lDeviceInfo.DevicePath);
        WriteLn('LUsb0FilterIndex: ',lDeviceInfo.LUsb0FilterIndex);
        if lDeviceInfo.Connected then
          WriteLn('Connected: True')
        else
          WriteLn('Connected: False');
        WriteLn('SyncFlags: '+Format('%x',[lDeviceInfo.SyncFlags]));
      end;
    end;
	finally
    if Assigned(lDeviceList) then
  		LstK_Free(lDeviceList);
  end;
end;


begin
  WriteLn('libusbK Device enumeration demo');
  if not libusbK.DllAvailable then
  begin
    WriteLn('Error: '+libusbK.LIBUSBK_DLL+' not available!');
    Halt(1);
  end;
  EnumerateAttachedDevices;
  WriteLn('libusbK Device enumeration done');

(* Example output
libusbK Device enumeration demo
Device 0 ---------------------------------
VID: 1204
PID: 34323
MI: -1
InstanceID: 6&564E695&0&1
DriverID: 0
DeviceInterfaceGUID: {53373f62-b5e4-d526-b292-f86533b3e7df}
InstanceID: USB\Vid_04b4&Pid_8613\6&564e695&0&1
ClassGUID: {ECFB0CFD-74C4-4F52-BBF7-343461CD72AC}
Mfg: Cypress Semiconductor Corp.
DeviceDesc: Cypress Generic USB Device (LibUSB)
Service: libusbK
SymbolicLink: \\?\USB#Vid_04b4&Pid_8613#6&564e695&0&1#{53373f62-b5e4-d526-b292-f86533b3e7df}
DevicePath: \\?\USB#Vid_04b4&Pid_8613#6&564e695&0&1#{53373f62-b5e4-d526-b292-f86533b3e7df}
LUsb0FilterIndex: -1
Connected: True
SyncFlags: 0
libusbK Device enumeration done
*)


end.
