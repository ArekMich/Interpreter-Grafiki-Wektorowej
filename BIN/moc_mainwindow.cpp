/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../GrafikaWektorowa/GrafikaWektorowa/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[22];
    char stringdata0[415];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 23), // "on_myPushButton_clicked"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 11), // "resizeEvent"
QT_MOC_LITERAL(4, 48, 13), // "QResizeEvent*"
QT_MOC_LITERAL(5, 62, 10), // "return_pen"
QT_MOC_LITERAL(6, 73, 18), // "QGraphicsRectItem*"
QT_MOC_LITERAL(7, 92, 4), // "rect"
QT_MOC_LITERAL(8, 97, 7), // "tmp_pen"
QT_MOC_LITERAL(9, 105, 22), // "on_clearButton_clicked"
QT_MOC_LITERAL(10, 128, 30), // "on_myClearScreenButton_clicked"
QT_MOC_LITERAL(11, 159, 29), // "on_mySaveToFileButton_clicked"
QT_MOC_LITERAL(12, 189, 27), // "on_myListWidget_itemClicked"
QT_MOC_LITERAL(13, 217, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(14, 234, 4), // "item"
QT_MOC_LITERAL(15, 239, 14), // "mouseMoveEvent"
QT_MOC_LITERAL(16, 254, 12), // "QMouseEvent*"
QT_MOC_LITERAL(17, 267, 30), // "on_actionClearButton_triggered"
QT_MOC_LITERAL(18, 298, 35), // "on_actionTakeScreenButton_tri..."
QT_MOC_LITERAL(19, 334, 28), // "on_actionFaqButton_triggered"
QT_MOC_LITERAL(20, 363, 18), // "ProvideContextMenu"
QT_MOC_LITERAL(21, 382, 32) // "on_actionExplainButton_triggered"

    },
    "MainWindow\0on_myPushButton_clicked\0\0"
    "resizeEvent\0QResizeEvent*\0return_pen\0"
    "QGraphicsRectItem*\0rect\0tmp_pen\0"
    "on_clearButton_clicked\0"
    "on_myClearScreenButton_clicked\0"
    "on_mySaveToFileButton_clicked\0"
    "on_myListWidget_itemClicked\0"
    "QListWidgetItem*\0item\0mouseMoveEvent\0"
    "QMouseEvent*\0on_actionClearButton_triggered\0"
    "on_actionTakeScreenButton_triggered\0"
    "on_actionFaqButton_triggered\0"
    "ProvideContextMenu\0on_actionExplainButton_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    1,   80,    2, 0x08 /* Private */,
       5,    2,   83,    2, 0x08 /* Private */,
       9,    0,   88,    2, 0x08 /* Private */,
      10,    0,   89,    2, 0x08 /* Private */,
      11,    0,   90,    2, 0x08 /* Private */,
      12,    1,   91,    2, 0x08 /* Private */,
      15,    1,   94,    2, 0x08 /* Private */,
      17,    0,   97,    2, 0x08 /* Private */,
      18,    0,   98,    2, 0x08 /* Private */,
      19,    0,   99,    2, 0x08 /* Private */,
      20,    1,  100,    2, 0x08 /* Private */,
      21,    0,  103,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 6, QMetaType::QPen,    7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 16,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_myPushButton_clicked(); break;
        case 1: _t->resizeEvent((*reinterpret_cast< QResizeEvent*(*)>(_a[1]))); break;
        case 2: _t->return_pen((*reinterpret_cast< QGraphicsRectItem*(*)>(_a[1])),(*reinterpret_cast< QPen(*)>(_a[2]))); break;
        case 3: _t->on_clearButton_clicked(); break;
        case 4: _t->on_myClearScreenButton_clicked(); break;
        case 5: _t->on_mySaveToFileButton_clicked(); break;
        case 6: _t->on_myListWidget_itemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 7: _t->mouseMoveEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 8: _t->on_actionClearButton_triggered(); break;
        case 9: _t->on_actionTakeScreenButton_triggered(); break;
        case 10: _t->on_actionFaqButton_triggered(); break;
        case 11: _t->ProvideContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 12: _t->on_actionExplainButton_triggered(); break;
        default: ;
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
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE