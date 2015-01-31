import QtQuick 2.3

Rectangle {
    id: intField
    color: "lightblue"
    height: 26
    border.color: "black"
    radius: 4
    border.width: 1
    
    property int node: 0
    property int field: 0
    property alias label: label.text 

    Text {
        id: label
        anchors.fill: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.bold: false 
        font.pixelSize: 14
        color: "black"
    }    
}
