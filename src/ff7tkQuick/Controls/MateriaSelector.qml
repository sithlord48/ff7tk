// SPDX-FileCopyrightText: 2022 - 2023 Chris Rizzitello <sithlord48@gmail.com>
// SPDX-License-Identifier: LGPL-3.0-or-later

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import ff7tkQuick.DataTypes
import "Components" as FFComps

Item {
    id: root
    implicitWidth: typeCombo.implicitWidth + materiaCombo.implicitWidth + 18
    implicitHeight: 24
    property bool showPlaceHolderMateria: true
    property int currentId: FF7Materia.EmptyId

    ListModel {
        id: typeModel
        ListElement { text: qsTr("All Materia"); icon: "qrc:/materia/all" }
        ListElement { text: qsTr("Magic");       icon: "qrc:/materia/magic" }
        ListElement { text: qsTr("Summon");      icon: "qrc:/materia/summon" }
        ListElement { text: qsTr("Independent"); icon: "qrc:/materia/independent" }
        ListElement { text: qsTr("Support");     icon: "qrc:/materia/support" }
        ListElement { text: qsTr("Command");     icon: "qrc:/materia/command" }
    }

    ListModel { id: materiaModel }
    Component.onCompleted: { setupMateriaModel(0); materiaCombo.modelChanged() }
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
            onCurrentIndexChanged: setupMateriaModel(currentIndex)
        }
        FFComps.ComboBox {
            id: materiaCombo
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumWidth: materiaCombo.implicitWidth
            model: materiaModel
            onCurrentIndexChanged: currentId = currentIndex !== -1 ? model.get(currentIndex).data : currentId
        }
    }

    onShowPlaceHolderMateriaChanged: {
        var cI = materiaCombo.currentIndex
        typeCombo.currentIndex === 0 ? setupMateriaModel(typeCombo.currentIndex) : null
        materiaCombo.currentIndex = cI
    }

    function setupMateriaModel(type) {
        materiaModel.clear()
        for (let i = 0 ; i <= 90; i++) {
            if( (type === 0 || FF7Materia.type(i) === type) && FF7Materia.name(i) !== "") {
                if(String(FF7Materia.name(i)).includes(":")  && !root.showPlaceHolderMateria)
                    continue;
                materiaModel.append({ text: FF7Materia.name(i), icon: FF7Materia.iconResource(i), data: i})
            }
        }
    }
}
