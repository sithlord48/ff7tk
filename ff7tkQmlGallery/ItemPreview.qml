import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.4
import FF7Item 1.0

ColumnLayout {
    id: root

    Item {
        FF7Item {
            id:ff7Item
        }
        FontMetrics {
            id:fm
        }
    }
    ColumnLayout {
        RowLayout {
            Image {
                id: itemTypeIcon
                width: fm.height * 3; height: fm.height * 3
                fillMode: Image.PreserveAspectFit
            }
            Label {
                id: itemName
            }
        }
        Label {
            id: itemDesc
        }
        GroupBox {
            id: group_MSlots
            visible: false
            RowLayout {
                RowLayout {
                    id: mGroup1
                    Image{
                        id: lblMSlot1
                        source: "qrc" + ff7Item.materiaSlotResource()
                    }
                    Image{
                        id: lblLink1
                        source: "qrc" +ff7Item.materiaLinkResource()
                    }
                    Image{
                        id: lblMSlot2
                        source: "qrc" +ff7Item.materiaSlotResource()
                    }
                }
                RowLayout {
                    id: mGroup2
                    Image{
                        id: lblMSlot3
                        source: "qrc" +ff7Item.materiaSlotResource()
                    }
                    Image{
                        id: lblLink2
                        source: "qrc" +ff7Item.materiaLinkResource()
                    }
                    Image{
                        id: lblMSlot4
                        source: "qrc" +ff7Item.materiaSlotResource()
                    }
                }
                RowLayout {
                    id: mGroup3
                    Image{
                        id: lblMSlot5
                        source: "qrc" + ff7Item.materiaSlotResource()
                    }
                    Image{
                        id: lblLink3
                        source: "qrc" + ff7Item.materiaLinkResource()
                    }
                    Image{
                        id: lblMSlot6
                        source: "qrc" + ff7Item.materiaSlotResource()
                    }
                }
                RowLayout {
                    id: mGroup4
                    Image{
                        id: lblMSlot7
                        source: "qrc" + ff7Item.materiaSlotResource()
                    }
                    Image{
                        id: lblLink4
                        source: "qrc" + ff7Item.materiaLinkResource()
                    }
                    Image{
                        id: lblMSlot8
                        source: "qrc" + ff7Item.materiaSlotResource()
                    }
                }
            }
        }
        RowLayout {
            GroupBox {
                id:group_elemental
                title: "Elemental Effects"
                visible: false
                ColumnLayout {
                    ListView {
                        id: elementalList
                        delegate:Rectangle {
                            height: fm.height + 2
                            width: fm.averageCharacterWidth *17
                            color: palette.window
                            Text {
                                text: modelData
                                color: palette.text
                            }
                        }
                    }
                }
            }
            GroupBox {
                id:group_status
                title: "Status Effects"
                visible: false
                ColumnLayout {
                    ListView {
                        id: statusList
                        delegate:Rectangle {
                            height: fm.height + 2
                            width: fm.averageCharacterWidth * 17
                            Text {
                                text: modelData
                            }
                        }
                    }
                }
            }
        }
    }

    function setItem (itemID) {
        var type = ff7Item.type(itemID)
        //if(type == ff7Item.Unknown) { return }
        itemName.text = ff7Item.name(itemID)
        itemDesc.text = ff7Item.desc(itemID)
        itemTypeIcon.source = ff7Item.iconResource(itemID)

        if (type !== FF7Item.Item && type !== FF7Item.Accessory) {
            group_MSlots.visible = true
            group_MSlots.title = "APx" + Number(ff7Item.materiaGrowthRate(itemID)).toString()
            setSlots(itemID)
        } else {
            group_MSlots.visible = false
        }
        setElementalInfo(itemID)
        setStatusInfo(itemID)
    }

    function setSlots(itemID) {
        var MslotString = ""
        if (ff7Item.materiaGrowthRate(itemID) >0) {
            MslotString = ff7Item.materiaSlotResource()
        } else {
            MslotString = ff7Item.materiaSlotNoGrowthResource()
        }
        lblMSlot1.visible = false
        lblMSlot2.visible = false
        lblMSlot3.visible = false
        lblMSlot4.visible = false
        lblMSlot5.visible = false
        lblMSlot6.visible = false
        lblMSlot7.visible = false
        lblMSlot8.visible = false
        lblLink1.visible = false
        lblLink2.visible = false
        lblLink3.visible = false
        lblLink4.visible = false
        mGroup1.spacing = 14
        mGroup2.spacing = 14
        mGroup3.spacing = 14
        mGroup4.spacing = 14


        switch(ff7Item.materiaSlots(itemID)) {
            case 8:
                lblMSlot8.visible = true
            case 7:
                lblMSlot7.visible = true
            case 6:
                lblMSlot6.visible = true
            case 5:
                lblMSlot5.visible = true
            case 4:
                lblMSlot4.visible = true
            case 3:
                lblMSlot3.visible = true
            case 2:
                lblMSlot2.visible = true
            case 1:
                lblMSlot1.visible = true
        }
        switch(ff7Item.linkedSlots(itemID)) {
            case 4:
                lblLink4.visible = true
                mGroup4.spacing = 0
            case 3:
                lblLink3.visible = true
                mGroup3.spacing = 0
            case 2:
                lblLink2.visible = true
                mGroup2.spacing = 0
            case 1:
                lblLink1.visible = true
                mGroup1.spacing = 0
        }
    }

    function setElementalInfo(itemID) {
        elementalList.model = ff7Item.elementalEffects(itemID)
        console.log("Elemental Effects:" + ff7Item.elementalEffects(itemID))
        console.log("Elemental Box Items:" + elementalList.count.toString())

        if(elementalList.count == 0) {
            group_elemental.visible = false
            return;
        } else {
            elementalList.height = (elementalList.count * fm.height)
            group_elemental.height = elementalList.height
            group_elemental.visible = true
            console.log("Elemental Box Height:" + elementalList.height)
        }
    }

    function setStatusInfo(itemID) {
        statusList.model = ff7Item.statusEffects(itemID)
        console.log("Status Effects:" + ff7Item.statusEffects(itemID))
        console.log("Status Box Items:" + statusList.count.toString())
        if(statusList.count == 0) {
            group_status.visible = false
            return;
        } else {
            statusList.height = (statusList.count * fm.height)
            group_status.height = statusList.height
            group_status.visible = true
            console.log("Status Box Height:" + statusList.height)
        }
    }
}
