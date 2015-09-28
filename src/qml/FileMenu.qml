/***********************************************************************
 *
 * Filename: FileMenu.qml 
 *
 * Description: File specific menu items. 
 *
 * Copyright (C) 2015 Richard Layman, rlayman2000@yahoo.com 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ***********************************************************************/

import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.0 
import feather.command 1.0
import feather.scenegraph 1.0
import feather.tools 1.0


Menu {
    id: fileMenu 
    title: "File"
    visible: true

    property SceneGraph scenegraph: Null
    property Properties properties: Null

    style: MenuStyle { properties: fileMenu.properties }


    Tools { id: tools }
    FileDialog {
        id: importDialog
        title: "Import Obj"
        onAccepted: {
            importObjFilename.stringValue = tools.urlToString(importDialog.fileUrl)
            importObj.exec()       
            scenegraph.triggerUpdate()
            scenegraph.nodesAdded()
        }
        onRejected: {} 
    }

    PropertiesDialog {
        id: propDialog
        visible: false
        properties: fileMenu.properties
    }

    // COMMANDS
    Command {
        id: importObj
        name: "import_obj"
        parameters: [
            Parameter { 
                id: importObjFilename
                name: "filename"
                type: Parameter.String
                stringValue: ""
            },
            Parameter { 
                name: "selection"
                type: Parameter.Bool
                boolValue: true
            }
        ]
    }

    // ACTIONS

    // New 
    Action {
        id: newAction
        text: "New"
        tooltip: "Clear the scene"
        onTriggered: { scenegraph.clear() }
    }

    // Open
    Action {
        id: openAction
        text: "Open"
        tooltip: "Open feather model"
        onTriggered: {}
    }

    // Import Obj
    Action {
        id: importObjAction
        text: "Obj"
        tooltip: "Import models in the Obj format"
        onTriggered: { importDialog.visible = true }
    }

    // Properties
    Action {
        id: propAction
        text: "Properties"
        tooltip: "Modify application settings"
        onTriggered: { propDialog.visible = (propDialog.visible) ? false : true; }
    }

    // Close 
    Action {
        id: closeAction
        text: "Close"
        tooltip: "Close Feather"
        onTriggered: { Qt.quit() }
    }


    // MENU


    // New 
    MenuItem {
        action: newAction
    }

    // Open 
    MenuItem {
        action: openAction
    }

    MenuSeparator {}

    // Import Menu
    Menu {
        id: importMenu
        title: "Import"

        
        // Obj
        MenuItem {
            action: importObjAction
        }
    }

    MenuSeparator {}

    MenuItem {
        action: propAction
    }

    MenuSeparator {}

    // Close
    MenuItem {
        action: closeAction
    }

}
