/****************************************************************************
** Meta object code from reading C++ file 'genericusbdriver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../genericusbdriver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'genericusbdriver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_genericUsbDriver_t {
    QByteArrayData data[31];
    char stringdata0[309];
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
QT_MOC_LITERAL(16, 158, 6), // "setPsu"
QT_MOC_LITERAL(17, 165, 7), // "voltage"
QT_MOC_LITERAL(18, 173, 14), // "setFunctionGen"
QT_MOC_LITERAL(19, 188, 7), // "channel"
QT_MOC_LITERAL(20, 196, 19), // "functionGenControl*"
QT_MOC_LITERAL(21, 216, 11), // "fGenControl"
QT_MOC_LITERAL(22, 228, 13), // "setDeviceMode"
QT_MOC_LITERAL(23, 242, 4), // "mode"
QT_MOC_LITERAL(24, 247, 6), // "newDig"
QT_MOC_LITERAL(25, 254, 8), // "digState"
QT_MOC_LITERAL(26, 263, 7), // "psuTick"
QT_MOC_LITERAL(27, 271, 7), // "setGain"
QT_MOC_LITERAL(28, 279, 7), // "newGain"
QT_MOC_LITERAL(29, 287, 8), // "avrDebug"
QT_MOC_LITERAL(30, 296, 12) // "isoTimerTick"

    },
    "genericUsbDriver\0sendClearBuffer\0\0"
    "ch3751\0ch3752\0ch750\0setVisible_CH2\0"
    "visible\0gainBuffers\0multiplier\0"
    "disableWindow\0enabled\0enableMMTimer\0"
    "checkXY\0upTick\0killMe\0setPsu\0voltage\0"
    "setFunctionGen\0channel\0functionGenControl*\0"
    "fGenControl\0setDeviceMode\0mode\0newDig\0"
    "digState\0psuTick\0setGain\0newGain\0"
    "avrDebug\0isoTimerTick"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_genericUsbDriver[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   94,    2, 0x06 /* Public */,
       6,    1,  101,    2, 0x06 /* Public */,
       8,    1,  104,    2, 0x06 /* Public */,
      10,    1,  107,    2, 0x06 /* Public */,
      12,    0,  110,    2, 0x06 /* Public */,
      13,    1,  111,    2, 0x06 /* Public */,
      14,    0,  114,    2, 0x06 /* Public */,
      15,    0,  115,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    1,  116,    2, 0x0a /* Public */,
      18,    2,  119,    2, 0x0a /* Public */,
      22,    1,  124,    2, 0x0a /* Public */,
      24,    1,  127,    2, 0x0a /* Public */,
      26,    0,  130,    2, 0x0a /* Public */,
      27,    1,  131,    2, 0x0a /* Public */,
      29,    0,  134,    2, 0x0a /* Public */,
      30,    0,  135,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,    3,    4,    5,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Double,    9,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,   17,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 20,   19,   21,
    QMetaType::Void, QMetaType::Int,   23,
    QMetaType::Void, QMetaType::Int,   25,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   28,
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
        case 8: _t->setPsu((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: _t->setFunctionGen((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< functionGenControl*(*)>(_a[2]))); break;
        case 10: _t->setDeviceMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->newDig((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->psuTick(); break;
        case 13: _t->setGain((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 14: _t->avrDebug(); break;
        case 15: _t->isoTimerTick(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 9:
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
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
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
QT_END_MOC_NAMESPACE
