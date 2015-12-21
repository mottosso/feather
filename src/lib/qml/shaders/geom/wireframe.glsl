/***********************************************************************
 *
 * Filename: geom.glsl
 *
 * Description: Geometry shader to display a wireframe mesh.
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
//#version 300 es 
#version 130 

//#version 330 core // not supported 

//#extension GL_EXT_ARB_geometry_shader4 : enable
//#extension GL_EXT_separate_shader_objects : enable



//layout ( triangles ) in;
//layout (points) in;

//layout ( location = 0 ) highp in vec4 vertex;
//layout ( xfb_buffer = 1 ) out;
layout ( triangles ) in;

//layout ( triangle_strip, max_vertices = 3 ) out;
//layout ( triangle_strip, max_vertices = 3 ) out;


//layout ( triangle_strip ) out;
//layout ( points ) out;



//#extension GL_EXT_gpu_shader4 : enable
//attribute highp vec4 vertex;
//attribute highp vec4 color;
//attribute highp vec3 normal;
//uniform mediump int modelview;
//attribute highp vec3 lightposition;
//attribute highp vec4 shader_diffuse;
//uniform mediump mat4 matrix;

//uniform mat3 m_3x3_inv_transp;
//varying vec4 c;
//varying vec3 n;
//varying vec3 lposition;
//varying vec4 vcolor;

//layout (triangles) in;
//layout ( triangle_strip, max_vertices = 3 ) out;
//layout ( triangle_strip ) out;

void main(void)
{
    /*
    for(int i = 0; i < in.length(); ++i){
        //gl_Position = in[0].gl_Position;
        EmitVertex();
    }
    */
    //gl_Position = vertex[0]; 
    gl_Position = gl_PositionIn[0]; 
    //EmitVertex();
    //EndPrimitive();
    //gl_Points = vec4(0,0,0,0);
}
