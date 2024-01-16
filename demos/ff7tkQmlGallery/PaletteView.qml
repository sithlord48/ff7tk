//    SPDX-FileCopyrightText: 2024 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

import QtQuick
import QtQuick.Controls
import ff7tkQuick.Controls

Item {
    id: root
    property color labelColor: "red"
    Rectangle {
        id: rect1
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 32
        color: palette.window
        Label {
            anchors.centerIn: parent
            text: "Your system Palette"
        }
        Label {
            id: comboLabel
            anchors.left: parent.left
            text: "Label Color"
        }
        ComboBox {
            id: colorCombo
            anchors.left: comboLabel.right
            anchors.leftMargin: 6
            model: ListModel {
                ListElement{text: "Red"}
                ListElement{text: "Blue"}
                ListElement{text: "Yellow"}
                ListElement{text: "Green"}
                ListElement{text: "White"}
                ListElement{text: "Black"}
            }
            onCurrentIndexChanged: {
                root.labelColor = Qt.binding(function() {
                    return String(currentText).toLowerCase()
                })
            }
        }
    }
    Rectangle {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: rect1.bottom
        Column {
            id: palCols
            property int rectW: 100
            anchors.fill: parent
            anchors.margins: 6
            spacing: 6
            Row {
                height: palCols.rectW
                spacing: 6
                Rectangle {
                    width: palCols.rectW; height: width
                    color: palette.accent
                    border.color: root.labelColor
                    border.width: 1
                    Text {
                        anchors.centerIn: parent
                        color: root.labelColor
                        text: "accent"
                    }
                }
                Rectangle {
                    width: palCols.rectW; height: width
                    color: palette.active
                    border.color: root.labelColor
                    border.width: 1
                    Text {
                        anchors.centerIn: parent
                        color: root.labelColor
                        text: "active"
                    }
                }
                Rectangle {
                    width: palCols.rectW; height: width
                    color: palette.alternateBase
                    border.color: root.labelColor
                    border.width: 1
                    Text {
                        anchors.centerIn: parent
                        color: root.labelColor
                        text: "alt. Base"
                    }
                }
                Rectangle {
                    width: palCols.rectW; height: width
                    color: palette.base
                    border.color: root.labelColor
                    border.width: 1
                    Text {
                        anchors.centerIn: parent
                        color: root.labelColor
                        text: "base"
                    }
                }
                Rectangle {
                    width: palCols.rectW; height: width
                    color: palette.button
                    border.color: root.labelColor
                    border.width: 1
                    Text {
                        anchors.centerIn: parent
                        color: root.labelColor
                        text: "button"
                    }
                }
                Rectangle {
                    width: palCols.rectW; height: width
                    color: palette.buttonText
                    border.color: root.labelColor
                    border.width: 1
                    Text {
                        anchors.centerIn: parent
                        color: root.labelColor
                        text: "buttonText"
                    }
                }
                Rectangle {
                    width: palCols.rectW; height: width
                    color: palette.dark
                    border.color: root.labelColor
                    border.width: 1
                    Text {
                        anchors.centerIn: parent
                        color: root.labelColor
                        text: "dark"
                    }
                }
            }
            Row {
                spacing: 6
                Rectangle {
                    width: palCols.rectW; height: width
                    color: palette.disabled
                    border.color: root.labelColor
                    border.width: 1
                    Text {
                        anchors.centerIn: parent
                        color: root.labelColor
                        text: "disabled"
                    }
                }
                Rectangle {
                    width: palCols.rectW; height: width
                    color: palette.highlight
                    border.color: root.labelColor
                    border.width: 1
                    Text {
                        anchors.centerIn: parent
                        color: root.labelColor
                        text: "highlight"
                    }
                }
                Rectangle {
                    width: palCols.rectW; height: width
                    color: palette.highlightedText
                    border.color: root.labelColor
                    border.width: 1
                    Text {
                        anchors.centerIn: parent
                        color: root.labelColor
                        text: "highlightText"
                    }
                }
                Rectangle {
                    width: palCols.rectW; height: width
                    color: palette.light
                    border.color: root.labelColor
                    border.width: 1
                    Text {
                        anchors.centerIn: parent
                        color: root.labelColor
                        text: "light"
                    }
                }
                Rectangle {
                    width: palCols.rectW; height: width
                    color: palette.link
                    border.color: root.labelColor
                    border.width: 1
                    Text {
                        anchors.centerIn: parent
                        color: root.labelColor
                        text: "link"
                    }
                }
                Rectangle {
                    width: palCols.rectW; height: width
                    color: palette.linkVisited
                    border.color: root.labelColor
                    border.width: 1
                    Text {
                        anchors.centerIn: parent
                        color: root.labelColor
                        text: "linkVisited"
                    }
                }
                Rectangle {
                    width: palCols.rectW; height: width
                    color: palette.mid
                    border.color: root.labelColor
                    border.width: 1
                    Text {
                        anchors.centerIn: parent
                        color: root.labelColor
                        text: "mid"
                    }
                }
            }
            Row {
                spacing: 6
                Rectangle {
                    width: palCols.rectW; height: width
                    color: palette.midlight
                    border.color: root.labelColor
                    border.width: 1
                    Text {
                        anchors.centerIn: parent
                        color: root.labelColor
                        text: "midLight"
                    }
                }
                Rectangle {
                    width: palCols.rectW; height: width
                    color: palette.placeholderText
                    border.color: root.labelColor
                    border.width: 1
                    Text {
                        anchors.centerIn: parent
                        color: root.labelColor
                        text: "placeholder text"
                    }
                }
                Rectangle {
                    width: palCols.rectW; height: width
                    color: palette.shadow
                    border.color: root.labelColor
                    border.width: 1
                    Text {
                        anchors.centerIn: parent
                        color: root.labelColor
                        text: "shadow"
                    }
                }
                Rectangle {
                    width: palCols.rectW; height: width
                    color: palette.text
                    border.color: root.labelColor
                    border.width: 1
                    Text {
                        anchors.centerIn: parent
                        color: root.labelColor
                        text: "text"
                    }
                }
                Rectangle {
                    width: palCols.rectW; height: width
                    color: palette.toolTipBase
                    border.color: root.labelColor
                    border.width: 1
                    Text {
                        anchors.centerIn: parent
                        color: root.labelColor
                        text: "tooltip base"
                    }
                }
                Rectangle {
                    width: palCols.rectW; height: width
                    color: palette.toolTipText
                    border.color: root.labelColor
                    border.width: 1
                    Text {
                        anchors.centerIn: parent
                        color: root.labelColor
                        text: "tooltipText"
                    }
                }
                Rectangle {
                    width: palCols.rectW; height: width
                    color: palette.window
                    border.color: root.labelColor
                    border.width: 1
                    Text {
                        anchors.centerIn: parent
                        color: root.labelColor
                        text: "window"
                    }
                }
            }
            Row {
                spacing: 6
                Rectangle {
                    width: palCols.rectW; height: width
                    color: palette.windowText
                    border.color: root.labelColor
                    border.width: 1
                    Text {
                        anchors.centerIn: parent
                        color: root.labelColor
                        text: "windowText"
                    }
                }
            }
        }
    }
}
