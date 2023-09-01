import QtQuick
import QtQuick.Templates as T

T.ToolTip {
    id: root
    implicitWidth: textLabel.paintedWidth + 6
    implicitHeight: textLabel.paintedHeight + 2
    y: -textLabel.paintedHeight - 6
    x: ((parent.width - width) / 2) -2
    text: ""
    visible: parent.hovered && text !== ""
    delay: 1000
    contentItem: Text {
        id: textLabel
        text: root.text
        font: root.font
        color: palette.text
    }

    background: Rectangle {
        width: parent.width
        height: parent.height
        anchors.centerIn: parent
        border.color: palette.dark
        border.width: 1
        color: palette.base
        opacity: 0.2
    }
    enter: Transition {
        NumberAnimation { property: "opacity"; from: 0.0; to: 1.0 }
    }
    exit: Transition {
            NumberAnimation { property: "opacity"; from: 1.0; to: 0.0 }
    }
}
