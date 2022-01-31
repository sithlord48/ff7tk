import QtQuick 2.15
import org.ff7tk 1.0 as FF7tk

Item {
    id: root
    property int itemId: -1
    visible: itemId != -1
    Rectangle {
        anchors.fill: parent
        color: Qt.rgba(0.5,0.5,0.5,0.25)
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
                border.color: "black"
                border.width: 2
                color: palette.base
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
                border.color: "black"
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

//            GroupBox {
//                id: group_MSlots
//                visible: false
//                RowLayout {
//                    RowLayout {
//                        id: mGroup1
//                        Image{
//                            id: lblMSlot1
//                            source: "qrc" + FF7tk.FF7Item.materiaSlotResource()
//                            visible: FF7tk.FF7Item.materiaSlots(item)
//                        }
//                        Image{
//                            id: lblLink1
//                            source: "qrc" + FF7tk.FF7Item.materiaLinkResource()
//                        }
//                        Image{
//                            id: lblMSlot2
//                            source: "qrc" + FF7tk.FF7Item.materiaSlotResource()
//                        }
//                    }
//                    Row {
//                        id: mGroup2
//                        Image{
//                            id: lblMSlot3
//                            source: "qrc" + FF7tk.FF7Item.materiaSlotResource()
//                        }
//                        Image{
//                            id: lblLink2
//                            source: "qrc" + FF7tk.FF7Item.materiaLinkResource()
//                        }
//                        Image{
//                            id: lblMSlot4
//                            source: "qrc" + FF7tk.FF7Item.materiaSlotResource()
//                        }
//                    }
//                    Row {
//                        id: mGroup3
//                        Image{
//                            id: lblMSlot5
//                            source: "qrc" + FF7tk.FF7Item.materiaSlotResource()
//                        }
//                        Image{
//                            id: lblLink3
//                            source: "qrc" + FF7tk.FF7Item.materiaLinkResource()
//                        }
//                        Image{
//                            id: lblMSlot6
//                            source: "qrc" + FF7tk.FF7Item.materiaSlotResource()
//                        }
//                    }
//                    Row {
//                        id: mGroup4
//                        Image{
//                            id: lblMSlot7
//                            source: "qrc" + FF7tk.FF7Item.materiaSlotResource()
//                        }
//                        Image{
//                            id: lblLink4
//                            source: "qrc" + FF7tk.FF7Item.materiaLinkResource()
//                        }
//                        Image{
//                            id: lblMSlot8
//                            source: "qrc" + FF7tk.FF7Item.materiaSlotResource()
//                        }
//                    }
//                }
//            }

//        function setItem (itemID) {
//            var type = FF7tk.FF7Item.type(itemID)
//            //if(type == FF7tk.FF7Item.Unknown) { return }
//            itemName.text = FF7tk.FF7Item.name(itemID)
//            itemDesc.text = FF7tk.FF7Item.desc(itemID)
//            itemTypeIcon.source = FF7tk.FF7Item.iconResource(itemID)

//            if (type !== FF7tk.FF7Item.Item && type !== FF7tk.FF7Item.Accessory) {
//                group_MSlots.visible = true
//                group_MSlots.title = "APx" + Number(FF7tk.FF7Item.materiaGrowthRate(itemID)).toString()
//                setSlots(itemID)
//            } else {
//                group_MSlots.visible = false
//            }
//            setElementalInfo(itemID)
//            setStatusInfo(itemID)
//        }

//        function setSlots(itemID) {
//            var MslotString = ""
//            if (FF7tk.FF7Item.materiaGrowthRate(itemID) >0) {
//                MslotString = FF7tk.FF7Item.materiaSlotResource()
//            } else {
//                MslotString = FF7tk.FF7Item.materiaSlotNoGrowthResource()
//            }
//            lblMSlot1.visible = false
//            lblMSlot2.visible = false
//            lblMSlot3.visible = false
//            lblMSlot4.visible = false
//            lblMSlot5.visible = false
//            lblMSlot6.visible = false
//            lblMSlot7.visible = false
//            lblMSlot8.visible = false
//            lblLink1.visible = false
//            lblLink2.visible = false
//            lblLink3.visible = false
//            lblLink4.visible = false
//            mGroup1.spacing = 14
//            mGroup2.spacing = 14
//            mGroup3.spacing = 14
//            mGroup4.spacing = 14


//            switch(FF7tk.FF7Item.materiaSlots(itemID)) {
//            case 8:
//                lblMSlot8.visible = true
//            case 7:
//                lblMSlot7.visible = true
//            case 6:
//                lblMSlot6.visible = true
//            case 5:
//                lblMSlot5.visible = true
//            case 4:
//                lblMSlot4.visible = true
//            case 3:
//                lblMSlot3.visible = true
//            case 2:
//                lblMSlot2.visible = true
//            case 1:
//                lblMSlot1.visible = true
//            }
//            switch(FF7tk.FF7Item.linkedSlots(itemID)) {
//            case 4:
//                lblLink4.visible = true
//                mGroup4.spacing = 0
//            case 3:
//                lblLink3.visible = true
//                mGroup3.spacing = 0
//            case 2:
//                lblLink2.visible = true
//                mGroup2.spacing = 0
//            case 1:
//                lblLink1.visible = true
//                mGroup1.spacing = 0
//            }
//        }
