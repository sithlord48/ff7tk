import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    GroupBox {
        id:group_TextDemo
        title: "FF7Text Demo"
        TextDemo {
            id:txtDemo
        }
    }
}
