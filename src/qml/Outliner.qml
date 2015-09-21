/***********************************************************************
 *
 * Filename: Outliner.qml 
 *
 * Description: Window that display the node tree. 
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

import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQml.Models 2.2
import feather.scenegraph 1.0

Item {
//Window {
    id: outliner
    //title: "Outliner"
    //visible: true
    //flags: Qt.Tool
    //width: 300
    //height: 600
    property SceneGraph scenegraph: Null
    property Properties properties: Null
   
    TreeModel { id: treeModel }

    TreeView {
        id: tree
        anchors.fill: parent

        TableViewColumn {
            title: "name"
            role: "name"
            width: tree.width-40
        }

        TableViewColumn {
            title: "visible"
            role: "visible"
            //width: 100
        }

        model: treeModel
        selection: ItemSelectionModel { model: treeModel }
        selectionMode: SelectionMode.ContiguousSelection
        sortIndicatorVisible: true
        headerVisible: false
        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
        style: OutlinerLeafNode {}
 
        //onActivated: { console.log("item activated " + model.data(index,260)); scenegraph.clear_selection(); scenegraph.select_node(model.data(index,260)) }
        onClicked: { if(!model){ console.log("no model found") } else { console.log("item clicked for index " + index + " model " + model.data(index,260)); scenegraph.clear_selection(); scenegraph.select_node(model.data(index,260)) } }
   }

   function updateSg(){
        console.log("updateSg() model" + tree.model)
        tree.model.updateTree()
   } 

   Component.onCompleted: {
        scenegraph.update.connect(updateSg)
    }
}
