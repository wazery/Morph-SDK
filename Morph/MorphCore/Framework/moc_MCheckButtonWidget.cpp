/****************************************************************************
** Meta object code from reading C++ file 'MCheckButtonWidget.h'
**
** Created: Fri Apr 27 22:09:37 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MCheckButtonWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MCheckButtonWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MCheckButtonWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x05,
      39,   30,   19,   19, 0x05,
      53,   19,   19,   19, 0x05,
      61,   19,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
      69,   19,   19,   19, 0x0a,
      84,   30,   19,   19, 0x0a,
     103,   19,   19,   19, 0x0a,
     116,   19,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MCheckButtonWidget[] = {
    "MCheckButtonWidget\0\0clicked()\0isActive\0"
    "toggled(bool)\0enter()\0leave()\0"
    "printClicked()\0printToggled(bool)\0"
    "printEnter()\0printLeave()\0"
};

void MCheckButtonWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MCheckButtonWidget *_t = static_cast<MCheckButtonWidget *>(_o);
        switch (_id) {
        case 0: _t->clicked(); break;
        case 1: _t->toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->enter(); break;
        case 3: _t->leave(); break;
        case 4: _t->printClicked(); break;
        case 5: _t->printToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->printEnter(); break;
        case 7: _t->printLeave(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MCheckButtonWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MCheckButtonWidget::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MCheckButtonWidget,
      qt_meta_data_MCheckButtonWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MCheckButtonWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MCheckButtonWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MCheckButtonWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MCheckButtonWidget))
        return static_cast<void*>(const_cast< MCheckButtonWidget*>(this));
    return QObject::qt_metacast(_clname);
}

int MCheckButtonWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void MCheckButtonWidget::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MCheckButtonWidget::toggled(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MCheckButtonWidget::enter()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void MCheckButtonWidget::leave()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
