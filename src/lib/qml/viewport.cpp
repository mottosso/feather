/***********************************************************************
 *
 * Filename: viewport.cpp
 *
 * Description: Holds the scenegraph.
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

#include "viewport.hpp"

// MAIN VIEWPORT

Viewport::Viewport()
{
    m_pScene = new feather::gl::glScene();
    m_CurrentCamera = 0;
}

Viewport::~Viewport()
{
    delete m_pScene;
}

void Viewport::initialize(int width, int height)
{
    m_pScene->init();
}

void Viewport::nodeInitialize(int uid)
{
    m_pScene->nodeInit(uid);
}

void Viewport::nodesAdded()
{
    m_pScene->nodesAddedInit();
}

void Viewport::addItems(unsigned int uid)
{
    m_pScene->addItems(uid);
}

void Viewport::nodesRemoved()
{
    m_pScene->nodesRemovedInit();
}

void Viewport::render(int width, int height)
{
    m_pScene->draw(width,height);
}

void Viewport::moveCamera(double x, double y, double z)
{
    m_pScene->camera(m_CurrentCamera)->move(x,y,z);
}

void Viewport::rotateCamera(int x, int y)
{
    m_pScene->camera(m_CurrentCamera)->rotate(x,y);
}

void Viewport::zoomCamera(int z)
{
    m_pScene->camera(m_CurrentCamera)->zoom(z);
}
