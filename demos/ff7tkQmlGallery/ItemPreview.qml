import QtQuick
import org.ff7tk 1.0 as FF7tk

Item {
    id: root
    property int itemId: -1
    visible: itemId != -1
    Rectangle {
        anchors.fill: parent
        FontMetrics {
            id: fm
        }
        Image {
            id: itemIcon
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.margins: 6
            width: fm.height * 2.0; height: width
            fillMode: Image.PreserveAspectFit
            source: FF7tk.FF7Item.iconResource(itemId)
            antialiasing: true
        }
        Text {
            id: title
            anchors.top: parent.top
            anchors.left: itemIcon.right
            anchors.right: parent.right
            text: FF7tk.FF7Item.name(itemId)
            font.bold: true
            font.pixelSize: fm.height * 0.8
        }
        Text {
            id: desc
            anchors.top: title.bottom
            anchors.left: itemIcon.right
            anchors.leftMargin: 6
            anchors.right: parent.right
            text: FF7tk.FF7Item.desc(itemId)
            font.pixelSize: fm.height * 0.7
        }
        Rectangle {
            id: materiaSlots
            property string imagePath: FF7tk.FF7Item.materiaGrowthRate(itemId) > 0  ? FF7tk.FF7Item.materiaSlotResource() : FF7tk.FF7Item.materiaSlotNoGrowthResource()
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: desc.bottom
            anchors.topMargin: 6
            border.width: 2
            border.color: palette.dark
            height: 100
            visible: (FF7tk.FF7Item.type(itemId) !== FF7tk.FF7Item.Item) && (FF7tk.FF7Item.type(itemId) !== FF7tk.FF7Item.Accessory) && (FF7tk.FF7Item.type(itemId) !== FF7tk.FF7Item.Unknown)
            Text{
                id: materiaBoxTitle
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                text: "APx" + FF7tk.FF7Item.materiaGrowthRate(itemId)
                font.underline: true
                font.pixelSize: fm.height * 0.75
                horizontalAlignment: Text.AlignHCenter
            }
            Image{
                id: materiaSlot1
                anchors.left: parent.left
                anchors.leftMargin: 32
                anchors.top: materiaBoxTitle.bottom
                width: 64; height: width
                source: parent.imagePath
                visible: FF7tk.FF7Item.materiaSlots(itemId) > 0
            }
            Image{
                id: materiaLink1
                anchors.left: materiaSlot1.right
                anchors.verticalCenter: materiaSlot1.verticalCenter
                width: 32; height: 48
                source: FF7tk.FF7Item.materiaLinkResource()
                visible: FF7tk.FF7Item.linkedSlots(itemId) > 0
            }
            Image{
                id: materiaSlot2
                anchors.top: materiaBoxTitle.bottom
                anchors.left: materiaLink1.right
                width: 64; height: width
                source: parent.imagePath
                visible: FF7tk.FF7Item.materiaSlots(itemId) > 1
            }
            Image{
                id: materiaSlot3
                anchors.left: materiaSlot2.right
                anchors.leftMargin: 32
                anchors.top: materiaBoxTitle.bottom
                width: 64; height: width
                source: parent.imagePath
                visible: FF7tk.FF7Item.materiaSlots(itemId) > 2
            }
            Image{
                id: materiaLink2
                anchors.left: materiaSlot3.right
                anchors.verticalCenter: materiaSlot3.verticalCenter
                width: 32; height: 48
                source: FF7tk.FF7Item.materiaLinkResource()
                visible: FF7tk.FF7Item.linkedSlots(itemId) > 1
            }
            Image{
                id: materiaSlot4
                anchors.top: materiaBoxTitle.bottom
                anchors.left: materiaLink2.right
                width: 64; height: width
                source: parent.imagePath
                visible: FF7tk.FF7Item.materiaSlots(itemId) > 3
            }
            Image{
                id: materiaSlot5
                anchors.left: materiaSlot4.right
                anchors.leftMargin: 32
                anchors.top: materiaBoxTitle.bottom
                width: 64; height: width
                source: parent.imagePath
                visible: FF7tk.FF7Item.materiaSlots(itemId) > 4
            }
            Image{
                id: materiaLink3
                anchors.left: materiaSlot5.right
                anchors.verticalCenter: materiaSlot5.verticalCenter
                width: 32; height: 48
                source: FF7tk.FF7Item.materiaLinkResource()
                visible: FF7tk.FF7Item.linkedSlots(itemId) > 3
            }
            Image{
                id: materiaSlot6
                anchors.top: materiaBoxTitle.bottom
                anchors.left: materiaLink3.right
                width: 64; height: width
                source: parent.imagePath
                visible: FF7tk.FF7Item.materiaSlots(itemId) > 5
            }
            Image{
                id: materiaSlot7
                anchors.left: materiaSlot6.right
                anchors.leftMargin: 32
                anchors.top: materiaBoxTitle.bottom
                width: 64; height: width
                source: parent.imagePath
                visible: FF7tk.FF7Item.materiaSlots(itemId) > 6
            }
            Image{
                id: materiaLink4
                anchors.left: materiaSlot7.right
                anchors.verticalCenter: materiaSlot7.verticalCenter
                width: 32; height: 48
                source: FF7tk.FF7Item.materiaLinkResource()
                visible: FF7tk.FF7Item.linkedSlots(itemId) > 3
            }
            Image{
                id: materiaSlot8
                anchors.top: materiaBoxTitle.bottom
                anchors.left: materiaLink4.right
                width: 64; height: width
                source: parent.imagePath
                visible: FF7tk.FF7Item.materiaSlots(itemId) > 7
            }
        }
        Item {
            //Missing Height Cap
            id: groupElemental
            anchors.top: materiaSlots.visible ? materiaSlots.bottom : desc.bottom
            anchors.topMargin: 6
            anchors.left: parent.left
            anchors.leftMargin: 12
            width: 250
            height: elementTitle.paintedHeight + 10 + (elementalList.count * (fm.height + 3))
            visible: elementalList.count > 0
            Rectangle {
                anchors.fill: parent
                border.width: 2
                Text{
                    id: elementTitle
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    text: "Elemental Effects"
                    font.underline: true
                    font.pixelSize: fm.height * 0.75
                    horizontalAlignment: Text.AlignHCenter
                }
                ListView {
                    id: elementalList
                    anchors.margins: 6
                    anchors.top: elementTitle.bottom
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    model: FF7tk.FF7Item.elementalEffects(itemId)
                    boundsBehavior: Flickable.StopAtBounds
                    spacing: 2
                    delegate: Text {
                        id: elementItem
                        text: modelData
                        anchors.left: parent.left
                        anchors.leftMargin: 6
                        anchors.right: parent.right
                        font.pixelSize: fm.height * 0.7
                    }
                }
            }
        }
        Item {
            id: groupStatus
            anchors.left: elementalList.count > 0 ? groupElemental.right : parent.left
            anchors.leftMargin: 12
            anchors.top: materiaSlots.visible ? materiaSlots.bottom : desc.bottom
            anchors.topMargin: 6
            width: 250
            height: statusTitle.paintedHeight + 10 + (statusList.count * (fm.height + 3))
            visible: statusList.count > 0
            Rectangle {
                anchors.fill: parent
                border.width: 2
                clip: true
                Text{
                    id: statusTitle
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    text: "Status Effects"
                    font.underline: true
                    font.pixelSize: fm.height * 0.75
                    horizontalAlignment: Text.AlignHCenter
                }
                ListView {
                    id: statusList
                    anchors.margins: 6
                    anchors.top: statusTitle.bottom
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    model: FF7tk.FF7Item.statusEffects(itemId)
                    spacing: 3
                    delegate: Text {
                        text: modelData
                        anchors.left: parent.left
                        anchors.right: parent.right
                        font.pixelSize: fm.height * 0.7
                    }
                }
            }
        }
    }
}
