import QtQuick 2.1
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

ToolBar {
    height: 32

    // ACTIONS

    // Open 
    Action {
        id: openAction
        text: "Open"
        tooltip: "Open Feather Model"
        onTriggered: {}
    }

    // Save 
    Action {
        id: saveAction
        text: "Save"
        tooltip: "Save Feather Model"
        onTriggered: {}
    }
 
    // Undo 
    Action {
        id: undoAction
        text: "Undo"
        tooltip: "Undo last action"
        onTriggered: {}
    }
 
    // Redo 
    Action {
        id: redoAction
        text: "Redo"
        tooltip: "Redo last action"
        onTriggered: {}
    }
 
    // Vertex Select 
    Action {
        id: vertexSelectAction
        text: "Vertex Selection"
        tooltip: "Select Vertex"
        onTriggered: {}
    }

    // Edge Select 
    Action {
        id: edgeSelectAction
        text: "Edge Selection"
        tooltip: "Select Edge"
        onTriggered: {}
    }

    // Face Select 
    Action {
        id: faceSelectAction
        text: "Face Selection"
        tooltip: "Select Face"
        onTriggered: {}
    }

    // Object Select 
    Action {
        id: objectSelectAction
        text: "Object Selection"
        tooltip: "Select Object"
        onTriggered: {}
    }

    // Properties
    Action {
        id: propertyAction
        text: "Properties"
        tooltip: "Open Properties window"
        onTriggered: {}
    }

    // Smooth Shading 
    Action {
        id: smoothShadeAction
        text: "Smooth Shading"
        tooltip: "Display models in smooth shading mode"
        onTriggered: {}
    }

    // Orthographic 
    Action {
        id: orthographicAction
        text: "Orthographic"
        tooltip: "Go into orthographic mode"
        onTriggered: {}
    }

    // Grid 
    Action {
        id: gridAction
        text: "Grid"
        tooltip: "Show grid"
        onTriggered: {}
    }

    // Grid 
    Action {
        id: axisAction
        text: "Axis"
        tooltip: "Show axis"
        onTriggered: {}
    }


    // LAYOUT

    RowLayout {
        spacing: 6
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        ToolButton {
            width: 32; height: 32
            iconSource: "/usr/local/feather/icons/open.png"
            iconName: "open file"
            action: openAction
        } 

        ToolButton {
            width: 32; height: 32
            iconSource: "/usr/local/feather/icons/save.png"
            iconName: "save file"
            action: saveAction
        } 

        ToolButton {
            width: 32; height: 32
            iconSource: "/usr/local/feather/icons/undo.png"
            iconName: "undo action"
            action: undoAction
        }

        ToolButton {
            width: 32; height: 32
            iconSource: "/usr/local/feather/icons/redo.png"
            iconName: "redo action"
            action: redoAction
        }

    }

    RowLayout {
        spacing: 6
        anchors.centerIn: parent
        ToolButton {
            width: 32; height: 32
            iconSource: "/usr/local/feather/icons/point_select.png"
            iconName: "point select"
             action: vertexSelectAction
        } 

        ToolButton {
            width: 32; height: 32
            iconSource: "/usr/local/feather/icons/edge_select.png"
            iconName: "edge select"
            action: edgeSelectAction
        } 

        ToolButton {
            width: 32; height: 32
            iconSource: "/usr/local/feather/icons/face_select.png"
            iconName: "face select"
            action: faceSelectAction
        }

        ToolButton {
            width: 32; height: 32
            iconSource: "/usr/local/feather/icons/object_select.png"
            iconName: "object select"
            action: objectSelectAction
        }

    }

    RowLayout {
        spacing: 6
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right

        ToolButton {
            width: 32; height: 32
            iconSource: "/usr/local/feather/icons/props.png"
            iconName: "properties"
            action: propertyAction
        } 

        ToolButton {
            width: 32; height: 32
            iconSource: "/usr/local/feather/icons/smooth_shade.png"
            iconName: "smooth shading"
            action: smoothShadeAction
        } 

        ToolButton {
            width: 32; height: 32
            iconSource: "/usr/local/feather/icons/ortho.png"
            iconName: "orthographic view"
            action: orthographicAction
        } 

        ToolButton {
            width: 32; height: 32
            iconSource: "/usr/local/feather/icons/grid.png"
            iconName: "show grid"
            action: gridAction
        }

        ToolButton {
            width: 32; height: 32
            iconSource: "/usr/local/feather/icons/axis.png"
            iconName: "show axis"
            action: axisAction
        }

    }


}
