import QtQuick 2.1
import QtQuick.Controls 1.0
import feather.scenegraph 1.0

Menu {

    SceneGraph { id: sg }

    MenuItem {
        text: "Cube"
        //shortcut: "Ctrl+C"
        onTriggered: { sg.make_cube() }            
    }

    MenuItem {
        text: "Torus"
        //shortcut: "Ctrl+C"
        onTriggered: {}            
    }

    MenuItem {
        text: "Cylinder"
        //shortcut: "Ctrl+C"
        onTriggered: {}            
    }

    MenuItem {
        text: "Sphere"
        //shortcut: "Ctrl+C"
        onTriggered: {}            
    }

    MenuItem {
        text: "Cone"
        //shortcut: "Ctrl+C"
        onTriggered: {}            
    }

    MenuSeparator {}

    MenuItem {
        text: "Grid"
        //shortcut: "Ctrl+C"
        onTriggered: {}            
    }

}
