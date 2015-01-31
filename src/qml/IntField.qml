import QtQuick 2.3

Rectangle {
    id: intField
    color: "lightblue"
    height: 20
    //border.color: "black"
    radius: 4
    //border.width: 1
    
    property int node: 0
    property int field: 0
    property alias label: label.text 

    Text {
        id: label
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: valueBox.left
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.bold: false 
        font.pixelSize: 14
        color: "black"
    }    
    
    Rectangle {
        id: valueBox
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: 80
        border.color: "black"
        border.width: 1
        color: "limegreen"
        radius: 4

        Text {
            id: valueText
            text: "4"
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.bold: false 
            font.pixelSize: 14
            color: "black"
        }
    } 
}
