// =====================================================================================
// 
//       Filename:  viewport.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/14/2014 04:15:14 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#include "viewport.hpp"

// this is the grid 
GLfloat gridpoints[2][2][3] = {
    {
        {2,0,2}, // top right
        {2,0,-2} // bottom right
    },
    {
        {-2,0,2}, // top left
        {-2,0,-2} // bottom left
    }
};

float graphres = 200.0;


Viewport::Viewport()
{
}

Viewport::~Viewport()
{
}

void Viewport::initialize()
{
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);

    QOpenGLShader *vshader1 = new QOpenGLShader(QOpenGLShader::Vertex, &program1);
    const char *vsrc1 =
        "attribute highp vec4 vertex;\n"
        "attribute mediump vec3 normal;\n"
        "uniform mediump mat4 matrix;\n"
        "varying mediump vec4 color;\n"
        "void main(void)\n"
        "{\n"
        " vec3 toLight = normalize(vec3(0.0, 0.3, 1.0));\n"
        " float angle = max(dot(normal, toLight), 0.0);\n"
        " vec3 col = vec3(0.40, 1.0, 0.0);\n"
        " color = vec4(col * 0.2 + col * 0.8 * angle, 1.0);\n"
        " color = clamp(color, 0.0, 1.0);\n"
        " gl_Position = matrix * vertex;\n"
        "}\n";

    vshader1->compileSourceCode(vsrc1);

    QOpenGLShader *fshader1 = new QOpenGLShader(QOpenGLShader::Fragment, &program1);
    const char *fsrc1 =
        "varying mediump vec4 color;\n"
        "void main(void)\n"
        "{\n"
        " gl_FragColor = color;\n"
        "}\n";
    fshader1->compileSourceCode(fsrc1);

    program1.addShader(vshader1);
    program1.addShader(fshader1);
    program1.link();

    vertexAttr1 = program1.attributeLocation("vertex");
    normalAttr1 = program1.attributeLocation("normal");
    matrixUniform1 = program1.uniformLocation("matrix");

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    // setup grid
    // glMap2f(target,u1,u2,ustride,uorder,v1,v2,vstride,vorder,points)
    // u1,u2 = min and max values for u
    // v1,v2 = min and max values for v
    // *stride = the number of values between indepentent settings for these values
    // using the example of grid[2][2][3] would give you 0,1,3,2,0,1,6,2 (0.0,1.0,[3],[2],0.0,1.0,[2]*[3],[2])
    glMap2f(GL_MAP2_VERTEX_3,0,1,3,2,0,1,6,2,&gridpoints[0][0][0]);
    glEnable(GL_MAP2_VERTEX_3);

    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);

    // glMapGrid2f(nu,u1,u2,nv,v1,v2)
    // n* = number of steps
    // u1,u2 = from/to u
    // v1,v2 = from/to v
    glMapGrid2f(2,0.0,1.0,2,0.0,1.0);


    std::cout << "init\n";

    // setup the camera position here
    // setup the meshes here
}

void Viewport::render()
{
    glDepthMask(true);
    std::cout << "render\n";


    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glFrontFace(GL_CW);
    glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    // position camera
    glTranslatef(0,0.7,0);

    // draw scenegraph here
    
    // draw the grid
    drawGrid();

   glLineWidth(1.5);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
}

void Viewport::drawGrid()
{
    // min grid lines
    glLineWidth(1.25);
    glColor3f(0,0,1);
    glMapGrid2f(40,0.0,1.0,40,0.0,1.0);
    glEvalMesh2(GL_LINE,0,40,0,40); // GL_FILL and GL_POINT

    // max grid lines
    glLineWidth(1.5);
    glColor3f(0,0,0);
    glMapGrid2f(4,0.0,1.0,4,0.0,1.0);
    glEvalMesh2(GL_LINE,0,4,0,4); // GL_FILL and GL_POINT
}
