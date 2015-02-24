// Mesh Shader
attribute highp vec4 vertex;
attribute highp vec4 position;
uniform mediump mat4 matrix;

varying vec4 c;
varying vec4 pos;

void main(void)
{
    c = vec4(1.0,1.0,0.0,1.0);
    //pos = vec4(5.0, 5.0, 5.0, 0.0);
    gl_Position = matrix * (vertex + position);
}
