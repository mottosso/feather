#version 450

#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

layout (lines) in;
layout (line_strip, max_vertices = 2) out;

layout (binding = 1) uniform UBO 
{
	mat4 projection;
	mat4 model;
        int mode;
        // selection ids
        int point;
        int edge;
        int face;
        int object;
} ubo;

layout (location = 0) in vec3 inNormal[]; 
layout (location = 1) in ivec4 inId[]; 

layout (location = 0) out vec3 outColor;
layout (location = 1) out ivec4 outId;

void main() 
{
    float pointSize = 4.0;

    vec3 p0 = gl_in[0].gl_Position.xyz;
    vec3 p1 = gl_in[1].gl_Position.xyz;

    gl_Position = ubo.projection * (ubo.model * vec4(p0, 1.0));
    if(ubo.point == inId[0].r)
        outColor = vec3(1.0, 0.0, 0.0);
    else
        outColor = vec3(0.0, 0.0, 0.0);
    outId.r = inId[0].r;
    outId.g = inId[0].g;
    outId.b = gl_PrimitiveIDIn;
    outId.a = inId[0].a;
    EmitVertex();

    gl_Position = ubo.projection * (ubo.model * vec4(p1, 1.0));
    if(ubo.point == inId[0].r)
        outColor = vec3(1.0, 0.0, 0.0);
    else
        outColor = vec3(0.0, 0.0, 0.0);
    outId.r = inId[1].r;
    outId.g = inId[1].g;
    outId.b = gl_PrimitiveIDIn;
    outId.a = inId[1].a;
    EmitVertex();

    EndPrimitive();
}
