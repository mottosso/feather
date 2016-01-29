/* **********************************************************************
 *
 * Filename: viewport3.hpp
 *
 * Description: Qt3D version of the viewport that uses deferred rendering.
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

#include "viewport3.hpp"


Viewport3::Viewport3(Qt3D::QWindow* parent)
    : Qt3D::QWindow(parent),
    m_pFrame(new Qt3D::QFrameGraph())
{
    m_pCamera = defaultCamera();

    m_pCamera->setFieldOfView(45.0f);
    m_pCamera->setNearPlane(0.01f);
    m_pCamera->setFarPlane(1000.0f);
    m_pCamera->setProjectionType(Qt3D::QCameraLens::PerspectiveProjection);

    m_pCamera->setPosition(QVector3D(10.0f, 10.0f, -25.0f));
    m_pCamera->setUpVector(QVector3D(0.0f, 1.0f, 0.0f));
    m_pCamera->setViewCenter(QVector3D(0.0f, 0.0f, 10.0f));

    show();
}

Viewport3::~Viewport3()
{
    delete m_pFrame;
    m_pFrame=0;    
}


