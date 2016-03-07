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
//#include "scenegraph.hpp"

using namespace feather::gl;

// GL DRAWITEM
glDrawItem::glDrawItem(feather::draw::Item* _item, Type _type)
    : m_item(_item),m_type(_type)
{
    m_Uid=_item->uid;
    m_Nid=_item->nid;
}

glDrawItem::~glDrawItem()
{
}


// GL MESH
glMesh::glMesh(feather::draw::Item* _item, Type _type)
    : glDrawItem(_item,glDrawItem::Mesh)
{
    m_Fid=static_cast<feather::draw::Mesh*>(_item)->fid;
}

glMesh::~glMesh()
{

}

void glMesh::init()
{

    // Vertex Shader
    QOpenGLShader* vert = new QOpenGLShader(QOpenGLShader::Vertex);
    vert->compileSourceFile("shaders/vert/mesh.glsl");
    m_pProgram->addShader(vert);

    // Fragment Shader
    QOpenGLShader* frag = new QOpenGLShader(QOpenGLShader::Fragment);
    frag->compileSourceFile("shaders/frag/lambert.glsl");
    m_pProgram->addShader(frag);

    // Geometry Shader
    // QOpenGLShader* geom = new QOpenGLShader(QOpenGLShader::Geometry);
    // geom->compileSourceFile("");
    // m_pProgram->addShader(geom);


    m_pProgram->link();
    m_glVertex = m_pProgram->attributeLocation("vertex");
    m_glColor = m_pProgram->attributeLocation("color");
    m_glMatrix = m_pProgram->uniformLocation("matrix");
    m_glNormal = m_pProgram->attributeLocation("normal");
    m_glView = m_pProgram->uniformLocation("modelview");
    m_glSelected = m_pProgram->uniformLocation("Selected");
    m_glLayerColor = m_pProgram->attributeLocation("LayerColor");
    m_glLightPosition = m_pProgram->attributeLocation("LightPosition");
    m_glLightAmbient = m_pProgram->attributeLocation("LightAmbient");
    m_glLightDiffuse = m_pProgram->attributeLocation("LightDiffuse");
    m_glLightSpecular = m_pProgram->attributeLocation("LightSpecular");
    m_glMaterialAmbient = m_pProgram->attributeLocation("MaterialAmbient");
    m_glMaterialDiffuse = m_pProgram->attributeLocation("MaterialDiffuse");
    m_glMaterialSpecular = m_pProgram->attributeLocation("MaterialSpecular");
    m_glMaterialShininess = m_pProgram->attributeLocation("MaterialShininess");
    m_glCameraPosition = m_pProgram->attributeLocation("CameraPosition");
    m_glShaderDiffuse = m_pProgram->attributeLocation("ShaderDiffuse");

}

void glMesh::build()
{

    feather::FMesh mesh;
    feather::qml::command::get_field_val(m_Uid,m_Nid,m_Fid,mesh);                
        
    uint id=0;                                                             
    int fcount=0; // this is a temp value to test selection                
    //std::for_each(mesh.f.begin(), mesh.f.end(), [this,&mesh,&id,&fcount,&m_aGlei,&m_aGli,&m_aGlc](feather::FFace _face){
    std::for_each(mesh.f.begin(), mesh.f.end(), [this,&mesh,&id,&fcount](feather::FFace _face){

        //for_each(_face.begin(),_face.end(),[&mesh,&m_aGlei](feather::FFacePoint _fp){ m_aGlei.push_back(_fp.v); });
       for_each(_face.begin(),_face.end(),[this,&mesh](feather::FFacePoint _fp){ m_aGlei.push_back(_fp.v); });

        while(id+2 <= _face.size()) {
            if(fcount==3) {
                m_aGlc.push_back(feather::FColorRGBA(1.0,0.0,0.0,1.0));
                m_aGlc.push_back(feather::FColorRGBA(1.0,0.0,0.0,1.0));
                m_aGlc.push_back(feather::FColorRGBA(1.0,0.0,0.0,1.0));
            } else {
                m_aGlc.push_back(feather::FColorRGBA());
                m_aGlc.push_back(feather::FColorRGBA());
                m_aGlc.push_back(feather::FColorRGBA());
            }
            //std::cout << "v" << id << ":" << _face.at(id).v << ",";
            std::cout << "v.y" << id << ":" << mesh.v.at(_face.at(id).v).y << ",";
            m_aV.push_back(mesh.v.at(_face.at(id).v));
            m_aVn.push_back(mesh.vn.at(_face.at(id).vn));
            //glvn.push_back(vn.at(_face.at(id).vn));
            m_aGli.push_back(_face.at(id).v);

            //std::cout << "v" << id+1 << ":" << _face.at(id+1).v << ",";
            m_aV.push_back(mesh.v.at(_face.at(id+1).v));
            m_aVn.push_back(mesh.vn.at(_face.at(id+1).vn));
            //glvn.push_back(vn.at(_face.at(id+1).vn));
            m_aGli.push_back(_face.at(id+1).v);

            if(id+2 < _face.size()) {
                //std::cout << "v" << id+2 << ":" << _face.at(id+2).v << ",";
                m_aV.push_back(mesh.v.at(_face.at(id+2).v));
                m_aVn.push_back(mesh.vn.at(_face.at(id+2).vn));
                //glvn.push_back(vn.at(_face.at(id+2).vn));
                m_aGli.push_back(_face.at(id+2).v);
            } else {
                //std::cout << "v" << 0 << ":" << _face.at(0).v << ",";
                m_aV.push_back(mesh.v.at(_face.at(0).v));
                m_aVn.push_back(mesh.vn.at(_face.at(0).vn));
                //glvn.push_back(vn.at(_face.at(0).vn));
                m_aGli.push_back(_face.at(0).v);
            }

            id=id+2;
        }

        fcount++;
        id=0;

    });

}

