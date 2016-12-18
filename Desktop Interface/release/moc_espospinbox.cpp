/****************************************************************************
** Meta object code from reading C++ file 'espospinbox.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui_elements/espospinbox.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'espospinbox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_espoSpinBox_t {
    QByteArrayData data[10];
    char stringdata0[84];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_espoSpinBox_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_espoSpinBox_t qt_meta_stringdata_espoSpinBox = {
    {
QT_MOC_LITERAL(0, 0, 11), // "espoSpinBox"
QT_MOC_LITERAL(1, 12, 14), // "maximumChanged"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 6), // "linked"
QT_MOC_LITERAL(4, 35, 6), // "setMax"
QT_MOC_LITERAL(5, 42, 6), // "newMax"
QT_MOC_LITERAL(6, 49, 6), // "setMin"
QT_MOC_LITERAL(7, 56, 6), // "newMin"
QT_MOC_LITERAL(8, 63, 14), // "changeStepping"
QT_MOC_LITERAL(9, 78, 5) // "value"

    },
    "espoSpinBox\0maximumChanged\0\0linked\0"
    "setMax\0newMax\0setMin\0newMin\0changeStepping\0"
    "value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_espoSpinBox[] = {

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
       4,    1,   37,    2, 0x0a /* Public */,
       6,    1,   40,    2, 0x0a /* Public */,
       8,    1,   43,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void, QMetaType::Double,    7,
    QMetaType::Void, QMetaType::Double,    9,

       0        // eod
};

void espoSpinBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        espoSpinBox *_t = static_cast<espoSpinBox *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->maximumChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->setMax((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->setMin((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->changeStepping((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject espoSpinBox::staticMetaObject = {
    { &QDoubleSpinBox::staticMetaObject, qt_meta_stringdata_espoSpinBox.data,
      qt_meta_data_espoSpinBox,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *espoSpinBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *espoSpinBox::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_espoSpinBox.stringdata0))
        return static_cast<void*>(const_cast< espoSpinBox*>(this));
    return QDoubleSpinBox::qt_metacast(_clname);
}

int espoSpinBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDoubleSpinBox::qt_metacall(_c, _id, _a);
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
