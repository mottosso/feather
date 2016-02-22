/***********************************************************************
 *
 * Filename: TimeController.qml 
 *
 * Description: Controls playback. 
 *
 * Copyright (C) 2016 Richard Layman, rlayman2000@yahoo.com 
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


Rectangle {
    id: window
    width: 148 
    height: 28 
    color: "lightgrey"
    border.width: 1
    property int cpos: 0
    //property alias smpte: time.smpte
    property int state: 0 // 0=stop, 1=playforward, 2=playbackward

    signal play()
    signal seek(int pos) //msec
    signal stop()
    signal pause()

    ExclusiveGroup { id: group }

    Item {
        id: controller
        anchors.fill: parent
        anchors.margins: 4

        Row {
            spacing: 4

            ImageButton {
                id: rewindButton 
                width: 20
                height: 20
                imageNormal: "icons/button_rewind_normal.svg"
                imageActive: "icons/button_rewind_active.svg"
                imageHover: "icons/button_rewind_hover.svg"
                imageDisabled: "icons/button_rewind_disabled.svg"
                exclusiveGroup: group
            }

            ImageButton {
                id: backFrameButton 
                width: 20 
                height: 20 
                imageNormal: "icons/button_frame_backward_normal.svg"
                imageActive: "icons/button_frame_backward_active.svg"
                imageHover: "icons/button_frame_backward_hover.svg"
                imageDisabled: "icons/button_frame_backward_disabled.svg"
                exclusiveGroup: group
            }

            ImageButton {
                id: playBackwardButton 
                width: 20
                height: 20
                imageNormal: "icons/button_play_backward_normal.svg"
                imageActive: "icons/button_play_backward_active.svg"
                imageHover: "icons/button_play_backward_hover.svg"
                imageDisabled: "icons/button_play_backward_disabled.svg"
                exclusiveGroup: group
            }

            ImageButton {
                id: playForwardButton 
                width: 20
                height: 20
                imageNormal: "icons/button_play_forward_normal.svg"
                imageActive: "icons/button_play_forward_active.svg"
                imageHover: "icons/button_play_forward_hover.svg"
                imageDisabled: "icons/button_play_forward_disabled.svg"
                exclusiveGroup: group
             }

            ImageButton {
                id: forwardFrameButton 
                width: 20
                height: 20
                imageNormal: "icons/button_frame_forward_normal.svg"
                imageActive: "icons/button_frame_forward_active.svg"
                imageHover: "icons/button_frame_forward_hover.svg"
                imageDisabled: "icons/button_frame_forward_disabled.svg"
                exclusiveGroup: group
             }

            ImageButton {
                id: fastForwardButton 
                width: 20
                height: 20
                imageNormal: "icons/button_fast_forward_normal.svg"
                imageActive: "icons/button_fast_forward_active.svg"
                imageHover: "icons/button_fast_forward_hover.svg"
                imageDisabled: "icons/button_fast_forward_disabled.svg"
                exclusiveGroup: group
             }
            /* 
            TimeCode {
                id: time
                width: 80
                height: 20
                timeSize: 12
                timeColor: "yellow"
            }
            */
        }
    }

    function on_play(){
        playForwardButton.checked=true
        play()
    }

    function on_pause(){
        //pauseButton.checked=true
        pause()
    }

    Component.onCompleted: {
        playForwardButton.buttonPressed.connect(on_play)
        //pauseButton.buttonPressed.connect(on_pause)
    }
}