void glMesh::draw()
{
    //field::FieldBase* f = feather::scenegraph::get_fieldBase(node.uid,320,3);

    //typedef field::Field<FMesh>* fielddata;
    //fielddata tf = static_cast<fielddata>(f);

    if(m_aV.size() >= 4)
    {
        /*
           QVector3D lpos;
           lpos.setX(10);
           lpos.setY(20);
           lpos.setZ(0);
           */

        m_pProgram->bind();
        //feather::FLayer layer;
        //qml::command::get_layer(m_Uid,layer);
        FColorRGB lcolor = FColorRGB(); //layer.color;
        m_pProgram->setUniformValue(m_glSelected, false);
        m_pProgram->setAttributeValue(m_glLayerColor, QColor(lcolor.int_red(),lcolor.int_green(),lcolor.int_blue()));
        //m_pProgram->setAttributeValue(m_glLightPosition, lpos);
        m_pProgram->setAttributeValue(m_glLightAmbient, QColor(0,0,0));
        m_pProgram->setAttributeValue(m_glLightDiffuse, QColor(255,255,255));
        m_pProgram->setAttributeValue(m_glLightSpecular, QColor(0,0,0));
        m_pProgram->setAttributeValue(m_glMaterialAmbient, QColor(0,0,0));
        m_pProgram->setAttributeValue(m_glMaterialDiffuse, QColor(255,255,255));
        m_pProgram->setAttributeValue(m_glMaterialSpecular, QColor(0,0,0));
        m_pProgram->setAttributeValue(m_glMaterialShininess, 0.5);

        m_pProgram->setUniformValue(m_glMatrix, *m_pView);

        m_pProgram->enableAttributeArray(m_glVertex);
        m_pProgram->enableAttributeArray(m_glColor);
        m_pProgram->enableAttributeArray(m_glNormal);
        m_pProgram->setAttributeArray(m_glVertex, GL_DOUBLE, &m_aV[0], 3);
        m_pProgram->setAttributeArray(m_glColor, GL_FLOAT, &m_aGlc[0], 4);
        m_pProgram->setAttributeArray(m_glNormal, GL_DOUBLE, &m_aVn[0],3);

        int glView=0;
        m_pProgram->setUniformValue(m_glView, glView);

        // SHADED
        glPolygonMode(GL_FRONT, GL_FILL);
        glDrawElements(GL_TRIANGLES, m_aGli.size(), GL_UNSIGNED_INT, &m_aGli[0]);

        // WIREFRAME
        glLineWidth(1.5);
        glView=1;
        m_pProgram->setUniformValue(m_glView, glView);

        glPolygonMode(GL_FRONT, GL_LINE);
        glDrawElements(GL_TRIANGLES, m_aGli.size(), GL_UNSIGNED_INT, &m_aGli[0]);

    }

    m_pProgram->disableAttributeArray(m_glVertex);
    m_pProgram->disableAttributeArray(m_glColor);
    m_pProgram->disableAttributeArray(m_glNormal);
    m_pProgram->release();

}

