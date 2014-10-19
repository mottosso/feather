import QtQuick 2.3
import QtQuick.Controls 1.2

Menu {
    id: viewMenu 
    title: "View"
    visible: true


    // ACTIONS


    // Wireframe 
    Action {
        id: wireframeAction
        text: "Wireframe"
        tooltip: "display the model's polygonal mesh only, no shading"
        onTriggered: {}
    }


    // MENU

 
    // Wireframe 
    MenuItem {
        action: wireframeAction
    }

    MenuSeparator {}

}
