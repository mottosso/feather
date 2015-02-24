// =====================================================================================
// 
//       Filename:  gl_scene.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  02/18/2015 09:02:12 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#include "gl_scene.hpp"
#include "commands.hpp"

// GL CAMERA

using namespace feather;

gl::glCamera::glCamera(): m_CamPitchAngle(0), m_CamTiltAngle(0), m_CamZoom(-6.0), m_Scale(1)
{

}

gl::glCamera::~glCamera()
{

}

void gl::glCamera::init()
{

}

void gl::glCamera::draw(int width, int height)
{
    const qreal fov=25.0,near=0.1, far=60.0;
    qreal aspect=(float)width/(float)height;

    m_View.setToIdentity();
    m_View.perspective(fov,aspect,near,far); 
    //m_View.ortho(-1.0/aspect,1.0/aspect,-1.0*aspect,1.0*aspect,1.0,20.0);
    m_View.translate(0.0,1.0,m_CamZoom);
    m_View.rotate(m_CamTiltAngle,1.0,0.0,0.0);
    m_View.rotate(m_CamPitchAngle,0.0,1.0,0.0);
    m_View.rotate(0,0.0,0.0,1.0);
}

void gl::glCamera::rotate(int x, int y)
{
    m_CamPitchAngle += x;
    m_CamTiltAngle -= y;
}

void gl::glCamera::zoom(int z)
{
    m_CamZoom += (float)z/240.0;
}

// GL LIGHT

gl::glLight::glLight()
{
    m_Position.setX(4);
    m_Position.setY(4);
    m_Position.setZ(4);

    m_pFragShader = new QOpenGLShader(QOpenGLShader::Fragment);
    m_pVertShader = new QOpenGLShader(QOpenGLShader::Vertex);
}

gl::glLight::~glLight()
{
    delete m_pFragShader;
    delete m_pVertShader;
}

void gl::glLight::init()
{
    m_pFragShader->compileSourceFile("shaders/frag/wireframe.glsl");
    m_pVertShader->compileSourceFile("shaders/vert/light.glsl");

    m_Program.addShader(m_pFragShader);
    m_Program.addShader(m_pVertShader);

    m_Program.link();

    m_Vertex = m_Program.attributeLocation("vertex");
    m_Matrix = m_Program.uniformLocation("matrix");
    m_PositionId = m_Program.attributeLocation("position");
 
    // Point Mesh 
    m_aModel.push_back(FVertex3D(0.0,1.0,0.0));
    m_aModel.push_back(FVertex3D(0.0,-1.0,0.0));
    m_aModel.push_back(FVertex3D(1.0,0.0,0.0));
    m_aModel.push_back(FVertex3D(-1.0,0.0,0.0));
    m_aModel.push_back(FVertex3D(0.0,0.0,1.0));
    m_aModel.push_back(FVertex3D(0.0,0.0,-1.0));
    m_aModel.push_back(FVertex3D(0.75,0.0,-0.75));
    m_aModel.push_back(FVertex3D(-0.75,0.0,0.75));
    m_aModel.push_back(FVertex3D(-0.75,0.0,0.75));
    m_aModel.push_back(FVertex3D(0.75,0.0,-0.75));
    m_aModel.push_back(FVertex3D(0.75,0.75,0.0));
    m_aModel.push_back(FVertex3D(-0.75,-0.75,0.0));
    m_aModel.push_back(FVertex3D(0.0,0.75,0.75));
    m_aModel.push_back(FVertex3D(0.0,-0.75,-0.75));
    m_aModel.push_back(FVertex3D(-0.75,0.75,0.0));
    m_aModel.push_back(FVertex3D(0.75,-0.75,0.0));
    m_aModel.push_back(FVertex3D(0.0,0.75,-0.75));
    m_aModel.push_back(FVertex3D(0.0,-0.75,0.75));
    m_aModel.push_back(FVertex3D(0.75,0.75,0.75));
    m_aModel.push_back(FVertex3D(-0.75,-0.75,-0.75));
    m_aModel.push_back(FVertex3D(-0.75,0.75,-0.75));
    m_aModel.push_back(FVertex3D(0.75,-0.75,0.75));
    m_aModel.push_back(FVertex3D(0.75,0.75,-0.75));
    m_aModel.push_back(FVertex3D(-0.75,-0.75,0.75));
    m_aModel.push_back(FVertex3D(-0.75,0.75,0.75));
    m_aModel.push_back(FVertex3D(0.75,-0.75,-0.75));
}

