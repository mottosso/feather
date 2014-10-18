import QtQuick 2.2
import QtQuick.Controls 1.2

ApplicationWindow {
    id: outliner
    title: "Outliner"
    visible: true
    flags: Qt.Tool
    width: 300
    height: 600
    
    Rectangle {
        id: tree
        anchors.fill: parent
        color: "white"
    }
    
}
