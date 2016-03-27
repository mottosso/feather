#version 450

#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inUV;
layout (location = 3) in vec3 inColor;
layout (location = 4) in uint inSelection;


layout (binding = 0) uniform UBO 
{
	mat4 projection;
	mat4 model;
        int mode;
} ubo;

layout (location = 0) out vec3 outNormal;
layout (location = 1) out uint outSelection;

void main() 
{
    outNormal = inNormal;
    outSelection = inSelection;
    gl_Position = vec4(inPosition.xyz, 1.0);
}