void glMesh::update()
{
}


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
    const qreal fov=85.0,near=0.5, far=100.0;
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
    //m_View.translate(m_Translate.x,m_Translate.y,m_Translate.z);
    m_View.translate(0,0,-10);
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
    //m_aGlInfo.clear();

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

void glScene::nodeInit(int uid)
{
    //feather::FGlInfo info;
    //info.program = new QOpenGLShaderProgram;
    //info.view = &m_apCameras.at(0)->view();
    //info.uid = uid;

    //qml::command::gl_init(uid,info);
    //m_aGlInfo.push_back(info);
}

void glScene::nodesAddedInit()
{
    std::vector<unsigned int> uids;
    qml::command::nodes_added(uids);
    for_each(uids.begin(), uids.end(), [this](unsigned int& uid){
        //std::cout << "gl init for uid:" << uid << std::endl;
        nodeInit(uid);
    });
    // since we only have one viewport now, this will do
    // but later we will need to move this for multiple
    // viewports
    qml::command::nodes_updated();
}

void glScene::addItems(unsigned int uid)
{
    feather::status pass;
    unsigned int nid = feather::qml::command::get_node_id(uid,pass);
    feather::draw::DrawItems items;
    feather::qml::command::get_node_draw_items(nid,items);
    std::cout << "add draw item " << uid << std::endl;
    
    m_apItems.clear();
    
    for(auto item : items) {
        item->uid=uid;
        item->nid=nid;
        switch(item->type){
            case feather::draw::Item::Mesh:
                std::cout << "add Mesh\n";
                m_apItems.push_back(new glMesh(item));
                m_apItems.at(m_apItems.size()-1)->setProgram(m_pProgram);
                m_apItems.at(m_apItems.size()-1)->setView(m_pView);
                m_apItems.at(m_apItems.size()-1)->init();
                m_apItems.at(m_apItems.size()-1)->build();
                break;
            case feather::draw::Item::Line:
                std::cout << "add Line\n";
                //m_apItems.append(new Line(item,this));
                break;
            case feather::draw::Item::PerspCamera:
                std::cout << "updating Perspective Camear draw item\n";
                //m_apItems.append(new PerspCamera(item,this));
                break;
            default:
                std::cout << "nothing built\n";
        }
        //m_apItems.at(m_apItems.size()-1)->draw();
    }
}

void glScene::nodesRemovedInit()
{
    std::vector<unsigned int> uids;
    qml::command::nodes_added(uids);
    for_each(uids.begin(), uids.end(), [this](unsigned int& uid){
        //std::cout << "gl init for uid:" << uid << std::endl;
        nodeInit(uid);
    });
    // since we only have one viewport now, this will do
    // but later we will need to move this for multiple
    // viewports
    qml::command::nodes_updated();
}

void glScene::draw(int width, int height)
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

    // Draw DrawItems
    for(auto n : m_apItems){
         n->setProgram(m_pProgram);
         n->setView(m_pView);
         m_pView = &m_apCameras.at(0)->view();
 
         switch(n->item()->type){
            case feather::draw::Item::Mesh:
                std::cout << "draw Mesh\n";
               static_cast<glMesh*>(n)->draw();
                break;
            case feather::draw::Item::Line:
                std::cout << "draw Line\n";
                //m_apItems.append(new Line(item,this));
                break;
            case feather::draw::Item::PerspCamera:
                std::cout << "draw Perspective Camera\n";
                //m_apItems.append(new PerspCamera(item,this));
                break;
            default:
                std::cout << "nothing drawn\n";
        }
    }


    /* 
    while(maxUid > minUid) {
        if(qml::command::node_exists(maxUid))
            qml::command::gl_draw(maxUid,info);
        --maxUid;
    }
    */

    glEnable(GL_MULTISAMPLE);

    /*
    for_each(m_aGlInfo.begin(), m_aGlInfo.end(), [](FGlInfo& info){
        // sanity check
        if(qml::command::node_exists(info.uid))
            qml::command::gl_draw(info.uid,info);
    });
    */

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

void glScene::draw_grid()
{
    m_GridProgram.enableAttributeArray(m_GridVAttr);
    m_GridProgram.setAttributeArray(m_GridVAttr, GL_DOUBLE, &m_aGrid[0], 3);
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glDrawArrays(GL_LINES, 0, 84);
    m_GridProgram.disableAttributeArray(m_GridVAttr);
}

void glScene::draw_axis()
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


void glScene::make_grid() {
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
