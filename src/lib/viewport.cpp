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

float points[] = {
   0.0f,  0.5f,  0.0f,
   0.5f, -0.5f,  0.0f,
  -0.5f, -0.5f,  0.0f
};

Viewport::Viewport()
{
}

Viewport::~Viewport()
{
}

void Viewport::initialize()
{
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);

    /*
    GLuint vbo = 0;
    glGenBuffers (1, &vbo);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (float), points, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);
    glEnableVertexAttribArray (0);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    */

    QOpenGLShader *vshader1 = new QOpenGLShader(QOpenGLShader::Vertex, &program1);
    vshader1->compileSourceFile("test.vert");

    QOpenGLShader *fshader1 = new QOpenGLShader(QOpenGLShader::Fragment, &program1);
    fshader1->compileSourceFile("test.frag");

    program1.addShader(vshader1);
    program1.addShader(fshader1);
    program1.link();

    vertexAttr1 = program1.attributeLocation("vertex");
    normalAttr1 = program1.attributeLocation("normal");
    matrixUniform1 = program1.uniformLocation("matrix");

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    // setup the camera position here
    // setup the meshes here

    createMesh();
}

void Viewport::render()
{
    glDepthMask(true);

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glFrontFace(GL_CW);
    glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    QMatrix4x4 modelview;
    //modelview.rotate(m_fAngle, 0.0f, 1.0f, 0.0f);
    //modelview.rotate(m_fAngle, 1.0f, 0.0f, 0.0f);
    //modelview.rotate(m_fAngle, 0.0f, 0.0f, 1.0f);
    //modelview.scale(m_fScale);
    modelview.translate(0.0f, 0.0f, -1.0f);

    program1.bind();
    program1.setUniformValue(matrixUniform1, modelview);
    program1.release();

    // draw scenegraph here
    glBindVertexArray (vao);
    glDrawArrays (GL_TRIANGLES, 0, 3);


    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
}

void Viewport::createMesh()
{
    vbo = 0;
    glGenBuffers (1, &vbo);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (float), points, GL_STATIC_DRAW);

    vao = 0;
    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);
    glEnableVertexAttribArray (0);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);


}
