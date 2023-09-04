import QtQuick
import QtQuick.Templates as T

T.Label {
    id: root
    FontMetrics { id:fm; font: root.font }
    property bool drawBackground: false
    height: fm.height
    text: "Button"
    color: root.enabled ? palette.text : Qt.darker(palette.text)
    leftPadding: 3
    rightPadding: 3

    background: Rectangle {
        visible: root.drawBackground
        opacity: enabled ? 1 : 0.3
        color: palette.button
        radius: 2
    }
}

