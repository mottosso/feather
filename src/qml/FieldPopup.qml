import QtQuick 2.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import feather.scenegraph 1.0
import feather.node 1.0

Menu {
    SceneGraph { id: sg }

    // ACTIONS

    // Make Plane 
    Action {
        id: lockFieldAction
        text: "Lock"
        tooltip: "Lock the field so it can't be edited"
        onTriggered: { }
    }


    // LAYOUT

    MenuItem {
        action: lockFieldAction 
    }

}
