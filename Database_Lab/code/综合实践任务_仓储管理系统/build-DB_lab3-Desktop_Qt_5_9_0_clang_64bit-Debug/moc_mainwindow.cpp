/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../DB_lab3/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[20];
    char stringdata0[266];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 12), // "dataReceived"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 18), // "on_loginin_clicked"
QT_MOC_LITERAL(4, 44, 11), // "func_switch"
QT_MOC_LITERAL(5, 56, 12), // "buyer_logout"
QT_MOC_LITERAL(6, 69, 11), // "buyer_flash"
QT_MOC_LITERAL(7, 81, 12), // "buyer_gflash"
QT_MOC_LITERAL(8, 94, 12), // "buyer_submit"
QT_MOC_LITERAL(9, 107, 7), // "request"
QT_MOC_LITERAL(10, 115, 13), // "seller_logout"
QT_MOC_LITERAL(11, 129, 12), // "seller_flash"
QT_MOC_LITERAL(12, 142, 13), // "seller_gflash"
QT_MOC_LITERAL(13, 156, 13), // "seller_submit"
QT_MOC_LITERAL(14, 170, 14), // "auditor_logout"
QT_MOC_LITERAL(15, 185, 15), // "auditor_poflash"
QT_MOC_LITERAL(16, 201, 16), // "auditor_posubmit"
QT_MOC_LITERAL(17, 218, 15), // "auditor_soflash"
QT_MOC_LITERAL(18, 234, 16), // "auditor_sosubmit"
QT_MOC_LITERAL(19, 251, 14) // "auditor_gflash"

    },
    "MainWindow\0dataReceived\0\0on_loginin_clicked\0"
    "func_switch\0buyer_logout\0buyer_flash\0"
    "buyer_gflash\0buyer_submit\0request\0"
    "seller_logout\0seller_flash\0seller_gflash\0"
    "seller_submit\0auditor_logout\0"
    "auditor_poflash\0auditor_posubmit\0"
    "auditor_soflash\0auditor_sosubmit\0"
    "auditor_gflash"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   99,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,  102,    2, 0x0a /* Public */,
       4,    1,  103,    2, 0x0a /* Public */,
       5,    0,  106,    2, 0x0a /* Public */,
       6,    0,  107,    2, 0x0a /* Public */,
       7,    0,  108,    2, 0x0a /* Public */,
       8,    1,  109,    2, 0x0a /* Public */,
      10,    0,  112,    2, 0x0a /* Public */,
      11,    0,  113,    2, 0x0a /* Public */,
      12,    0,  114,    2, 0x0a /* Public */,
      13,    1,  115,    2, 0x0a /* Public */,
      14,    0,  118,    2, 0x0a /* Public */,
      15,    0,  119,    2, 0x0a /* Public */,
      16,    1,  120,    2, 0x0a /* Public */,
      17,    0,  123,    2, 0x0a /* Public */,
      18,    1,  124,    2, 0x0a /* Public */,
      19,    0,  127,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dataReceived((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->on_loginin_clicked(); break;
        case 2: _t->func_switch((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 3: _t->buyer_logout(); break;
        case 4: _t->buyer_flash(); break;
        case 5: _t->buyer_gflash(); break;
        case 6: _t->buyer_submit((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->seller_logout(); break;
        case 8: _t->seller_flash(); break;
        case 9: _t->seller_gflash(); break;
        case 10: _t->seller_submit((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->auditor_logout(); break;
        case 12: _t->auditor_poflash(); break;
        case 13: _t->auditor_posubmit((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: _t->auditor_soflash(); break;
        case 15: _t->auditor_sosubmit((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 16: _t->auditor_gflash(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::dataReceived)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::dataReceived(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
