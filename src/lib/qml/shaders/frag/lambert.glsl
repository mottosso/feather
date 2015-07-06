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

//varying vec4 c;
varying vec4 vcolor;
varying vec3 n;
varying vec3 lposition;
//varying int view;

uniform vec3 Ambient;
//uniform vec3 LightColor;
uniform vec3 LightDirection;
uniform vec3 HalfVector;
uniform float Shininess;
uniform float Strength;
uniform int modelview;



void main(void) {
    //float diffuse = max(0.0, dot(n, LightDirection));
    //float specular = max(0.0, dot(n, HalfVector));
    float diffuse = max(0.0, dot(n, lposition));
    float specular = max(0.0, dot(n, vec3(1,1,1)));


    // faces away from the light won't be lit
    if(diffuse == 0.0)
        specular = 0.0;
    else
        specular = pow(specular, 1.0); // sharpen highlight

    //specular = pow(specular, Shininess); // sharpen highlight

    //vec3 scatteredLight = Ambient + LightColor * diffuse;
    //vec3 reflectedLight = LightColor * specular * Strength;
    vec3 scatteredLight = 0.2 + vec3(1.0,1.0,1.0) * diffuse;
    vec3 reflectedLight = vec3(1.0,1.0,1.0) * specular * 1.0;


    vec3 rgb = min(vcolor.rgb * scatteredLight + reflectedLight, vec3(1.0));

    if(modelview==0) {
        gl_FragColor = vec4(rgb, vcolor.a);
    }
    else if(modelview==1) {
        gl_FragColor = vec4(0,0,0,1);
    } else {
        gl_FragColor = vec4(1,0,1,1);
    }

    //gl_FragColor = vec4(reflectedLight, 1);

}
