/****************************************************************************
** Meta object code from reading C++ file 'cursorenabler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui_elements/cursorenabler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cursorenabler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_cursorEnabler_t {
    QByteArrayData data[10];
    char stringdata0[99];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_cursorEnabler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_cursorEnabler_t qt_meta_stringdata_cursorEnabler = {
    {
QT_MOC_LITERAL(0, 0, 13), // "cursorEnabler"
QT_MOC_LITERAL(1, 14, 8), // "tickHori"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 8), // "tickVert"
QT_MOC_LITERAL(4, 33, 12), // "passOnSignal"
QT_MOC_LITERAL(5, 46, 12), // "QMouseEvent*"
QT_MOC_LITERAL(6, 59, 5), // "event"
QT_MOC_LITERAL(7, 65, 11), // "setTurnedOn"
QT_MOC_LITERAL(8, 77, 7), // "enabled"
QT_MOC_LITERAL(9, 85, 13) // "clickDetected"

    },
    "cursorEnabler\0tickHori\0\0tickVert\0"
    "passOnSignal\0QMouseEvent*\0event\0"
    "setTurnedOn\0enabled\0clickDetected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_cursorEnabler[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       3,    1,   42,    2, 0x06 /* Public */,
       4,    1,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   48,    2, 0x0a /* Public */,
       9,    1,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, 0x80000000 | 5,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, 0x80000000 | 5,    6,

       0        // eod
};

void cursorEnabler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        cursorEnabler *_t = static_cast<cursorEnabler *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->tickHori((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->tickVert((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->passOnSignal((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 3: _t->setTurnedOn((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->clickDetected((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (cursorEnabler::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&cursorEnabler::tickHori)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (cursorEnabler::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&cursorEnabler::tickVert)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (cursorEnabler::*_t)(QMouseEvent * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&cursorEnabler::passOnSignal)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject cursorEnabler::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_cursorEnabler.data,
      qt_meta_data_cursorEnabler,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *cursorEnabler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *cursorEnabler::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_cursorEnabler.stringdata0))
        return static_cast<void*>(const_cast< cursorEnabler*>(this));
    return QLabel::qt_metacast(_clname);
}

int cursorEnabler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void cursorEnabler::tickHori(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void cursorEnabler::tickVert(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void cursorEnabler::passOnSignal(QMouseEvent * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