void gl::glLight::draw(QMatrix4x4& view)
{
    m_Program.bind();
    m_Program.setAttributeValue(m_PositionId, m_Position);
    m_Program.setUniformValue(m_Matrix, view);
    m_Program.enableAttributeArray(m_Vertex);
    m_Program.setAttributeArray(m_Vertex, GL_FLOAT, &m_aModel[0], 3);
    glLineWidth(2);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawArrays(GL_LINES, 0, m_aModel.size());
    m_Program.disableAttributeArray(m_Vertex);
    m_Program.release();
}

// GL MESH

gl::glMesh::glMesh(glLight* light)
{
    m_pLight = light;
    m_pFillShader = new QOpenGLShader(QOpenGLShader::Fragment);
    m_pEdgeShader = new QOpenGLShader(QOpenGLShader::Fragment);
    m_pVertShader = new QOpenGLShader(QOpenGLShader::Vertex);
    m_ShaderDiffuse = QColor(175,175,175);
}

gl::glMesh::~glMesh()
{

}

void gl::glMesh::init()
{
    m_pFillShader->compileSourceFile("shaders/frag/lambert.glsl");
    m_pVertShader->compileSourceFile("shaders/vert/mesh.glsl");

    m_Program.addShader(m_pFillShader);
    m_Program.addShader(m_pVertShader);

    m_Program.link();

    m_Vertex = m_Program.attributeLocation("vertex");
    m_Matrix = m_Program.uniformLocation("matrix");
    m_Normal = m_Program.attributeLocation("normal");
    m_LightPositionId = m_Program.attributeLocation("lightposition");
    m_ShaderDiffuseId = m_Program.attributeLocation("shader_diffuse");

    // test Cube Vertex
    // Front 
    m_apV.push_back(FVertex3D(1.0,1.0,1.0));
    m_apV.push_back(FVertex3D(1.0,-1.0,1.0));
    m_apV.push_back(FVertex3D(-1.0,-1.0,1.0));
    m_apV.push_back(FVertex3D(-1.0,1.0,1.0));
    // R Side
    m_apV.push_back(FVertex3D(1.0,1.0,1.0));
    m_apV.push_back(FVertex3D(1.0,1.0,-1.0));
    m_apV.push_back(FVertex3D(1.0,-1.0,-1.0));
    m_apV.push_back(FVertex3D(1.0,-1.0,1.0));
    // L Side
    m_apV.push_back(FVertex3D(-1.0,1.0,1.0));
    m_apV.push_back(FVertex3D(-1.0,-1.0,1.0));
    m_apV.push_back(FVertex3D(-1.0,-1.0,-1.0));
    m_apV.push_back(FVertex3D(-1.0,1.0,-1.0));
    // Back 
    m_apV.push_back(FVertex3D(1.0,1.0,-1.0));
    m_apV.push_back(FVertex3D(-1.0,1.0,-1.0));
    m_apV.push_back(FVertex3D(-1.0,-1.0,-1.0));
    m_apV.push_back(FVertex3D(1.0,-1.0,-1.0));
    // Top
    m_apV.push_back(FVertex3D(1.0,1.0,1.0));
    m_apV.push_back(FVertex3D(-1.0,1.0,1.0));
    m_apV.push_back(FVertex3D(-1.0,1.0,-1.0));
    m_apV.push_back(FVertex3D(1.0,1.0,-1.0));
    // Bottom 
    m_apV.push_back(FVertex3D(1.0,-1.0,1.0));
    m_apV.push_back(FVertex3D(1.0,-1.0,-1.0));
    m_apV.push_back(FVertex3D(-1.0,-1.0,-1.0));
    m_apV.push_back(FVertex3D(-1.0,-1.0,1.0));

    // test Cube Normals
    // Front
    m_apVn.push_back(FVertex3D(0.0,0.0,1.0));
    m_apVn.push_back(FVertex3D(0.0,0.0,1.0));
    m_apVn.push_back(FVertex3D(0.0,0.0,1.0));
    m_apVn.push_back(FVertex3D(0.0,0.0,1.0));
    // Left
    m_apVn.push_back(FVertex3D(-1.0,0.0,0.0));
    m_apVn.push_back(FVertex3D(-1.0,0.0,0.0));
    m_apVn.push_back(FVertex3D(-1.0,0.0,0.0));
    m_apVn.push_back(FVertex3D(-1.0,0.0,0.0));
    // Right 
    m_apVn.push_back(FVertex3D(1.0,0.0,0.0));
    m_apVn.push_back(FVertex3D(1.0,0.0,0.0));
    m_apVn.push_back(FVertex3D(1.0,0.0,0.0));
    m_apVn.push_back(FVertex3D(1.0,0.0,0.0));
    // Back 
    m_apVn.push_back(FVertex3D(0.0,0.0,-1.0));
    m_apVn.push_back(FVertex3D(0.0,0.0,-1.0));
    m_apVn.push_back(FVertex3D(0.0,0.0,-1.0));
    m_apVn.push_back(FVertex3D(0.0,0.0,-1.0));
    // Top 
    m_apVn.push_back(FVertex3D(0.0,1.0,0.0));
    m_apVn.push_back(FVertex3D(0.0,1.0,0.0));
    m_apVn.push_back(FVertex3D(0.0,1.0,0.0));
    m_apVn.push_back(FVertex3D(0.0,1.0,0.0));
    // Bottom 
    m_apVn.push_back(FVertex3D(0.0,-1.0,0.0));
    m_apVn.push_back(FVertex3D(0.0,-1.0,0.0));
    m_apVn.push_back(FVertex3D(0.0,-1.0,0.0));
    m_apVn.push_back(FVertex3D(0.0,-1.0,0.0));
}

