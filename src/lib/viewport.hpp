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

class Viewport
{

    public:
        Viewport();
        ~Viewport();

        void initialize();
        void render();
        void drawMesh();

    private:
        QSize m_viewportSize;
        QOpenGLShaderProgram program1;
        int vertexAttr1;
        int normalAttr1;
        int colorUniform1;
        int matrixUniform1;
        float m_fAngle;
        float m_fScale;
};


#endif
