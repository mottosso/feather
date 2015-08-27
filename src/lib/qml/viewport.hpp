/***********************************************************************
 *
 * Filename: viewport.hpp
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

#ifndef VIEWPORT_HPP 
#define VIEWPORT_HPP

#include "deps.hpp"
#include "qml_deps.hpp"
#include "types.hpp"
#include "gl_scene.hpp"

class Viewport
{

    public:
        Viewport();
        ~Viewport();

        void initialize(int width, int height);
        void nodeInitialize(int uid);
        void render(int width, int height);
        void moveCamera(double x, double y, double z);
        void rotateCamera(int x, int y);
        void zoomCamera(int z);

    private:
        QSize m_viewportSize;
        feather::gl::glScene* m_pScene;    
        int m_CurrentCamera;
};


#endif
