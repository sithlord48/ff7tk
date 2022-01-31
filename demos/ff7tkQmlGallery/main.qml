import QtQuick 2.15
import QtQuick.Controls 2.15
import org.ff7tk 1.0 as FF7tk

ApplicationWindow {
    id: root
    width: 800
    height: 600
    title: "ff7tkQmlGallery-" + ff7tkVersion
    visible: true
    header: Item {
        id: headerItem
        Text{
            id: previewLabel
            text: "Current Preview:"
        }
        ComboBox {
            id: comboSelector
            model: ["", "Text Demo", "ItemPreview"]
            anchors.right: parent.right
            anchors.left: previewLabel.right
            anchors.leftMargin: 6
            onCurrentIndexChanged: {
                itemLoader.sourceComponent = Qt.binding(function() {
                    if(comboSelector.currentIndex === 1)
                        return textDemoComponent
                    else if(comboSelector.currentIndex === 2)
                        return itemPreviewComponent
                    else{
                        console.log("TEST")
                        return testComponent
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
        id: textDemoComponent
        TextDemo { }
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
