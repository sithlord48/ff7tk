import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import FF7Text 1.0

ColumnLayout {
    id:root
    Item {
        FF7Text {
            id:ff7Text
        }
    }
    CheckBox {
        id:jpCHK
        text: "Japanese (toPc)"
        onCheckedStateChanged: ff7Text.japanese = jpCHK.checked
    }
    RowLayout {
        TextField{
            id:txtInput
            style: TextFieldStyle {
                textColor: palette.text
            }
        }
        Button {
            Text {
                text:"toPC"
                color: palette.text
            }
            onClicked: txtOutput.text = ff7Text.toPC(txtInput.text)
        }
        Button {
            Text {
                text:"toFF7"
                color: palette.text
            }
            onClicked: txtOutput.text = ff7Text.toFF7(txtInput.text)
        }
    Layout.fillWidth: true
    }
    TextField{
        id:txtOutput
        placeholderText: "Converted Text Here"
        style: TextFieldStyle {
            textColor: palette.text
        }
        Layout.fillWidth: true
    }
}

