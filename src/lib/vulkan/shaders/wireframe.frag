#version 450

#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

layout (binding = 1) uniform sampler2D samplerColorMap;

layout (location = 0) in vec3 inNormal;
layout (location = 1) in vec2 inUV;
layout (location = 2) in vec3 inColor;
layout (location = 3) in vec3 inPosition;
layout (location = 4) in vec3 inEdgeDistance;

layout (location = 0) out vec4 outColor;

void main() 
{
        // wireframe
        // find smallest distance
        float d = min(inEdgeDistance.x, inEdgeDistance.y);
        d = min(d,inEdgeDistance.z);

        // determine the mix factor with the line color
        float mixVal = smoothstep(0.002 - 0.002, 0.002 + 0.002, d);
        
        // misc shading code
	//vec4 color = texture(samplerColorMap, inUV) * vec4(inColor, 1.0);

	vec3 N = normalize(inNormal);
	//vec3 L = normalize(LightVec);
	//vec3 V = normalize(ViewVec);
	//vec3 R = reflect(-L, N);
	//vec3 diffuse = max(dot(N, L), 0.0) * VColor;
	//vec3 specular = pow(max(dot(R, V), 0.0), 16.0) * vec3(0.75);
        outColor = mix(vec4(0,0,0,1), vec4(inColor, 1.0), mixVal);
}
