import QtQuick
import QtQuick.Templates as T

T.ApplicationWindow {
    id: root
    visible: true
    property alias backgroundColor: bk.color
    background: Rectangle {
        id: bk
        color: palette.alternateBase
    }
}
