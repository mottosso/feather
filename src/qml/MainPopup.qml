import QtQuick 2.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import feather.scenegraph 1.0

Menu {
    SceneGraph { id: sg }
    /*
    style: MenuStyle {
        frame: Rectangle { color: "red"; border.color: "black"; border.width: 1; radius: 10 }
        //itemDelegate.background: Rectangle { border.color: "black"; border.width: 1; radius: 10 }
    }
    */

    // ACTIONS

    // Make Plane 
    Action {
        id: makePlaneAction
        text: "Plane"
        tooltip: "Create Polygon Plane"
        onTriggered: { sg.add_node(Node.Object,Object.Plane,1) }
    }

    // Make Cube 
    Action {
        id: makeCubeAction
        text: "Cube"
        tooltip: "Create Polygon Cube"
        onTriggered: {}
    }

    // Make Torus 
    Action {
        id: makeTorusAction
        text: "Torus"
        tooltip: "Create Polygon Torus"
        onTriggered: {}
    }

    // Make Cylinder 
    Action {
        id: makeCylinderAction
        text: "Cylinder"
        tooltip: "Create Polygon Cylinder"
        onTriggered: {}
    }

    // Make Sphere 
    Action {
        id: makeSphereAction
        text: "Sphere"
        tooltip: "Create Polygon Sphere"
        onTriggered: {}
    }

    // Make Cone
    Action {
        id: makeConeAction
        text: "Cone"
        tooltip: "Create Polygon Cone"
        onTriggered: {}
    }

    // Make Grid
    Action {
        id: makeGridAction
        text: "Grid"
        tooltip: "Create Polygon Grid"
        onTriggered: {}
    }



    // LAYOUT

    MenuItem {
        action: makePlaneAction
    }

    MenuItem {
        action: makeCubeAction
    }

    MenuItem {
        action: makeTorusAction
    }

    MenuItem {
        action: makeCylinderAction
    }

    MenuItem {
        action: makeSphereAction
    }

    MenuItem {
        action: makeConeAction
    }

    MenuSeparator {}

    MenuItem {
        action: makeGridAction
    }

}
