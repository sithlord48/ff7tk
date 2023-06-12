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
