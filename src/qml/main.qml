/***********************************************************************
 *
 * Filename: main.qml 
 *
 * Description: Entry point for the qml main window. 
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
import QtQuick.Layouts 1.1
import feather.scenegraph 1.0

ApplicationWindow {
    id: window
    width: 1200
    height: 700
    visible: true
    title: "Feather 0.1"

    SceneGraph { id: sg }

    Properties { id: properties }

    menuBar: MainMenu { properties: properties }

    toolBar: MainToolBar {}

    statusBar: StatusBar {
        RowLayout { BusyIndicator { implicitWidth: 10; implicitHeight: 10; running: true } Label { text: "Feather 0.1" } }
    }

    Item {
        id: centralWidgetId
        anchors.fill: parent

        Viewport3D {
            id: vp3d
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: cmdLineId.top
        }

        CommandLine {
            id: cmdLineId
            height: 30
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
        }
    }

    SceneGraphDialog {
        id: sgEditor
        scenegraph: sg
    }

    FieldEditor {
        id: fieldEditor
        scenegraph: sg
        properties: properties
    }

    //Outliner {}
    //Material {}
}
