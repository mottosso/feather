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

class Viewport {

    public:
        Viewport();
        ~Viewport();

        void render();
        void initialize();
        void createMesh();
        void setContext(QOpenGLContext* context) { m_context=context; };
    private:
        QOpenGLShaderProgram program1;
        int vertexAttr1;
        int normalAttr1;
        int colorUniform1;
        int matrixUniform1;
        GLuint vbo;
        GLuint vao;

        // VBO Items
        QOpenGLVertexArrayObject* m_vao1;
        QOpenGLContext* m_context;
        QOpenGLBuffer m_positionBuffer;
        QOpenGLBuffer m_colorBuffer;
};

#endif
