/****************************************************************************
** Meta object code from reading C++ file 'scoperangeenterdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../scoperangeenterdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scoperangeenterdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_scopeRangeEnterDialog_t {
    QByteArrayData data[9];
    char stringdata0[106];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_scopeRangeEnterDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_scopeRangeEnterDialog_t qt_meta_stringdata_scopeRangeEnterDialog = {
    {
QT_MOC_LITERAL(0, 0, 21), // "scopeRangeEnterDialog"
QT_MOC_LITERAL(1, 22, 11), // "yTopUpdated"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 3), // "val"
QT_MOC_LITERAL(4, 39, 11), // "yBotUpdated"
QT_MOC_LITERAL(5, 51, 13), // "windowUpdated"
QT_MOC_LITERAL(6, 65, 12), // "toUpdateYTop"
QT_MOC_LITERAL(7, 78, 12), // "toUpdateYBot"
QT_MOC_LITERAL(8, 91, 14) // "toUpdateWindow"

    },
    "scopeRangeEnterDialog\0yTopUpdated\0\0"
    "val\0yBotUpdated\0windowUpdated\0"
    "toUpdateYTop\0toUpdateYBot\0toUpdateWindow"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_scopeRangeEnterDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,
       5,    1,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   53,    2, 0x08 /* Private */,
       7,    1,   56,    2, 0x08 /* Private */,
       8,    1,   59,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,

       0        // eod
};

void scopeRangeEnterDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        scopeRangeEnterDialog *_t = static_cast<scopeRangeEnterDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->yTopUpdated((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->yBotUpdated((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->windowUpdated((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->toUpdateYTop((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->toUpdateYBot((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->toUpdateWindow((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (scopeRangeEnterDialog::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&scopeRangeEnterDialog::yTopUpdated)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (scopeRangeEnterDialog::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&scopeRangeEnterDialog::yBotUpdated)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (scopeRangeEnterDialog::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&scopeRangeEnterDialog::windowUpdated)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject scopeRangeEnterDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_scopeRangeEnterDialog.data,
      qt_meta_data_scopeRangeEnterDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *scopeRangeEnterDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *scopeRangeEnterDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_scopeRangeEnterDialog.stringdata0))
        return static_cast<void*>(const_cast< scopeRangeEnterDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int scopeRangeEnterDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void scopeRangeEnterDialog::yTopUpdated(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void scopeRangeEnterDialog::yBotUpdated(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void scopeRangeEnterDialog::windowUpdated(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
