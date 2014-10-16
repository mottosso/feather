import QtQuick 2.1

Rectangle {
    id: menu
    height: 24
    color: "lightgrey"
    radius: 4
    border.color: "black"
    border.width: 1

    FileMenu { id: fileMenu }

    Row {
        spacing: 10

        MenuItem {
            //width: contentWidth + 10 
            //height: menu.height
            //horizontalAlignment: Text.AlignHCenter
            //verticalAlignment: Text.AlignVCenter 
            label: "File"
            //color: "black"
            menu: fileMenu
        }

        Text {
            width: contentWidth + 10 
            height: menu.height
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter 
            text: "Edit"
            color: "black"
        }


    }

}
