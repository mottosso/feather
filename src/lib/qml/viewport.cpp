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

// MAIN VIEWPORT

Viewport::Viewport()
{
    m_pScene = new feather::gl::glScene();
    m_CurrentCamera = 0;
}

Viewport::~Viewport()
{
    delete m_pScene;
}

void Viewport::initialize(int width, int height)
{
    m_pScene->init();
}

void Viewport::render(int width, int height)
{
    m_pScene->draw(width,height);
}

void Viewport::rotateCamera(int x, int y)
{
    m_pScene->camera(m_CurrentCamera)->rotate(x,y);
}

void Viewport::zoomCamera(int z)
{
    m_pScene->camera(m_CurrentCamera)->zoom(z);
}
