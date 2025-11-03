/****************************************************************************
** Meta object code from reading C++ file 'contactuserlist.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../contactuserlist.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'contactuserlist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN15ContactUserListE_t {};
} // unnamed namespace

template <> constexpr inline auto ContactUserList::qt_create_metaobjectdata<qt_meta_tag_ZN15ContactUserListE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ContactUserList",
        "sig_loading_contact_user",
        "",
        "sig_switch_apply_friend_page",
        "sig_switch_friend_info_page",
        "std::shared_ptr<UserInfo>",
        "user_info",
        "slot_item_clicked",
        "QListWidgetItem*",
        "item",
        "slot_add_auth_firend",
        "std::shared_ptr<AuthInfo>",
        "slot_auth_rsp",
        "std::shared_ptr<AuthRsp>"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'sig_loading_contact_user'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sig_switch_apply_friend_page'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sig_switch_friend_info_page'
        QtMocHelpers::SignalData<void(std::shared_ptr<UserInfo>)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 5, 6 },
        }}),
        // Slot 'slot_item_clicked'
        QtMocHelpers::SlotData<void(QListWidgetItem *)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 8, 9 },
        }}),
        // Slot 'slot_add_auth_firend'
        QtMocHelpers::SlotData<void(std::shared_ptr<AuthInfo>)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 11, 2 },
        }}),
        // Slot 'slot_auth_rsp'
        QtMocHelpers::SlotData<void(std::shared_ptr<AuthRsp>)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 13, 2 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ContactUserList, qt_meta_tag_ZN15ContactUserListE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ContactUserList::staticMetaObject = { {
    QMetaObject::SuperData::link<QListWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15ContactUserListE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15ContactUserListE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN15ContactUserListE_t>.metaTypes,
    nullptr
} };

void ContactUserList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ContactUserList *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->sig_loading_contact_user(); break;
        case 1: _t->sig_switch_apply_friend_page(); break;
        case 2: _t->sig_switch_friend_info_page((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<UserInfo>>>(_a[1]))); break;
        case 3: _t->slot_item_clicked((*reinterpret_cast< std::add_pointer_t<QListWidgetItem*>>(_a[1]))); break;
        case 4: _t->slot_add_auth_firend((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<AuthInfo>>>(_a[1]))); break;
        case 5: _t->slot_auth_rsp((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<AuthRsp>>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ContactUserList::*)()>(_a, &ContactUserList::sig_loading_contact_user, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ContactUserList::*)()>(_a, &ContactUserList::sig_switch_apply_friend_page, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ContactUserList::*)(std::shared_ptr<UserInfo> )>(_a, &ContactUserList::sig_switch_friend_info_page, 2))
            return;
    }
}

const QMetaObject *ContactUserList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ContactUserList::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15ContactUserListE_t>.strings))
        return static_cast<void*>(this);
    return QListWidget::qt_metacast(_clname);
}

int ContactUserList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ContactUserList::sig_loading_contact_user()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ContactUserList::sig_switch_apply_friend_page()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ContactUserList::sig_switch_friend_info_page(std::shared_ptr<UserInfo> _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}
QT_WARNING_POP
