/****************************************************************************
** Meta object code from reading C++ file 'esposlider.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui_elements/esposlider.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'esposlider.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_espoSlider_t {
    QByteArrayData data[9];
    char stringdata0[74];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_espoSlider_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_espoSlider_t qt_meta_stringdata_espoSlider = {
    {
QT_MOC_LITERAL(0, 0, 10), // "espoSlider"
QT_MOC_LITERAL(1, 11, 6), // "lcdOut"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 6), // "values"
QT_MOC_LITERAL(4, 26, 14), // "voltageChanged"
QT_MOC_LITERAL(5, 41, 10), // "newVoltage"
QT_MOC_LITERAL(6, 52, 9), // "selfMoved"
QT_MOC_LITERAL(7, 62, 6), // "newval"
QT_MOC_LITERAL(8, 69, 4) // "poke"

    },
    "espoSlider\0lcdOut\0\0values\0voltageChanged\0"
    "newVoltage\0selfMoved\0newval\0poke"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_espoSlider[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    1,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   40,    2, 0x0a /* Public */,
       8,    0,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Double,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,

       0        // eod
};

void espoSlider::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        espoSlider *_t = static_cast<espoSlider *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->lcdOut((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->voltageChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->selfMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->poke(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (espoSlider::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&espoSlider::lcdOut)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (espoSlider::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&espoSlider::voltageChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject espoSlider::staticMetaObject = {
    { &QSlider::staticMetaObject, qt_meta_stringdata_espoSlider.data,
      qt_meta_data_espoSlider,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *espoSlider::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *espoSlider::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_espoSlider.stringdata0))
        return static_cast<void*>(const_cast< espoSlider*>(this));
    return QSlider::qt_metacast(_clname);
}

int espoSlider::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSlider::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void espoSlider::lcdOut(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void espoSlider::voltageChanged(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
