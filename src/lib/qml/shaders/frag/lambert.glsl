/***********************************************************************
 *
 * Filename: lambert.glsl
 *
 * Description: Fragment shader for lambert surfaces.
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

#version 120
//#extension GL_EXT_gpu_shader4 : enable
//#extension GL_EXT_fragment_shader4 : enable

varying vec3 n;

varying vec3 position;
uniform vec3 LightPosition;
uniform vec3 CameraPosition;
uniform vec4 ShaderDiffuse;

uniform vec3 LightIntensity;
uniform vec3 Kd;
uniform vec3 Ka;
uniform vec3 Ks;
uniform float Shininess;

vec3 ads()
{
    //vec3 _lposition = LightPosition;
    //vec3 _lposition = n;
    vec3 _lposition = vec3(0,20,20);
    vec3 _lintensity = vec3(1.0,1.0,1.0);
    vec3 _Ka = vec3(0.25);
    vec3 _Kd = vec3(0.75);
    vec3 _Ks = vec3(0.0);
    float _shininess = 0.1;

    vec3 _n = normalize(n);
    vec3 _s = normalize(vec3(_lposition) - position);
    vec3 _v = normalize(vec3(-position));
    vec3 _r = reflect(-_s,_n);
    
    return _lintensity * (_Ka + _Kd * max(dot(_s,_n),0.0));
    //return _lintensity * (_Ka + _Kd * max(dot(_s,_n),0.0) + _Ks * pow(max(dot(_r,_v),0.0), _shininess));
}

void main(void) {
    gl_FragColor = vec4(ads(),1.0);
}
