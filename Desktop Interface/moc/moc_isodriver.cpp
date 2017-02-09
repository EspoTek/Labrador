/****************************************************************************
** Meta object code from reading C++ file 'isodriver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../isodriver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'isodriver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_isoDriver_t {
    QByteArrayData data[83];
    char stringdata0[1132];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_isoDriver_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_isoDriver_t qt_meta_stringdata_isoDriver = {
    {
QT_MOC_LITERAL(0, 0, 9), // "isoDriver"
QT_MOC_LITERAL(1, 10, 7), // "setGain"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 7), // "newGain"
QT_MOC_LITERAL(4, 27, 13), // "disableWindow"
QT_MOC_LITERAL(5, 41, 7), // "enabled"
QT_MOC_LITERAL(6, 49, 21), // "setCursorStatsVisible"
QT_MOC_LITERAL(7, 71, 19), // "sendCursorStatsText"
QT_MOC_LITERAL(8, 91, 4), // "text"
QT_MOC_LITERAL(9, 96, 19), // "singleShotTriggered"
QT_MOC_LITERAL(10, 116, 9), // "triggered"
QT_MOC_LITERAL(11, 126, 13), // "multimeterMax"
QT_MOC_LITERAL(12, 140, 13), // "multimeterMin"
QT_MOC_LITERAL(13, 154, 14), // "multimeterMean"
QT_MOC_LITERAL(14, 169, 20), // "sendMultimeterLabel1"
QT_MOC_LITERAL(15, 190, 20), // "sendMultimeterLabel2"
QT_MOC_LITERAL(16, 211, 20), // "sendMultimeterLabel3"
QT_MOC_LITERAL(17, 232, 14), // "changeTimeAxis"
QT_MOC_LITERAL(18, 247, 8), // "positive"
QT_MOC_LITERAL(19, 256, 16), // "sendTriggerValue"
QT_MOC_LITERAL(20, 273, 12), // "sendVmax_CH1"
QT_MOC_LITERAL(21, 286, 12), // "sendVmin_CH1"
QT_MOC_LITERAL(22, 299, 13), // "sendVmean_CH1"
QT_MOC_LITERAL(23, 313, 12), // "sendVmax_CH2"
QT_MOC_LITERAL(24, 326, 12), // "sendVmin_CH2"
QT_MOC_LITERAL(25, 339, 13), // "sendVmean_CH2"
QT_MOC_LITERAL(26, 353, 9), // "setWindow"
QT_MOC_LITERAL(27, 363, 9), // "newWindow"
QT_MOC_LITERAL(28, 373, 15), // "setVoltageRange"
QT_MOC_LITERAL(29, 389, 12), // "QWheelEvent*"
QT_MOC_LITERAL(30, 402, 5), // "event"
QT_MOC_LITERAL(31, 408, 9), // "timerTick"
QT_MOC_LITERAL(32, 418, 15), // "pauseEnable_CH1"
QT_MOC_LITERAL(33, 434, 15), // "pauseEnable_CH2"
QT_MOC_LITERAL(34, 450, 22), // "pauseEnable_multimeter"
QT_MOC_LITERAL(35, 473, 10), // "startTimer"
QT_MOC_LITERAL(36, 484, 12), // "clearBuffers"
QT_MOC_LITERAL(37, 497, 6), // "ch3751"
QT_MOC_LITERAL(38, 504, 6), // "ch3752"
QT_MOC_LITERAL(39, 511, 5), // "ch750"
QT_MOC_LITERAL(40, 517, 14), // "setVisible_CH2"
QT_MOC_LITERAL(41, 532, 7), // "visible"
QT_MOC_LITERAL(42, 540, 11), // "gainBuffers"
QT_MOC_LITERAL(43, 552, 10), // "multiplier"
QT_MOC_LITERAL(44, 563, 8), // "gainTick"
QT_MOC_LITERAL(45, 572, 11), // "setAutoGain"
QT_MOC_LITERAL(46, 584, 15), // "graphMousePress"
QT_MOC_LITERAL(47, 600, 12), // "QMouseEvent*"
QT_MOC_LITERAL(48, 613, 17), // "graphMouseRelease"
QT_MOC_LITERAL(49, 631, 14), // "graphMouseMove"
QT_MOC_LITERAL(50, 646, 16), // "cursorEnableHori"
QT_MOC_LITERAL(51, 663, 16), // "cursorEnableVert"
QT_MOC_LITERAL(52, 680, 17), // "setTriggerEnabled"
QT_MOC_LITERAL(53, 698, 15), // "setTriggerLevel"
QT_MOC_LITERAL(54, 714, 5), // "level"
QT_MOC_LITERAL(55, 720, 20), // "setSingleShotEnabled"
QT_MOC_LITERAL(56, 741, 14), // "setTriggerMode"
QT_MOC_LITERAL(57, 756, 7), // "newMode"
QT_MOC_LITERAL(58, 764, 9), // "setAC_CH1"
QT_MOC_LITERAL(59, 774, 9), // "setAC_CH2"
QT_MOC_LITERAL(60, 784, 17), // "setMultimeterType"
QT_MOC_LITERAL(61, 802, 4), // "type"
QT_MOC_LITERAL(62, 807, 19), // "setSeriesResistance"
QT_MOC_LITERAL(63, 827, 10), // "resistance"
QT_MOC_LITERAL(64, 838, 15), // "multimeterStats"
QT_MOC_LITERAL(65, 854, 8), // "enableMM"
QT_MOC_LITERAL(66, 863, 18), // "setAutoMultimeterV"
QT_MOC_LITERAL(67, 882, 18), // "setAutoMultimeterI"
QT_MOC_LITERAL(68, 901, 18), // "setForceMillivolts"
QT_MOC_LITERAL(69, 920, 17), // "setForceMilliamps"
QT_MOC_LITERAL(70, 938, 13), // "setForceVolts"
QT_MOC_LITERAL(71, 952, 12), // "setForceAmps"
QT_MOC_LITERAL(72, 965, 26), // "setSerialDecodeEnabled_CH1"
QT_MOC_LITERAL(73, 992, 26), // "setSerialDecodeEnabled_CH2"
QT_MOC_LITERAL(74, 1019, 9), // "setXYmode"
QT_MOC_LITERAL(75, 1029, 23), // "triggerGroupStateChange"
QT_MOC_LITERAL(76, 1053, 13), // "slowTimerTick"
QT_MOC_LITERAL(77, 1067, 11), // "setTopRange"
QT_MOC_LITERAL(78, 1079, 6), // "newTop"
QT_MOC_LITERAL(79, 1086, 11), // "setBotRange"
QT_MOC_LITERAL(80, 1098, 6), // "newBot"
QT_MOC_LITERAL(81, 1105, 13), // "setTimeWindow"
QT_MOC_LITERAL(82, 1119, 12) // "takeSnapshot"

    },
    "isoDriver\0setGain\0\0newGain\0disableWindow\0"
    "enabled\0setCursorStatsVisible\0"
    "sendCursorStatsText\0text\0singleShotTriggered\0"
    "triggered\0multimeterMax\0multimeterMin\0"
    "multimeterMean\0sendMultimeterLabel1\0"
    "sendMultimeterLabel2\0sendMultimeterLabel3\0"
    "changeTimeAxis\0positive\0sendTriggerValue\0"
    "sendVmax_CH1\0sendVmin_CH1\0sendVmean_CH1\0"
    "sendVmax_CH2\0sendVmin_CH2\0sendVmean_CH2\0"
    "setWindow\0newWindow\0setVoltageRange\0"
    "QWheelEvent*\0event\0timerTick\0"
    "pauseEnable_CH1\0pauseEnable_CH2\0"
    "pauseEnable_multimeter\0startTimer\0"
    "clearBuffers\0ch3751\0ch3752\0ch750\0"
    "setVisible_CH2\0visible\0gainBuffers\0"
    "multiplier\0gainTick\0setAutoGain\0"
    "graphMousePress\0QMouseEvent*\0"
    "graphMouseRelease\0graphMouseMove\0"
    "cursorEnableHori\0cursorEnableVert\0"
    "setTriggerEnabled\0setTriggerLevel\0"
    "level\0setSingleShotEnabled\0setTriggerMode\0"
    "newMode\0setAC_CH1\0setAC_CH2\0"
    "setMultimeterType\0type\0setSeriesResistance\0"
    "resistance\0multimeterStats\0enableMM\0"
    "setAutoMultimeterV\0setAutoMultimeterI\0"
    "setForceMillivolts\0setForceMilliamps\0"
    "setForceVolts\0setForceAmps\0"
    "setSerialDecodeEnabled_CH1\0"
    "setSerialDecodeEnabled_CH2\0setXYmode\0"
    "triggerGroupStateChange\0slowTimerTick\0"
    "setTopRange\0newTop\0setBotRange\0newBot\0"
    "setTimeWindow\0takeSnapshot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_isoDriver[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      61,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      19,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  319,    2, 0x06 /* Public */,
       4,    1,  322,    2, 0x06 /* Public */,
       6,    1,  325,    2, 0x06 /* Public */,
       7,    1,  328,    2, 0x06 /* Public */,
       9,    1,  331,    2, 0x06 /* Public */,
      11,    1,  334,    2, 0x06 /* Public */,
      12,    1,  337,    2, 0x06 /* Public */,
      13,    1,  340,    2, 0x06 /* Public */,
      14,    1,  343,    2, 0x06 /* Public */,
      15,    1,  346,    2, 0x06 /* Public */,
      16,    1,  349,    2, 0x06 /* Public */,
      17,    1,  352,    2, 0x06 /* Public */,
      19,    1,  355,    2, 0x06 /* Public */,
      20,    1,  358,    2, 0x06 /* Public */,
      21,    1,  361,    2, 0x06 /* Public */,
      22,    1,  364,    2, 0x06 /* Public */,
      23,    1,  367,    2, 0x06 /* Public */,
      24,    1,  370,    2, 0x06 /* Public */,
      25,    1,  373,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      26,    1,  376,    2, 0x0a /* Public */,
      28,    1,  379,    2, 0x0a /* Public */,
      31,    0,  382,    2, 0x0a /* Public */,
      32,    1,  383,    2, 0x0a /* Public */,
      33,    1,  386,    2, 0x0a /* Public */,
      34,    1,  389,    2, 0x0a /* Public */,
      35,    0,  392,    2, 0x0a /* Public */,
      36,    3,  393,    2, 0x0a /* Public */,
      40,    1,  400,    2, 0x0a /* Public */,
      42,    1,  403,    2, 0x0a /* Public */,
      44,    0,  406,    2, 0x0a /* Public */,
      45,    1,  407,    2, 0x0a /* Public */,
      46,    1,  410,    2, 0x0a /* Public */,
      48,    1,  413,    2, 0x0a /* Public */,
      49,    1,  416,    2, 0x0a /* Public */,
      50,    1,  419,    2, 0x0a /* Public */,
      51,    1,  422,    2, 0x0a /* Public */,
      52,    1,  425,    2, 0x0a /* Public */,
      53,    1,  428,    2, 0x0a /* Public */,
      55,    1,  431,    2, 0x0a /* Public */,
      56,    1,  434,    2, 0x0a /* Public */,
      58,    1,  437,    2, 0x0a /* Public */,
      59,    1,  440,    2, 0x0a /* Public */,
      60,    1,  443,    2, 0x0a /* Public */,
      62,    1,  446,    2, 0x0a /* Public */,
      64,    0,  449,    2, 0x0a /* Public */,
      65,    0,  450,    2, 0x0a /* Public */,
      66,    1,  451,    2, 0x0a /* Public */,
      67,    1,  454,    2, 0x0a /* Public */,
      68,    1,  457,    2, 0x0a /* Public */,
      69,    1,  460,    2, 0x0a /* Public */,
      70,    1,  463,    2, 0x0a /* Public */,
      71,    1,  466,    2, 0x0a /* Public */,
      72,    1,  469,    2, 0x0a /* Public */,
      73,    1,  472,    2, 0x0a /* Public */,
      74,    1,  475,    2, 0x0a /* Public */,
      75,    1,  478,    2, 0x0a /* Public */,
      76,    0,  481,    2, 0x0a /* Public */,
      77,    1,  482,    2, 0x0a /* Public */,
      79,    1,  485,    2, 0x0a /* Public */,
      81,    1,  488,    2, 0x0a /* Public */,
      82,    0,  491,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,   27,
    QMetaType::Void, 0x80000000 | 29,   30,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,   37,   38,   39,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::Void, QMetaType::Double,   43,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, 0x80000000 | 47,   30,
    QMetaType::Void, 0x80000000 | 47,   30,
    QMetaType::Void, 0x80000000 | 47,   30,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Double,   54,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Int,   57,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Int,   61,
    QMetaType::Void, QMetaType::Double,   63,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   78,
    QMetaType::Void, QMetaType::Double,   80,
    QMetaType::Void, QMetaType::Double,   27,
    QMetaType::Void,

       0        // eod
};

