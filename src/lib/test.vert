in vec3 vp;
void main () {
  gl_Position = vec4 (vp, 1.0);
}
/*
attribute highp vec4 vertices;
varying highp vec2 coords;
void main() {
    gl_Position = vertices;
    coords = vertices.xy;
}*/
