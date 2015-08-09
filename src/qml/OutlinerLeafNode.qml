/***********************************************************************
 *
 * Filename: OutlinerLeafNode.qml 
 *
 * Description: Leaf node drawn by the Outliner. 
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
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4


TreeViewStyle {
    id: style

    backgroundColor: "#848482"
    alternateBackgroundColor: "#848482"

    itemDelegate: Item {
        Item { id: nodeName; visible: false; Row { Image { sourceSize.width: 16; sourceSize.height: 16; source: "icons/"+model.icon } Text { elide: styleData.elideMode; font.pixelSize: 12; text: model.name } } }
        Item { id: nodeVisible; visible: false; CheckBox { checked: model.visible } }
        Component.onCompleted: {
            switch(styleData.column){
                case 0:
                    nodeName.visible=true;
                    nodeVisible.visible=false;
                    break;
                case 1:
                    nodeName.visible=false;
                    nodeVisible.visible=true;
                    break;
                default:
                    0 
            }
        }
    }

}

