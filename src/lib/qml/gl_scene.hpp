// =====================================================================================
// 
//       Filename:  gl_scene.hpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  02/18/2015 08:55:38 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#ifndef GL_SCENE_HPP
#define GL_SCENE_HPP

#include "deps.hpp"
#include "qml_deps.hpp"
#include "types.hpp"

namespace feather
{

    namespace gl
    {

        enum CameraType { Orthographic, Perspective };

        class glCamera
        {
            public:
                glCamera();
                ~glCamera();
                void init();
                void draw(int width, int height);
                void rotate(int x, int y);
                void zoom(int z);
                QMatrix4x4& view() { return m_View; };

            private:
                float m_CamPitchAngle;
                float m_CamTiltAngle;
                float m_CamZoom;
                float m_Scale;
                QMatrix4x4 m_View;
        };

        enum LightType { Ambient, Point, Spot, Direct };

        class glLight
        {
            public:
                glLight();
                ~glLight();
                void init();
                void draw(QMatrix4x4& view);
                QVector3D& position() { return m_Position; };

            private:
                QOpenGLShader* m_pFragShader;
                QOpenGLShader* m_pVertShader;
                QOpenGLShaderProgram m_Program;
                QVector3D m_Position;
                std::vector<FVertex3D> m_aModel;
                LightType m_Type;
                int m_Vertex;
                int m_Matrix;
                int m_PositionId;
        };

        class glMesh
        {
            public:
                glMesh(glLight* light);
                ~glMesh();
                void init();
                void draw(QMatrix4x4& view);

            private:
                QOpenGLShaderProgram m_Program;
                QOpenGLShader* m_pFillShader;
                QOpenGLShader* m_pEdgeShader;
                QOpenGLShader* m_pVertShader;
                int m_Vertex;
                int m_Matrix;
                int m_Normal;
                int m_LightPositionId;
                int m_ShaderDiffuseId; 
                std::vector<FVertex3D> m_apV;
                std::vector<FVertex3D> m_apVn;
                QColor m_ShaderDiffuse;
                glLight* m_pLight;
        };

        class glScene
        {
            public:
                glScene();
                ~glScene();
                void init();
                void draw(int width, int height);
                void draw_grid();
                void make_grid();
                void draw_axis();
                glCamera* camera(int camera) { return m_apCameras.at(camera); };

            private:
                std::vector<glCamera*> m_apCameras;
                std::vector<glMesh*> m_apMeshes;
                std::vector<glLight*> m_apLights;
                QOpenGLShaderProgram m_GridProgram;
                QOpenGLShaderProgram m_AxisProgram;
                QOpenGLShader* m_pGridShader;
                QOpenGLShader* m_pGridFragShader;
                QOpenGLShader* m_pAxisVShader;
                int m_AxisVAttr;
                int m_AxisMAttr;
                int m_GridVAttr;
                int m_GridMAttr;
                std::vector<FVertex3D> m_aGrid;
                std::vector<FVertex3D> m_aAxis;
        };

    } // namespace gl

} //  namespace feather

#endif
