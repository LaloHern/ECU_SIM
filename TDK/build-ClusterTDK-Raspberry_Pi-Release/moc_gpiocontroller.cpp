/****************************************************************************
** Meta object code from reading C++ file 'gpiocontroller.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ClusterTDK/gpiocontroller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gpiocontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GPIOController_t {
    QByteArrayData data[21];
    char stringdata0[250];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GPIOController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GPIOController_t qt_meta_stringdata_GPIOController = {
    {
QT_MOC_LITERAL(0, 0, 14), // "GPIOController"
QT_MOC_LITERAL(1, 15, 12), // "speedChanged"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 16), // "engineRpmChanged"
QT_MOC_LITERAL(4, 46, 17), // "engineTempChanged"
QT_MOC_LITERAL(5, 64, 16), // "fuelLevelChanged"
QT_MOC_LITERAL(6, 81, 20), // "leftTurnLightChanged"
QT_MOC_LITERAL(7, 102, 21), // "rightTurnLightChanged"
QT_MOC_LITERAL(8, 124, 8), // "pollLoop"
QT_MOC_LITERAL(9, 133, 6), // "canMsg"
QT_MOC_LITERAL(10, 140, 11), // "writeCANMsg"
QT_MOC_LITERAL(11, 152, 2), // "id"
QT_MOC_LITERAL(12, 155, 3), // "len"
QT_MOC_LITERAL(13, 159, 13), // "setMsgPayload"
QT_MOC_LITERAL(14, 173, 10), // "m_canMsgId"
QT_MOC_LITERAL(15, 184, 5), // "speed"
QT_MOC_LITERAL(16, 190, 9), // "engineRpm"
QT_MOC_LITERAL(17, 200, 10), // "engineTemp"
QT_MOC_LITERAL(18, 211, 9), // "fuelLevel"
QT_MOC_LITERAL(19, 221, 13), // "leftTurnLight"
QT_MOC_LITERAL(20, 235, 14) // "rightTurnLight"

    },
    "GPIOController\0speedChanged\0\0"
    "engineRpmChanged\0engineTempChanged\0"
    "fuelLevelChanged\0leftTurnLightChanged\0"
    "rightTurnLightChanged\0pollLoop\0canMsg\0"
    "writeCANMsg\0id\0len\0setMsgPayload\0"
    "m_canMsgId\0speed\0engineRpm\0engineTemp\0"
    "fuelLevel\0leftTurnLight\0rightTurnLight"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GPIOController[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       7,   82, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,
       3,    0,   65,    2, 0x06 /* Public */,
       4,    0,   66,    2, 0x06 /* Public */,
       5,    0,   67,    2, 0x06 /* Public */,
       6,    0,   68,    2, 0x06 /* Public */,
       7,    0,   69,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   70,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
       9,    0,   71,    2, 0x02 /* Public */,
      10,    2,   72,    2, 0x02 /* Public */,
      13,    2,   77,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

 // methods: parameters
    QMetaType::UChar,
    QMetaType::Void, QMetaType::UInt, QMetaType::UChar,   11,   12,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,

 // properties: name, type, flags
      14, QMetaType::UChar, 0x00095001,
      15, QMetaType::Int, 0x00495103,
      16, QMetaType::Int, 0x00495103,
      17, QMetaType::Int, 0x00495103,
      18, QMetaType::Int, 0x00495103,
      19, QMetaType::Bool, 0x00495103,
      20, QMetaType::Bool, 0x00495103,

 // properties: notify_signal_id
       0,
       0,
       1,
       2,
       3,
       4,
       5,

       0        // eod
};

void GPIOController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GPIOController *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->speedChanged(); break;
        case 1: _t->engineRpmChanged(); break;
        case 2: _t->engineTempChanged(); break;
        case 3: _t->fuelLevelChanged(); break;
        case 4: _t->leftTurnLightChanged(); break;
        case 5: _t->rightTurnLightChanged(); break;
        case 6: _t->pollLoop(); break;
        case 7: { unsigned char _r = _t->canMsg();
            if (_a[0]) *reinterpret_cast< unsigned char*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->writeCANMsg((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< unsigned char(*)>(_a[2]))); break;
        case 9: _t->setMsgPayload((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GPIOController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPIOController::speedChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GPIOController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPIOController::engineRpmChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GPIOController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPIOController::engineTempChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (GPIOController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPIOController::fuelLevelChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (GPIOController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPIOController::leftTurnLightChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (GPIOController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPIOController::rightTurnLightChanged)) {
                *result = 5;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<GPIOController *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< unsigned char*>(_v) = _t->canMsg(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->speed(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->engineRpm(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->engineTemp(); break;
        case 4: *reinterpret_cast< int*>(_v) = _t->fuelLevel(); break;
        case 5: *reinterpret_cast< bool*>(_v) = _t->leftTurnLight(); break;
        case 6: *reinterpret_cast< bool*>(_v) = _t->rightTurnLight(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<GPIOController *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 1: _t->setSpeed(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->setEngineRpm(*reinterpret_cast< int*>(_v)); break;
        case 3: _t->setEngineTemp(*reinterpret_cast< int*>(_v)); break;
        case 4: _t->setFuelLevel(*reinterpret_cast< int*>(_v)); break;
        case 5: _t->setLeftTurnLight(*reinterpret_cast< bool*>(_v)); break;
        case 6: _t->setRightTurnLight(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject GPIOController::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_GPIOController.data,
    qt_meta_data_GPIOController,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GPIOController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GPIOController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GPIOController.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int GPIOController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 7;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void GPIOController::speedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void GPIOController::engineRpmChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void GPIOController::engineTempChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void GPIOController::fuelLevelChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void GPIOController::leftTurnLightChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void GPIOController::rightTurnLightChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
