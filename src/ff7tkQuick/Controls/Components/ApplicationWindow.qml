// SPDX-FileCopyrightText: 2023 Chris Rizzitello <sithlord48@gmail.com>
// SPDX-License-Identifier: LGPL-3.0-or-later

import QtQuick
import QtQuick.Templates as T

T.ApplicationWindow {
    id: root
    visible: true
    property alias backgroundColor: bk.color
    background: Rectangle {
        id: bk
        color: palette.window
    }
}
