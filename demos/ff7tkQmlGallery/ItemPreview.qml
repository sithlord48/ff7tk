import QtQuick
import QtQuick.Layouts
import org.ff7tk 1.0 as FF7tk

Item {
    id: root
    property int itemId: -1
    visible: itemId != -1

    Rectangle {
        anchors.fill: parent
        color: palette.base
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
            color: palette.text
        }
        Text {
            id: desc
            anchors.top: title.bottom
            anchors.left: itemIcon.right
            anchors.leftMargin: 6
            anchors.right: parent.right
            text: FF7tk.FF7Item.desc(itemId)
            font.pixelSize: fm.height * 0.7
            color: palette.text
        }
        Rectangle {
            id: materiaSlots
            property int leftMargin: materiaLink1.width
            property string imagePath: FF7tk.FF7Item.materiaGrowthRate(itemId) > 0  ? FF7tk.FF7Item.materiaSlotResource() : FF7tk.FF7Item.materiaSlotNoGrowthResource()
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: desc.bottom
            anchors.topMargin: 6
            border.width: 2
            border.color: palette.dark
            color: palette.alternateBase
            height: 64
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
                color: palette.text
            }
            RowLayout {
                spacing: 0
                anchors {
                    top: materiaBoxTitle.bottom
                    topMargin: parent.height / 16
                    bottom: parent.bottom
                    bottomMargin: parent.height / 16
                    left: parent.left
                    leftMargin:materiaSlots.border.width
                    right: parent.right
                    rightMargin:materiaSlots.border.width
                }

                Image{
                    id: materiaSlot1
                    Layout.fillHeight: true
                    Layout.leftMargin: width / 4
                    Layout.preferredHeight: 32
                    Layout.preferredWidth: 32
                    fillMode: Qt.KeepAspectRatio
                    sourceSize: Qt.size(width,height)
                    source: materiaSlots.imagePath
                    visible: FF7tk.FF7Item.materiaSlots(itemId) > 0
                }
                Image{
                    id: materiaLink1
                    Layout.fillHeight: true
                    Layout.maximumWidth: height / 4
                    fillMode: Qt.KeepAspectRatio
                    source: FF7tk.FF7Item.materiaLinkResource()
                    sourceSize: Qt.size(width,height)
                    visible: FF7tk.FF7Item.linkedSlots(itemId) > 0
                }
                Image{
                    id: materiaSlot2
                    Layout.fillHeight: true
                    Layout.leftMargin: materiaLink1.visible ? -1 : materiaSlots.leftMargin
                    Layout.preferredHeight: 32
                    Layout.preferredWidth: 32
                    fillMode: Qt.KeepAspectRatio
                    source: materiaSlots.imagePath
                    sourceSize: Qt.size(width,height)
                    visible: FF7tk.FF7Item.materiaSlots(itemId) > 1
                }
                Image{
                    id: materiaSlot3
                    Layout.fillHeight: true
                    Layout.leftMargin: width / 4
                    Layout.preferredHeight: 32
                    Layout.preferredWidth: 32
                    fillMode: Qt.KeepAspectRatio
                    sourceSize: Qt.size(width,height)
                    source: materiaSlots.imagePath
                    visible: FF7tk.FF7Item.materiaSlots(itemId) > 2
                }
                Image{
                    id: materiaLink2
                    Layout.fillHeight: true
                    Layout.maximumWidth: height / 4
                    fillMode: Qt.KeepAspectRatio
                    source: FF7tk.FF7Item.materiaLinkResource()
                    sourceSize: Qt.size(width,height)
                    visible: FF7tk.FF7Item.linkedSlots(itemId) > 1
                }
                Image{
                    id: materiaSlot4
                    Layout.fillHeight: true
                    Layout.leftMargin: materiaLink2.visible ? -1 : materiaSlots.leftMargin
                    Layout.preferredHeight: 32
                    Layout.preferredWidth: 32
                    fillMode: Qt.KeepAspectRatio
                    source: materiaSlots.imagePath
                    sourceSize: Qt.size(width,height)
                    visible: FF7tk.FF7Item.materiaSlots(itemId) > 3
                }
                Image{
                    id: materiaSlot5
                    Layout.fillHeight: true
                    Layout.leftMargin: width / 4
                    Layout.preferredHeight: 32
                    Layout.preferredWidth: 32
                    fillMode: Qt.KeepAspectRatio
                    source: materiaSlots.imagePath
                    sourceSize: Qt.size(width,height)
                    visible: FF7tk.FF7Item.materiaSlots(itemId) > 4
                }
                Image{
                    id: materiaLink3
                    Layout.fillHeight: true
                    Layout.maximumWidth: height / 4
                    fillMode: Qt.KeepAspectRatio
                    source: FF7tk.FF7Item.materiaLinkResource()
                    sourceSize: Qt.size(width,height)
                    visible: FF7tk.FF7Item.linkedSlots(itemId) > 3
                }
                Image{
                    id: materiaSlot6
                    Layout.fillHeight: true
                    Layout.leftMargin: materiaLink3.visible ? -1 : materiaSlots.leftMargin
                    Layout.preferredHeight: 32
                    Layout.preferredWidth: 32
                    fillMode: Qt.KeepAspectRatio
                    source: materiaSlots.imagePath
                    sourceSize: Qt.size(width,height)
                    visible: FF7tk.FF7Item.materiaSlots(itemId) > 5
                }
                Image{
                    id: materiaSlot7
                    Layout.fillHeight: true
                    Layout.leftMargin: width / 4
                    Layout.preferredHeight: 32
                    Layout.preferredWidth: 32
                    fillMode: Qt.KeepAspectRatio
                    source: materiaSlots.imagePath
                    sourceSize: Qt.size(width,height)
                    visible: FF7tk.FF7Item.materiaSlots(itemId) > 6
                }
                Image{
                    id: materiaLink4
                    Layout.fillHeight: true
                    Layout.maximumWidth: height / 4
                    fillMode: Qt.KeepAspectRatio
                    source: FF7tk.FF7Item.materiaLinkResource()
                    sourceSize: Qt.size(width,height)
                    visible: FF7tk.FF7Item.linkedSlots(itemId) > 3
                }
                Image{
                    id: materiaSlot8
                    Layout.fillHeight: true
                    Layout.leftMargin: materiaLink4.visible ? -1 : materiaSlots.leftMargin
                    Layout.preferredHeight: 32
                    Layout.preferredWidth: 32
                    fillMode: Qt.KeepAspectRatio
                    source: materiaSlots.imagePath
                    sourceSize: Qt.size(width,height)
                    visible: FF7tk.FF7Item.materiaSlots(itemId) > 7
                }
                Rectangle {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    color: materiaSlots.color
                }
            }
        }
        Item {
            //Missing Height Cap
            id: groupElemental
            anchors.top: materiaSlots.visible ? materiaSlots.bottom : desc.bottom
            anchors.topMargin: 6
            anchors.left: parent.left
            anchors.leftMargin: 6
            width: (parent.width / 2) - 12
            height: elementTitle.paintedHeight + 10 + (elementalList.count * (fm.height + 3))
            visible: elementalList.count > 0
            Rectangle {
                anchors.fill: parent
                border.width: 2
                clip: true
                color: palette.alternateBase
                Text{
                    id: elementTitle
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    text: "Elemental Effects"
                    font.underline: true
                    font.pixelSize: fm.height * 0.75
                    horizontalAlignment: Text.AlignHCenter
                    color: palette.text
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
                        color: palette.text
                    }
                }
            }
        }
        Item {
            id: groupStatus
            anchors.left: elementalList.count > 0 ? groupElemental.right : parent.left
            anchors.leftMargin: 6
            anchors.top: materiaSlots.visible ? materiaSlots.bottom : desc.bottom
            anchors.topMargin: 6
            width: groupElemental.visible ? (parent.width / 2) - 6 : (parent.width / 2) - 12
            height: statusTitle.paintedHeight + 10 + (statusList.count * (fm.height + 3))
            visible: statusList.count > 0
            Rectangle {
                anchors.fill: parent
                border.width: 2
                clip: true
                color: palette.alternateBase
                Text{
                    id: statusTitle
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    text: "Status Effects"
                    font.underline: true
                    font.pixelSize: fm.height * 0.75
                    horizontalAlignment: Text.AlignHCenter
                    color: palette.text
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
                        color: palette.text
                    }
                }
            }
        }
    }
}
