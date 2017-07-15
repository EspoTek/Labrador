/****************************************************************************
** Meta object code from reading C++ file 'unixusbdriver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../unixusbdriver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'unixusbdriver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
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
struct qt_meta_stringdata_unixUsbDriver_t {
    QByteArrayData data[6];
    char stringdata0[73];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_unixUsbDriver_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_unixUsbDriver_t qt_meta_stringdata_unixUsbDriver = {
    {
QT_MOC_LITERAL(0, 0, 13), // "unixUsbDriver"
QT_MOC_LITERAL(1, 14, 12), // "isoTimerTick"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 12), // "recoveryTick"
QT_MOC_LITERAL(4, 41, 17), // "shutdownProcedure"
QT_MOC_LITERAL(5, 59, 13) // "backupCleanup"

    },
    "unixUsbDriver\0isoTimerTick\0\0recoveryTick\0"
    "shutdownProcedure\0backupCleanup"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_unixUsbDriver[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a /* Public */,
       3,    0,   35,    2, 0x0a /* Public */,
       4,    0,   36,    2, 0x0a /* Public */,
       5,    0,   37,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void unixUsbDriver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        unixUsbDriver *_t = static_cast<unixUsbDriver *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->isoTimerTick(); break;
        case 1: _t->recoveryTick(); break;
        case 2: _t->shutdownProcedure(); break;
        case 3: _t->backupCleanup(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject unixUsbDriver::staticMetaObject = {
    { &genericUsbDriver::staticMetaObject, qt_meta_stringdata_unixUsbDriver.data,
      qt_meta_data_unixUsbDriver,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *unixUsbDriver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *unixUsbDriver::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_unixUsbDriver.stringdata0))
        return static_cast<void*>(const_cast< unixUsbDriver*>(this));
    return genericUsbDriver::qt_metacast(_clname);
}

int unixUsbDriver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = genericUsbDriver::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
