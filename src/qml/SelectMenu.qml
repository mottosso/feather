import QtQuick 2.3
import QtQuick.Controls 1.2

Menu {
    id: selectMenu 
    title: "Select"
    visible: true


    // ACTIONS


    // Deselect 
    Action {
        id: deselectAction
        text: "Deselect"
        tooltip: "Deselect all objects"
        onTriggered: {}
    }


    // MENU


    // Deselect 
    MenuItem {
        action: deselectAction
    }

    MenuSeparator {}

}
