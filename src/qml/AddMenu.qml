import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.0 
import feather.scenegraph 1.0
import feather.nodes 1.0
import feather.command 1.0

Menu {

    id: addMenu
    title: "Add"
    visible: true

    SceneGraph {
        id: sg
    }

    // COMMANDS
    /*
    Command {
        id: importObj
        name: "import_obj"
        parameters: [
            Parameter { 
                name: "filename"
                type: Parameter.String
                stringValue: "test"
            },
            Parameter { 
                name: "selection"
                type: Parameter.Bool
                boolValue: true
            }
        ]
    }
    */

    // ACTIONS

    // Add Polygon Plane 
    Action {
        id: addPolygonPlaneAction
        text: "Plane"
        tooltip: "Add polygon plane to the scenegraph"
        onTriggered: {
            sg.add_node(Node.Object,325)
        }
    }

    // Add Polygon Cube
    Action {
        id: addPolygonCubeAction
        text: "Cube"
        tooltip: "Add polygon cube to the scenegraph"
        onTriggered: {}
    }


    // MENU

    // Polygon Menu
    Menu {
        id: polygonMenu
        title: "Polygon"

        // Plane 
        MenuItem {
            action: addPolygonPlaneAction
        }

        // Cube 
        MenuItem {
            action: addPolygonCubeAction
        }

    }

    // Light Menu
    Menu {
        id: lightMenu
        title: "Light"

        // 
        //MenuItem {
        //    action: 
        //}

    }

    // Camera Menu
    Menu {
        id: cameraMenu 
        title: "Camera"

        // 
        //MenuItem {
        //    action: 
        //}

    }

    MenuSeparator {}

    // Base Menu
    Menu {
        id: baseMenu 
        title: "Base"

        // 
        //MenuItem {
        //    action: 
        //}

    }

}
