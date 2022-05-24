/****************************************************************************
** Meta object code from reading C++ file 'data.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../service/data.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'data.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_data_t {
    QByteArrayData data[11];
    char stringdata0[130];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_data_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_data_t qt_meta_stringdata_data = {
    {
QT_MOC_LITERAL(0, 0, 4), // "data"
QT_MOC_LITERAL(1, 5, 10), // "readyReady"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 9), // "init_time"
QT_MOC_LITERAL(4, 27, 12), // "refresh_plot"
QT_MOC_LITERAL(5, 40, 15), // "onNewConnection"
QT_MOC_LITERAL(6, 56, 14), // "processMessage"
QT_MOC_LITERAL(7, 71, 18), // "socketDisconnected"
QT_MOC_LITERAL(8, 90, 8), // "showTime"
QT_MOC_LITERAL(9, 99, 14), // "datamanagement"
QT_MOC_LITERAL(10, 114, 15) // "sendDataClient1"

    },
    "data\0readyReady\0\0init_time\0refresh_plot\0"
    "onNewConnection\0processMessage\0"
    "socketDisconnected\0showTime\0datamanagement\0"
    "sendDataClient1"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_data[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x0a /* Public */,
       3,    0,   60,    2, 0x0a /* Public */,
       4,    0,   61,    2, 0x0a /* Public */,
       5,    0,   62,    2, 0x08 /* Private */,
       6,    0,   63,    2, 0x08 /* Private */,
       7,    0,   64,    2, 0x08 /* Private */,
       8,    0,   65,    2, 0x08 /* Private */,
       9,    0,   66,    2, 0x08 /* Private */,
      10,    0,   67,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void data::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<data *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->readyReady(); break;
        case 1: _t->init_time(); break;
        case 2: _t->refresh_plot(); break;
        case 3: _t->onNewConnection(); break;
        case 4: _t->processMessage(); break;
        case 5: _t->socketDisconnected(); break;
        case 6: _t->showTime(); break;
        case 7: _t->datamanagement(); break;
        case 8: _t->sendDataClient1(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject data::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_data.data,
    qt_meta_data_data,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *data::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *data::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_data.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int data::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
