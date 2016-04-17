#version 450

#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

layout (binding = 1) uniform sampler2D samplerColorMap;

layout (location = 0) out vec4 outColor;
layout (location = 1) out ivec4 outSelection;

void main() 
{
    outColor = vec4(1,0,0,1);

    outSelection = ivec4(0,0,0,0);
}
