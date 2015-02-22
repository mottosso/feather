// Mesh Shader
attribute highp vec4 vertex;
attribute highp vec3 normal;
uniform mediump mat4 matrix;

uniform mat3 m_3x3_inv_transp;
varying vec4 color;
varying vec3 n;

/*
struct lightSource
{
    vec4 position;
    vec4 diffuse;
    float constantAttenuation, linearAttenuation, quadraticAttenuation;
    float spotCutoff, spotExponent;
    vec3 spotDirection;
};

    lightSource light0 = lightSource(
            vec4(0.0,  1.0,  2.0, 1.0),
            vec4(1.0, 1.0, 1.0, 1.0),
            0.0, 1.0, 0.0,
            80.0, 20.0,
            vec3(-1.0, -0.5, -1.0)
            );
*/
 
struct lightSource
{
  vec4 position;
  vec4 diffuse;
};

lightSource light0 = lightSource(
    vec4(1.0, 0.0, 1.0, 0.0),
    vec4(1.0, 1.0, 1.0, 1.0)
);

struct material
{
    vec4 diffuse;
};

material mymaterial = material(vec4(0.5, 0.2, 0.8, 1.0));

void main(void)
{
    vec3 lightDirection = vec3(1.0,0,0.5);

    n = normalize(gl_NormalMatrix * gl_Normal); 
    float ndot;
    ndot = max(dot(normal,lightDirection),0.0);

    vec3 normalDirection = normalize(m_3x3_inv_transp * gl_Normal);

    vec3 diffuseReflection
        = vec3(light0.diffuse) * vec3(mymaterial.diffuse) * ndot;

    color = vec4(diffuseReflection, 1.0);

    gl_Position = matrix * vertex;
}
