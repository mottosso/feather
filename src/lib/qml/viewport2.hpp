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
    Q_PROPERTY(QColor diffuseColor READ diffuseColor WRITE setDiffuseColor NOTIFY diffuseColorChanged)
 
    public:
        Object(QNode *parent = 0);
        QColor diffuseColor();

    public Q_SLOTS:
        void setDiffuseColor(const QColor &diffuseColor);
 
    Q_SIGNALS:
        void diffuseColorChanged();
 
    private:
        Qt3D::QTransform *m_transform;
        Qt3D::QTranslateTransform *m_translate;
        Qt3D::QScaleTransform *m_scale;
        Qt3D::QGeometryRenderer *m_mesh;
        Qt3D::QPhongMaterial *m_material;
};


class Viewport2 : public Qt3D::QEntity
{
    Q_OBJECT

    public:
        explicit Viewport2(Qt3D::QNode *parent = 0);
        ~Viewport2();

    private Q_SLOTS:
        void updateScene();
        void buildScene();

    private:
        QVector<Object*> m_entities;
};

#endif
