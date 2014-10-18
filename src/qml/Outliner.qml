import QtQuick 2.2
import QtQuick.Window 2.2

Window {
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
