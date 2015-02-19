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

// GL CAMERA

using namespace feather;

gl::glCamera::glCamera()
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
    m_View.translate(0.0,1.0,m_camZoom);
    m_View.rotate(m_camTiltAngle,1.0,0.0,0.0);
    m_View.rotate(m_camPitchAngle,0.0,1.0,0.0);
    m_View.rotate(0,0.0,0.0,1.0);
}

void gl::glCamera::rotate(int x, int y)
{
    m_camPitchAngle += x;
    m_camTiltAngle -= y;
}

void gl::glCamera::zoom(int z)
{
    m_camZoom += (float)z/240.0;
}


// GL MESH

gl::glMesh::glMesh()
{


}

gl::glMesh::~glMesh()
{

}

void gl::glMesh::init()
{

}

void gl::glMesh::draw()
{

}


// GL SCENE

gl::glScene::glScene()
{
    m_apCameras.push_back(new feather::gl::glCamera());
}

gl::glScene::~glScene()
{

}

void gl::glScene::init()
{

}

void gl::glScene::draw()
{

}

