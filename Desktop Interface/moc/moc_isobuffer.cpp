/****************************************************************************
** Meta object code from reading C++ file 'isobuffer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../isobuffer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'isobuffer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_isoBuffer_t {
    QByteArrayData data[7];
    char stringdata0[64];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_isoBuffer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_isoBuffer_t qt_meta_stringdata_isoBuffer = {
    {
QT_MOC_LITERAL(0, 0, 9), // "isoBuffer"
QT_MOC_LITERAL(1, 10, 12), // "enableFileIO"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 6), // "QFile*"
QT_MOC_LITERAL(4, 31, 4), // "file"
QT_MOC_LITERAL(5, 36, 13), // "disableFileIO"
QT_MOC_LITERAL(6, 50, 13) // "updateConsole"

    },
    "isoBuffer\0enableFileIO\0\0QFile*\0file\0"
    "disableFileIO\0updateConsole"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_isoBuffer[] = {

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
       1,    1,   29,    2, 0x0a /* Public */,
       5,    0,   32,    2, 0x0a /* Public */,
       6,    0,   33,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void isoBuffer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        isoBuffer *_t = static_cast<isoBuffer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->enableFileIO((*reinterpret_cast< QFile*(*)>(_a[1]))); break;
        case 1: _t->disableFileIO(); break;
        case 2: _t->updateConsole(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QFile* >(); break;
            }
            break;
        }
    }
}

const QMetaObject isoBuffer::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_isoBuffer.data,
      qt_meta_data_isoBuffer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *isoBuffer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *isoBuffer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_isoBuffer.stringdata0))
        return static_cast<void*>(const_cast< isoBuffer*>(this));
    return QWidget::qt_metacast(_clname);
}

int isoBuffer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
