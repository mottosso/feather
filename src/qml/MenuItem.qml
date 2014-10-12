import QtQuick 2.2

Item {
    width: 150 
    height: 24
    property alias label: label.text

    Rectangle {
        id: bg
        anchors.fill: parent
        anchors.margins: 2
        color: "grey"
        radius: 4
        visible: false
    }

    Text {
        id: label
        anchors.fill: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter 
        text: "****"
        //font.bold: true
        color: "black"
    }

    MouseArea {
        anchors.fill: parent
        //onHoverIn: { bg.visible = true } 
    }
}
