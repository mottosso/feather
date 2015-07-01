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
attribute highp vec4 lightposition;
attribute highp vec4 shader_diffuse;
uniform mediump mat4 matrix;

uniform mat3 m_3x3_inv_transp;
varying vec4 c;
varying vec3 n;

varying vec4 vcolor;

/*
struct lightSource
{
    vec4 position;
    vec4 diffuse;
    float constantAttenuation, linearAttenuation, quadraticAttenuation;
    float spotCutoff, spotExponent;
    vec3 spotDirection;
};

    lightSource light0 = lightSource(
            vec4(0.0,  1.0,  2.0, 1.0),
            vec4(1.0, 1.0, 1.0, 1.0),
            0.0, 1.0, 0.0,
            80.0, 20.0,
            vec3(-1.0, -0.5, -1.0)
            );
*/
 
struct lightSource
{
  vec4 position;
  vec4 diffuse;
};

lightSource light0 = lightSource(
    lightposition,
    vec4(0.5, 0.5, 0.5, 1.0)
);

struct material
{
    vec4 diffuse;
};

material mymaterial = material(shader_diffuse);

void main(void)
{
    //vec4 lightDirection = vec4(10.0, 10.0, 10.0, 1.0);

    n = normalize(gl_NormalMatrix * gl_Normal); 
    float ndot;
    ndot = max(dot(normal,vec3(light0.position)),0.0);

    //vec3 normalDirection = normalize(m_3x3_inv_transp * gl_Normal);

    vec3 diffuseReflection = vec3(light0.diffuse) * vec3(mymaterial.diffuse) * ndot;

    c = vec4(diffuseReflection, 1.0);
    vcolor = color;
    gl_Position = matrix * vertex;
}
