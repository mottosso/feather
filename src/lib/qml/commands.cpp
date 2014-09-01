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
//#include "field.hpp"
#include "scenegraph.hpp"
//#include "polygon_plane.hpp"
//#include "root_node.hpp"

using namespace feather;
using namespace feather::qml;

status command::init() {
    //scenegraph::add_node<node::Root>(0);
    return status();
}

status command::add_node(int node, int id)
{
    //return scenegraph::add_sgnode<node::N>::exec(node,id);
}

status command::make_plane() {
    std::cout << "make plane\n";
    //scenegraph::add_node<node::PolygonPlane>(1);
    //scenegraph::add_node<node::Transform>(2);
    //CONNECT_FIELDS(1,node_selection.at(0),node_selection.at(1))
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
    //scenegraph::draw_gl();
    return status();
}
