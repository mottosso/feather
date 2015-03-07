/***********************************************************************
 *
 * Filename: ui.hpp
 *
 * Description: Used to store the layout of the ui.
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

#ifndef UI_HPP
#define UI_HPP

namespace feather
{

    namespace ui
    {

        enum Location {
            Menu,
            Popup,
            FieldEditor
        };

        template <int _Node>
            void layout(std::string& msg) { };

        template <int _Location, int _StartNode, int _EndNode>
            struct get_layout {
                static void exec(int n, std::string& msg) { return get_layout<_Location,_StartNode-1,_EndNode>::exec(n,msg); };
            };

    } // namespace ui

} // namespace feather

#endif
