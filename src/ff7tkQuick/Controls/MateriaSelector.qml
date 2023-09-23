/****************************************************************************/
//    copyright 2022 - 2023 Chris Rizzitello <sithlord48@gmail.com>         //
//                                                                          //
//    This file is part of FF7tk                                            //
//                                                                          //
//    FF7tk is free software: you can redistribute it and/or modify         //
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License, or     //
//    (at your option) any later version.                                   //
//                                                                          //
//    FF7tk is distributed in the hope that it will be useful,              //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         //
//    GNU General Public License for more details.                          //
/****************************************************************************/

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
