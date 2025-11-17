/****************************************************************************
** Meta object code from reading C++ file 'notepad_window.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../notepad_window.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'notepad_window.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_NotepadWindow_t {
    QByteArrayData data[10];
    char stringdata0[117];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NotepadWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NotepadWindow_t qt_meta_stringdata_NotepadWindow = {
    {
QT_MOC_LITERAL(0, 0, 13), // "NotepadWindow"
QT_MOC_LITERAL(1, 14, 21), // "on_findButton_clicked"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 7), // "add_tab"
QT_MOC_LITERAL(4, 45, 9), // "add_space"
QT_MOC_LITERAL(5, 55, 9), // "add_enter"
QT_MOC_LITERAL(6, 65, 14), // "add_ctrl_enter"
QT_MOC_LITERAL(7, 80, 10), // "add_simbol"
QT_MOC_LITERAL(8, 91, 15), // "add_mouse_press"
QT_MOC_LITERAL(9, 107, 9) // "save_file"

    },
    "NotepadWindow\0on_findButton_clicked\0"
    "\0add_tab\0add_space\0add_enter\0"
    "add_ctrl_enter\0add_simbol\0add_mouse_press\0"
    "save_file"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NotepadWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,

 // slots: parameters
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

void NotepadWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NotepadWindow *_t = static_cast<NotepadWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_findButton_clicked(); break;
        case 1: _t->add_tab(); break;
        case 2: _t->add_space(); break;
        case 3: _t->add_enter(); break;
        case 4: _t->add_ctrl_enter(); break;
        case 5: _t->add_simbol(); break;
        case 6: _t->add_mouse_press(); break;
        case 7: _t->save_file(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject NotepadWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_NotepadWindow.data,
      qt_meta_data_NotepadWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *NotepadWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NotepadWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_NotepadWindow.stringdata0))
        return static_cast<void*>(const_cast< NotepadWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int NotepadWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
