/****************************************************************************/
//    copyright 2017 - 2023 Chris Rizzitello <sithlord48@gmail.com>         //
//                                                                          //
//    This file is part of FF7tk                                            //
//                                                                          //
//    FF7tk is free software: you can redistribute it and/or modify         //
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License, or     //
//    (at your option) any later version.                                   //
//                                                                          //
//    FF7tk is distributed in the hope that it will be useful,              //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         //
//    GNU General Public License for more details.                          //
/****************************************************************************/

import QtQuick
import QtQuick.Controls
import ff7tkQuick.DataTypes
import ff7tkQuick.Controls as FF7tkControls


ApplicationWindow {
    id: root
    width: 800
    height: 600
    title: "ff7tkQmlGallery-" + FF7tkInfo.ff7tkVersion
    visible: true
    header: Item {
        id: headerItem
        Text{
            id: previewLabel
            text: "Current Preview:"
            color: palette.text
            anchors.verticalCenter: comboSelector.verticalCenter
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
        anchors.topMargin: comboSelector.height + 6
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
                model: [ "None", "Magic", "Support", "Summon","Independent", "Command"]
                onCurrentIndexChanged: {
                    switch (currentIndex) {
                        case 0: materiaSlotButton.currentID = FF7Materia.EmptyId; break;
                        case 1: materiaSlotButton.currentID = FF7Materia.Fire; break;
                        case 2: materiaSlotButton.currentID = FF7Materia.All; break;
                        case 3: materiaSlotButton.currentID = FF7Materia.ChocoMog; break;
                        case 4: materiaSlotButton.currentID = FF7Materia.MpPlus; break;
                        case 5: materiaSlotButton.currentID = FF7Materia.Steal; break;
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
            FF7tkControls.MateriaSlotButton {
                id: materiaSlotButton
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: combo_materiaID.right
                anchors.right: parent.right
                anchors.margins: 10
                currentID: FF7Materia.EmptyId
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
        Item {
            anchors.fill: parent
            Rectangle {
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                color: palette.alternateBase
                height: 50
                id: materiaEditorControls
                SpinBox {
                    id: spStarHeight
                    anchors.top: parent.top
                    anchors.left: parent.left
                    from: 0; to: 256
                    value: materiaEditor.starHeight
                    onValueChanged: materiaEditor.starHeight = value
                }
                Text {
                    anchors.top:parent.top
                    anchors.left: spStarHeight.right
                    text: "Id: " + materiaEditor.currentId
                }
                Text {
                    anchors.top:parent.top
                    anchors.right: parent.right
                    text: "Ap: " + materiaEditor.currentAp
                }
                CheckBox {
                    anchors.left: parent.left
                    anchors.top: spStarHeight.bottom
                    anchors.bottom: parent.bottom
                    text: "Editable"
                    checked: materiaEditor.editable
                    onCheckedChanged: materiaEditor.editable = checked
                }
                CheckBox {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: spStarHeight.bottom
                    anchors.bottom: parent.bottom
                    text: "Show PlaceHolder Materia"
                    checked: materiaEditor.showPlaceHolderMateria
                    onCheckedChanged: materiaEditor.showPlaceHolderMateria = checked
                }
                CheckBox {
                    anchors.right: parent.right
                    anchors.top: spStarHeight.bottom
                    anchors.bottom: parent.bottom
                    text: "ShortLayout"
                    checked: materiaEditor.fixedHeightSkills
                    onCheckedChanged: materiaEditor.fixedHeightSkills = checked
                }
            }
            FF7tkControls.MateriaEditor {
                id: materiaEditor
                anchors { fill: parent; topMargin: materiaEditorControls.height + 3 }
            }
        }
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
            FF7tkControls.ItemPreview {
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
