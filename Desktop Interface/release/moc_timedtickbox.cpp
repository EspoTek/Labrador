/****************************************************************************
** Meta object code from reading C++ file 'timedtickbox.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui_elements/timedtickbox.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'timedtickbox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_timedTickBox_t {
    QByteArrayData data[6];
    char stringdata0[55];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_timedTickBox_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_timedTickBox_t qt_meta_stringdata_timedTickBox = {
    {
QT_MOC_LITERAL(0, 0, 12), // "timedTickBox"
QT_MOC_LITERAL(1, 13, 10), // "resetTimer"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 9), // "timerTick"
QT_MOC_LITERAL(4, 35, 11), // "enableTimer"
QT_MOC_LITERAL(5, 47, 7) // "enabled"

    },
    "timedTickBox\0resetTimer\0\0timerTick\0"
    "enableTimer\0enabled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_timedTickBox[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    0,   30,    2, 0x0a /* Public */,
       4,    1,   31,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    5,

       0        // eod
};

void timedTickBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        timedTickBox *_t = static_cast<timedTickBox *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->resetTimer(); break;
        case 1: _t->timerTick(); break;
        case 2: _t->enableTimer((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject timedTickBox::staticMetaObject = {
    { &QCheckBox::staticMetaObject, qt_meta_stringdata_timedTickBox.data,
      qt_meta_data_timedTickBox,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *timedTickBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *timedTickBox::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_timedTickBox.stringdata0))
        return static_cast<void*>(const_cast< timedTickBox*>(this));
    return QCheckBox::qt_metacast(_clname);
}

int timedTickBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCheckBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
