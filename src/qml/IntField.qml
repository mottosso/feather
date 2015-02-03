import QtQuick 2.3
import feather.field 1.0

Rectangle {
    id: intField
    height: 18
    radius: 4
   
    property alias uId: field.uid // this is a unique of the node 
    property alias nodeKey: field.node // this if the node's number assigned by the plugin
    property alias fieldKey: field.field // this is the fields number assigned by the plugin
    property alias label: label.text 
    property int value: field.intVal

    Field { id: field }


    // LABEL

    Text {
        id: label
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: valueBox.left
        anchors.margins: 4
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 12
    }    
   
    // VALUE
 
    Rectangle {
        id: valueBox
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: 80
        border.color: "black"
        border.width: 1
        radius: 4

        Text {
            id: valueText
            text: value 
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.bold: false 
            font.pixelSize: 14
        }
    } 


    states: [
        // NORMAL
        State {
            name: "normal"
            PropertyChanges {
                target: intField 
                color: "lightgrey"
            }

            PropertyChanges {
                target: label 
                color: "black"
                font.bold: false
            }
 
            PropertyChanges {
                target: valueBox
                color: "lightblue"
            }

            PropertyChanges {
                target: valueText
                color: "black"
                font.bold: false
            }
        },

        // HOVER
        State {
            name: "hover"
            PropertyChanges {
                target: intField 
                color: "lightblue"
            }

            PropertyChanges {
                target: label 
                color: "black"
                font.bold: true 
            }

            PropertyChanges {
                target: valueBox
                color: "midnightblue"
            }

            PropertyChanges {
                target: valueText
                color: "white"
                 font.bold: true 
            }
        },

        // PRESSED  
        State {
            name: "pressed"
            PropertyChanges {
                target: intField 
                color: "green"
            }

            PropertyChanges {
                target: label 
                color: "black"
                font.bold: true 
            }

            PropertyChanges {
                target: valueBox
                color: "limegreen"
            }

            PropertyChanges {
                target: valueText
                color: "black"
                font.bold: true 
            }
        }

    ]


    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true 
        acceptedButtons: Qt.LeftButton | Qt.RightButton

        onPressed: {
            if(mouse.button == Qt.RightButton)
                console.log("rb clicked");
            intField.state="pressed"
            intField.update()
        }

        //onPositionChanged: { }
        onReleased: { intField.state="normal" }
        onEntered: { intField.state="hover" }
        onExited: { intField.state="normal" }
        onWheel: { field.intVal = field.intVal+1 }
    }

    Component.onCompleted: { intField.state="normal" }
}
