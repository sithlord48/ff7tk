import QtQuick
import QtQuick.Templates as T

T.CheckBox {
    id: root
    text: "CheckBox"
    property string toolTipText: ""
    property bool drawBackground: true
    tristate: false //QQC is broken here ?
    implicitHeight: 24
    height: implicitHeight
    implicitWidth: text.paintedWidth + root.indicator.width + root.rightPadding + root.leftPadding + 12
    hoverEnabled: true
    ToolTip {
        text: root.toolTipText
    }

    background: Item {
        Rectangle {
            anchors.fill: parent
            border.color: palette.highlight
            border.width: 2
            color: "transparent"
            visible: root.activeFocus
        }
        Rectangle {
            anchors.fill: parent
            color: palette.alternateBase
            opacity: .2
            visible: root.drawBackground
        }
    }

    indicator: Canvas {
        id: canvas
        x: root.height * .15
        y: (parent.height - height) / 2
        anchors.verticalCenter: root.verticalCenter
        width: text.paintedHeight % 2 === 0 ? text.paintedHeight : text.paintedHeight + 1
        height: width

        Connections {
            target: root
            function onWidthChanged() { canvas.requestPaint() }
            function onHeightChanged() { canvas.requestPaint() }
            function onCheckStateChanged() { canvas.requestPaint() }
            function onDownChanged() {canvas.requestPaint() }
        }
        onPaint: {
            var ctx = getContext("2d")
            ctx.reset()
            ctx.moveTo(0, 0)
            ctx.fillStyle = palette.alternateBase
            ctx.roundedRect(0,0, width, height, root.height * 0.15, root.height * 0.15)
            ctx.fill()
            ctx.roundedRect(0, 0, width, height, root.height * 0.15, root.height * 0.15)
            ctx.lineWidth = 3
            ctx.strokeStyle = root.down ? palette.highlight : palette.text
            ctx.stroke();
            if (root.checkState === Qt.Checked) {
                ctx.moveTo(4, 4)
                ctx.lineTo(width - 4 , height - 4)
                ctx.moveTo(4, height - 4)
                ctx.lineTo(width - 4 , 4)
                ctx.stroke()
            } else if(root.checkState === Qt.PartiallyChecked) {
                ctx.moveTo(4, height / 2)
                ctx.lineTo(width - 4, height / 2)
                ctx.stroke()
            }
        }
    }

    contentItem: Text {
        id: text
        text: root.text
        opacity: enabled ? 1.0 : 0.3
        color: root.down || (!root.drawBackground && root.activeFocus) ? palette.highlight : palette.text
        verticalAlignment: Text.AlignVCenter
        leftPadding: paintedHeight + (root.height * .3)
    }
}
