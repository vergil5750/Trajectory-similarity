/****************************************************************************
** Meta object code from reading C++ file 'lcmwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "lcmwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lcmwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_lcmWidget_t {
    QByteArrayData data[11];
    char stringdata0[133];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lcmWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lcmWidget_t qt_meta_stringdata_lcmWidget = {
    {
QT_MOC_LITERAL(0, 0, 9), // "lcmWidget"
QT_MOC_LITERAL(1, 10, 8), // "openFile"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 1), // "i"
QT_MOC_LITERAL(4, 22, 15), // "calcLcmSequence"
QT_MOC_LITERAL(5, 38, 13), // "drawSequences"
QT_MOC_LITERAL(6, 52, 17), // "onLowerLimChanged"
QT_MOC_LITERAL(7, 70, 5), // "value"
QT_MOC_LITERAL(8, 76, 17), // "onUpperLimChanged"
QT_MOC_LITERAL(9, 94, 22), // "onRefreshButtonClicked"
QT_MOC_LITERAL(10, 117, 15) // "updateThreshold"

    },
    "lcmWidget\0openFile\0\0i\0calcLcmSequence\0"
    "drawSequences\0onLowerLimChanged\0value\0"
    "onUpperLimChanged\0onRefreshButtonClicked\0"
    "updateThreshold"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lcmWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x0a /* Public */,
       4,    0,   52,    2, 0x0a /* Public */,
       5,    0,   53,    2, 0x0a /* Public */,
       6,    1,   54,    2, 0x0a /* Public */,
       8,    1,   57,    2, 0x0a /* Public */,
       9,    0,   60,    2, 0x0a /* Public */,
      10,    0,   61,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void lcmWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        lcmWidget *_t = static_cast<lcmWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->openFile((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->calcLcmSequence(); break;
        case 2: _t->drawSequences(); break;
        case 3: _t->onLowerLimChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->onUpperLimChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->onRefreshButtonClicked(); break;
        case 6: _t->updateThreshold(); break;
        default: ;
        }
    }
}

const QMetaObject lcmWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_lcmWidget.data,
      qt_meta_data_lcmWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *lcmWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lcmWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_lcmWidget.stringdata0))
        return static_cast<void*>(const_cast< lcmWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int lcmWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
