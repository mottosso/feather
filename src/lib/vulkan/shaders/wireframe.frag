#version 450

#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

layout (binding = 1) uniform sampler2D samplerColorMap;

layout (location = 0) in vec3 VNormal;
layout (location = 1) in vec2 VUV;
layout (location = 2) in vec3 VColor;
layout (location = 3) in vec3 VPosition;
layout (location = 4) in vec3 VEdgeDistance;

layout (location = 0) out vec4 FragColor;

void main() 
{
        // wireframe
        // find smallest distance
        float d = min(VEdgeDistance.x, VEdgeDistance.y);
        d = min(d,VEdgeDistance.z);

        // determine the mix factor with the line color
        float mixVal = smoothstep(0.002 - 0.002, 0.002 + 0.002, d);

        
        // misc shading code
	//vec4 color = texture(samplerColorMap, VUV) * vec4(VColor, 1.0);

	vec3 N = normalize(VNormal);
	//vec3 L = normalize(LightVec);
	//vec3 V = normalize(ViewVec);
	//vec3 R = reflect(-L, N);
	//vec3 diffuse = max(dot(N, L), 0.0) * VColor;
	//vec3 specular = pow(max(dot(R, V), 0.0), 16.0) * vec3(0.75);
        FragColor = mix(vec4(0,0,0,1), vec4(VColor, 1.0), mixVal);
}
