/****************************************************************************
** Meta object code from reading C++ file 'genericusbdriver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../genericusbdriver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'genericusbdriver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_genericUsbDriver_t {
    QByteArrayData data[35];
    char stringdata0[361];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_genericUsbDriver_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_genericUsbDriver_t qt_meta_stringdata_genericUsbDriver = {
    {
QT_MOC_LITERAL(0, 0, 16), // "genericUsbDriver"
QT_MOC_LITERAL(1, 17, 15), // "sendClearBuffer"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 6), // "ch3751"
QT_MOC_LITERAL(4, 41, 6), // "ch3752"
QT_MOC_LITERAL(5, 48, 5), // "ch750"
QT_MOC_LITERAL(6, 54, 14), // "setVisible_CH2"
QT_MOC_LITERAL(7, 69, 7), // "visible"
QT_MOC_LITERAL(8, 77, 11), // "gainBuffers"
QT_MOC_LITERAL(9, 89, 10), // "multiplier"
QT_MOC_LITERAL(10, 100, 13), // "disableWindow"
QT_MOC_LITERAL(11, 114, 7), // "enabled"
QT_MOC_LITERAL(12, 122, 13), // "enableMMTimer"
QT_MOC_LITERAL(13, 136, 7), // "checkXY"
QT_MOC_LITERAL(14, 144, 6), // "upTick"
QT_MOC_LITERAL(15, 151, 6), // "killMe"
QT_MOC_LITERAL(16, 158, 15), // "connectedStatus"
QT_MOC_LITERAL(17, 174, 6), // "status"
QT_MOC_LITERAL(18, 181, 6), // "setPsu"
QT_MOC_LITERAL(19, 188, 7), // "voltage"
QT_MOC_LITERAL(20, 196, 14), // "setFunctionGen"
QT_MOC_LITERAL(21, 211, 7), // "channel"
QT_MOC_LITERAL(22, 219, 19), // "functionGenControl*"
QT_MOC_LITERAL(23, 239, 11), // "fGenControl"
QT_MOC_LITERAL(24, 251, 13), // "setDeviceMode"
QT_MOC_LITERAL(25, 265, 4), // "mode"
QT_MOC_LITERAL(26, 270, 6), // "newDig"
QT_MOC_LITERAL(27, 277, 8), // "digState"
QT_MOC_LITERAL(28, 286, 7), // "psuTick"
QT_MOC_LITERAL(29, 294, 7), // "setGain"
QT_MOC_LITERAL(30, 302, 7), // "newGain"
QT_MOC_LITERAL(31, 310, 8), // "avrDebug"
QT_MOC_LITERAL(32, 319, 12), // "isoTimerTick"
QT_MOC_LITERAL(33, 332, 12), // "recoveryTick"
QT_MOC_LITERAL(34, 345, 15) // "checkConnection"

    },
    "genericUsbDriver\0sendClearBuffer\0\0"
    "ch3751\0ch3752\0ch750\0setVisible_CH2\0"
    "visible\0gainBuffers\0multiplier\0"
    "disableWindow\0enabled\0enableMMTimer\0"
    "checkXY\0upTick\0killMe\0connectedStatus\0"
    "status\0setPsu\0voltage\0setFunctionGen\0"
    "channel\0functionGenControl*\0fGenControl\0"
    "setDeviceMode\0mode\0newDig\0digState\0"
    "psuTick\0setGain\0newGain\0avrDebug\0"
    "isoTimerTick\0recoveryTick\0checkConnection"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_genericUsbDriver[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,  109,    2, 0x06 /* Public */,
       6,    1,  116,    2, 0x06 /* Public */,
       8,    1,  119,    2, 0x06 /* Public */,
      10,    1,  122,    2, 0x06 /* Public */,
      12,    0,  125,    2, 0x06 /* Public */,
      13,    1,  126,    2, 0x06 /* Public */,
      14,    0,  129,    2, 0x06 /* Public */,
      15,    0,  130,    2, 0x06 /* Public */,
      16,    1,  131,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      18,    1,  134,    2, 0x0a /* Public */,
      20,    2,  137,    2, 0x0a /* Public */,
      24,    1,  142,    2, 0x0a /* Public */,
      26,    1,  145,    2, 0x0a /* Public */,
      28,    0,  148,    2, 0x0a /* Public */,
      29,    1,  149,    2, 0x0a /* Public */,
      31,    0,  152,    2, 0x0a /* Public */,
      32,    0,  153,    2, 0x0a /* Public */,
      33,    0,  154,    2, 0x0a /* Public */,
      34,    0,  155,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,    3,    4,    5,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Double,    9,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   17,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,   19,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 22,   21,   23,
    QMetaType::Void, QMetaType::Int,   25,
    QMetaType::Void, QMetaType::Int,   27,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   30,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void genericUsbDriver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        genericUsbDriver *_t = static_cast<genericUsbDriver *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendClearBuffer((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 1: _t->setVisible_CH2((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->gainBuffers((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->disableWindow((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->enableMMTimer(); break;
        case 5: _t->checkXY((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->upTick(); break;
        case 7: _t->killMe(); break;
        case 8: _t->connectedStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->setPsu((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->setFunctionGen((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< functionGenControl*(*)>(_a[2]))); break;
        case 11: _t->setDeviceMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->newDig((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->psuTick(); break;
        case 14: _t->setGain((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 15: _t->avrDebug(); break;
        case 16: _t->isoTimerTick(); break;
        case 17: _t->recoveryTick(); break;
        case 18: _t->checkConnection(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< functionGenControl* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (genericUsbDriver::*_t)(bool , bool , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&genericUsbDriver::sendClearBuffer)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (genericUsbDriver::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&genericUsbDriver::setVisible_CH2)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (genericUsbDriver::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&genericUsbDriver::gainBuffers)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (genericUsbDriver::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&genericUsbDriver::disableWindow)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (genericUsbDriver::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&genericUsbDriver::enableMMTimer)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (genericUsbDriver::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&genericUsbDriver::checkXY)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (genericUsbDriver::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&genericUsbDriver::upTick)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (genericUsbDriver::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&genericUsbDriver::killMe)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (genericUsbDriver::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&genericUsbDriver::connectedStatus)) {
                *result = 8;
                return;
            }
        }
    }
}

const QMetaObject genericUsbDriver::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_genericUsbDriver.data,
      qt_meta_data_genericUsbDriver,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *genericUsbDriver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *genericUsbDriver::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_genericUsbDriver.stringdata0))
        return static_cast<void*>(const_cast< genericUsbDriver*>(this));
    return QLabel::qt_metacast(_clname);
}

int genericUsbDriver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void genericUsbDriver::sendClearBuffer(bool _t1, bool _t2, bool _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void genericUsbDriver::setVisible_CH2(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void genericUsbDriver::gainBuffers(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void genericUsbDriver::disableWindow(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void genericUsbDriver::enableMMTimer()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void genericUsbDriver::checkXY(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void genericUsbDriver::upTick()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}

// SIGNAL 7
void genericUsbDriver::killMe()
{
    QMetaObject::activate(this, &staticMetaObject, 7, Q_NULLPTR);
}

// SIGNAL 8
void genericUsbDriver::connectedStatus(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_END_MOC_NAMESPACE
