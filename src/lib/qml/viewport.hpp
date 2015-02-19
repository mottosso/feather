// =====================================================================================
// 
//       Filename:  viewport.hpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/14/2014 04:12:34 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#ifndef VIEWPORT_HPP 
#define VIEWPORT_HPP

#include "deps.hpp"
#include "qml_deps.hpp"
#include "types.hpp"
#include "gl_scene.hpp"

class Viewport
{

    public:
        Viewport();
        ~Viewport();

        void initialize(int width, int height);
        void render(int width, int height);
        void rotateCamera(int x, int y);
        void zoomCamera(int z);

    private:
        QSize m_viewportSize;
        feather::gl::glScene* m_pScene;    
        int m_CurrentCamera;
};


#endif
