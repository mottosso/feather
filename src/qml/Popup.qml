import QtQuick 2.2

Item {

    //id: fileMenu
    width: 100
    height: 200
    //color: "darkgrey"
    //border.color: "black"
    //border.width: 1
    //radius: 4
    //anchors.margins: 4

    ListView {
        anchors.fill: parent
        model: FileMenuModel{}
        delegate: Column {
            spacing: 4
            MenuItem { title: name; color: "blue"; width: 100; height: 20 }
        }
    }

}


