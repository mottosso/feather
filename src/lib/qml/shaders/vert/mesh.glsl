/***********************************************************************
 *
 * Filename: mesh.glsl
 *
 * Description: Vertex shader for a mesh.
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
attribute highp vec4 color;
attribute highp vec3 normal;
uniform mediump int modelview;
uniform mediump int Selected;
attribute highp vec3 LightPosition;
attribute highp vec3 LightAmbient;
attribute highp vec3 LightDiffuse;
attribute highp vec3 LightSpecular;
attribute highp vec3 MaterialAmbient;
attribute highp vec3 MaterialDiffuse;
attribute highp vec3 MaterialSpecular;
attribute highp float MaterialShininess;
attribute highp vec3 CameraPosition;
attribute highp vec4 ShaderDiffuse;
uniform mediump mat4 matrix;

varying vec3 LightIntensity;

void main()
{
    vec3 norm = normalize(gl_NormalMatrix * normal);
    vec4 position = matrix * vertex;

    vec4 lposition = vec4(20,20,0,0);
    
    vec3 s = normalize(vec3(lposition-position));

    LightIntensity = LightDiffuse * MaterialDiffuse * max(dot(s,norm),0.0);

    gl_Position = matrix * vertex;
}