void isoDriver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        isoDriver *_t = static_cast<isoDriver *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setGain((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->disableWindow((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->setCursorStatsVisible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->sendCursorStatsText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->singleShotTriggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->multimeterMax((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->multimeterMin((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->multimeterMean((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->sendMultimeterLabel1((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->sendMultimeterLabel2((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->sendMultimeterLabel3((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->changeTimeAxis((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->sendTriggerValue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 13: _t->sendVmax_CH1((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 14: _t->sendVmin_CH1((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 15: _t->sendVmean_CH1((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 16: _t->sendVmax_CH2((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 17: _t->sendVmin_CH2((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 18: _t->sendVmean_CH2((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 19: _t->setWindow((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->setVoltageRange((*reinterpret_cast< QWheelEvent*(*)>(_a[1]))); break;
        case 21: _t->timerTick(); break;
        case 22: _t->pauseEnable_CH1((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 23: _t->pauseEnable_CH2((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: _t->pauseEnable_multimeter((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 25: _t->startTimer(); break;
        case 26: _t->clearBuffers((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 27: _t->setVisible_CH2((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 28: _t->gainBuffers((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 29: _t->gainTick(); break;
        case 30: _t->setAutoGain((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 31: _t->graphMousePress((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 32: _t->graphMouseRelease((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 33: _t->graphMouseMove((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 34: _t->cursorEnableHori((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 35: _t->cursorEnableVert((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 36: _t->setTriggerEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 37: _t->setTriggerLevel((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 38: _t->setSingleShotEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 39: _t->setTriggerMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 40: _t->setAC_CH1((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 41: _t->setAC_CH2((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 42: _t->setMultimeterType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 43: _t->setSeriesResistance((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 44: _t->multimeterStats(); break;
        case 45: _t->enableMM(); break;
        case 46: _t->setAutoMultimeterV((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 47: _t->setAutoMultimeterI((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 48: _t->setForceMillivolts((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 49: _t->setForceMilliamps((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 50: _t->setForceVolts((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 51: _t->setForceAmps((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 52: _t->setSerialDecodeEnabled_CH1((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 53: _t->setSerialDecodeEnabled_CH2((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 54: _t->setXYmode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 55: _t->triggerGroupStateChange((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 56: _t->slowTimerTick(); break;
        case 57: _t->setTopRange((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 58: _t->setBotRange((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 59: _t->setTimeWindow((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 60: _t->takeSnapshot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (isoDriver::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&isoDriver::setGain)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (isoDriver::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&isoDriver::disableWindow)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (isoDriver::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&isoDriver::setCursorStatsVisible)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (isoDriver::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&isoDriver::sendCursorStatsText)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (isoDriver::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&isoDriver::singleShotTriggered)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (isoDriver::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&isoDriver::multimeterMax)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (isoDriver::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&isoDriver::multimeterMin)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (isoDriver::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&isoDriver::multimeterMean)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (isoDriver::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&isoDriver::sendMultimeterLabel1)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (isoDriver::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&isoDriver::sendMultimeterLabel2)) {
                *result = 9;
                return;
            }
        }
        {
            typedef void (isoDriver::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&isoDriver::sendMultimeterLabel3)) {
                *result = 10;
                return;
            }
        }
        {
            typedef void (isoDriver::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&isoDriver::changeTimeAxis)) {
                *result = 11;
                return;
            }
        }
        {
            typedef void (isoDriver::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&isoDriver::sendTriggerValue)) {
                *result = 12;
                return;
            }
        }
        {
            typedef void (isoDriver::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&isoDriver::sendVmax_CH1)) {
                *result = 13;
                return;
            }
        }
        {
            typedef void (isoDriver::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&isoDriver::sendVmin_CH1)) {
                *result = 14;
                return;
            }
        }
        {
            typedef void (isoDriver::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&isoDriver::sendVmean_CH1)) {
                *result = 15;
                return;
            }
        }
        {
            typedef void (isoDriver::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&isoDriver::sendVmax_CH2)) {
                *result = 16;
                return;
            }
        }
        {
            typedef void (isoDriver::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&isoDriver::sendVmin_CH2)) {
                *result = 17;
                return;
            }
        }
        {
            typedef void (isoDriver::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&isoDriver::sendVmean_CH2)) {
                *result = 18;
                return;
            }
        }
    }
}

const QMetaObject isoDriver::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_isoDriver.data,
      qt_meta_data_isoDriver,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *isoDriver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *isoDriver::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_isoDriver.stringdata0))
        return static_cast<void*>(const_cast< isoDriver*>(this));
    return QLabel::qt_metacast(_clname);
}

int isoDriver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 61)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 61;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 61)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 61;
    }
    return _id;
}

// SIGNAL 0
void isoDriver::setGain(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void isoDriver::disableWindow(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void isoDriver::setCursorStatsVisible(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void isoDriver::sendCursorStatsText(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void isoDriver::singleShotTriggered(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void isoDriver::multimeterMax(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void isoDriver::multimeterMin(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void isoDriver::multimeterMean(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void isoDriver::sendMultimeterLabel1(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void isoDriver::sendMultimeterLabel2(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void isoDriver::sendMultimeterLabel3(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void isoDriver::changeTimeAxis(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void isoDriver::sendTriggerValue(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void isoDriver::sendVmax_CH1(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void isoDriver::sendVmin_CH1(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void isoDriver::sendVmean_CH1(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void isoDriver::sendVmax_CH2(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void isoDriver::sendVmin_CH2(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void isoDriver::sendVmean_CH2(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}
QT_END_MOC_NAMESPACE
