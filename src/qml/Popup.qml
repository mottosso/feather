import QtQuick 2.2

Item {
    id: popup
    width: 100
    height: 200

    Rectangle {
        anchors.fill: parent
        color: "darkgrey"
        border.color: "black"
        border.width: 1
    }

    ListView {
        id: view
        anchors.fill: popup
        //spacing: 2
        model: FileMenuModel{}         
        delegate: Column {
            MenuItem {
                title: name
                //height: 20
                width: popup.width
            }
        }
    }

}


