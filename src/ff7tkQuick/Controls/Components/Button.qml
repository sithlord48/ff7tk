// SPDX-FileCopyrightText: 2023 Chris Rizzitello <sithlord48@gmail.com>
// SPDX-License-Identifier: LGPL-3.0-or-later

import QtQuick
import QtQuick.Templates as T

T.Button {
    id: root
    implicitHeight: 24
    width: fm.advanceWidth(root.text) + 16
    text: "Button"
    FontMetrics {id:fm}
    contentItem: Text {
        id: textLabel
        anchors.fill: parent
        text: root.text
        font: root.font
        opacity: enabled ? 1.0 : 0.3
        color: root.down ? palette.highlight : palette.text
        leftPadding: 6
        rightPadding: 6
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        opacity: enabled ? 1 : 0.3
        border.color: root.activeFocus ? palette.highlight : root.down ? Qt.lighter(palette.dark) : palette.dark
        border.width: root.down ? 2 : 1
        color: palette.button
        radius: 2
    }
}
