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

namespace feather
{

    namespace gl
    {

        class glCamera
        {
            public:
                glCamera();
                ~glCamera();

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

        class glMesh
        {
            public:
                glMesh();
                ~glMesh();

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

        class glScene
        {
            public:
                glScene();
                ~glScene();

                void init();
                void draw();

            private:
                std::vector<glCamera*> m_apCameras;
                std::vector<glMesh*> m_apMeshes;
        };

    } // namespace gl

} //  namespace feather

#endif
