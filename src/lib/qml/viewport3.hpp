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
#ifndef VIEWPORT3_HPP                                                      
#define VIEWPORT3_HPP

#include "deps.hpp"
#include "qml_deps.hpp"                                                    
#include "types.hpp"                                                       

class Viewport3 : public Qt3D::QWindow
{
    Q_OBJECT
    
    public:
        Viewport3(Qt3D::QWindow* parent=0);
        ~Viewport3();

    private:
        Qt3D::QFrameGraph* m_pFrame;
        Qt3D::QCamera* m_pCamera;
};

#endif
