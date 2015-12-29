/***********************************************************************
 *
 * Filename: draw.hpp
 *
 * Description: Used to draw items in the viewport.
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

#ifndef DRAW_HPP
#define DRAW_HPP

#include "deps.hpp"
#include "types.hpp"

namespace feather {

    namespace draw {

        struct Item {};

        struct Line : public Item
        {
            enum Type { Solid, Dashed };
            Line(FVector3D _sp, FVector3D _ep, FColorRGB _color, Type _type=Solid) : sp(_sp), ep(_ep), color(_color), type(_type) {};
            FVector3D sp;
            FVector3D ep;
            FColorRGB color;
            Type type;
        };

        typedef std::vector<Item*> DrawItems;

    } // namespace draw

} // namespace feather

#define DRAW_IT(__node_enum)\
    template <> status node_draw_it<__node_enum>(draw::DrawItems& items)

#define DRAW_LINE(__startpoint,__endpoint,__color,__type)\
    items.push_back(new draw::Line(__startpoint,__endpoint,__color,__type);
    
#endif
