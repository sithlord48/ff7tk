// SPDX-FileCopyrightText: 2022 - 2023 Chris Rizzitello <sithlord48@gmail.com>
// SPDX-License-Identifier: LGPL-3.0-or-later

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import ff7tkQuick.DataTypes
import "Components" as FFComps

Item {
    id: root
    implicitWidth: typeCombo.implicitWidth + itemCombo.implicitWidth + 18
    implicitHeight: 24
    property bool showPlaceHolderitem: false
    property int currentId: FF7Item.EmptyItem
    ListModel {
        id: typeModel
        ListElement { text: qsTr("All items"); icon: "" }
        ListElement { text: qsTr("Item");       icon: "qrc:/items/item" }
        ListElement { text: qsTr("Armor");      icon: "qrc:/items/armor" }
        ListElement { text: qsTr("Accessory"); icon: "qrc:/items/accessory" }
        ListElement { text: qsTr("Cloud's Weapons");     icon: "qrc:/items/sword" }
        ListElement { text: qsTr("Barret's Weapons");     icon: "qrc:/items/gunarm" }
        ListElement { text: qsTr("Tifa's Weapons");     icon: "qrc:/items/glove" }
        ListElement { text: qsTr("Red's Weapons");     icon: "qrc:/items/clip" }
        ListElement { text: qsTr("Aerith's Weapons");     icon: "qrc:/items/staff" }
        ListElement { text: qsTr("Cid's Weapons");     icon: "qrc:/items/spear" }
        ListElement { text: qsTr("Yuffie's Weapons");     icon: "qrc:/items/star" }
        ListElement { text: qsTr("Cait's Weapons");     icon: "qrc:/items/mphone" }
        ListElement { text: qsTr("Vincent's Weapons");     icon: "qrc:/items/gun" }
    }

    ListModel { id: itemModel }
    Component.onCompleted: { setupItemModel(0); itemCombo.modelChanged() }
    RowLayout {
        id: selectorRow
        anchors.fill: parent
        height: 24
        spacing: 6
        FFComps.ComboBox {
            id: typeCombo
            Layout.fillHeight: true
            Layout.preferredWidth: typeCombo.implicitWidth
            model: typeModel
            onCurrentIndexChanged: setupItemModel(currentIndex)
        }
        FFComps.ComboBox {
            id: itemCombo
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumWidth: itemCombo.implicitWidth
            model: itemModel
            onCurrentIndexChanged: currentId = currentIndex !== -1 ? model.get(currentIndex).data : currentId
        }
    }

    onShowPlaceHolderitemChanged: {
        var cI = itemCombo.currentIndex
        typeCombo.currentIndex === 0 ? setupItemModel(typeCombo.currentIndex) : null
        itemCombo.currentIndex = cI
    }

    function setupItemModel(type) {
        itemModel.clear()
        for (let i = 0 ; i <= 320; i++) {
            if( (type === 0 || FF7Item.type(i) === type) && FF7Item.name(i) !== "")
                itemModel.append({ text: FF7Item.name(i), icon: FF7Item.iconResource(i), data: i})
        }
    }
}
