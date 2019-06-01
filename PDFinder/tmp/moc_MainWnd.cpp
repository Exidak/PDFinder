/****************************************************************************
** Meta object code from reading C++ file 'MainWnd.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MainWnd.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWnd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWnd_t {
    QByteArrayData data[14];
    char stringdata0[174];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWnd_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWnd_t qt_meta_stringdata_MainWnd = {
    {
QT_MOC_LITERAL(0, 0, 7), // "MainWnd"
QT_MOC_LITERAL(1, 8, 15), // "browseDirectory"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 11), // "startSearch"
QT_MOC_LITERAL(4, 37, 12), // "openDocument"
QT_MOC_LITERAL(5, 50, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(6, 67, 4), // "item"
QT_MOC_LITERAL(7, 72, 6), // "column"
QT_MOC_LITERAL(8, 79, 19), // "searchFilesFinished"
QT_MOC_LITERAL(9, 99, 18), // "searchTextFinished"
QT_MOC_LITERAL(10, 118, 10), // "saveResult"
QT_MOC_LITERAL(11, 129, 10), // "loadResult"
QT_MOC_LITERAL(12, 140, 14), // "hideResultLine"
QT_MOC_LITERAL(13, 155, 18) // "showLastHiddenLine"

    },
    "MainWnd\0browseDirectory\0\0startSearch\0"
    "openDocument\0QTreeWidgetItem*\0item\0"
    "column\0searchFilesFinished\0"
    "searchTextFinished\0saveResult\0loadResult\0"
    "hideResultLine\0showLastHiddenLine"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWnd[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    2,   61,    2, 0x08 /* Private */,
       8,    0,   66,    2, 0x08 /* Private */,
       9,    0,   67,    2, 0x08 /* Private */,
      10,    0,   68,    2, 0x08 /* Private */,
      11,    0,   69,    2, 0x08 /* Private */,
      12,    0,   70,    2, 0x08 /* Private */,
      13,    0,   71,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Int,    6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWnd::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWnd *_t = static_cast<MainWnd *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->browseDirectory(); break;
        case 1: _t->startSearch(); break;
        case 2: _t->openDocument((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->searchFilesFinished(); break;
        case 4: _t->searchTextFinished(); break;
        case 5: _t->saveResult(); break;
        case 6: _t->loadResult(); break;
        case 7: _t->hideResultLine(); break;
        case 8: _t->showLastHiddenLine(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWnd::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWnd.data,
      qt_meta_data_MainWnd,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWnd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWnd::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWnd.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWnd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
