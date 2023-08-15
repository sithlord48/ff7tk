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
    implicitWidth: childrenRect.width + 12
    property bool showPlaceHolderMateria: true
    property bool editable: true
    property bool fixedHeightSkills: true
    property int starHeight: 24
    property int currentId: FF7Materia.EmptyId
    property int currentAp: FF7Materia.maxMateriaAp
    readonly property bool isEmpty: ((currentId === FF7Materia.EmptyId))
    readonly property int level: FF7Materia.materiaLevel(currentId, currentAp)
    signal copyActionTriggered(int currentId, int currentAp)
    signal cutActionTriggered(int currentId, int currentAp)
    signal pasteActionTriggered()

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

    Rectangle {
        anchors.fill: parent
        color: palette.base
        RowLayout {
            id: selectorRow
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            height: 24
            anchors.margins: 6
            spacing: 6
            FFComps.ComboBox {
                id: typeCombo
                visible: root.editable
                Layout.fillHeight: true
                Layout.preferredWidth: implicitWidth
                model: typeModel
                onCurrentIndexChanged: setupMateriaModel(currentIndex)
            }
            FFComps.ComboBox {
                id: materiaCombo
                visible: root.editable
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.minimumWidth: implicitWidth
                model: materiaModel
                onCurrentIndexChanged: currentId = currentIndex !== -1 ? model.get(currentIndex).data : currentId
            }
            Image {
                visible: !root.editable && currentId !== FF7Materia.EmptyId
                Layout.fillHeight: true
                Layout.preferredWidth: height
                source: FF7Materia.iconResource(currentId)
                antialiasing: true
            }
            FFComps.Label {
                visible: !root.editable && currentId !== FF7Materia.EmptyId
                Layout.fillHeight: true
                text: FF7Materia.name(currentId)
                verticalAlignment: Qt.AlignVCenter
            }
            Button {
                Layout.fillHeight: true
                Layout.preferredWidth: height
                flat: true
                display: AbstractButton.IconOnly
                action: copyAction
            }
            Button {
                Layout.fillHeight: true
                Layout.preferredWidth: height
                flat: true
                visible: root.editable
                display: AbstractButton.IconOnly
                action: pasteAction
            }
            Button {
                Layout.fillHeight: true
                Layout.preferredWidth: height
                flat: true
                visible: root.editable
                display: AbstractButton.IconOnly
                action: deleteAction
            }
            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
        }
        Item {
            id: starGroup
            anchors.top: selectorRow.bottom; anchors.topMargin: 6
            anchors.left: parent.left; anchors.leftMargin: 6
            visible: FF7Materia.levels(currentId) > 1
            height: visible ? root.starHeight + 6 : 0
            width: (height * 5) + 40
            Image {
                anchors.left: parent.left
                anchors.leftMargin: 6
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: height
                visible: FF7Materia.levels(currentId) >= 1
                source: root.level >= 1 ? FF7Materia.fullStarResource(currentId) : FF7Materia.emptyStarResource(currentId)
                MouseArea {
                    anchors.fill: parent
                    onClicked: sbAP.value = 0
                    visible: root.editable
                }
            }
            Image {
                anchors.left: parent.left
                anchors.leftMargin: 2 * (6) + height
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: height
                visible: FF7Materia.levels(currentId) >= 2
                source: root.level >= 2 ? FF7Materia.fullStarResource(currentId) : FF7Materia.emptyStarResource(currentId)
                MouseArea {
                    anchors.fill: parent
                    onClicked: sbAP.value = FF7Materia.apForLevel(currentId, 1)
                    visible: root.editable
                }
            }
            Image {
                anchors.left: parent.left
                anchors.leftMargin: (3 * 6) + (2 * height)
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: height
                visible: FF7Materia.levels(currentId) >= 3
                source: root.level >= 3 ? FF7Materia.fullStarResource(currentId) : FF7Materia.emptyStarResource(currentId)
                MouseArea {
                    anchors.fill: parent
                    onClicked: sbAP.value = FF7Materia.apForLevel(currentId, 2)
                    visible: root.editable
                }
            }
            Image {
                anchors.left: parent.left
                anchors.leftMargin: (4 * 6) + (3 * height)
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: height
                visible: FF7Materia.levels(currentId) >= 4
                source: root.level >= 4 ? FF7Materia.fullStarResource(currentId) : FF7Materia.emptyStarResource(currentId)
                MouseArea {
                    anchors.fill: parent
                    onClicked: sbAP.value = FF7Materia.apForLevel(currentId, 3)
                    visible: root.editable
                }
            }
            Image {
                anchors.left: parent.left
                anchors.leftMargin: (5 * 6) + (4 * height)
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: height
                visible: FF7Materia.levels(currentId) >= 5
                source: root.level >= 5 ? FF7Materia.fullStarResource(currentId) : FF7Materia.emptyStarResource(currentId)
                MouseArea {
                    anchors.fill: parent
                    onClicked: sbAP.value = FF7Materia.apForLevel(currentId, 4)
                    visible: root.editable
                }
            }
        }

        Item {
            id: apRow
            anchors.topMargin: 12
            anchors.top: starGroup.width > (root.width * .45) ? starGroup.bottom : selectorRow.bottom
            anchors.left: starGroup.width > (root.width * .45) ? parent.left : starGroup.right
            anchors.right: parent.right
            visible: FF7Materia.levels(currentId) > 1
            height: visible ? 24 : 0
            Text {
                id: txtAp
                anchors.left: parent.left; anchors.leftMargin: 6
                anchors.verticalCenter: sbAP.verticalCenter
                property string t: root.editable ? "" : sbAP.value
                text: "Ap: " + t
                color: palette.text
            }
            SpinBox {
                id: sbAP
                property int displayValue: (currentAp > FF7Materia.apToMax(currentId)) ? FF7Materia.apToMax(currentId) : displayValue
                anchors.top: parent.top; anchors.bottom: parent.bottom
                anchors.left: txtAp.right; anchors.leftMargin: 6
                visible: root.editable
                editable: true
                wrap: true
                from: 0
                to: isEmpty ? FF7Materia.maxMateriaAp : FF7Materia.apToMax(currentId)
                value: displayValue
                onValueChanged: currentAp = (value >= FF7Materia.apToMax(currentId)) ? FF7Materia.maxMateriaAp : value
            }
            Text {
                anchors.left: sbAP.right; anchors.verticalCenter: sbAP.verticalCenter
                text: " / " + FF7Materia.apToMax(currentId)
                color: palette.text
            }
        }

        GroupBox {
            id: statChangesBox
            visible: FF7Materia.statString(currentId) !== "" && currentId !== FF7Materia.EmptyId
            height: visible ? implicitHeight : 0
            anchors.top: apRow.bottom
            anchors.margins: 8
            anchors.left: parent.left
            anchors.right: parent.right
            title: "Stat Changes"
            Text {
                anchors.fill: parent
                color: palette.text
                text: FF7Materia.statString(currentId)
            }
        }

        GroupBox {
            property string element: FF7Materia.element(currentId) !== "" ? "-" + FF7Materia.element(currentId) : ""
            id: skillBox
            anchors.top: statChangesBox.bottom
            anchors.topMargin: 8
            anchors.margins: 8
            anchors.left: parent.left
            anchors.right: addedEffectBox.left
            height: /*root.fixedHeightSkills || */currentId !== FF7Materia.EnemySkill ? ( (txtAp.paintedHeight + 2) * 5) + txtAp.paintedHeight + 24 + 8 : root.height - (y + 8)
            title: "Skills" + element
            visible: currentId !== FF7Materia.EmptyId
            ListView {
                id: skillView
                anchors.fill: parent
                anchors.margins: 3
                boundsBehavior: ListView.StopAtBounds
                spacing: 3
                ScrollBar.vertical: ScrollBar { active: true }
                model: currentId === FF7Materia.EnemySkill ? root.editable ? FF7Materia.skills(currentId) : FF7Materia.skillsForLevel(currentId, level) : FF7Materia.skillsForLevel(currentId, level)
                delegate: Row {
                    spacing: 3
                    width: parent ? parent.width : 0
                    height: txtLabel.paintedHeight
                    Image {
                        id: icon
                        visible: currentId === FF7Materia.EnemySkill && root.editable
                        source: (level & (1 << model.index)) ? FF7Materia.fullStarResource(currentId) : FF7Materia.emptyStarResource(currentId)
                        height: parent.height - (parent.height * .1)
                        width: height
                        MouseArea {
                            anchors.fill: parent
                            onClicked: (level & (1 << model.index)) ? currentAp -= Math.pow(2, model.index) : currentAp += Math.pow(2, model.index)
                        }
                    }
                    Text {
                        id: txtLabel
                        height: parent.height
                        text: modelData
                        color: palette.text
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }

        }

        GroupBox {
            id: addedEffectBox
            anchors.top: statChangesBox.bottom
            anchors.topMargin: 8
            anchors.margins: 8
            width: visible ? root.width * .4 : 0
            anchors.right: parent.right
            visible: FF7Materia.status(currentId)[0] !== ""
            height: root.fixedHeightSkills ? ( (txtAp.paintedHeight + 2) * 5) + txtAp.paintedHeight + 24 + 8 : root.height - (y + 8)
            title: qsTr("Added Effect")
            ListView {
                id: effectView
                anchors.fill: parent
                anchors.margins: 3
                boundsBehavior: ListView.StopAtBounds
                spacing: 3
                model: FF7Materia.status(currentId)
                delegate: Row {
                    spacing: 3
                    width: parent.width
                    height: txtSkillLabel.paintedHeight
                    Text {
                        id: txtSkillLabel
                        height: parent.height
                        text: modelData
                        color: palette.text
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }
        }

        Action {
            id: copyAction
            icon.height: parent.height
            icon.width: parent.height
            icon.name: "edit-copy"
            icon.source: ":/common/edit-copy"
            shortcut: StandardKey.Copy
            onTriggered: root.copyActionTriggered(currentId, currentAp)
        }

        Action {
            id: pasteAction
            icon.height: parent.height
            icon.width: parent.height
            icon.name: "edit-paste"
            icon.source: ":/common/edit-paste"
            shortcut: StandardKey.Paste
            onTriggered: root.pasteActionTriggered()
        }

        Action {
            id: deleteAction
            icon.height: parent.height
            icon.width: parent.height
            icon.name: "edit-clear"
            icon.source: ":/common/edit-clear"
            shortcut: StandardKey.Delete
            onTriggered: {
                currentId = FF7Materia.EmptyId
                currentAp = FF7Materia.maxMateriaAp
                typeCombo.currentIndex = 0
                materiaCombo.currentIndex = -1
            }
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
