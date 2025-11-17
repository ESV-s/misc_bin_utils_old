/****************************************************************************
** Meta object code from reading C++ file 'key_press_eater.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../key_press_eater.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'key_press_eater.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_KeyPressNotepad_t {
    QByteArrayData data[8];
    char stringdata0[93];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KeyPressNotepad_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KeyPressNotepad_t qt_meta_stringdata_KeyPressNotepad = {
    {
QT_MOC_LITERAL(0, 0, 15), // "KeyPressNotepad"
QT_MOC_LITERAL(1, 16, 9), // "press_tab"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 11), // "press_space"
QT_MOC_LITERAL(4, 39, 11), // "press_enter"
QT_MOC_LITERAL(5, 51, 16), // "press_ctrl_enter"
QT_MOC_LITERAL(6, 68, 12), // "press_simbol"
QT_MOC_LITERAL(7, 81, 11) // "mouse_press"

    },
    "KeyPressNotepad\0press_tab\0\0press_space\0"
    "press_enter\0press_ctrl_enter\0press_simbol\0"
    "mouse_press"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KeyPressNotepad[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,
       4,    0,   46,    2, 0x06 /* Public */,
       5,    0,   47,    2, 0x06 /* Public */,
       6,    0,   48,    2, 0x06 /* Public */,
       7,    0,   49,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void KeyPressNotepad::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        KeyPressNotepad *_t = static_cast<KeyPressNotepad *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->press_tab(); break;
        case 1: _t->press_space(); break;
        case 2: _t->press_enter(); break;
        case 3: _t->press_ctrl_enter(); break;
        case 4: _t->press_simbol(); break;
        case 5: _t->mouse_press(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (KeyPressNotepad::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KeyPressNotepad::press_tab)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (KeyPressNotepad::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KeyPressNotepad::press_space)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (KeyPressNotepad::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KeyPressNotepad::press_enter)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (KeyPressNotepad::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KeyPressNotepad::press_ctrl_enter)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (KeyPressNotepad::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KeyPressNotepad::press_simbol)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (KeyPressNotepad::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KeyPressNotepad::mouse_press)) {
                *result = 5;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject KeyPressNotepad::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_KeyPressNotepad.data,
      qt_meta_data_KeyPressNotepad,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *KeyPressNotepad::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KeyPressNotepad::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_KeyPressNotepad.stringdata0))
        return static_cast<void*>(const_cast< KeyPressNotepad*>(this));
    return QObject::qt_metacast(_clname);
}

int KeyPressNotepad::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void KeyPressNotepad::press_tab()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void KeyPressNotepad::press_space()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void KeyPressNotepad::press_enter()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void KeyPressNotepad::press_ctrl_enter()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void KeyPressNotepad::press_simbol()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void KeyPressNotepad::mouse_press()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
