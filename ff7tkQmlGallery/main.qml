import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    ColumnLayout {
        anchors.fill: parent
        ComboBox {
            id: combo_Selector
            model: ["", "Text Demo", "ItemPreview"]
            style: ComboBoxStyle {
                textColor: SystemPalette.text
            }
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
                    maximumValue: 319
                    onValueChanged: itemDemo.setItem(value)
                    style: SpinBoxStyle {
                        textColor: SystemPalette.text
                    }
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
