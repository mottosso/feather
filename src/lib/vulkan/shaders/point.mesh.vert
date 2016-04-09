#version 450

#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable
//#extension GL_EXT_gpu_shader4: enable

layout (location = 0) in vec3 inPosition;
layout (location = 4) in vec3 inId;

layout (binding = 0) uniform UBO 
{
	mat4 projection;
	mat4 model;
        int mode;
} ubo;

layout (location = 0) out vec3 outPosition;
layout (location = 1) out vec3 outId;

void main() 
{
    outPosition = inPosition;
    gl_Position = vec4(inPosition.xyz, 1.0);
    outId = inId;
}
