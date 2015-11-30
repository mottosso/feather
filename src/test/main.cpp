/***********************************************************************
 *
 * Filename: main.cpp
 *
 * Description: This is for testing of the Core.
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

#include "deps.hpp"
#include "scenegraph.hpp"

int main(int argc, char **argv)
{
    feather::scenegraph::load_plugins();
    std::cout << "FEATHER CORE TESTING STARTING:\n\tAdding node 0 and node 320 to SG: ";
    feather::scenegraph::add_node(1,"root"); // empty 
    feather::scenegraph::add_node(321,"plane"); // polygon plane
    feather::scenegraph::add_node(320,"shape"); // polygon shape
    return 0;
};
