/****************************************************************************
** Meta object code from reading C++ file 'gahnooslashlinuxusbdriver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gahnooslashlinuxusbdriver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gahnooslashlinuxusbdriver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_worker_t {
    QByteArrayData data[3];
    char stringdata0[15];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_worker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_worker_t qt_meta_stringdata_worker = {
    {
QT_MOC_LITERAL(0, 0, 6), // "worker"
QT_MOC_LITERAL(1, 7, 6), // "handle"
QT_MOC_LITERAL(2, 14, 0) // ""

    },
    "worker\0handle\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_worker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void worker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        worker *_t = static_cast<worker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->handle(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject worker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_worker.data,
      qt_meta_data_worker,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *worker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *worker::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_worker.stringdata0))
        return static_cast<void*>(const_cast< worker*>(this));
    return QObject::qt_metacast(_clname);
}

int worker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_gahnooSlashLinuxUsbDriver_t {
    QByteArrayData data[4];
    char stringdata0[53];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_gahnooSlashLinuxUsbDriver_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_gahnooSlashLinuxUsbDriver_t qt_meta_stringdata_gahnooSlashLinuxUsbDriver = {
    {
QT_MOC_LITERAL(0, 0, 25), // "gahnooSlashLinuxUsbDriver"
QT_MOC_LITERAL(1, 26, 12), // "isoTimerTick"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 12) // "recoveryTick"

    },
    "gahnooSlashLinuxUsbDriver\0isoTimerTick\0"
    "\0recoveryTick"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_gahnooSlashLinuxUsbDriver[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a /* Public */,
       3,    0,   25,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void gahnooSlashLinuxUsbDriver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        gahnooSlashLinuxUsbDriver *_t = static_cast<gahnooSlashLinuxUsbDriver *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->isoTimerTick(); break;
        case 1: _t->recoveryTick(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject gahnooSlashLinuxUsbDriver::staticMetaObject = {
    { &genericUsbDriver::staticMetaObject, qt_meta_stringdata_gahnooSlashLinuxUsbDriver.data,
      qt_meta_data_gahnooSlashLinuxUsbDriver,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *gahnooSlashLinuxUsbDriver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *gahnooSlashLinuxUsbDriver::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_gahnooSlashLinuxUsbDriver.stringdata0))
        return static_cast<void*>(const_cast< gahnooSlashLinuxUsbDriver*>(this));
    return genericUsbDriver::qt_metacast(_clname);
}

int gahnooSlashLinuxUsbDriver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = genericUsbDriver::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
