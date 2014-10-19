import QtQuick 2.3
import QtQuick.Controls 1.2

Menu {
    id: helpMenu 
    title: "Help"
    visible: true


    // ACTIONS


    // About 
    Action {
        id: aboutAction
        text: "About"
        tooltip: "About Feather"
        onTriggered: {}
    }


    // MENU


    // About 
    MenuItem {
        action: aboutAction
    }

    MenuSeparator {}

}
