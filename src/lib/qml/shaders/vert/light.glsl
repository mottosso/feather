/***********************************************************************
 *
 * Filename: light.glsl
 *
 * Description: Vertex shader for a light.
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

attribute highp vec4 vertex;
attribute highp vec4 position;
uniform mediump mat4 matrix;

varying vec4 c;
varying vec4 pos;

void main(void)
{
    c = vec4(1.0,1.0,0.0,1.0);
    //pos = vec4(5.0, 5.0, 5.0, 0.0);
    gl_Position = matrix * (position + vertex);
}
