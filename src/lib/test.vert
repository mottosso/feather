attribute highp vec4 vertices;
uniform highp mat4 matrix;
void main()
{
    gl_Position = matrix * vertices;
}
