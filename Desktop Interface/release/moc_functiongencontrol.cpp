/****************************************************************************
** Meta object code from reading C++ file 'functiongencontrol.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../functiongencontrol.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'functiongencontrol.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_functionGenControl_t {
    QByteArrayData data[24];
    char stringdata0[333];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_functionGenControl_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_functionGenControl_t qt_meta_stringdata_functionGenControl = {
    {
QT_MOC_LITERAL(0, 0, 18), // "functionGenControl"
QT_MOC_LITERAL(1, 19, 19), // "functionGenToUpdate"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 7), // "channel"
QT_MOC_LITERAL(4, 48, 19), // "functionGenControl*"
QT_MOC_LITERAL(5, 68, 11), // "fGenControl"
QT_MOC_LITERAL(6, 80, 14), // "setMaxFreq_CH1"
QT_MOC_LITERAL(7, 95, 7), // "maxFreq"
QT_MOC_LITERAL(8, 103, 14), // "setMinFreq_CH1"
QT_MOC_LITERAL(9, 118, 7), // "minFreq"
QT_MOC_LITERAL(10, 126, 14), // "setMaxFreq_CH2"
QT_MOC_LITERAL(11, 141, 14), // "setMinFreq_CH2"
QT_MOC_LITERAL(12, 156, 16), // "waveformName_CH1"
QT_MOC_LITERAL(13, 173, 7), // "newName"
QT_MOC_LITERAL(14, 181, 14), // "freqUpdate_CH1"
QT_MOC_LITERAL(15, 196, 7), // "newFreq"
QT_MOC_LITERAL(16, 204, 19), // "amplitudeUpdate_CH1"
QT_MOC_LITERAL(17, 224, 12), // "newAmplitude"
QT_MOC_LITERAL(18, 237, 16), // "offsetUpdate_CH1"
QT_MOC_LITERAL(19, 254, 9), // "newOffset"
QT_MOC_LITERAL(20, 264, 16), // "waveformName_CH2"
QT_MOC_LITERAL(21, 281, 14), // "freqUpdate_CH2"
QT_MOC_LITERAL(22, 296, 19), // "amplitudeUpdate_CH2"
QT_MOC_LITERAL(23, 316, 16) // "offsetUpdate_CH2"

    },
    "functionGenControl\0functionGenToUpdate\0"
    "\0channel\0functionGenControl*\0fGenControl\0"
    "setMaxFreq_CH1\0maxFreq\0setMinFreq_CH1\0"
    "minFreq\0setMaxFreq_CH2\0setMinFreq_CH2\0"
    "waveformName_CH1\0newName\0freqUpdate_CH1\0"
    "newFreq\0amplitudeUpdate_CH1\0newAmplitude\0"
    "offsetUpdate_CH1\0newOffset\0waveformName_CH2\0"
    "freqUpdate_CH2\0amplitudeUpdate_CH2\0"
    "offsetUpdate_CH2"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_functionGenControl[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   79,    2, 0x06 /* Public */,
       6,    1,   84,    2, 0x06 /* Public */,
       8,    1,   87,    2, 0x06 /* Public */,
      10,    1,   90,    2, 0x06 /* Public */,
      11,    1,   93,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    1,   96,    2, 0x0a /* Public */,
      14,    1,   99,    2, 0x0a /* Public */,
      16,    1,  102,    2, 0x0a /* Public */,
      18,    1,  105,    2, 0x0a /* Public */,
      20,    1,  108,    2, 0x0a /* Public */,
      21,    1,  111,    2, 0x0a /* Public */,
      22,    1,  114,    2, 0x0a /* Public */,
      23,    1,  117,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::Double,    7,
    QMetaType::Void, QMetaType::Double,    9,
    QMetaType::Void, QMetaType::Double,    7,
    QMetaType::Void, QMetaType::Double,    9,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::Double,   15,
    QMetaType::Void, QMetaType::Double,   17,
    QMetaType::Void, QMetaType::Double,   19,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::Double,   15,
    QMetaType::Void, QMetaType::Double,   17,
    QMetaType::Void, QMetaType::Double,   19,

       0        // eod
};

void functionGenControl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        functionGenControl *_t = static_cast<functionGenControl *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->functionGenToUpdate((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< functionGenControl*(*)>(_a[2]))); break;
        case 1: _t->setMaxFreq_CH1((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->setMinFreq_CH1((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->setMaxFreq_CH2((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->setMinFreq_CH2((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->waveformName_CH1((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->freqUpdate_CH1((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->amplitudeUpdate_CH1((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->offsetUpdate_CH1((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: _t->waveformName_CH2((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->freqUpdate_CH2((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->amplitudeUpdate_CH2((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: _t->offsetUpdate_CH2((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
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
            typedef void (functionGenControl::*_t)(int , functionGenControl * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&functionGenControl::functionGenToUpdate)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (functionGenControl::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&functionGenControl::setMaxFreq_CH1)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (functionGenControl::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&functionGenControl::setMinFreq_CH1)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (functionGenControl::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&functionGenControl::setMaxFreq_CH2)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (functionGenControl::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&functionGenControl::setMinFreq_CH2)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject functionGenControl::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_functionGenControl.data,
      qt_meta_data_functionGenControl,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *functionGenControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *functionGenControl::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_functionGenControl.stringdata0))
        return static_cast<void*>(const_cast< functionGenControl*>(this));
    return QLabel::qt_metacast(_clname);
}

int functionGenControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void functionGenControl::functionGenToUpdate(int _t1, functionGenControl * _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void functionGenControl::setMaxFreq_CH1(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void functionGenControl::setMinFreq_CH1(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void functionGenControl::setMaxFreq_CH2(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void functionGenControl::setMinFreq_CH2(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
