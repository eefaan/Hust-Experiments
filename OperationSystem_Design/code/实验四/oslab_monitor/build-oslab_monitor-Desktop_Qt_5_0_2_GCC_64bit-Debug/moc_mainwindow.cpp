/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Desktop/oslab_monitor/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[21];
    char stringdata[231];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 8),
QT_MOC_LITERAL(2, 20, 0),
QT_MOC_LITERAL(3, 21, 3),
QT_MOC_LITERAL(4, 25, 3),
QT_MOC_LITERAL(5, 29, 4),
QT_MOC_LITERAL(6, 34, 6),
QT_MOC_LITERAL(7, 41, 12),
QT_MOC_LITERAL(8, 54, 12),
QT_MOC_LITERAL(9, 67, 7),
QT_MOC_LITERAL(10, 75, 15),
QT_MOC_LITERAL(11, 91, 20),
QT_MOC_LITERAL(12, 112, 23),
QT_MOC_LITERAL(13, 136, 16),
QT_MOC_LITERAL(14, 153, 12),
QT_MOC_LITERAL(15, 166, 13),
QT_MOC_LITERAL(16, 180, 10),
QT_MOC_LITERAL(17, 191, 4),
QT_MOC_LITERAL(18, 196, 9),
QT_MOC_LITERAL(19, 206, 12),
QT_MOC_LITERAL(20, 219, 10)
    },
    "MainWindow\0sys_info\0\0num\0Msg\0shut\0"
    "reboot\0send_signals\0set_sys_info\0"
    "row_num\0set_status_time\0set_status_cpu_usage\0"
    "set_status_memory_usage\0set_process_list\0"
    "process_shut\0process_creat\0search_pid\0"
    "text\0graph_cpu\0graph_memory\0graph_swap\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   89,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       5,    0,   94,    2, 0x0a,
       6,    0,   95,    2, 0x0a,
       7,    0,   96,    2, 0x0a,
       8,    2,   97,    2, 0x0a,
      10,    0,  102,    2, 0x0a,
      11,    0,  103,    2, 0x0a,
      12,    0,  104,    2, 0x0a,
      13,    0,  105,    2, 0x0a,
      14,    0,  106,    2, 0x0a,
      15,    0,  107,    2, 0x0a,
      16,    1,  108,    2, 0x0a,
      18,    0,  111,    2, 0x0a,
      19,    0,  112,    2, 0x0a,
      20,    0,  113,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    9,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->sys_info((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->shut(); break;
        case 2: _t->reboot(); break;
        case 3: _t->send_signals(); break;
        case 4: _t->set_sys_info((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 5: _t->set_status_time(); break;
        case 6: _t->set_status_cpu_usage(); break;
        case 7: _t->set_status_memory_usage(); break;
        case 8: _t->set_process_list(); break;
        case 9: _t->process_shut(); break;
        case 10: _t->process_creat(); break;
        case 11: _t->search_pid((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->graph_cpu(); break;
        case 13: _t->graph_memory(); break;
        case 14: _t->graph_swap(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::sys_info)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::sys_info(int _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
