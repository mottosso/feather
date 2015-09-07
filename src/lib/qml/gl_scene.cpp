/***********************************************************************
 *
 * Filename: gl_scene.cpp
 *
 * Description: Draws the scenegraph.
 *
 * Copyright (C) 2015 Richard Layman, rlayman2000@yahoo.com 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ***********************************************************************/

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
    const qreal fov=25.0,near=0.5, far=100.0;
    qreal aspect=-(double)width/(double)height;
    //std::cout << "camera width=" << width << " height=" << height << " aspect ratio=" << aspect << std::endl;

    m_View.setToIdentity();
    m_View.perspective(fov,aspect,near,far); 
    //m_View.ortho(-1.0/aspect,1.0/aspect,-1.0*aspect,1.0*aspect,1.0,20.0);
    // fix location
    m_View.rotate(180,0.0,0.0,1.0); // match qt's view to gl
    m_View.translate(0.0,-1.0,m_CamZoom);
    m_View.rotate(m_CamTiltAngle,-1.0,0.0,0.0);
    m_View.rotate(m_CamPitchAngle,0.0,1.0,0.0);
    m_View.rotate(0,0.0,0.0,1.0);
    m_View.translate(m_Translate.x,m_Translate.y,m_Translate.z);
}

void gl::glCamera::move(double x, double y, double z)
{
    m_Translate.x += x;
    m_Translate.y += y;
    m_Translate.z += z;
}

void gl::glCamera::rotate(int x, int y)
{
    m_CamPitchAngle += (double)x;
    m_CamTiltAngle -= (double)y;
}

void gl::glCamera::zoom(int z)
{
    m_CamZoom += (double)z/240.0;
}


// GL SCENE

gl::glScene::glScene() :
    m_pView(new QMatrix4x4),
    m_pProgram(new QOpenGLShaderProgram),
    m_showAxis(true),
    m_showGrid(true),
    m_ShadingMode(SHADED),
    m_SelectionMode(OBJECT)
{
    m_apCameras.push_back(new gl::glCamera());
   
    /* 
    m_GlInfo.view = m_pView;
    m_GlInfo.program = m_pProgram;
    m_GlInfo.view = &m_apCameras.at(0)->view();
    */
}

gl::glScene::~glScene()
{
    for(uint i=0; i < m_apCameras.size(); i++) {
        delete m_apCameras[i];
    }
    m_apCameras.clear();

    delete m_pView;
    m_pView=0;
    delete m_pProgram;
    m_pProgram=0;
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

    int minUid = qml::command::get_min_uid();
    int maxUid = qml::command::get_max_uid();

    /*
    feather::FGlInfo info;
    info.view = m_pView;
    info.program = m_pProgram;
    info.view = &m_apCameras.at(0)->view();
    */

    // clear out all the instances of GlInfo
    m_aGlInfo.clear();

    while(maxUid > minUid) {
        if(qml::command::node_exists(maxUid))
            nodeInit(maxUid);
        --maxUid;
    }

    glFrontFace(GL_CW);
    glCullFace(GL_BACK);

    // This is for multisample - but it currently doesn't work
    int bufs;
    int samples;
    glHint(GL_SAMPLES, 8);
    glGetIntegerv(GL_SAMPLE_BUFFERS, &bufs);
    glGetIntegerv(GL_SAMPLES, &samples);

    // smoothing
    //glShadeModel(GL_FLAT);                    // shading mathod: GL_SMOOTH or GL_FLAT
    //glPixelStorei(GL_UNPACK_ALIGNMENT, 4);      // 4-byte pixel alignment

    // enable /disable features
    /*
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    //glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
     //glClearColor(0.75, 0.75, 0.75, 0.0);
    glClearStencil(0);                          // clear stencil buffer
    */
    glClearDepth(1.0f);                         // 0 is near, 1 is far
    glDepthFunc(GL_LEQUAL);
}

void gl::glScene::nodeInit(int uid)
{
    feather::FGlInfo info;
    //info.view = m_pView;
    //info.program = m_pProgram;
    info.program = new QOpenGLShaderProgram;
    info.view = &m_apCameras.at(0)->view();
    info.uid = uid;

    qml::command::gl_init(uid,info);
    m_aGlInfo.push_back(info);
}

