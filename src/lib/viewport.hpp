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

        void initialize(int width, int height);
        void render();
        void drawMesh();
        void drawFloor();

    private:
        QSize m_viewportSize;
        QOpenGLShaderProgram program1;
        QOpenGLShaderProgram floorShader;
        int vertexAttr1;
        int floorVertexAttr1;
        int normalAttr1;
        int colorUniform1;
        int matrixUniform1;
        int matrixFloorUniform1;
        float m_fAngle;
        float m_fScale;
        QMatrix4x4 pview;
};


#endif
