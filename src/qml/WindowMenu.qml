import QtQuick 2.3
import QtQuick.Controls 1.2

Menu {
    id: windowMenu 
    title: "Window"
    visible: true


    // ACTIONS


    // Outliner 
    Action {
        id: outlinerAction
        text: "Outliner"
        tooltip: "Open Outliner window"
        onTriggered: {}
    }

    // Material 
    Action {
        id: materialAction
        text: "Material"
        tooltip: "Open Material window"
        onTriggered: {}
    }


    // MENU


    // Outliner 
    MenuItem {
        action: outlinerAction
    }

    // Material 
    MenuItem {
        action: materialAction
    }

    MenuSeparator {}

}
