/****************************************************************************
** Meta object code from reading C++ file 'MyGraphicsView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../QtLightPrint/MyGraphicsView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MyGraphicsView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyGraphicsView_t {
    QByteArrayData data[9];
    char stringdata0[76];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyGraphicsView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyGraphicsView_t qt_meta_stringdata_MyGraphicsView = {
    {
QT_MOC_LITERAL(0, 0, 14), // "MyGraphicsView"
QT_MOC_LITERAL(1, 15, 12), // "mouseMovePos"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 1), // "p"
QT_MOC_LITERAL(4, 31, 12), // "ScaleChanged"
QT_MOC_LITERAL(5, 44, 7), // "addItem"
QT_MOC_LITERAL(6, 52, 3), // "row"
QT_MOC_LITERAL(7, 56, 14), // "QGraphicsItem*"
QT_MOC_LITERAL(8, 71, 4) // "item"

    },
    "MyGraphicsView\0mouseMovePos\0\0p\0"
    "ScaleChanged\0addItem\0row\0QGraphicsItem*\0"
    "item"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyGraphicsView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    1,   32,    2, 0x06 /* Public */,
       5,    2,   35,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QPoint,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7,    6,    8,

       0        // eod
};

void MyGraphicsView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MyGraphicsView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->mouseMovePos((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 1: _t->ScaleChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->addItem((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QGraphicsItem*(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGraphicsItem* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MyGraphicsView::*)(QPoint );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyGraphicsView::mouseMovePos)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MyGraphicsView::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyGraphicsView::ScaleChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MyGraphicsView::*)(int , QGraphicsItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyGraphicsView::addItem)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MyGraphicsView::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsView::staticMetaObject>(),
    qt_meta_stringdata_MyGraphicsView.data,
    qt_meta_data_MyGraphicsView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MyGraphicsView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyGraphicsView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyGraphicsView.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsView::qt_metacast(_clname);
}

int MyGraphicsView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void MyGraphicsView::mouseMovePos(QPoint _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MyGraphicsView::ScaleChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MyGraphicsView::addItem(int _t1, QGraphicsItem * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
