program opendevice;

{$APPTYPE CONSOLE}

uses
  SysUtils, Classes,
  libusbK in '..\libusbK.pas',
  UExampleHelpers;
var
  VID, PID : Integer;
procedure EvaluateCommandLine;
var
  i : Integer;
  s, s0,s1 : String;
  n : Integer;
begin
  for i := 1 to ParamCount do
  begin
    s := Uppercase(ParamStr(i)); //copy the whole current param string and convert to upper cases
    s0 := Copy(s,1,4);  // copy the first 4 signs
    if (s0 = 'VID=') or
       (s0 = 'PID=') then
    begin // we got a vid or pid parm
      s1 := Copy(s,5,MaxInt); // copy everything behind the '='
      if Copy(s1,1,2) = '0X' then // check the c-style hex notation
        s1 := '$'+ Copy(s1,3,MaxInt); // replace by delphi hex-notation
      n := StrToIntDef(s1,-1); // convert, place -1 on any convert error
      if (s0 = 'VID=') then
        VID := n
      else if (s0 = 'PID=') then
        PID := n;
    end;
  end;
end;
const
  UsbPipeTypeString : array[USBD_PIPE_TYPE] of String = (
    'Control',
    'Isochronous',
    'Bulk,',
    'Interrupt'
  );

var
  devlist : TStringList;
  i,j,k : Integer;
  devhandle : KUSB_HANDLE;
  pipeinfo : WINUSB_PIPE_INFORMATION;
begin
  WriteLn('OpenDevice test for LibusbK');
  WriteLn('Returns Pipe info for all devices, or limited to a given VID/PID pair');
  WriteLn('usage:');
  WriteLn('opendevice [VID=nnnn] [PID=nnnn]');
  WriteLn('VID and PID may use decimal or hexadecimal notation');
  VID := -1;
  PID := -1;
  EvaluateCommandLine;
  if VID < 0 then
    WriteLn('VID is not used!')
  else
    WriteLn('VID used '+Format('%d (0x%x',[VID,VID]));
  if VID < 0 then
    WriteLn('PID is not used!')
  else
    WriteLn('PID used '+Format('%d (0x%x',[PID,PID]));
  devlist := TStringList.Create;
  try
    ListLibusbKDevices(devlist,VID,PID);
    if devlist.Count <= 0 then
    begin
      WriteLn('Error: No device found!');
      Exit;
    end;
    for i := 0 to devlist.Count-1 do
    begin
      if UsbK_InitFromDevicePath(devlist[i],devhandle) then
      begin
        try
          WriteLn('Opened device "'+devlist[i]+'"');
          j := 0;
          while UsbK_SetCurrentAlternateSetting(devhandle,j) do
          begin
            WriteLn('Using AlternateSetting ',j);
            k := 0;
            while UsbK_QueryPipe(devhandle,j,k,pipeinfo) do
            begin
              WriteLn(Format('  PipeId=0x%2.2x PipeType=0x%2.2x ("%s") Interval=%u MaximumPacketSize=%u',
                             [pipeInfo.PipeId, Byte(pipeInfo.PipeType),UsbPipeTypeString[pipeInfo.PipeType], pipeInfo.Interval, pipeInfo.MaximumPacketSize]));
              Inc(k);
            end;
            Inc(j);
          end;
        finally
          UsbK_Free(devhandle);
        end;
      end
      else
        WriteLn('Error: can not open device "'+devlist[i]+'"');
    end;
  finally
    devlist.Free;
  end;
(* Example output
OpenDevice test for LibusbK
Returns Pipe info for all devices, or limited to a given VID/PID pair
usage:
opendevice [VID=nnnn] [PID=nnnn]
VID and PID may use decimal or hexadecimal notation
VID is not used!
PID is not used!
Opened device "\\?\USB#Vid_04b4&Pid_8613#6&1b8c4f52&0&1#{53373f62-b5e4-d526-b292
-f86533b3e7df}"
Using AlternateSetting 0
Using AlternateSetting 1
  PipeId=0x01 PipeType=0x02 ("Bulk,") Interval=0 MaximumPacketSize=512
  PipeId=0x81 PipeType=0x02 ("Bulk,") Interval=0 MaximumPacketSize=512
  PipeId=0x02 PipeType=0x02 ("Bulk,") Interval=0 MaximumPacketSize=512
  PipeId=0x04 PipeType=0x02 ("Bulk,") Interval=0 MaximumPacketSize=512
  PipeId=0x86 PipeType=0x02 ("Bulk,") Interval=0 MaximumPacketSize=512
  PipeId=0x88 PipeType=0x02 ("Bulk,") Interval=0 MaximumPacketSize=512
Using AlternateSetting 2
  PipeId=0x01 PipeType=0x03 ("Interrupt") Interval=1 MaximumPacketSize=64
  PipeId=0x81 PipeType=0x03 ("Interrupt") Interval=1 MaximumPacketSize=64
  PipeId=0x02 PipeType=0x03 ("Interrupt") Interval=1 MaximumPacketSize=512
  PipeId=0x04 PipeType=0x02 ("Bulk,") Interval=0 MaximumPacketSize=512
  PipeId=0x86 PipeType=0x03 ("Interrupt") Interval=1 MaximumPacketSize=512
  PipeId=0x88 PipeType=0x02 ("Bulk,") Interval=0 MaximumPacketSize=512
Using AlternateSetting 3
  PipeId=0x01 PipeType=0x03 ("Interrupt") Interval=1 MaximumPacketSize=64
  PipeId=0x81 PipeType=0x03 ("Interrupt") Interval=1 MaximumPacketSize=64
  PipeId=0x02 PipeType=0x01 ("Isochronous") Interval=1 MaximumPacketSize=512
  PipeId=0x04 PipeType=0x02 ("Bulk,") Interval=0 MaximumPacketSize=512
  PipeId=0x86 PipeType=0x01 ("Isochronous") Interval=1 MaximumPacketSize=512
  PipeId=0x88 PipeType=0x02 ("Bulk,") Interval=0 MaximumPacketSize=512}
*)

end.
