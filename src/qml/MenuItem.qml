import QtQuick 2.3

Item {
    width: 150 
    height: 24
    property alias label: label.text
    signal triggered()
    property MenuPanel menu: null

    Rectangle {
        id: bg
        anchors.fill: parent
        anchors.margins: 4
        color: "grey"
        radius: 4
        visible: false
    }

    Text {
        id: label
        anchors.fill: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter 
        color: "black"
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered: { console.log("enter item"); bg.visible = true ; if(menu){ menu.visible=true } }
        onExited: { console.log("exit item"); bg.visible = false }
        onClicked: { triggered() } 
    }

    Component.onCompleted: { /*(menu==null) ?  width = label.contentWidth + 10 : width = menu.width*/ }
}
