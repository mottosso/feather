import QtQuick 2.1
import QtQuick.Controls 1.2

Rectangle {
    id: menu
    height: 24
    color: "lightgrey"
    radius: 4
    border.color: "black"
    border.width: 1

    FileMenu{ id: fileMenu }

    Component.onCompleted: { fileMenu.popup() }
}
