import QtQuick 2.15
import QtQuick.Controls 2.15
import org.ff7tk 1.0 as FF7tk

Item {
    id:root

Column {
    anchors.fill: parent
    TextField{
        id:txtInput
        anchors.left: parent.left
        anchors.right: parent.right
        placeholderText: "Text to Convert"
    }
    Row {
        id: btnRow
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 6
        CheckBox {
            anchors.top: parent.top
            text: "Use Japanese Pc output"
            onCheckedChanged: FF7tk.FF7Text.japanese = checkState
        }
        Button {
            anchors.top:parent.top
            text:"Convert to PC"
            enabled: txtInput.text !== ""
            onClicked: txtOutput.text = FF7tk.FF7Text.toPC(txtInput.text)
        }
        Button {
            anchors.top: parent.top
            text: "Convert to FF7Text"
            enabled: txtInput.text !== ""
            onClicked: txtOutput.text = FF7tk.FF7Text.toFF7(txtInput.text)
        }
    }
    TextField{
        id:txtOutput
        anchors.left: parent.left
        anchors.right: parent.right
        placeholderText: "Converted Text Here"
    }
}
}
