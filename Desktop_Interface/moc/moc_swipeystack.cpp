/****************************************************************************
** Meta object code from reading C++ file 'swipeystack.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui_elements/swipeystack.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'swipeystack.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_swipeyStack_t {
    QByteArrayData data[10];
    char stringdata0[106];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_swipeyStack_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_swipeyStack_t qt_meta_stringdata_swipeyStack = {
    {
QT_MOC_LITERAL(0, 0, 11), // "swipeyStack"
QT_MOC_LITERAL(1, 12, 15), // "mousePressEvent"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 12), // "QMouseEvent*"
QT_MOC_LITERAL(4, 42, 5), // "event"
QT_MOC_LITERAL(5, 48, 17), // "mouseReleaseEvent"
QT_MOC_LITERAL(6, 66, 14), // "enableWrapping"
QT_MOC_LITERAL(7, 81, 7), // "enabled"
QT_MOC_LITERAL(8, 89, 10), // "cycleStack"
QT_MOC_LITERAL(9, 100, 5) // "delta"

    },
    "swipeyStack\0mousePressEvent\0\0QMouseEvent*\0"
    "event\0mouseReleaseEvent\0enableWrapping\0"
    "enabled\0cycleStack\0delta"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_swipeyStack[] = {

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
       1,    1,   34,    2, 0x0a /* Public */,
       5,    1,   37,    2, 0x0a /* Public */,
       6,    1,   40,    2, 0x0a /* Public */,
       8,    1,   43,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Int,    9,

       0        // eod
};

void swipeyStack::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        swipeyStack *_t = static_cast<swipeyStack *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->mousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 1: _t->mouseReleaseEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 2: _t->enableWrapping((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->cycleStack((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject swipeyStack::staticMetaObject = {
    { &QStackedWidget::staticMetaObject, qt_meta_stringdata_swipeyStack.data,
      qt_meta_data_swipeyStack,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *swipeyStack::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *swipeyStack::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_swipeyStack.stringdata0))
        return static_cast<void*>(const_cast< swipeyStack*>(this));
    return QStackedWidget::qt_metacast(_clname);
}

int swipeyStack::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QStackedWidget::qt_metacall(_c, _id, _a);
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
