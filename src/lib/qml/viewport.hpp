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

class Camera
{
    public:
        Camera();
        ~Camera();

        void init();
        void translate();
        void rotate(int x, int y);
        void zoom(int z);


    private:
        float m_camPitchAngle;
        float m_camTiltAngle;
        float m_camZoom;
        float m_fScale;
        QMatrix4x4 pview;
};

class Mesh
{
    public:
        Mesh();
        ~Mesh();

        void init();
        void draw();

    private:
        QOpenGLShaderProgram m_Program;
        QOpenGLShader* m_pShader;
        int m_vertex;
        int m_matrix;
        int m_normal;
        std::vector<feather::FVector3D>* m_apBuffer;
};

class Viewport
{

    public:
        Viewport();
        ~Viewport();

        void initialize(int width, int height);
        void render(int width, int height);
        void makeGrid();
        void drawMesh();
        void drawGrid();
        void drawAxis();
        void initTextures();
        void rotateCamera(int x, int y);
        void zoomCamera(int z);


    private:
        QSize m_viewportSize;
        QOpenGLShaderProgram program1;
        QOpenGLShaderProgram gridProgram;
        QOpenGLShaderProgram axisProgram;
        int vertexAttr1;
        int gridVAttr;
        int gridMAttr;
        int axisVAttr;
        int axisMAttr;
        int normalAttr1;
        int colorUniform1;
        int matrixUniform1;
        int matrixFloorUniform1;
        int texture;
        int texcoord;
        float m_camPitchAngle;
        float m_camTiltAngle;
        float m_camZoom;
        float m_fScale;
        QMatrix4x4 pview;
        QOpenGLShader* meshShader;
        QOpenGLShader* gridShader;
        QOpenGLShader* gridFragShader;
        QOpenGLShader* greenShader;
        QOpenGLShader* axisVShader;
    
        float r;
};


#endif
