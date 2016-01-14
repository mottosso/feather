/***********************************************************************
 *
 * Filename: viewport2hpp
 *
 * Description: Qt3D version of the viewport that displays the scenegraph.
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
#ifndef VIEWPORT2_HPP 
#define VIEWPORT2_HPP

#include "deps.hpp"
#include "qml_deps.hpp"
#include "types.hpp"


class DrawItem : public Qt3D::QEntity
{
    Q_OBJECT

    public:
        enum Type{
            None,
            Line,
            Mesh
        };
        DrawItem(Type _type=None, Qt3D::QNode *parent=0);
        ~DrawItem();
        inline void setType(Type t) { m_type=t; };
        inline Type type() { return m_type; }; 
    private:
        Type m_type;
};


// MESH 

class Mesh : public DrawItem 
{
    Q_OBJECT
    
    public:
        Mesh(Qt3D::QNode *parent=0);
        ~Mesh();

    private Q_SLOTS:
        void mouseClicked();
 
    private:
        void build();
        Qt3D::QTransform *m_pTransform;
        Qt3D::QPhongMaterial *m_pMaterial;
        Qt3D::QGeometryRenderer *m_pMesh;
        Qt3D::QMouseInput *m_pMouseInput;
        std::vector<feather::FVertex3D> m_aVertex;
        Qt3D::QAttribute *m_meshAttribute;
        Qt3D::QBuffer *m_vertexBuffer;
};



// LINE

class Line : public DrawItem 
{
    Q_OBJECT
    
    public:
        Line(Qt3D::QNode *parent=0);
        ~Line();

    private Q_SLOTS:
        void mouseClicked();
 
    private:
        void build();
        Qt3D::QTransform *m_pTransform;
        Qt3D::QPhongMaterial *m_pMaterial;
        Qt3D::QGeometryRenderer *m_pMesh;
        Qt3D::QMouseInput *m_pMouseInput;
        std::vector<feather::FVertex3D> m_aVertex;
        Qt3D::QAttribute *m_meshAttribute;
        Qt3D::QBuffer *m_vertexBuffer;
};


// GRID

class AxisGeometry : public Qt3D::QGeometry
{
    Q_OBJECT

    public:
        AxisGeometry(Qt3D::QNode *parent=0);
 
    private:
        void build();
        std::vector<feather::FVertex3D> m_axis;
        Qt3D::QAttribute *m_meshAttribute;
        Qt3D::QBuffer *m_vertexBuffer;
};


class Axis : public Qt3D::QEntity
{
    Q_OBJECT
    
    public:
        Axis(Qt3D::QNode *parent=0);
        ~Axis();
        AxisGeometry* grid() { return static_cast<AxisGeometry*>(m_pMesh->geometry()); };

    private Q_SLOTS:
        void mouseClicked();
 
    private:
        void build();
        Qt3D::QTransform *m_pTransform;
        Qt3D::QMaterial *m_pMaterial;
        Qt3D::QGeometryRenderer *m_pMesh;
        Qt3D::QMouseInput *m_pMouseInput;
};


// GRID

class GridGeometry : public Qt3D::QGeometry
{
    Q_OBJECT

    public:
        GridGeometry(Qt3D::QNode *parent=0);
        int majorSubDividLevel();
        int minorSubDividLevel();
        void setMajorSubDividLevel(const int &level);
        void setMinorSubDividLevel(const int &level);
       
    private:
        void build();
        int m_majorLevel;
        int m_minorLevel;
        std::vector<feather::FVertex3D> m_grid;
        Qt3D::QAttribute *m_meshAttribute;
        Qt3D::QBuffer *m_vertexBuffer;
};


class Grid : public Qt3D::QEntity
{
    Q_OBJECT
    Q_PROPERTY(QColor diffuseColor READ diffuseColor WRITE setDiffuseColor NOTIFY diffuseColorChanged)
    
    public:
        Grid(Qt3D::QNode *parent=0);
        ~Grid();
        GridGeometry* grid() { return static_cast<GridGeometry*>(m_pMesh->geometry()); };
        QColor diffuseColor();

    public Q_SLOTS:
        void setDiffuseColor(const QColor &diffuseColor);
 
    Q_SIGNALS:
        void diffuseColorChanged();
 
    private:
        void build();
        Qt3D::QTransform *m_pTransform;
        Qt3D::QPhongMaterial *m_pMaterial;
        Qt3D::QGeometryRenderer *m_pMesh;
};

// MESHES

class TessellatedGeometry : public Qt3D::QGeometry
{
    Q_OBJECT
    public:
        TessellatedGeometry(Qt3D::QNode *parent=0);

    private:
        Qt3D::QAttribute *m_positionAttribute;
        Qt3D::QBuffer *m_vertexBuffer;
};



class Object: public Qt3D::QEntity
{
    Q_OBJECT
    Q_PROPERTY(QColor ambientColor READ ambientColor WRITE setAmbientColor NOTIFY ambientColorChanged)
    Q_PROPERTY(QColor specularColor READ specularColor WRITE setSpecularColor NOTIFY specularColorChanged)
    Q_PROPERTY(QColor diffuseColor READ diffuseColor WRITE setDiffuseColor NOTIFY diffuseColorChanged)
 
    public:
        Object(QNode *parent = 0);
        QColor ambientColor();
        QColor specularColor();
        QColor diffuseColor();

    public Q_SLOTS:
        void setAmbientColor(const QColor &ambientColor);
        void setSpecularColor(const QColor &specularColor);
        void setDiffuseColor(const QColor &diffuseColor);
 
    Q_SIGNALS:
        void ambientColorChanged();
        void specularColorChanged();
        void diffuseColorChanged();
 
    private Q_SLOTS:
        void onClicked(Qt3D::Q3DMouseEvent* event);
        void onEvent(Qt3D::Q3DMouseEvent* event);

    private:
        Qt3D::QTransform *m_transform;
        Qt3D::QTranslateTransform *m_translate;
        Qt3D::QScaleTransform *m_scale;
        Qt3D::QGeometryRenderer *m_mesh;
        Qt3D::QPhongMaterial *m_material;
        Qt3D::QMouseController *m_pMouseController;
        Qt3D::QMouseInput *m_pMouseInput;
};


class Viewport2 : public Qt3D::QEntity
{
    Q_OBJECT
    Q_PROPERTY(int majorSubDividLevel READ majorSubDividLevel WRITE setMajorSubDividLevel NOTIFY majorSubDividLevelChanged)
    Q_PROPERTY(int minorSubDividLevel READ minorSubDividLevel WRITE setMinorSubDividLevel NOTIFY minorSubDividLevelChanged)
    Q_PROPERTY(bool showGrid READ showGrid WRITE setShowGrid NOTIFY showGridChanged)
    Q_PROPERTY(bool showAxis READ showAxis WRITE setShowAxis NOTIFY showAxisChanged)
 
    public:
        enum Display {
            Hide,
            BoundingBox,
            Point,
            Edge,
            Wireframe,
            SmoothShaded,
            FlatShaded,
            Rendered
        };

        explicit Viewport2(Qt3D::QNode *parent = 0);
        ~Viewport2();
        int majorSubDividLevel();
        int minorSubDividLevel();
        bool showGrid();
        bool showAxis();
        Q_INVOKABLE void doUpdate(){ updateScene(); };

    private Q_SLOTS:
        void updateScene();
        void buildScene();
        void setMajorSubDividLevel(const int &level);
        void setMinorSubDividLevel(const int &level);
        void setShowGrid(const bool &show);
        void setShowAxis(const bool &show);
        void onEntered();
        void onClicked(Qt3D::Q3DMouseEvent* event);

   Q_SIGNALS:
        void majorSubDividLevelChanged();
        void minorSubDividLevelChanged();
        void showGridChanged();
        void showAxisChanged();
 
    private:
        bool m_showGrid;
        bool m_showAxis;
        QVector<DrawItem*> m_apDrawItems;
        Grid* m_pGrid;
        Axis* m_pAxis;
        Qt3D::QMouseController *m_pMouseController;
        Qt3D::QMouseInput *m_pMouseInput;
        Line* m_pLine;
};

#endif
