attribute highp vec4 vertex;
uniform mediump mat4 matrix;
varying mediump vec4 color;
//varying highp vec2 texcoord;

void main(void)
{
    gl_Position = matrix * vertex;
    //texcoord = vertex.xy;
}

