//    SPDX-FileCopyrightText: 2017 - 2023 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

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
        color: palette.window
        height: comboSelector.height + 18
        Label {
            id: previewLabel
            text: "Current Preview:"
            anchors.verticalCenter: comboSelector.verticalCenter
        }
        ComboBox {
            id: comboSelector
            anchors {
                verticalCenter: parent.verticalCenter
                left: previewLabel.right; leftMargin: 6
                right: parent.right; rightMargin: 6
            }
            model: ListModel {
                ListElement{text: ""}
                ListElement{text: "Text Demo"}
                ListElement{text: "ItemPreview"}
                ListElement{text: "Materia Button"}
                ListElement{text: "Materia Editor"}
                ListElement{text: "Palette Preview"}
            }
            onCurrentIndexChanged: {
                itemLoader.sourceComponent = Qt.binding(function() {
                    switch(comboSelector.currentIndex) {
                        case 1: return textDemoComponent
                        case 2: return itemPreviewComponent
                        case 3: return materiaButtonComponent
                        case 4: return materiaEditorComponent
                        case 5: return paletteComponent;
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
                anchors.centerIn: parent
                text: "Please Select an Item to Preview"
            }
        }
    }

    Component {
        id: paletteComponent
        PaletteView {
            anchors.fill: parent
            anchors.topMargin: 6
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
                height: 55
                id: materiaEditorControls
                QQC.SpinBox {
                    id: spStarHeight
                    anchors.top: parent.top
                    anchors.left: parent.left
                    from: 0; to: 256
                    value: materiaEditor.starHeight
                    onValueChanged: materiaEditor.starHeight = value
                }
                CheckBox {
                    anchors.verticalCenter: spStarHeight.verticalCenter
                    anchors.left: spStarHeight.right
                    text: "Editable"
                    checked: materiaEditor.editable
                    onCheckedChanged: materiaEditor.editable = checked
                }
                CheckBox {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: spStarHeight.verticalCenter
                    text: "Show PlaceHolder Materia"
                    checked: materiaEditor.showPlaceHolderMateria
                    onCheckedChanged: materiaEditor.showPlaceHolderMateria = checked
                }
                CheckBox {
                    anchors.right: parent.right
                    anchors.verticalCenter: spStarHeight.verticalCenter
                    text: "ShortLayout"
                    checked: materiaEditor.fixedHeightSkills
                    onCheckedChanged: materiaEditor.fixedHeightSkills = checked
                }
                Label {
                    anchors.top:spStarHeight.bottom
                    anchors.left: parent.left
                    text: "Id: " + materiaEditor.currentId
                }
                Label {
                    anchors.top:spStarHeight.bottom
                    anchors.right: parent.right
                    text: "Ap: " + materiaEditor.currentAp
                }
            }
            MateriaEditor {
                id: materiaEditor
                anchors { fill: parent; topMargin: materiaEditorControls.height + 2; leftMargin: 6; rightMargin: 6 }
            }
        }
    }

    Component {
        id: itemPreviewComponent
        Item{
            Label {
                id: itemPreviewOptions
                anchors.left: parent.left
                anchors.verticalCenter: itemSelector.verticalCenter
                anchors.margins: 6
                text: "Item Id to Preview"
            }
            ItemSelector {
                id: itemSelector
                anchors.top: parent.top
                anchors.left: itemPreviewOptions.right
                anchors.rightMargin: 6
                currentId: FF7Item.EmptyItem
            }
            ItemPreview {
                anchors.top: itemSelector.bottom
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 6
                itemId: itemSelector.currentId
            }
        }
    }
}
