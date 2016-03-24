#version 450

#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

layout (triangles) in;
layout (triangle_strip, max_vertices=3) out;

layout (binding = 1) uniform UBO 
{
	mat4 projection;
	mat4 model;
} ubo;

layout (location = 0) in vec3 inNormal[]; 
layout (location = 1) in vec2 inUV[];
layout (location = 2) in vec3 inColor[];
layout (location = 3) in vec3 inPosition[];

layout (location = 0) out vec3 outNormal;
layout (location = 1) out vec2 outUV;
layout (location = 2) out vec3 outColor;
layout (location = 3) out vec3 outPosition;
layout (location = 4) out vec3 outEdgeDistance;

void main() 
{
    // transform each vertex into viewport space
    vec3 p0 = vec3(ubo.model * (gl_in[0].gl_Position / gl_in[0].gl_Position.w));
    vec3 p1 = vec3(ubo.model * (gl_in[1].gl_Position / gl_in[1].gl_Position.w));
    vec3 p2 = vec3(ubo.model * (gl_in[2].gl_Position / gl_in[2].gl_Position.w));

    // find the altitudes
    float a = length(p1-p2);
    float b = length(p2-p0);
    float c = length(p1-p0);
    float alpha = acos((b*b + c*c - a*a)/(2.0*b*c));
    float beta = acos((a*a + c*c - b*b)/(2.0*a*c));
    float ha = abs(c*sin(beta));
    float hb = abs(c*sin(alpha));
    float hc = abs(b*sin(alpha));

    // pass the triangle

    outEdgeDistance = vec3(ha,0,0);
    outUV = inUV[0];
    outColor = inColor[0];
    outPosition = inPosition[0];
    outNormal = inNormal[0];
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();

    outEdgeDistance = vec3(0,hb,0);
    outUV = inUV[1];
    outColor = inColor[1];
    outPosition = inPosition[1];
    outNormal = inNormal[1];
    gl_Position = gl_in[1].gl_Position;
    EmitVertex();

    outEdgeDistance = vec3(0,0,hc);
    outUV = inUV[2];
    outColor = inColor[2];
    outPosition = inPosition[2];
    outNormal = inNormal[2];
    gl_Position = gl_in[2].gl_Position;
    EmitVertex();

    EndPrimitive();
}
