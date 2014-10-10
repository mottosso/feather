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
#include "commands.hpp"

struct Vector3D
{
    Vector3D(float _x=0, float _y=0, float _z=0): x(_x),y(_y),z(_z){};
    float x,y,z;
};

std::vector<Vector3D> points;
std::vector<Vector3D> grid;
std::vector<Vector3D> axis;
//std::vector<Vector3D> axisX;
//std::vector<Vector3D> axisY;
//std::vector<Vector3D> axisZ;

Viewport::Viewport() : m_camPitchAngle(0),m_camTiltAngle(0),m_camZoom(-6.0),m_fScale(1),r(0)
{

}

Viewport::~Viewport()
{
    delete meshShader;
    delete gridShader;
    delete gridFragShader;
    delete greenShader;
    delete axisVShader;
}

void Viewport::initialize(int width, int height)
{
    // Test
    QOpenGLShader *vshader1 = new QOpenGLShader(QOpenGLShader::Vertex, &program1);
    vshader1->compileSourceFile("mesh.glsl");

    QOpenGLShader *fshader1 = new QOpenGLShader(QOpenGLShader::Fragment, &program1);
    fshader1->compileSourceFile("texture.glsl");

    program1.addShader(vshader1);
    program1.addShader(fshader1);
    program1.link();

    // Grid
    gridShader = new QOpenGLShader(QOpenGLShader::Vertex, &gridProgram);
    gridShader->compileSourceFile("grid.glsl");
 
    gridFragShader = new QOpenGLShader(QOpenGLShader::Fragment, &gridProgram);
    gridFragShader->compileSourceFile("grid_frag.glsl");

    //greenShader = new QOpenGLShader(QOpenGLShader::Fragment, &gridProgram);
    //greenShader->compileSourceFile("green.glsl");

    gridProgram.addShader(gridShader);
    gridProgram.addShader(gridFragShader);
    gridProgram.link();

    // Axis 
    axisVShader = new QOpenGLShader(QOpenGLShader::Vertex, &axisProgram);
    axisVShader->compileSourceFile("axis.glsl"); 

    axisProgram.addShader(axisVShader);
    axisProgram.link();

    //initTextures();

    // use these to access variable in the glsl
    vertexAttr1 = program1.attributeLocation("vertex");
    texture = program1.uniformLocation("tex");
    //texcoord = program1.uniformLocation("texcoord");
    gridVAttr = gridProgram.attributeLocation("vertex");
    axisVAttr = axisProgram.attributeLocation("vertex");
    //normalAttr1 = program1.attributeLocation("normal");
    //colorUniform1 = program1.uniformLocation("color");
    matrixUniform1 = program1.uniformLocation("matrix");
    gridMAttr = gridProgram.uniformLocation("matrix");
    axisMAttr = axisProgram.uniformLocation("matrix");


    points.push_back(Vector3D(-1,-1,0));
    points.push_back(Vector3D(1,-1,0));
    points.push_back(Vector3D(-1,1,0));
    points.push_back(Vector3D(1,1,0));

    // make the grid
    makeGrid();
    /*
    grid.push_back(Vector3D(-1,0,-1));
    grid.push_back(Vector3D(1,0,-1));
    grid.push_back(Vector3D(-1,0,1));
    grid.push_back(Vector3D(1,0,1));
    */

    axis.push_back(Vector3D(0,0,0));
    axis.push_back(Vector3D(10,0,0)); // X
    axis.push_back(Vector3D(0,0,0));
    axis.push_back(Vector3D(0,10,0)); // Y
    axis.push_back(Vector3D(0,0,0));
    axis.push_back(Vector3D(0,0,10)); // Z

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    /*
    const qreal fov=45.0,near=0.01, far=20.0;
    qreal aspect=(float)width/(float)height;

    pview.setToIdentity();
    pview.perspective(fov,aspect,near,far); 
    pview.lookAt(QVector3D(1.0,2.0,6.0),QVector3D(0,0,0),QVector3D(0,-1,0)); 
    */
}

void Viewport::render(int width, int height)
{

    const qreal fov=25.0,near=0.1, far=60.0;
    qreal aspect=(float)width/(float)height;

    pview.setToIdentity();
    pview.perspective(fov,aspect,near,far); 
    //pview.ortho(-1.0/aspect,1.0/aspect,-1.0*aspect,1.0*aspect,1.0,20.0);
    pview.translate(0.0,1.0,m_camZoom);
    pview.rotate(m_camTiltAngle,1.0,0.0,0.0);
    pview.rotate(m_camPitchAngle,0.0,1.0,0.0);
    pview.rotate(0,0.0,0.0,1.0);

    r=r+0.1; 

    glDepthMask(true);

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glFrontFace(GL_CW);
    glCullFace(GL_FRONT);
    //glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);

    // draw test plane
    program1.bind();
    program1.setUniformValue(matrixUniform1, pview);
    program1.setUniformValue(texture,0);
    drawMesh();
    program1.release();

    // draw the axis 
    axisProgram.bind();
    axisProgram.setUniformValue(axisMAttr, pview);
    drawAxis();
    axisProgram.release();

    // draw the grid
    gridProgram.bind();
    gridProgram.setUniformValue(gridMAttr, pview);
    drawGrid();
    gridProgram.release();

    // draw each node
    feather::qml::command::draw_sg(pview);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
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

void Viewport::makeGrid() {
    int pos = -10;

    for(int i=0; i <= 20; i++)
    {
        grid.push_back(Vector3D(-10,0,pos));
        grid.push_back(Vector3D(10,0,pos));
        pos += 1;
    }

    pos = -10;
 
    for(int i=0; i <= 20; i++)
    {
        grid.push_back(Vector3D(pos,0,-10));
        grid.push_back(Vector3D(pos,0,10));
        pos += 1;
    }
 
}

void Viewport::drawGrid() {
    gridProgram.enableAttributeArray(gridVAttr);
    gridProgram.setAttributeArray(gridVAttr, GL_FLOAT, &grid[0], 3);
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glDrawArrays(GL_LINES, 0, 84);
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    gridProgram.disableAttributeArray(gridVAttr);
}

void Viewport::drawAxis() {
    axisProgram.enableAttributeArray(axisVAttr);
    axisProgram.setAttributeArray(axisVAttr, GL_FLOAT, &axis[0], 3);
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glLineWidth(2.25);
    glColor3f(1.0,0.0,0.0);
    glDrawArrays(GL_LINES, 0, 2);
    glColor3f(0.0,1.0,0.0);
    glDrawArrays(GL_LINES, 2, 2);
    glColor3f(0.0,0.0,1.0);
    glDrawArrays(GL_LINES, 4, 2);
    glLineWidth(1.25);
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    axisProgram.disableAttributeArray(axisVAttr);
}

void Viewport::initTextures()
{
    // Loading texture unit 0
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    //texture = bindTexture(QImage("texture.png"));
    //glBindTexture(GL_TEXTURE_2D, texture);
    //glBindSampler(0, linearFiltering);

    // Set nearest filtering mode for texture minification
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Set bilinear filtering mode for texture magnification
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void Viewport::rotateCamera(int x, int y)
{
    m_camPitchAngle += x;
    m_camTiltAngle -= y;
}

void Viewport::zoomCamera(int z)
{
    m_camZoom += (float)z/240.0;
}
