#version 450

#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

layout (binding = 1) uniform sampler2D samplerColorMap;

layout (location = 0) in vec3 inNormal;
layout (location = 1) in vec2 inUV;
layout (location = 2) in vec3 inColor;
layout (location = 3) in vec3 inPosition;
layout (location = 4) in vec3 inEdgeDistance;
layout (location = 5) flat in int inId;
layout (location = 6) flat in float inPointSize;
layout (location = 7) in vec3 inPointPosition;

layout (location = 0) out vec4 outColor;

void main() 
{
        // wireframe
        // find smallest distance
        float d = min(inEdgeDistance.x, inEdgeDistance.y);
        d = min(d,inEdgeDistance.z);

        // determine the mix factor with the line color
        float mixVal = smoothstep(inPointSize - 0.002, inPointSize + 0.002, d);
        
        // misc shading code
	//vec4 color = texture(samplerColorMap, inUV) * vec4(inColor, 1.0);

	vec3 N = normalize(inNormal);
	//vec3 L = normalize(LightVec);
	//vec3 V = normalize(ViewVec);
	//vec3 R = reflect(-L, N);
	//vec3 diffuse = max(dot(N, L), 0.0) * VColor;
	//vec3 specular = pow(max(dot(R, V), 0.0), 16.0) * vec3(0.75);

        vec4 pointColor = vec4(0,1,0,1);
        vec4 edgeColor = vec4(0,0,0,1);
        vec4 faceColor = mix(vec4(0,0,0,1), vec4(inColor, 1.0), mixVal);
        vec4 faceSelectedColor = mix(vec4(0,0,0,1), vec4(1,0,0,1), mixVal);
    
        
        float pointSize = 0.02;
        float a = inPointPosition.x - inPointPosition.y;
        float b = inPointPosition.x - inPointPosition.z;
        float pointMix = 0;
        if(inPointPosition.x > (1.0 - pointSize) && a > (1.0 - pointSize) && b > (1.0 - pointSize))    
            pointMix = 1;


        if(inId==0) {
            outColor = faceSelectedColor;
        } else {
            outColor = faceColor;
        }
        outColor = mix(outColor, pointColor, pointMix);
}
