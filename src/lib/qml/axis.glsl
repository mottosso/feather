attribute highp vec4 vertex;
uniform mediump mat4 matrix;
varying mediump vec4 color;

void main(void)
{
    gl_Position = matrix * vertex;
}

