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
    property int currentId: FF7Materia.EmptyId
    property int currentAp: FF7Materia.MaxMateriaAp
    property bool isEmpty: ((currentId === FF7Materia.EmptyId) && (currentAp === FF7Materia.MaxMateriaAp))
    ListModel {
        id: typeModel
        ListElement { text: qsTr("All Materia"); icon: "qrc:/materia/all" }
        ListElement { text: qsTr("Magic");       icon: "qrc:/materia/magic" }
        ListElement { text: qsTr("Summon");      icon: "qrc:/materia/summon" }
        ListElement { text: qsTr("Independent"); icon: "qrc:/materia/independent" }
        ListElement { text: qsTr("Support");     icon: "qrc:/materia/support" }
        ListElement { text: qsTr("Command");     icon: "qrc:/materia/command" }
    }
    ListModel {
        id: materiaModel
    }
    Component.onCompleted: {setupMateriaModel(0)}

    Rectangle {
        anchors.fill: parent
        color: palette.base
        RowLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            height: 24
            anchors.margins: 6
            FFComps.ComboBox {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.preferredWidth: parent.width * .33
                model: typeModel
                onCurrentIndexChanged: {
                    console.log("Index Changed to " + currentIndex)
                    setupMateriaModel(currentIndex)
                }
            }
            FFComps.ComboBox {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.preferredWidth: parent.width * 0.66
                model: materiaModel
                onCurrentIndexChanged: currentId = model.get(currentIndex).data
            }
        }
    }
    function setupMateriaModel(type) {
        materiaModel.clear()
        for (let i = 0 ; i < 90; i++) {
            if( (type === 0 || FF7Materia.type(i) === type) && FF7Materia.name(i) !== "") {
                materiaModel.append({ text: FF7Materia.name(i), icon: FF7Materia.iconResource(i), data: i})
            }
        }
    }
}
