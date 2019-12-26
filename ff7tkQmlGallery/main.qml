import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.4


ApplicationWindow {

    visible: true
    ColumnLayout {
        anchors.fill: parent
        ComboBox {
            id: combo_Selector
            model: ["", "Text Demo", "ItemPreview"]
            Layout.fillWidth: true
            onCurrentIndexChanged: indexChanged(combo_Selector.currentIndex)
        }

        GroupBox {
            id:group_TextDemo
            visible: false
            title: "FF7Text Demo"
            TextDemo {
                id:txtDemo
            }
        }
        GroupBox {
            id:group_ItemDemo
            visible: false
            title: "FF7ItemPreview"
            ColumnLayout {
                SpinBox {
                    id:sb_itemNumber
                    to: 319
                    onValueChanged: itemDemo.setItem(value)
                }
                ItemPreview {
                    id:itemDemo
                }
            }
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
    function indexChanged(newIndex) {
        group_ItemDemo.visible = false
        group_TextDemo.visible = false

        switch(newIndex) {
            case 1:
                group_TextDemo.visible = true
                break;
            case 2:
                group_ItemDemo.visible = true
                break;
        }

    }
}
