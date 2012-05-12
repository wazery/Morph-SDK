/****************************************************************************
** Meta object code from reading C++ file 'MButtonWidget.h'
**
** Created: Fri Apr 27 22:09:35 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MButtonWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MButtonWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MButtonWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      25,   14,   14,   14, 0x05,
      35,   14,   14,   14, 0x05,
      46,   14,   14,   14, 0x05,
      54,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      62,   14,   14,   14, 0x0a,
      77,   14,   14,   14, 0x0a,
      90,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MButtonWidget[] = {
    "MButtonWidget\0\0clicked()\0pressed()\0"
    "released()\0enter()\0leave()\0printClicked()\0"
    "printEnter()\0printLeave()\0"
};

void MButtonWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MButtonWidget *_t = static_cast<MButtonWidget *>(_o);
        switch (_id) {
        case 0: _t->clicked(); break;
        case 1: _t->pressed(); break;
        case 2: _t->released(); break;
        case 3: _t->enter(); break;
        case 4: _t->leave(); break;
        case 5: _t->printClicked(); break;
        case 6: _t->printEnter(); break;
        case 7: _t->printLeave(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData MButtonWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MButtonWidget::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MButtonWidget,
      qt_meta_data_MButtonWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MButtonWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MButtonWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MButtonWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MButtonWidget))
        return static_cast<void*>(const_cast< MButtonWidget*>(this));
    return QObject::qt_metacast(_clname);
}

int MButtonWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void MButtonWidget::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MButtonWidget::pressed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void MButtonWidget::released()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void MButtonWidget::enter()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void MButtonWidget::leave()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}
QT_END_MOC_NAMESPACE
