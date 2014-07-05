uniform sampler2D tex;
varying vec2 texcoord;
//varying mediump vec4 color;
void main(void)
{
    gl_FragColor = texture2D(tex,texcoord);
    //gl_FragColor = vec4(1.0,1.0,0.0,1.0);
}
