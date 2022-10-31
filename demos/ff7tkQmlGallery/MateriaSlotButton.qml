import QtQuick
import QtQuick.Controls
import org.ff7tk 1.0 as FF7tk

Item {
    property bool growthSlot: true
    property bool clickable: true
    property int currentID: FF7tk.FF7Materia.EmptyId
    signal clicked()
    implicitHeight: 32
    implicitWidth: 32
    Image{
        id: slot
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        sourceSize: Qt.size(width,height)
        source: growthSlot ? FF7tk.FF7Item.materiaSlotNoGrowthResource() : FF7tk.FF7Item.materiaSlotResource()
        Image {
            anchors {
                fill: parent
                verticalCenter: parent.verticalCenter
                horizontalCenter: parent.horizontalCenter
                topMargin:slot.paintedHeight /11; bottomMargin: slot.paintedHeight /11
                leftMargin: slot.paintedWidth /11; rightMargin: slot.paintedWidth /11
            }
            fillMode: Image.PreserveAspectFit
            source: FF7tk.FF7Materia.iconResource(currentID)
            MouseArea {
                anchors.fill: parent
                visible: root.clickable
                onClicked: root.clicked
            }
        }
    }
}
