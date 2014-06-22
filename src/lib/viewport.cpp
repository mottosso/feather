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
   0.0f,  1.0f,  0.0f,
   -1.0f, 1.0f,  0.0f,
  1.0f, -1.0f,  0.0f
};

int indics[] = { 0, 1, 2 };

float color[] = {
  1.0f,  1.0f,  1.0f,
  1.0f, 1.0f,  1.0f,
  1.0f, 1.0f,  1.0f
};

Viewport::Viewport()
{
}

Viewport::~Viewport()
{
}

void Viewport::initialize()
{
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

    QOpenGLShader *vshader1 = new QOpenGLShader(QOpenGLShader::Vertex, &program1);
    vshader1->compileSourceFile("test.vert");

    QOpenGLShader *fshader1 = new QOpenGLShader(QOpenGLShader::Fragment, &program1);
    fshader1->compileSourceFile("test.frag");

    program1.addShader(vshader1);
    program1.addShader(fshader1);
    program1.link();

    // use these to access variable in the glsl
    //vertexAttr1 = program1.attributeLocation("vertex");
    //normalAttr1 = program1.attributeLocation("normal");
    //matrixUniform1 = program1.uniformLocation("matrix");

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    // setup the camera position here
    // setup the meshes here
    //createMesh();

    // VBO ITEMS

    // Create VAO for first object to render
    m_vao1 = new QOpenGLVertexArrayObject(m_context);
    m_vao1->create();
    m_vao1->bind();

    // Setup VBOs and IBO (use QOpenGLBuffer to buffer data,
    // specify format, usage hint etc). These will be
    // remembered by the currently bound VAO
    m_positionBuffer.create();
    m_positionBuffer.setUsagePattern( QOpenGLBuffer::StreamDraw );
    m_positionBuffer.bind();
    m_positionBuffer.allocate( points,
                               3 * 3 * sizeof( float ) );
    program1.enableAttributeArray( "vertexPosition" );
    program1.setAttributeBuffer( "vertexPosition", GL_FLOAT, 0, 3 );

    m_colorBuffer.create();
    m_colorBuffer.setUsagePattern( QOpenGLBuffer::StaticDraw );
    m_colorBuffer.bind();
    m_colorBuffer.allocate( color,
                            3 * 3 * sizeof( float ) );
    program1.enableAttributeArray( "vertexColor" );
    program1.setAttributeBuffer( "vertexColor", GL_FLOAT, 0, 3 );
}

void Viewport::render()
{
    glDepthMask(true);

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    //glFrontFace(GL_CW);
    //glCullFace(GL_FRONT);
    //glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    QMatrix4x4 modelview;
    //modelview.rotate(m_fAngle, 0.0f, 1.0f, 0.0f);
    //modelview.rotate(m_fAngle, 1.0f, 0.0f, 0.0f);
    //modelview.rotate(m_fAngle, 0.0f, 0.0f, 1.0f);
    //modelview.scale(m_fScale);
    modelview.translate(0.0f, 0.0f, -0.4f);

    program1.bind();
    program1.setUniformValue(matrixUniform1, modelview);

    m_vao1->bind();
    glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,indics);

    // draw scenegraph here

    program1.release();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);


}

void Viewport::createMesh()
{
    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);
    glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (float), points, GL_STATIC_DRAW);
    glGenBuffers (1, &vbo);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray (0);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glBindVertexArray (0);

    /*
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
    */
}
