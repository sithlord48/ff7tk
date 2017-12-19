import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 600
    height: 1000
    ColumnLayout {
        GroupBox {
            id:group_TextDemo
            title: "FF7Text Demo"
            TextDemo {
                id:txtDemo
            }
        }
        GroupBox {
            id:group_ItemDemo
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
                    Layout.fillHeight: true
                }
            }
        }
    }
}
