import QtQuick 2.1
//import QtQuick.Window 2.1
//import QtQuick.Dialogs 1.0
import QtQuick.Controls 1.2
//import QtQuick.Controls.Styles 1.0
import QtQuick.Layouts 1.1

Rectangle {
    height: 36
    color: "lightgrey"
    radius: 4
    border.color: "black"
    border.width: 1

    RowLayout {
        spacing: 6
        anchors.centerIn: parent
        ToolButton {
            width: 32; height: 32
            iconSource: "/usr/local/feather/icons/point_select.png"
            iconName: "point select"
        } 

        ToolButton {
            width: 32; height: 32
            iconSource: "/usr/local/feather/icons/edge_select.png"
            iconName: "edge select"
        } 

        ToolButton {
            width: 32; height: 32
            iconSource: "/usr/local/feather/icons/face_select.png"
            iconName: "face select"
        }

        ToolButton {
            width: 32; height: 32
            iconSource: "/usr/local/feather/icons/object_select.png"
            iconName: "object select"
        }

        ToolButton {
            width: 32; height: 32 
            iconSource: "/usr/local/feather/icons/smooth_shade.png"
            iconName: "smooth shade"
        }

    }

}

/*
ToolBar {

    RowLayout {
        spacing: 6
        anchors.centerIn: parent
        ToolButton {
            width: 32; height: 32
            iconSource: "/usr/local/feather/icons/point_select.png"
            iconName: "point select"
        } 

        ToolButton {
            width: 32; height: 32
            iconSource: "/usr/local/feather/icons/edge_select.png"
            iconName: "edge select"
        } 

        ToolButton {
            width: 32; height: 32
            iconSource: "/usr/local/feather/icons/face_select.png"
            iconName: "face select"
        }

        ToolButton {
            width: 32; height: 32
            iconSource: "/usr/local/feather/icons/object_select.png"
            iconName: "object select"
        }

        ToolButton {
            width: 32; height: 32 
            iconSource: "/usr/local/feather/icons/smooth_shade.png"
            iconName: "smooth shade"
        }

    }

}
*/
