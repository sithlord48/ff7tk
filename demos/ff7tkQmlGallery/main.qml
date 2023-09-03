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
import QtQuick.Controls as QQC
import ff7tkQuick.DataTypes
import ff7tkQuick.Controls


ApplicationWindow {
    id: root
    width: 800
    height: 600
    title: "ff7tkQmlGallery - " + FF7tkInfo.ff7tkVersion
    header: Rectangle {
        id: headerItem
        color: palette.alternateBase
        border.color: palette.dark
        border.width: 2
        height: comboSelector.height + 12
        Label {
            id: previewLabel
            text: "Current Preview:"
            anchors.verticalCenter: comboSelector.verticalCenter
        }
        ComboBox {
            id: comboSelector
            anchors {
                margins: 6
                top: parent.top
                left: previewLabel.right; right: parent.right
            }
            model: ListModel {
                ListElement{text: ""}
                ListElement{text: "Text Demo"}
                ListElement{text: "ItemPreview"}
                ListElement{text: "Materia Button"}
                ListElement{text: "Materia Editor"}
            }
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
        anchors.topMargin: 6
    }

    Component {
        id: testComponent
        Rectangle {
            color: palette.base
            Label {
                anchors.centerIn:parent
                text: "Please Select an Item to Preview"
            }
        }
    }

    Component {
        id: materiaButtonComponent
        Item {
            anchors.fill: parent
            Item {
                anchors.fill: parent
                height: 50
                Label {
                    id: lbl_materiaId
                    anchors.verticalCenter: combo_materiaID.verticalCenter
                    anchors.left: parent.left
                    text: "Materia Type"
                }
                ComboBox {
                    id: combo_materiaID
                    anchors.top: parent.top
                    anchors.left: lbl_materiaId.right
                    anchors.leftMargin: 6
                    model: ListModel {
                        ListElement{text: "None"; value: 0xFF}
                        ListElement{text: "Magic"; value: FF7Materia.Fire}
                        ListElement{text: "Support"; value: FF7Materia.All}
                        ListElement{text: "Summon";value: FF7Materia.ChocoMog}
                        ListElement{text: "Independent"; value: FF7Materia.MpPlus}
                        ListElement{text: "Command"; value: FF7Materia.Steal}
                    }
                    onCurrentIndexChanged: materiaSlotButton.currentID = combo_materiaID.model.get(currentIndex).value
                }
                CheckBox {
                    id: cb_materiaSlotGrowth
                    anchors.top: combo_materiaID.bottom
                    anchors.left: parent.left
                    anchors.margins: 4
                    text: "Slot Growth"
                }
            }

            MateriaSlotButton {
                id: materiaSlotButton
                anchors.fill: parent
                anchors.topMargin: 60
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
                QQC.SpinBox {
                    id: spStarHeight
                    anchors.top: parent.top
                    anchors.left: parent.left
                    from: 0; to: 256
                    value: materiaEditor.starHeight
                    onValueChanged: materiaEditor.starHeight = value
                }
                Label {
                    anchors.top:parent.top
                    anchors.left: spStarHeight.right
                    text: "Id: " + materiaEditor.currentId
                }
                Label {
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
            MateriaEditor {
                id: materiaEditor
                anchors { fill: parent; topMargin: materiaEditorControls.height + 3 }
            }
        }
    }

    Component {
        id: itemPreviewComponent
        Item{
            Label {
                id: itemPreviewOptions
                anchors.left: parent.left
                anchors.verticalCenter: sb_itemNumber.verticalCenter
                anchors.margins: 6
                text: "Item Id to Preview"
            }
            QQC.SpinBox {
                id:sb_itemNumber
                anchors.top: parent.top
                anchors.left: itemPreviewOptions.right
                anchors.rightMargin: 6
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
