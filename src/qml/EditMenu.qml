import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.0 

Menu {
    id: editMenu 
    title: "Edit"
    visible: true


    // ACTIONS


    // Undo 
    Action {
        id: undoAction
        text: "Undo"
        tooltip: "Erase previous action"
        onTriggered: {}
    }


    // MENU


    // Undo 
    MenuItem {
        action: undoAction
    }

    MenuSeparator {}

}
