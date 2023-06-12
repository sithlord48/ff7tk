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
import QtQuick.Controls as QQC
import QtQuick.Templates as T

T.ComboBox {
    FontMetrics {id: fm}
    id: root
    anchors.topMargin: 4
    background: Rectangle {
        implicitWidth: root.width
        implicitHeight: fm.height * 1.5
        anchors.fill: parent
        color: root.pressed ? palette.highlight : palette.button
        border.color: palette.highlight
        border.width: (root.activeFocus && !root.popup.visible) ? 2 : 0
        radius: 2
    }
    delegate: QQC.ItemDelegate {
        width: root.width
        highlighted: root.highlightedIndex === model.index
        background: Rectangle {
            anchors.fill: parent
            color: highlighted ? palette.highlight : index % 2 === 0 ? palette.base : palette.alternateBase
        }
        contentItem: Row {
            spacing: 6
            Image { source: model.icon; height: fm.height; width: height; antialiasing: true }
            Text { text: model.text; color: palette.text }
        }
    }
    contentItem: Item {
        width: root.width
        anchors.fill: parent

        Image {
            id: icon
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: parent.height / 6
            source: root.model.get(root.currentIndex).icon
            height: fm.height
            width: height
            antialiasing: true
        }
        Text {
            rightPadding: root.indicator.width + root.spacing
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: icon.right
            anchors.leftMargin: 6
            text: root.model.get(root.currentIndex).text
            font: root.font
            color: palette.text
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }
    }
    popup: T.Popup {
        y: root.height - 1
        width: root.width
        implicitHeight: contentItem.implicitHeight
        height: visible ? contentItem.implicitHeight : 0
        padding: 1

        contentItem: ListView {
            clip: true
            boundsBehavior: ListView.StopAtBounds
            implicitHeight: Math.min(300, contentHeight)
            model: root.popup.visible ? root.delegateModel : null
            currentIndex: root.highlightedIndex
            QQC.ScrollIndicator.vertical: QQC.ScrollIndicator { visible: true }
        }
        background: Rectangle {
            anchors.fill: parent
            color: palette.alternateBase
            border.color: palette.alternateBase
            radius: 2
        }
    }
    indicator: Canvas {
        id: canvas
        x: root.width - width - root.rightPadding - 6
        y: root.topPadding + (root.availableHeight - height) / 2
        width: 12
        height: 8
        contextType: "2d"

        Connections {
            target: root
            function onPressedChanged() { canvas.requestPaint(); }
        }

        onPaint: {
            context.reset();
            context.moveTo(0, 0);
            context.lineTo(width, 0);
            context.lineTo(width / 2, height);
            context.closePath();
            context.fillStyle = palette.text;
            context.fill();
        }
    }
}
