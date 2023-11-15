//    SPDX-FileCopyrightText: 2017 - 2023 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

import QtQuick
import QtQuick.Controls as QQC
import ff7tkQuick.DataTypes
import ff7tkQuick.Controls

Item {
    id:root

    Column {
        anchors.fill: parent
        spacing: 3
        QQC.TextField{
            id:txtInput
            anchors.left: parent.left
            anchors.right: parent.right
            placeholderText: "Text to Convert"
        }
        Row {
            id: btnRow
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 6
            CheckBox {
                anchors.top: parent.top
                text: "Use Japanese Pc output"
                onCheckedChanged: FF7Text.japanese = checkState
            }
            Button {
                anchors.top:parent.top
                text:"Convert to PC"
                enabled: txtInput.text !== ""
                onClicked: txtOutput.text = FF7Text.toPC(txtInput.text)
            }
            Button {
                anchors.top: parent.top
                text: "Convert to FF7Text"
                enabled: txtInput.text !== ""
                onClicked: txtOutput.text = FF7Text.toFF7(txtInput.text)
            }
        }
        QQC.TextField{
            id:txtOutput
            anchors.left: parent.left
            anchors.right: parent.right
            placeholderText: "Converted Text Here"
        }
    }
}
