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

struct Vector3D
{
    Vector3D(float _x=0, float _y=0, float _z=0): x(_x),y(_y),z(_z){};
    float x,y,z;
};

std::vector<Vector3D> points;
std::vector<Vector3D> grid;

Viewport::Viewport() : m_fAngle(0),m_fScale(1)
{

}

Viewport::~Viewport()
{

}

void Viewport::initialize(int width, int height)
{
    QOpenGLShader *vshader1 = new QOpenGLShader(QOpenGLShader::Vertex, &program1);
    vshader1->compileSourceFile("test.vert");

    QOpenGLShader *fshader1 = new QOpenGLShader(QOpenGLShader::Fragment, &program1);
    fshader1->compileSourceFile("test.frag");

    program1.addShader(vshader1);
    program1.addShader(fshader1);
    program1.link();

    QOpenGLShader *gridShader = new QOpenGLShader(QOpenGLShader::Vertex, &gridProgram);
    gridShader->compileSourceFile("grid.glsl");
 
    greenShader = new QOpenGLShader(QOpenGLShader::Fragment, &gridProgram);
    greenShader->compileSourceFile("green.glsl");

    gridProgram.addShader(gridShader);
    gridProgram.addShader(greenShader);
    gridProgram.link();

    // use these to access variable in the glsl
    vertexAttr1 = program1.attributeLocation("vertex");
    gridVAttr = gridProgram.attributeLocation("vertex");
    //normalAttr1 = program1.attributeLocation("normal");
    //colorUniform1 = program1.uniformLocation("color");
    matrixUniform1 = program1.uniformLocation("matrix");
    gridMAttr = gridProgram.uniformLocation("matrix");

    points.push_back(Vector3D(-1,-1,0));
    points.push_back(Vector3D(1,-1,0));
    points.push_back(Vector3D(-1,1,0));
    points.push_back(Vector3D(1,1,0));

    grid.push_back(Vector3D(-1,0,-1));
    grid.push_back(Vector3D(1,0,-1));
    grid.push_back(Vector3D(-1,0,1));
    grid.push_back(Vector3D(1,0,1));

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    const qreal fov=45.0,near=0.01, far=20.0;
    qreal aspect=(float)width/(float)height;

    pview.setToIdentity();
    pview.perspective(fov,aspect,near,far); 
    pview.lookAt(QVector3D(0.0,-2,6.0),QVector3D(0,0,0),QVector3D(0,1,0)); 
}

void Viewport::render()
{
    glDepthMask(true);

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glFrontFace(GL_CW);
    glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    // draw test plane
    program1.bind();
    program1.setUniformValue(matrixUniform1, pview);
    drawMesh();
    program1.release();

    // draw the grid
    gridProgram.bind();
    gridProgram.setUniformValue(gridMAttr, pview);
    drawGrid();
    gridProgram.release();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    m_fAngle += 0.1;
}

void Viewport::drawMesh() {
    //program1.enableAttributeArray(normalAttr1);
    program1.enableAttributeArray(vertexAttr1);
    program1.setAttributeArray(vertexAttr1, GL_FLOAT, &points[0], 3);
    //program1.setAttributeArray(normalAttr1, normals.constData());
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    //program1.disableAttributeArray(normalAttr1);
    program1.disableAttributeArray(vertexAttr1);
}

void Viewport::drawGrid() {
    gridProgram.enableAttributeArray(gridVAttr);
    gridProgram.setAttributeArray(gridVAttr, GL_FLOAT, &grid[0], 3);
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    gridProgram.disableAttributeArray(gridVAttr);
}

