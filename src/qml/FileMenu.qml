import QtQuick 2.2

Rectangle {
    id: menu
    width: 100
    height: 24*view.count
    FileMenuModel { id: fileModel }
    MenuItemDelegate { id: fileDelegate }

    ListView {
        id: view
        anchors.fill: parent
        anchors.margins: 2
        spacing: 2
        model: fileModel
        delegate: fileDelegate

   }

}
