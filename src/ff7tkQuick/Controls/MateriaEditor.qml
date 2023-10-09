// SPDX-FileCopyrightText: 2022 - 2023 Chris Rizzitello <sithlord48@gmail.com>
// SPDX-License-Identifier: LGPL-3.0-or-later

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import ff7tkQuick.DataTypes
import "Components" as FFComps

Item {
    id: root
    implicitWidth: mSelector.implicitWidth + (24 * 4)
    property alias showPlaceHolderMateria: mSelector.showPlaceHolderMateria
    property bool editable: true
    property bool fixedHeightSkills: true
    property int starHeight: 24
    property alias currentId: mSelector.currentId
    property int currentAp: FF7Materia.maxMateriaAp
    readonly property bool isEmpty: ((currentId === FF7Materia.EmptyId))
    readonly property int level: FF7Materia.materiaLevel(currentId, currentAp)
    signal copyActionTriggered(int currentId, int currentAp)
    signal cutActionTriggered(int currentId, int currentAp)
    signal pasteActionTriggered()

    Rectangle {
        anchors.fill: parent
        color: palette.base
        RowLayout {
            id: selectorRow
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.leftMargin: 6
            anchors.rightMargin: 6
            spacing: 6
            MateriaSelector {
                property int lastId: 0xFF
                id: mSelector
                visible: root.editable
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.preferredWidth: mSelector.implicitWidth + 12
                onCurrentIdChanged: {
                    var preMax = lastId === FF7Materia.EmptyId ? FF7Materia.maxMateriaAp : FF7Materia.apToMax(lastId)
                    var currentMax = FF7Materia.apToMax(currentId)
                    if(preMax <= currentMax && (currentAp >= currentMax))
                        root.currentAp = preMax
                    if(preMax >= currentMax && (currentAp >= currentMax))
                        root.currentAp = FF7Materia.maxMateriaAp
                    lastId = currentId
                }
            }
            Image {
                visible: !root.editable && currentId !== FF7Materia.EmptyId
                Layout.margins: 4
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
            anchors.top: starGroup.width > (root.width * .45) ? starGroup.bottom : selectorRow.bottom
            anchors.topMargin: 12
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
                anchors.top: parent.top; anchors.bottom: parent.bottom
                anchors.left: txtAp.right; anchors.leftMargin: 6
                visible: root.editable
                editable: true
                wrap: true
                from: 0
                to: isEmpty ? FF7Materia.maxMateriaAp : FF7Materia.apToMax(currentId)
                value: currentAp
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
            anchors.top: starGroup.width < (root.width * .45) ? starGroup.bottom : apRow.bottom
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
}
