// =====================================================================================
// 
//       Filename:  commands.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  08/02/2014 09:47:41 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#include "commands.hpp"
#include "polygon_mesh.hpp"
#include "scenegraph.hpp"
#include "polygon_plane.hpp"

using namespace feather;
using namespace feather::qml;

status command::make_plane() {
    std::cout << "make plane\n";
    scenegraph::add_node<node::PolygonPlane>("A");
    return status();
}

status command::make_cube() {
    std::cout << "make cube\n";
   // create a sgNode
   /*
    scenegraph::sgNode sgnode(1,node::PolygonMesh,new node::NodeAttributes(), new Fields());
    scenegraph::SceneGraphSingleton::Instance()->push_back(sgnode);
    node::Node<node::PolygonMesh>::init(sgnode.nattr,sgnode.fields);
    scenegraph::update();
    */
    return status();
}

status command::draw_sg(QMatrix4x4& view)
{
    scenegraph::draw_gl();
    return status();
}
