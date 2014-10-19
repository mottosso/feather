import QtQuick 2.3
import QtQuick.Controls 1.2

Menu {
    id: toolsMenu 
    title: "Tools"
    visible: true


    // ACTIONS


    // Undo 
    Action {
        id: centerAction
        text: "Center"
        tooltip: "Center the object at [0,0,0]"
        onTriggered: {}
    }


    // MENU


    // Center 
    MenuItem {
        action: centerAction
    }

    MenuSeparator {}

}
