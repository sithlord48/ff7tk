// SPDX-FileCopyrightText: 2022 - 2023 Chris Rizzitello <sithlord48@gmail.com>
// SPDX-License-Identifier: LGPL-3.0-or-later

import QtQuick
import QtQuick.Controls
import ff7tkQuick.DataTypes

Item {
    id: root
    property bool growthSlot: true
    property bool clickable: true
    property int currentID: FF7Materia.EmptyId
    signal clicked()
    implicitHeight: 32
    implicitWidth: 32
    Image{
        id: slot
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        sourceSize: Qt.size(width,height)
        source: growthSlot ? FF7Item.materiaSlotNoGrowthResource() : FF7Item.materiaSlotResource()
        Image {
            anchors {
                fill: parent
                verticalCenter: parent.verticalCenter
                horizontalCenter: parent.horizontalCenter
                topMargin:slot.paintedHeight /11; bottomMargin: slot.paintedHeight /11
                leftMargin: slot.paintedWidth /11; rightMargin: slot.paintedWidth /11
            }
            fillMode: Image.PreserveAspectFit
            source: FF7Materia.iconResource(currentID)
            MouseArea {
                anchors.fill: parent
                visible: root.clickable
                onClicked: root.clicked
            }
        }
    }
}