void gl::glScene::nodesAddedInit()
{
    std::vector<int> uids;
    qml::command::nodes_added(uids);
    for_each(uids.begin(), uids.end(), [this](int& uid){
        //std::cout << "gl init for uid:" << uid << std::endl;
        nodeInit(uid);
    });
    // since we only have one viewport now, this will do
    // but later we will need to move this for multiple
    // viewports
    qml::command::nodes_updated();
}

void gl::glScene::draw(int width, int height)
{
    glViewport(0,0,width,height);

    /*
    glClear(GL_STENCIL_BUFFER_BIT);
    glStencilFunc(GL_ALWAYS, 0x1, 0x1);
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
    */

    glDepthMask(true);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glClearStencil(0);                          // clear stencil buffer
    glClearDepth(1.0f);                         // 0 is near, 1 is far

    // smoothing
    glEnable(GL_DEPTH_TEST);
    /*
    glEnable(GL_STENCIL_TEST);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glEnable(GL_BLEND);
    //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glDepthFunc(GL_LEQUAL);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    */
   //glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE);

    /*
    // turn off smoothing
    if ( m_GlMode_Enum != SELECTION ) {
        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
        glHint(GL_POLYGON_SMOOTH_HINT, GL_DONT_CARE);
    }
    */

    // this does nothing
    //glShadeModel(GL_SMOOTH);                    // shading mathod: GL_SMOOTH or GL_FLAT
 
    //int minUid = qml::command::get_min_uid();
    //int maxUid = qml::command::get_max_uid();

    // Draw SG Nodes
    /*
    feather::FGlInfo info;
    info.view = m_pView;
    info.program = m_pProgram;
    m_pView = &m_apCameras.at(0)->view();
    */
    //info.view = m_pView;

    /* 
    while(maxUid > minUid) {
        if(qml::command::node_exists(maxUid))
            qml::command::gl_draw(maxUid,info);
        --maxUid;
    }
    */

    glEnable(GL_MULTISAMPLE);

    for_each(m_aGlInfo.begin(), m_aGlInfo.end(), [](FGlInfo& info){
        // sanity check
        if(qml::command::node_exists(info.uid))
            qml::command::gl_draw(info.uid,info);
    });

    // draw the axis 
    if(m_showAxis){
        m_AxisProgram.bind();
        m_AxisProgram.setUniformValue(m_AxisMAttr, m_apCameras.at(0)->view());
        draw_axis();
        m_AxisProgram.release();
    }

    // draw the grid
    if(m_showGrid){
        m_GridProgram.bind();
        m_GridProgram.setUniformValue(m_GridMAttr, m_apCameras.at(0)->view());
        draw_grid();
        m_GridProgram.release();
    }

    glDisable(GL_MULTISAMPLE);

    // draw each node
    //feather::qml::command::draw_sg(m_apCameras.at(0)->view());
    glDisable(GL_DEPTH_TEST);
    /*
    glDisable(GL_STENCIL_TEST);
    //glDisable(GL_LIGHTING);
    //glDisable(GL_TEXTURE_2D);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_POLYGON_SMOOTH);
    glDisable(GL_BLEND);
    */

    m_apCameras.at(0)->draw(width,height);
}

void gl::glScene::draw_grid()
{
    m_GridProgram.enableAttributeArray(m_GridVAttr);
    m_GridProgram.setAttributeArray(m_GridVAttr, GL_DOUBLE, &m_aGrid[0], 3);
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glDrawArrays(GL_LINES, 0, 84);
    m_GridProgram.disableAttributeArray(m_GridVAttr);
}

void gl::glScene::draw_axis()
{
    m_AxisProgram.enableAttributeArray(m_AxisVAttr);
    m_AxisProgram.setAttributeArray(m_AxisVAttr, GL_DOUBLE, &m_aAxis[0], 3);
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glLineWidth(4.25);
    glColor3f(1.0,0.0,0.0);
    glDrawArrays(GL_LINES, 0, 2);
    glColor3f(0.0,1.0,0.0);
    glDrawArrays(GL_LINES, 2, 2);
    glColor3f(0.0,0.0,1.0);
    glDrawArrays(GL_LINES, 4, 2);
    glLineWidth(1.25);
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
