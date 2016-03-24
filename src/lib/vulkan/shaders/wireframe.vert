#version 450

#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inUV;
layout (location = 3) in vec3 inColor;

layout (binding = 0) uniform UBO 
{
	mat4 projection;
	mat4 model;
} ubo;

layout (location = 0) out vec3 outNormal;
layout (location = 1) out vec2 outUV;
layout (location = 2) out vec3 outColor;
layout (location = 3) out vec3 outPosition;

void main() 
{
    /*
	outNormal = inNormal;
	outColor = inColor;
	outUV = inUV;
	gl_Position = ubo.projection * ubo.model * vec4(inPos.xyz, 1.0);
	
    vec4 pos = ubo.model * vec4(inPos, 1.0);
    outNormal = mat3(ubo.model) * inNormal;
	vec3 lPos = mat3(ubo.model) * ubo.lightPos.xyz;
    outLightVec = lPos - pos.xyz;
    outViewVec = -pos.xyz;		
    */
    vec4 pos = ubo.model * vec4(inPosition, 1.0);
    outPosition = vec3(ubo.model * vec4(inPosition, 1.0));
    outNormal = normalize(vec3(ubo.model * vec4(inNormal, 1.0)));
    //VColor = inColor;
    outColor = inColor;
    outUV = inUV;

    gl_Position = ubo.projection * ubo.model * vec4(inPosition.xyz, 1.0);
}
