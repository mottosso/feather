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

struct Vector3D
{
    Vector3D(float _x=0, float _y=0, float _z=0): x(_x),y(_y),z(_z){};
    float x,y,z;
};

std::vector<Vector3D> points;
std::vector<Vector3D> floorVertex;

Viewport::Viewport() : m_fAngle(0),m_fScale(1)
{

}

Viewport::~Viewport()
{

}

void Viewport::initialize(int width, int height)
{
    //glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

    QOpenGLShader *vshader1 = new QOpenGLShader(QOpenGLShader::Vertex, &program1);
    vshader1->compileSourceFile("test.vert");

    QOpenGLShader *fshader1 = new QOpenGLShader(QOpenGLShader::Fragment, &program1);
    fshader1->compileSourceFile("test.frag");

    program1.addShader(vshader1);
    program1.addShader(fshader1);
    program1.link();


    QOpenGLShader *vfloorshader1 = new QOpenGLShader(QOpenGLShader::Vertex, &floorShader);
    vfloorshader1->compileSourceFile("floor.vert");

    QOpenGLShader *ffloorshader1 = new QOpenGLShader(QOpenGLShader::Fragment, &floorShader);
    ffloorshader1->compileSourceFile("floor.frag");

    floorShader.addShader(vfloorshader1);
    floorShader.addShader(ffloorshader1);
    floorShader.link();


    // use these to access variable in the glsl
    vertexAttr1 = program1.attributeLocation("vertex");
    floorVertexAttr1 = floorShader.attributeLocation("fvertex");
    //normalAttr1 = program1.attributeLocation("normal");
    //colorUniform1 = program1.uniformLocation("color");
    matrixUniform1 = program1.uniformLocation("matrix");
    matrixFloorUniform1 = floorShader.uniformLocation("fmatrix");

    points.push_back(Vector3D(-1,-1,0));
    points.push_back(Vector3D(1,-1,0));
    points.push_back(Vector3D(-1,1,0));
    points.push_back(Vector3D(1,1,0));

    floorVertex.push_back(Vector3D(-1,0,-1));
    floorVertex.push_back(Vector3D(1,0,-1));
    floorVertex.push_back(Vector3D(-1,0,1));
    floorVertex.push_back(Vector3D(1,0,1));

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    const qreal fov=45.0,near=0.01, far=20.0;
    qreal aspect=(float)width/(float)height;

    pview.setToIdentity();
    pview.perspective(fov,aspect,near,far); 
    pview.lookAt(QVector3D(0.0,-2,6.0),QVector3D(0,0,0),QVector3D(0,1,0)); 

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

    //QColor color(0,255,0,255);

    //program1.bind();
 
    //QMatrix4x4 pview;
    //pview.perspective(fov,near,far,aspect); 
    //pview.lookAt(QVector3D(0.0,-2,6.0),QVector3D(0,0,0),QVector3D(0,1,0)); 
 
    QMatrix4x4 floorview;
    //floorview.scale(0.1);
    //floorview.setToIdentity();
    floorview.translate(0.0f, 0.0f, 0.0f);
 
    QMatrix4x4 modelview;
    //modelview.setToIdentity();
    //modelview.setToIdentity();
    //modelview.perspective(fov,near,far,aspect); 
    //modelview.rotate(m_fAngle, 0.0f, 1.0f, 0.0f);
    //modelview.rotate(m_fAngle, 1.0f, 0.0f, 0.0f);
    //modelview.rotate(m_fAngle, 0.0f, 0.0f, 1.0f);
    //modelview.scale(m_fScale);
    modelview.translate(0.0f, 0.0f, 0.0f);
    //modelview.perspective(fov,near,far,aspect); 
    //modelview.lookAt(QVector3D(0,-3,0.0),QVector3D(0,0,0),QVector3D(0,1,0)); 
    program1.bind();
    program1.setUniformValue(matrixUniform1, pview * modelview);
    //glTranslatef(0.0,-8.0,0.0);
    drawMesh();

    program1.release();

    floorShader.bind();
    floorShader.setUniformValue(matrixFloorUniform1, pview * floorview);
    //glTranslatef(0.0,-8.0,0.0);
    //drawFloor();

    floorShader.release();



    // draw the grid
    drawGrid();

    glLineWidth(1.5);

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

void Viewport::drawFloor() {
    floorShader.enableAttributeArray(floorVertexAttr1);
    floorShader.setAttributeArray(floorVertexAttr1, GL_FLOAT, &floorVertex[0], 3);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    floorShader.disableAttributeArray(floorVertexAttr1);
}

void Viewport::drawGrid() {
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

