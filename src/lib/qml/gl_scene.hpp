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

        class glDrawItem
        {
            public:
                enum Type{
                    None,
                    Line,
                    Mesh,
                    PerspCamera
                };
                glDrawItem(feather::draw::Item* _item, Type _type=None);
                ~glDrawItem();
                inline void setType(Type t) { m_type=t; };
                inline Type type() { return m_type; };
                virtual void init(){};
                virtual void build(){};
                virtual void draw(){};
                virtual void update(){};
                inline unsigned int uid() { return m_item->uid; };
                inline unsigned int nid() { return m_item->nid; };
                feather::draw::Item* item() { return m_item; };
                QOpenGLShaderProgram* program() { return m_pProgram; }
                void setProgram(QOpenGLShaderProgram* program) { m_pProgram = program; };
                QMatrix4x4* view() { return m_pView; };
                void setView(QMatrix4x4* view) { m_pView = view; };

            private:
                Type m_type;
                feather::draw::Item* m_item;

            protected:
                unsigned int m_Uid;
                unsigned int m_Nid;
                QOpenGLShaderProgram* m_pProgram;
                QMatrix4x4* m_pView;
                
                feather::FVertex3DArray m_aV;
                feather::FVertex3DArray m_aVn;
                feather::FIntArray m_aGlei; // edge index
                feather::FIntArray m_aGli; // index
                feather::FColorRGBAArray m_aGlc; // color 

                int m_glVertex;
                int m_glColor;
                int m_glMatrix;
                int m_glNormal;
                int m_glView; // 0=face, 1=edge, 2=point
                int m_glSelected;
                int m_glLayerColor;
                int m_glLightPosition;
                int m_glLightAmbient;
                int m_glLightDiffuse;
                int m_glLightSpecular;
                int m_glMaterialAmbient;
                int m_glMaterialDiffuse;
                int m_glMaterialSpecular;
                int m_glMaterialShininess;
                int m_glCameraPosition;
                int m_glShaderDiffuse;
        };


        class glMesh : public glDrawItem
        {
            public:
                glMesh(feather::draw::Item* _item, Type _type=None);
                ~glMesh();
                void init();
                void build();
                void draw();
                void update();
 
            private:
                unsigned int m_Fid;
       };

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


        class glScene
        {
            public:
                enum ShadingMode { FLAT, SHADED };
                enum SelectionMode { OBJECT, FACE, EDGE, VERTEX };

                glScene();
                ~glScene();
                void init();
                void nodeInit(int uid);
                void addItems(unsigned int uid);
                void nodesAddedInit();
                void nodesRemovedInit();
                void draw(int width, int height);
                void draw_grid();
                void make_grid();
                void draw_axis();
                glCamera* camera(int camera) { return m_apCameras.at(camera); };
                void showAxis(bool s) { m_showAxis = s; };
                void showGrid(bool s) { m_showGrid = s; };
                void setShadingMode(ShadingMode m) { m_ShadingMode = m; };
                void setSelectionMode(SelectionMode m) { m_SelectionMode = m; };

            private:
                std::vector<glCamera*> m_apCameras;
                //std::vector<glMesh*> m_apMeshes;
                //std::vector<glLight*> m_apLights;
                std::vector<glDrawItem*> m_apItems;
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
                //std::vector<feather::FGlInfo> m_aGlInfo;
                bool m_showAxis;
                bool m_showGrid;
                ShadingMode m_ShadingMode;
                SelectionMode m_SelectionMode;
        };

    } // namespace gl

} //  namespace feather

#endif
