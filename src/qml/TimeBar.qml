/***********************************************************************
 *
 * Filename: TimeBar.qml 
 *
 * Description: Displays the time and keyframes. 
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

Rectangle {
    id: timebar 
    color: "darkgrey"

    width: 500
    height: 20

    property double stime: 10.0
    property double etime: 10000.0 // millisecs
    property double cpos: 5000
    property double duration: etime - stime
    property int display: 0 // 0=frames, 1=seconds, 2=smpte
    property double fps: 24

    Canvas {
        id: bar 
        contextType: "2d"
        anchors.fill: parent
        anchors.margins: 2

        onPaint: {

            context.reset()

            var secondX = width/(20*24)
            var ppms = duration/width // pixels per msec
            var mspf = 1000/fps // msec per frame
            var ppf = width / ppms // pixels per frame
            var spos = ( ( stime/mspf ) * ppms )
            var cposX = ( ( cpos / ppms ) - ( stime / ppms ) )
            var frameX = spos 

            console.log("duration:" + duration + ", ppf: " +  ppf + ", ppms:" + ppms + ", mspf:" +  mspf + ", spos:" + spos + ", cposX:" + cposX)

            // frames 
            while(frameX < width) {
                // draw lines
                context.strokeStyle = "#000000"
                context.lineWidth = 1
                context.moveTo(frameX,0)
                context.lineTo(frameX,height)
                context.stroke()
                frameX = frameX + ppf
            }

            context.beginPath()
            // cpos 
            context.strokeStyle = "#ff0000"
            context.lineWidth = 2
            context.moveTo(cposX,0)
            context.lineTo(cposX,height)
            context.stroke()

            /*
            // draw connections
            context.strokeStyle = "#090909"
            context.path = path
            context.lineWidth = 1
            context.stroke()
            path.startY = path.startY + 100
            context.path = path
            context.strokeStyle = "#f90909"
 
            context.stroke()
            */
        }
 
    }

    function updateBar() {
        requestPaint()
    }
}
