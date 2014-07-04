attribute highp vec4 fvertex;
uniform mediump mat4 fmatrix;
varying mediump vec4 color;
void main(void)
{
    gl_Position = fmatrix * fvertex;
}

