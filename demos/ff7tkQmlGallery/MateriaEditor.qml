import QtQuick
import QtQuick.Layouts
import org.ff7tk as FF7tk

Item {
    id: root
    property int currentId: FF7tk.FF7Materia.EmptyId
    property int currentAp: FF7tk.FF7Materia.MaxMateriaAp
    property bool isEmpty: ((currentId === FF7tk.FF7Materia.EmptyId) && (currentAp === FF7tk.FF7Materia.MaxMateriaAp))
    FontMetrics {
        id: fm
    }
    ListModel {
        id: typeModel
        ListElement { text: qsTr("All Materia"); icon: "/materia/all" }
        ListElement { text: qsTr("Magic");       icon: "/materia/magic" }
        ListElement { text: qsTr("Summon");      icon: "/materia/summon" }
        ListElement { text: qsTr("Independent"); icon: "/materia/independent" }
        ListElement { text: qsTr("Support");     icon: "/materia/support" }
        ListElement { text: qsTr("Command");     icon: "/materia/command" }
    }
    ListModel {
        id: materiaModel
    }
    Component.onCompleted: {setupMateriaModel(0)}

    Rectangle {
        anchors.fill: parent
        color: palette.base
        RowLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.margins: 6
            ComboBox {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.preferredWidth: parent.width * .33
                model: typeModel
                onCurrentIndexChanged: {
                    console.log("Index Changed to " + currentIndex)
                    setupMateriaModel(currentIndex)
                }
            }
            ComboBox {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.preferredWidth: parent.width * 0.66
                model: materiaModel
                onCurrentIndexChanged: currentId = model.get(currentIndex).data
            }
        }
    }
    function setupMateriaModel(type) {
        materiaModel.clear()
        for (let i = 0 ; i < 90; i++) {
            if( (type === 0 || FF7tk.FF7Materia.type(i) === type) && FF7tk.FF7Materia.name(i) !== "") {
                materiaModel.append({ text: FF7tk.FF7Materia.name(i), icon: FF7tk.FF7Materia.iconResource(i), data: i})
            }
        }
    }
}
