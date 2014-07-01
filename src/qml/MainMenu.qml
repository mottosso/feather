import QtQuick 2.2

Rectangle {
    height: 32
    anchors.top: parent.top
    anchors.left: parent.left
    anchors.right: parent.right
    MainMenuModel { id: mainModel }
    MenuItemDelegate { id: mainDelegate }
    color: "grey"
    border.color: "black"
    border.width: 1

    ListView {
        id: view
        anchors.fill: parent
        anchors.margins: 2
        orientation: Qt.Horizontal
        spacing: 2
        model: mainModel
        delegate: mainDelegate

   }


    //FileMenu {}

}
