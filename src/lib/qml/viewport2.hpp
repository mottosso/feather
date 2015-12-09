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
//#include "gl_scene.hpp"
#include <Qt3DCore/QEntity>

// Headers for BoxEntity
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DCore/QTranslateTransform>
#include <Qt3DCore/QScaleTransform>
#include <Qt3DRenderer/QCuboidMesh>
#include <Qt3DRenderer/QPhongMaterial>


class BoxEntity : public Qt3D::QEntity
{
    Q_OBJECT

    Q_PROPERTY(QColor diffuseColor READ diffuseColor WRITE setDiffuseColor NOTIFY diffuseColorChanged)
    Q_PROPERTY(float angle READ angle WRITE setAngle NOTIFY angleChanged)
    Q_PROPERTY(float radius READ radius WRITE setRadius NOTIFY radiusChanged)

public:
    BoxEntity(QNode *parent = 0);

    QColor diffuseColor();
    float angle() const;
    float radius() const;

public Q_SLOTS:
    void setDiffuseColor(const QColor &diffuseColor);
    void setAngle(float arg);
    void setRadius(float arg);

Q_SIGNALS:
    void diffuseColorChanged();
    void angleChanged();
    void radiusChanged();

private:
    void updateTransformation();

    Qt3D::QTransform *m_transform;
    Qt3D::QTranslateTransform *m_translate;
    Qt3D::QScaleTransform *m_scale;
    Qt3D::QCuboidMesh *m_mesh;
    Qt3D::QPhongMaterial *m_material;
    float m_angle;
    float m_radius;
};


class QTimer;


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
        QVector<BoxEntity *> m_entities;
        QTimer *m_timer;
        bool m_even;
};

#endif
