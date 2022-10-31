import QtQuick
import QtQuick.Controls
import org.ff7tk 1.0 as FF7tk

ApplicationWindow {
    id: root
    width: 800
    height: 600
    title: "ff7tkQmlGallery-" + FF7tk.FF7Info.version
    visible: true
    header: Item {
        id: headerItem
        Text{
            id: previewLabel
            text: "Current Preview:"
        }
        ComboBox {
            id: comboSelector
            model: ["", "Text Demo", "ItemPreview", "MateriaButton", "MateriaEditor"]
            anchors.right: parent.right
            anchors.left: previewLabel.right
            anchors.leftMargin: 6
            onCurrentIndexChanged: {
                itemLoader.sourceComponent = Qt.binding(function() {
                    switch(comboSelector.currentIndex) {
                        case 1: return textDemoComponent;
                        case 2: return itemPreviewComponent;
                        case 3: return materiaButtonComponent;
                        case 4: return materiaEditorComponent;
                        default: return testComponent;
                    }
                })
            }
        }
    }
    Loader {
        id: itemLoader
        anchors.fill: parent
        anchors.topMargin: previewLabel.paintedHeight + 6
    }

    Component {
        id: testComponent
        Rectangle {
            color: "lightblue"
            Text {
                text: "Please Select an Item to Preview"
            }
        }
    }

    Component {
        id: materiaButtonComponent
        Item {
            anchors.fill: parent
            Label {
                id: lbl_materiaId
                anchors.top: parent.top
                anchors.left: parent.left
                palette: palette
                text: "Materia Type"
            }
            ComboBox {
                id: combo_materiaID
                anchors.top: parent.top
                anchors.left: lbl_materiaId.right
                anchors.leftMargin: 6
                model: ["None", "Magic", "Support", "Summon","Independent", "Command"]
                onCurrentIndexChanged: {
                    switch (currentIndex) {
                        case 0: materiaSlotButton.currentID = FF7tk.FF7Materia.EmptyId; break;
                        case 1: materiaSlotButton.currentID = FF7tk.FF7Materia.Fire; break;
                        case 2: materiaSlotButton.currentID = FF7tk.FF7Materia.All; break;
                        case 3: materiaSlotButton.currentID = FF7tk.FF7Materia.ChocoMog; break;
                        case 4: materiaSlotButton.currentID = FF7tk.FF7Materia.MpPlus; break;
                        case 5: materiaSlotButton.currentID = FF7tk.FF7Materia.Steal; break;
                    }
                }
            }
            CheckBox {
                id: cb_materiaSlotGrowth
                anchors.top: lbl_materiaId.bottom
                height: 30
                anchors.left: parent.left
                anchors.right: parent.right
                text: "Slot Growth"
            }
            MateriaSlotButton {
                id: materiaSlotButton
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: combo_materiaID.right
                anchors.right: parent.right
                anchors.margins: 10
                currentID: FF7tk.FF7Materia.EmptyId
                growthSlot: cb_materiaSlotGrowth.checked
            }
        }
    }

    Component {
        id: textDemoComponent
        TextDemo { }
    }

    Component {
        id: materiaEditorComponent
        MateriaEditor {}
    }

    Component {
        id: itemPreviewComponent
        Item{
            Text {
                id: itemPreviewOptions
                anchors.left: parent.left
                anchors.top:parent.top
                anchors.margins: 6
                text: "FF7ItemPreview - Options"
            }
            SpinBox {
                id:sb_itemNumber
                anchors.top: itemPreviewOptions.bottom
                anchors.left: parent.left
                anchors.margins: 6
                editable: true
                value: -1
                from: -1
                to: 319
            }
            ItemPreview {
                anchors.top: sb_itemNumber.bottom
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 6
                itemId: sb_itemNumber.value
            }
        }
    }
}