void gl::glMesh::draw(QMatrix4x4& view)
{
    m_Program.bind();
    m_Program.setAttributeValue(m_LightPositionId, m_pLight->position());
 
    m_Program.setUniformValue(m_Matrix, view);
    m_Program.enableAttributeArray(m_Vertex);
    m_Program.enableAttributeArray(m_Normal);
    m_Program.setAttributeArray(m_Vertex, GL_FLOAT, &m_apV[0], 3);
    m_Program.setAttributeArray(m_Normal, GL_FLOAT, &m_apVn[0],3);

    m_ShaderDiffuse.setRgb(100,100,100);
    m_Program.setAttributeValue(m_ShaderDiffuseId, m_ShaderDiffuse);
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);
    glDrawArrays(GL_QUADS, 0, m_apV.size());

    m_ShaderDiffuse.setRgb(0,0,0);
    m_Program.setAttributeValue(m_ShaderDiffuseId, m_ShaderDiffuse);
    glLineWidth(4.5);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawArrays(GL_QUADS, 0, m_apV.size());

    m_Program.disableAttributeArray(m_Normal);
    m_Program.disableAttributeArray(m_Vertex);
    m_Program.release();
}


// GL SCENE

gl::glScene::glScene()
{
    m_apCameras.push_back(new gl::glCamera());
    m_apLights.push_back(new gl::glLight());
    m_apMeshes.push_back(new gl::glMesh(m_apLights.at(0)));
}

gl::glScene::~glScene()
{

}

