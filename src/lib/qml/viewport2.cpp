/***********************************************************************
 *
 * Filename: viewport2.cpp
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

#include "viewport2.hpp"

// MAIN VIEWPORT

//#include "examplescene.h"
//#include "boxentity.h"

//#include <QTimer>
//#include <qmath.h>


BoxEntity::BoxEntity(QNode *parent)
    : Qt3D::QEntity(parent)
    , m_transform(new Qt3D::QTransform())
    , m_translate(new Qt3D::QTranslateTransform())
    , m_mesh(new Qt3D::QCuboidMesh())
    , m_material(new Qt3D::QPhongMaterial())
    , m_angle(0.0f)
      , m_radius(1.0f)
{
    m_transform->addTransform(m_translate);

    connect(m_material, SIGNAL(diffuseChanged()), this, SIGNAL(diffuseColorChanged()));
    m_material->setAmbient(Qt::gray);
    m_material->setSpecular(Qt::white);
    m_material->setShininess(150.0f);

    addComponent(m_transform);
    addComponent(m_mesh);
    addComponent(m_material);
}

void BoxEntity::setDiffuseColor(const QColor &diffuseColor)
{
    m_material->setDiffuse(diffuseColor);
}

void BoxEntity::setAngle(float arg)
{
    if (m_angle == arg)
        return;

    m_angle = arg;
    emit angleChanged();
    updateTransformation();
}

void BoxEntity::setRadius(float arg)
{
    if (m_radius == arg)
        return;

    m_radius = arg;
    emit radiusChanged();
    updateTransformation();
}

QColor BoxEntity::diffuseColor()
{
    return m_material->diffuse();
}

float BoxEntity::angle() const
{
    return m_angle;
}

float BoxEntity::radius() const
{
    return m_radius;
}

void BoxEntity::updateTransformation()
{
    m_translate->setTranslation(QVector3D(qCos(m_angle) * m_radius,
                1.0f,
                qSin(m_angle) * m_radius));
}



Viewport2::Viewport2(Qt3D::QNode *parent)
    : Qt3D::QEntity(parent)
    , m_timer(new QTimer(this))
    , m_even(true)
{
    QObject::connect(m_timer, SIGNAL(timeout()), SLOT(updateScene()));
    m_timer->setInterval(1200);
    m_timer->start();
}

Viewport2::~Viewport2()
{
    qDeleteAll(m_entities);
}

void Viewport2::updateScene()
{
    if (m_entities.isEmpty()) {
        buildScene();
    } else {
        int i = 0;
        Q_FOREACH (BoxEntity *entity, m_entities) {
            if (i % 2 == 0)
                entity->setParent(m_even ? Q_NULLPTR : this);
            else
                entity->setParent(m_even ? this : Q_NULLPTR);
            ++i;
        }
        m_even = !m_even;
    }
}

void Viewport2::buildScene()
{
    int count = 20;
    const float radius = 5.0f;

    for (int i = 0; i < count; ++i) {
        BoxEntity *entity = new BoxEntity;
        const float angle = M_PI * 2.0f * float(i) / count;
        entity->setAngle(angle);
        entity->setRadius(radius);
        entity->setDiffuseColor(QColor(qFabs(qCos(angle)) * 255, 204, 75));
        m_entities.append(entity);
    }
}

