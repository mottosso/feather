/***********************************************************************
 *
 * Filename: gl_scene.hpp
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
                void move(double x, double y, double z);
                void rotate(int x, int y);
                void zoom(int z);
                QMatrix4x4& view() { return m_View; };

            private:
                double m_CamPitchAngle;
                double m_CamTiltAngle;
                double m_CamZoom;
                double m_Scale;
                FVertex3D m_Translate;
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
                void nodeInit(int uid);
                void draw(int width, int height);
                void draw_grid();
                void make_grid();
                void draw_axis();
                glCamera* camera(int camera) { return m_apCameras.at(camera); };

            private:
                std::vector<glCamera*> m_apCameras;
                std::vector<glMesh*> m_apMeshes;
                std::vector<glLight*> m_apLights;
                QMatrix4x4* m_pView;
                QOpenGLShaderProgram* m_pProgram;
                QOpenGLShaderProgram m_GridProgram;
                QOpenGLShaderProgram m_AxisProgram;
                int m_AxisVAttr;
                int m_AxisMAttr;
                int m_GridVAttr;
                int m_GridMAttr;
                std::vector<FVertex3D> m_aGrid;
                std::vector<FVertex3D> m_aAxis;
                feather::FGlInfo m_GlInfo;
        };

    } // namespace gl

} //  namespace feather

#endif