void gl::glScene::init()
{
    m_GridProgram.addShaderFromSourceCode(QOpenGLShader::Vertex,
            "attribute highp vec4 vertex;\n"
            "uniform mediump mat4 matrix;\n"
            "varying mediump vec4 color;\n"
            "void main(void)\n"
            "{\n"
            "gl_Position = matrix * vertex;\n"
            "}");

    m_GridProgram.addShaderFromSourceCode(QOpenGLShader::Fragment,
            "varying mediump vec4 color;\n"
            "void main(void)\n"
            "{\n"
            "gl_FragColor = vec4(0.0,0.0,0.0,1.0);\n"
            "}");

    m_GridProgram.link();

    // Axis 
    m_AxisProgram.addShaderFromSourceCode(QOpenGLShader::Vertex,
            "attribute highp vec4 vertex;\n"
            "uniform mediump mat4 matrix;\n"
            "varying mediump vec4 color;\n"
            "void main(void)\n"
            "{\n"
            "gl_Position = matrix * vertex;\n"
            "}");

    m_AxisProgram.link();

    m_GridVAttr = m_GridProgram.attributeLocation("vertex");
    m_AxisVAttr = m_AxisProgram.attributeLocation("vertex");
    m_GridMAttr = m_GridProgram.uniformLocation("matrix");
    m_AxisMAttr = m_AxisProgram.uniformLocation("matrix");

    // make the grid
    make_grid();

    m_aAxis.push_back(FVertex3D(0,0,0));
    m_aAxis.push_back(FVertex3D(10,0,0)); // X
    m_aAxis.push_back(FVertex3D(0,0,0));
    m_aAxis.push_back(FVertex3D(0,10,0)); // Y
    m_aAxis.push_back(FVertex3D(0,0,0));
    m_aAxis.push_back(FVertex3D(0,0,10)); // Z

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    m_apLights.at(0)->init();
    m_apMeshes.at(0)->init();
}

void gl::glScene::draw(int width, int height)
{
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

    m_apMeshes.at(0)->draw(m_apCameras.at(0)->view());

    m_apLights.at(0)->draw(m_apCameras.at(0)->view());

    // draw the axis 
    m_AxisProgram.bind();
    m_AxisProgram.setUniformValue(m_AxisMAttr, m_apCameras.at(0)->view());
    draw_axis();
    m_AxisProgram.release();

    // draw the grid
    m_GridProgram.bind();
    m_GridProgram.setUniformValue(m_GridMAttr, m_apCameras.at(0)->view());
    draw_grid();
    m_GridProgram.release();

    // draw each node
    feather::qml::command::draw_sg(m_apCameras.at(0)->view());
     
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    m_apCameras.at(0)->draw(width,height);
}

void gl::glScene::draw_grid()
{
    m_GridProgram.enableAttributeArray(m_GridVAttr);
    m_GridProgram.setAttributeArray(m_GridVAttr, GL_FLOAT, &m_aGrid[0], 3);
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glDrawArrays(GL_LINES, 0, 84);
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    m_GridProgram.disableAttributeArray(m_GridVAttr);
}

void gl::glScene::draw_axis()
{
    m_AxisProgram.enableAttributeArray(m_AxisVAttr);
    m_AxisProgram.setAttributeArray(m_AxisVAttr, GL_FLOAT, &m_aAxis[0], 3);
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
    m_AxisProgram.disableAttributeArray(m_AxisVAttr);
}


void gl::glScene::make_grid() {
    int pos = -10;

    for(int i=0; i <= 20; i++)
    {
        m_aGrid.push_back(FVertex3D(-10,0,pos));
        m_aGrid.push_back(FVertex3D(10,0,pos));
        pos += 1;
    }

    pos = -10;
 
    for(int i=0; i <= 20; i++)
    {
        m_aGrid.push_back(FVertex3D(pos,0,-10));
        m_aGrid.push_back(FVertex3D(pos,0,10));
        pos += 1;
    }
 
}

