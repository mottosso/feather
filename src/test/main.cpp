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
    feather::status p;
    feather::scenegraph::load_plugins();


    // ADD NODES


    // add node tests
    std::cout << "FEATHER CORE TESTING STARTING:\n\tAdding root, plane, and shape nodes to the SG: ";
    unsigned int root=0;
    unsigned int plane=0;
    unsigned int shape=0;
    root = feather::scenegraph::add_node(1,"root"); // empty 
    std::cout << " root uid:" << root;
    plane = feather::scenegraph::add_node(321,"plane"); // polygon plane
    std::cout << " plane uid:" << plane;
    shape = feather::scenegraph::add_node(320,"shape"); // polygon shape
    std::cout << " shape uid:" << shape;
    std::cout << "\nNODES ADDED\n\n";
 
    feather::scenegraph::update();
    std::cout << "\n\n";


    // CONNECT NODES


    // node connection tests
    std::cout << "CONNECTING NODES:\n\tConnecting root.child->plane.parent: ";
    // root.child->plane.parent
    p = feather::scenegraph::connect(root,2,plane,1);
    if(!p.state){
        std::cout << "failed" << std::endl;
        return 1; 
    } else {
        std::cout << "passed" << std::endl;
    }
    // plane.child->shape.parent
    p = feather::scenegraph::connect(plane,2,shape,1);
    std::cout << "\tConnecting plane.child->shape.parent: " << ((!p.state) ? "failed" : "passed") << std::endl;
    if(!p.state){
        std::cout << "failed" << std::endl;
        return 1; 
    } else {
        std::cout << "passed" << std::endl;
    }
    // plane.mesh->plane.mesh
    p = feather::scenegraph::connect(plane,5,shape,3);
    std::cout << "\tConnecting plane.mesh->shape.mesh: ";
    if(!p.state){
        std::cout << "failed" << std::endl;
        return 1; 
    } else {
        std::cout << "passed" << std::endl;
    }
    std::cout << "CONNECTION TESTS COMPLETE\n\n"; 

    feather::scenegraph::update();
    std::cout << "\n\n";

    
    // DISCONNECTING NODES

    // TODO for now removing a node should get rid of all it's in and out connections

    // REMOVING NODES
    std::cout << "REMOVING NODES:\n\tremoving shape node: ";
    // root.child->plane.parent
    p = feather::scenegraph::remove_node(shape);
    if(!p.state){
        std::cout << "failed" << std::endl;
        return 1; 
    } else {
        std::cout << "passed" << std::endl;
    }
    std::cout << "REMOVING TEST COMPLETE\n\n";

    feather::scenegraph::update();
    std::cout << "\n\n";


    std::cout << "FEATHER CORE TESTING COMPLETE - ALL GOOD\n";
    return 0;
};
