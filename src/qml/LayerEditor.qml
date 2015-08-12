/***********************************************************************
 *
 * Filename: LayerEditor.qml 
 *
 * Description: Container for layers.
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
import QtQuick.Window 2.2
import feather.scenegraph 1.0
import feather.layer 1.0

Window {
    id: layerEditor 
    title: "Layer Editor"
    visible: true
    flags: Qt.Tool
    width: 200
    height: 500
    property SceneGraph scenegraph: Null

    LayerModel { id: layerModel }

    Rectangle {
        id: layerFrame
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height
        anchors.margins: 1
        border.color: "black"
        border.width: 1
        color: properties.getColor("windowBg")
        radius: 2
 
        ListView {
            spacing: 0
            anchors.fill: parent
            //anchors.margins: 1
            model: layerModel
            //delegate: LayerEditorValue { properties: fieldEditor.properties; width: parent.width; uId: uid; nodeKey: nid; fieldKey: fid; fieldType: type }
            delegate: LayerBar { width: parent.width; barId: layerId; barName: layerName; barColor: layerColor; barVisible: layerVisible; barLocked: layerLocked }
        }

    }

    function updateColor() {
        console.log("update node color")
        layerFrame.color = properties.getColor("panel")        
        //nodeTitle.color = properties.getColor("labelBg")        
        //nodeBaseTitle.color = properties.getColor("labelBg")        
        layerEditor.color = properties.getColor("windowBg")

    }

    Component.onCompleted: {
        updateColor()
    }    

}
