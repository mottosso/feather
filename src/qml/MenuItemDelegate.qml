import QtQuick 2.2

Component {
 
    Rectangle {
        id: item
        width: parent.width
        height: 20 
        color: "grey"

        Text {
            id: menuItemName
            text: name
        } 

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true

            onClicked: console.log("clicked")
            onEntered: item.color = "lightgrey"
            onExited: item.color = "grey"
        }
   
    }
}

