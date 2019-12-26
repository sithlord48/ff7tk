import QtQuick 2.9
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.4
import org.ff7tk 1.0 as FF7tk

ColumnLayout {
    id:root
    CheckBox {
        id:jpCHK
        text: "Japanese (toPc)"
        onCheckedChanged: FF7tk.FF7Text.japanese = jpCHK.checked
    }
    RowLayout {
        TextField{
            id:txtInput
        }
        Button {
            Text {
                text:"toPC"
            }
            onClicked: txtOutput.text = FF7tk.FF7Text.toPC(txtInput.text)
        }
        Button {
            Text {
                text:"toFF7"
            }
            onClicked: txtOutput.text = FF7tk.FF7Text.toFF7(txtInput.text)
        }
    Layout.fillWidth: true
    }
    TextField{
        id:txtOutput
        placeholderText: "Converted Text Here"
        Layout.fillWidth: true
    }
}

