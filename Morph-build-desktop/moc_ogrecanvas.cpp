/****************************************************************************
** Meta object code from reading C++ file 'ogrecanvas.h'
**
** Created: Sun Jan 29 10:17:40 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Morph/ogrecanvas.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ogrecanvas.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_OgreCanvas[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   12,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      55,   53,   11,   11, 0x0a,
      82,   12,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_OgreCanvas[] = {
    "OgreCanvas\0\0pos\0cameraPositionChanged(Ogre::Vector3)\0"
    "c\0setBackgroundColor(QColor)\0"
    "setCameraPosition(Ogre::Vector3)\0"
};

const QMetaObject OgreCanvas::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_OgreCanvas,
      qt_meta_data_OgreCanvas, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &OgreCanvas::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *OgreCanvas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *OgreCanvas::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OgreCanvas))
        return static_cast<void*>(const_cast< OgreCanvas*>(this));
    return QWidget::qt_metacast(_clname);
}

int OgreCanvas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: cameraPositionChanged((*reinterpret_cast< const Ogre::Vector3(*)>(_a[1]))); break;
        case 1: setBackgroundColor((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 2: setCameraPosition((*reinterpret_cast< const Ogre::Vector3(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void OgreCanvas::cameraPositionChanged(const Ogre::Vector3 & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
