/****************************************************************************
** Meta object code from reading C++ file 'topview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Desktop/oslab_monitor/topview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'topview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_topview_t {
    QByteArrayData data[11];
    char stringdata[98];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_topview_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_topview_t qt_meta_stringdata_topview = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 7),
QT_MOC_LITERAL(2, 16, 0),
QT_MOC_LITERAL(3, 17, 3),
QT_MOC_LITERAL(4, 21, 3),
QT_MOC_LITERAL(5, 25, 11),
QT_MOC_LITERAL(6, 37, 12),
QT_MOC_LITERAL(7, 50, 14),
QT_MOC_LITERAL(8, 65, 11),
QT_MOC_LITERAL(9, 77, 6),
QT_MOC_LITERAL(10, 84, 12)
    },
    "topview\0pc_name\0\0num\0Msg\0launch_time\0"
    "running_time\0system_version\0CPU_version\0"
    "CPU_hz\0send_signals\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_topview[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   49,    2, 0x05,
       5,    2,   54,    2, 0x05,
       6,    2,   59,    2, 0x05,
       7,    2,   64,    2, 0x05,
       8,    2,   69,    2, 0x05,
       9,    2,   74,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
      10,    0,   79,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void topview::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        topview *_t = static_cast<topview *>(_o);
        switch (_id) {
        case 0: _t->pc_name((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->launch_time((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->running_time((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->system_version((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->CPU_version((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 5: _t->CPU_hz((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->send_signals(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (topview::*_t)(int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&topview::pc_name)) {
                *result = 0;
            }
        }
        {
            typedef void (topview::*_t)(int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&topview::launch_time)) {
                *result = 1;
            }
        }
        {
            typedef void (topview::*_t)(int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&topview::running_time)) {
                *result = 2;
            }
        }
        {
            typedef void (topview::*_t)(int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&topview::system_version)) {
                *result = 3;
            }
        }
        {
            typedef void (topview::*_t)(int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&topview::CPU_version)) {
                *result = 4;
            }
        }
        {
            typedef void (topview::*_t)(int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&topview::CPU_hz)) {
                *result = 5;
            }
        }
    }
}

const QMetaObject topview::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_topview.data,
      qt_meta_data_topview,  qt_static_metacall, 0, 0}
};


const QMetaObject *topview::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *topview::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_topview.stringdata))
        return static_cast<void*>(const_cast< topview*>(this));
    return QWidget::qt_metacast(_clname);
}

int topview::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void topview::pc_name(int _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void topview::launch_time(int _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void topview::running_time(int _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void topview::system_version(int _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void topview::CPU_version(int _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void topview::CPU_hz(int _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
