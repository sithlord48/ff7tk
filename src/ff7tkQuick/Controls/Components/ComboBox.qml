// SPDX-FileCopyrightText: 2022 - 2023 Chris Rizzitello <sithlord48@gmail.com>
// SPDX-License-Identifier: LGPL-3.0-or-later


import QtQuick
import QtQuick.Controls as QQC
import QtQuick.Templates as T

T.ComboBox {
    FontMetrics {id: fm; font.pixelSize: root.fontSize}
    id: root
    property bool scale: false
    property string placeHolderText: ""
    readonly property int fontSize: scale ? root.height *.6 : root.font.pixelSize
    readonly property bool validIcon: currentIndex === -1 ? false : model.get(currentIndex).icon !== undefined
    readonly property bool validText: currentIndex === -1 ? false : model.get(currentIndex).text !== undefined
    implicitHeight: scale ? 16 : fm.height * 1.5
    implicitWidth: contentItem.implicitWidth

    background: Rectangle {
        color: root.pressed ? palette.highlight : palette.button
        border.color: root.activeFocus ? palette.highlight : palette.dark
        border.width: 2
        radius: 2
        Rectangle {
            anchors.horizontalCenter: parent.horizontalCenter
            y: root.popup.y
            width: root.popup.width
            height: 2
            color: palette.button
            visible: root.popup.visible
        }
    }

    delegate: QQC.ItemDelegate {
        anchors.horizontalCenter: parent ? parent.horizontalCenter : undefined
        width: root.width - root.indicator.width - 10
        height: textDelegate.paintedHeight * 1.75
        highlighted: root.highlightedIndex === model.index
        background: Rectangle {
            color: highlighted ? palette.highlight : index % 2 === 0 ? palette.base : palette.alternateBase
        }
        contentItem: Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 6
            Image {
                anchors.verticalCenter: parent.verticalCenter
                anchors.margins: parent.height / 6
                source: model.icon === undefined ? "" : model.icon
                height: parent.height - 2
                width: model.icon === undefined ? 0 : height
                antialiasing: true
            }
            Text {
                id: textDelegate
                anchors.verticalCenter: parent.verticalCenter
                anchors.margins: 6
                text: model.text === undefined ? "" : model.text
                font.pixelSize: root.fontSize
                color: palette.text
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }
        }
    }
    contentItem: Item {
        anchors.margins: 2
        anchors.fill: parent
        Image {
            id: icon
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.margins: parent.height / 6

            source: validIcon ? root.model.get(root.currentIndex).icon : ""
            height: textLabel.font.pixelSize - 2
            width: validIcon ? height : 0
            antialiasing: true
        }
        Text {
            id: textLabel
            anchors.rightMargin: root.height / 2
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: icon.right
            anchors.right: parent.right
            anchors.margins: 6
            text: validText ? root.model.get(root.currentIndex).text : root.currentIndex === -1 ? root.placeHolderText : ""
            font.pixelSize: root.fontSize
            color: palette.text
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }
    }
    popup: T.Popup {
        y: root.height - 2
        x: contentItem.x - padding + (root.indicator.width / 2)
        implicitWidth: contentItem.implicitWidth
        implicitHeight: contentItem.implicitHeight + (padding * 2) + 2
        padding: 1

        contentItem: ListView {
            clip: true
            boundsBehavior: ListView.StopAtBounds
            anchors.top: parent.top; anchors.topMargin: 2
            anchors.bottom: parent.bottom; anchors.bottomMargin: 2
            implicitHeight: Math.min(scale ? Math.max(root.contentItem.height, 300) : 300, contentHeight + anchors.topMargin + anchors.bottomMargin + (spacing * count) + spacing )
            implicitWidth: root.width - root.indicator.width
            model: root.popup.visible ? root.delegateModel : null
            currentIndex: root.highlightedIndex
            keyNavigationEnabled: true
            QQC.ScrollIndicator.vertical: QQC.ScrollIndicator { visible: true }
        }
        background: Canvas {
            width: root.popup.width % 2 === 0 ? root.popup.width : root.popup.width + 1
            height: root.popup.height % 2 === 0 ? root.popup.height : root.popup.height + 1
            onPaint: {
                var ctx = getContext("2d")
                ctx.reset()
                ctx.fillStyle = palette.base
                ctx.fillRect(0,0, width, height)
                ctx.lineWidth = 4
                ctx.strokeStyle = palette.highlight
                if ( (root.popup.y + 1) === (root.height - 1)) {
                    ctx.moveTo(0,0)
                    ctx.lineTo(0, height)
                    ctx.lineTo(width, height)
                    ctx.lineTo(width, 0)
                } else if ( (root.popup.height + root.popup.y) == (root.y + 2) ) {
                    ctx.moveTo(0, height)
                    ctx.lineTo(0, 0)
                    ctx.lineTo(width, 0)
                    ctx.lineTo(width, height)
                } else {
                    ctx.moveTo(0, 0)
                    ctx.lineTo(width, 0)
                    ctx.lineTo(width, height)
                    ctx.lineTo(0, height)
                    ctx.lineTo(0,0)
                }
                ctx.stroke()
            }
        }

        enter: Transition {
            NumberAnimation { property: "height"; from: 0; to: popup.implicitHeight }
        }
        exit: Transition {
            NumberAnimation { property: "height"; from: popup.implicitHeight; to: 0 }
        }
    }
    indicator: Canvas {
        id: canvas
        anchors.right: root.right; anchors.rightMargin: root.height * 0.15
        anchors.verticalCenter: root.verticalCenter
        width: root.fontSize  % 2 === 0 ? root.fontSize : root.fontSize + 1
        height: (root.fontSize / 2 )  % 2 === 0 ? root.fontSize / 2 : (root.fontSize / 2) + 1

        Connections {
            target: popup
            function onVisibleChanged() { canvas.requestPaint() }
        }
        Connections {
            target: root
            function onWidthChanged() { canvas.requestPaint() }
            function onHeightChanged() { canvas.requestPaint() }
        }
        onPaint: {
            var ctx = getContext("2d")
            ctx.reset()
            ctx.moveTo(0, 0)
            ctx.lineTo(width, 0)
            ctx.lineTo(width / 2, height)
            ctx.closePath()
            ctx.fillStyle = root.popup.visible ? palette.highlight : palette.text
            ctx.fill()
        }
    }
    onModelChanged: adjustIWidth()
    onFontChanged: adjustIWidth()
    function adjustIWidth() {
        var widestItem = 0;
        for(var i = 0; i < model.count; i++) {
            var fmWidth = fm.advanceWidth(root.model.get(i).text)
            widestItem = Math.max(fmWidth, widestItem)
        }
        var iconPadding = root.model.count > 0 ? root.model.get(0).icon !== undefined ? fm.height + 6 : 0 : 0
        root.implicitWidth = widestItem + iconPadding + root.indicator.width + (root.popup.padding * 2) + 32
    }
}
