/****************************************************************************
** Meta object code from reading C++ file 'auditor_mw.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../DB_lab3/auditor_mw.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'auditor_mw.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_auditor_mw_t {
    QByteArrayData data[15];
    char stringdata0[224];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_auditor_mw_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_auditor_mw_t qt_meta_stringdata_auditor_mw = {
    {
QT_MOC_LITERAL(0, 0, 10), // "auditor_mw"
QT_MOC_LITERAL(1, 11, 13), // "logout_signal"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 14), // "poflash_signal"
QT_MOC_LITERAL(4, 41, 15), // "posubmit_signal"
QT_MOC_LITERAL(5, 57, 7), // "request"
QT_MOC_LITERAL(6, 65, 14), // "soflash_signal"
QT_MOC_LITERAL(7, 80, 15), // "sosubmit_signal"
QT_MOC_LITERAL(8, 96, 13), // "gflash_signal"
QT_MOC_LITERAL(9, 110, 17), // "on_logout_clicked"
QT_MOC_LITERAL(10, 128, 18), // "on_poflash_clicked"
QT_MOC_LITERAL(11, 147, 19), // "on_posubmit_clicked"
QT_MOC_LITERAL(12, 167, 18), // "on_soflash_clicked"
QT_MOC_LITERAL(13, 186, 19), // "on_sosubmit_clicked"
QT_MOC_LITERAL(14, 206, 17) // "on_gflash_clicked"

    },
    "auditor_mw\0logout_signal\0\0poflash_signal\0"
    "posubmit_signal\0request\0soflash_signal\0"
    "sosubmit_signal\0gflash_signal\0"
    "on_logout_clicked\0on_poflash_clicked\0"
    "on_posubmit_clicked\0on_soflash_clicked\0"
    "on_sosubmit_clicked\0on_gflash_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_auditor_mw[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    0,   75,    2, 0x06 /* Public */,
       4,    1,   76,    2, 0x06 /* Public */,
       6,    0,   79,    2, 0x06 /* Public */,
       7,    1,   80,    2, 0x06 /* Public */,
       8,    0,   83,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   84,    2, 0x0a /* Public */,
      10,    0,   85,    2, 0x0a /* Public */,
      11,    0,   86,    2, 0x0a /* Public */,
      12,    0,   87,    2, 0x0a /* Public */,
      13,    0,   88,    2, 0x0a /* Public */,
      14,    0,   89,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void auditor_mw::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auditor_mw *_t = static_cast<auditor_mw *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->logout_signal(); break;
        case 1: _t->poflash_signal(); break;
        case 2: _t->posubmit_signal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->soflash_signal(); break;
        case 4: _t->sosubmit_signal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->gflash_signal(); break;
        case 6: _t->on_logout_clicked(); break;
        case 7: _t->on_poflash_clicked(); break;
        case 8: _t->on_posubmit_clicked(); break;
        case 9: _t->on_soflash_clicked(); break;
        case 10: _t->on_sosubmit_clicked(); break;
        case 11: _t->on_gflash_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (auditor_mw::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&auditor_mw::logout_signal)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (auditor_mw::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&auditor_mw::poflash_signal)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (auditor_mw::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&auditor_mw::posubmit_signal)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (auditor_mw::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&auditor_mw::soflash_signal)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (auditor_mw::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&auditor_mw::sosubmit_signal)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (auditor_mw::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&auditor_mw::gflash_signal)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject auditor_mw::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_auditor_mw.data,
      qt_meta_data_auditor_mw,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *auditor_mw::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *auditor_mw::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_auditor_mw.stringdata0))
        return static_cast<void*>(const_cast< auditor_mw*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int auditor_mw::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void auditor_mw::logout_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void auditor_mw::poflash_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void auditor_mw::posubmit_signal(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void auditor_mw::soflash_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void auditor_mw::sosubmit_signal(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void auditor_mw::gflash_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
