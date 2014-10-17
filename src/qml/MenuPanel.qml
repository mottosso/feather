import QtQuick 2.3
import QtQml.Models 2.1

Rectangle {
    id: panel
    width: 150
    height: 200
    color: "lightgrey"
    radius: 4
    border.color: "black"
    border.width: 1
    y: 24
    property ListModel model: null

    ListView {
        id: panel_view
        width: 133
        height: 200

        Component {
            id: panelDelegates
            Item {
                id: wrapper
                width: 150 
                height: 24
                Text {
                    id: label
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter 
                    color: (wrapper.ListView.isCurrentItem) ? "red" : "black"
                    text: model.name
                }
            }
        }
        delegate: panelDelegates 
        model: panel.model
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered: { console.log("enter panel"); panel.visible = true }
        onExited: { console.log("exit panel"); panel.visible = false }
    }

    Component.onCompleted: { panel.visible = false }
}
