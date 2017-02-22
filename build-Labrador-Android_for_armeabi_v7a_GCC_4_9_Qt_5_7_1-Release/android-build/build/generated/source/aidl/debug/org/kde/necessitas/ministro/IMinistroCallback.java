/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: C:\\Qt\\5.7\\android_armv7\\src\\android\\java\\src\\org\\kde\\necessitas\\ministro\\IMinistroCallback.aidl
 */
package org.kde.necessitas.ministro;
public interface IMinistroCallback extends android.os.IInterface
{
/** Local-side IPC implementation stub class. */
public static abstract class Stub extends android.os.Binder implements org.kde.necessitas.ministro.IMinistroCallback
{
private static final java.lang.String DESCRIPTOR = "org.kde.necessitas.ministro.IMinistroCallback";
/** Construct the stub at attach it to the interface. */
public Stub()
{
this.attachInterface(this, DESCRIPTOR);
}
/**
 * Cast an IBinder object into an org.kde.necessitas.ministro.IMinistroCallback interface,
 * generating a proxy if needed.
 */
public static org.kde.necessitas.ministro.IMinistroCallback asInterface(android.os.IBinder obj)
{
if ((obj==null)) {
return null;
}
android.os.IInterface iin = obj.queryLocalInterface(DESCRIPTOR);
if (((iin!=null)&&(iin instanceof org.kde.necessitas.ministro.IMinistroCallback))) {
return ((org.kde.necessitas.ministro.IMinistroCallback)iin);
}
return new org.kde.necessitas.ministro.IMinistroCallback.Stub.Proxy(obj);
}
@Override public android.os.IBinder asBinder()
{
return this;
}
@Override public boolean onTransact(int code, android.os.Parcel data, android.os.Parcel reply, int flags) throws android.os.RemoteException
{
switch (code)
{
case INTERFACE_TRANSACTION:
{
reply.writeString(DESCRIPTOR);
return true;
}
case TRANSACTION_loaderReady:
{
data.enforceInterface(DESCRIPTOR);
android.os.Bundle _arg0;
if ((0!=data.readInt())) {
_arg0 = android.os.Bundle.CREATOR.createFromParcel(data);
}
else {
_arg0 = null;
}
this.loaderReady(_arg0);
return true;
}
}
return super.onTransact(code, data, reply, flags);
}
private static class Proxy implements org.kde.necessitas.ministro.IMinistroCallback
{
private android.os.IBinder mRemote;
Proxy(android.os.IBinder remote)
{
mRemote = remote;
}
@Override public android.os.IBinder asBinder()
{
return mRemote;
}
public java.lang.String getInterfaceDescriptor()
{
return DESCRIPTOR;
}
/**
* This method is called by the Ministro service back into the application which
* implements this interface.
*
* param in - loaderParams
*            loaderParams fields:
*                 * Key Name                   Key type         Explanations
*                 * "error.code"               Integer          See below
*                 * "error.message"            String           Missing if no error, otherwise will contain the error message translated into phone language where available.
*                 * "dex.path"                 String           The list of jar/apk files containing classes and resources, needed to be passed to application DexClassLoader
*                 * "lib.path"                 String           The list of directories containing native libraries; may be missing, needed to be passed to application DexClassLoader
*                 * "loader.class.name"        String           Loader class name.
*
* "error.code" field possible errors:
*  - 0 no error.
*  - 1 incompatible Ministro version. Ministro needs to be upgraded.
*  - 2 not all modules could be satisfy.
*  - 3 invalid parameters
*  - 4 invalid qt version
*  - 5 download canceled
*
* The parameter contains additional fields which are used by the loader to start your application, so it must be passed to the loader.
*/
@Override public void loaderReady(android.os.Bundle loaderParams) throws android.os.RemoteException
{
android.os.Parcel _data = android.os.Parcel.obtain();
try {
_data.writeInterfaceToken(DESCRIPTOR);
if ((loaderParams!=null)) {
_data.writeInt(1);
loaderParams.writeToParcel(_data, 0);
}
else {
_data.writeInt(0);
}
mRemote.transact(Stub.TRANSACTION_loaderReady, _data, null, android.os.IBinder.FLAG_ONEWAY);
}
finally {
_data.recycle();
}
}
}
static final int TRANSACTION_loaderReady = (android.os.IBinder.FIRST_CALL_TRANSACTION + 0);
}
/**
* This method is called by the Ministro service back into the application which
* implements this interface.
*
* param in - loaderParams
*            loaderParams fields:
*                 * Key Name                   Key type         Explanations
*                 * "error.code"               Integer          See below
*                 * "error.message"            String           Missing if no error, otherwise will contain the error message translated into phone language where available.
*                 * "dex.path"                 String           The list of jar/apk files containing classes and resources, needed to be passed to application DexClassLoader
*                 * "lib.path"                 String           The list of directories containing native libraries; may be missing, needed to be passed to application DexClassLoader
*                 * "loader.class.name"        String           Loader class name.
*
* "error.code" field possible errors:
*  - 0 no error.
*  - 1 incompatible Ministro version. Ministro needs to be upgraded.
*  - 2 not all modules could be satisfy.
*  - 3 invalid parameters
*  - 4 invalid qt version
*  - 5 download canceled
*
* The parameter contains additional fields which are used by the loader to start your application, so it must be passed to the loader.
*/
public void loaderReady(android.os.Bundle loaderParams) throws android.os.RemoteException;
}
