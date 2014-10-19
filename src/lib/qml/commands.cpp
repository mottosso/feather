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
#include "polygon_plane.hpp"
#include "root_node.hpp"
#include "null.hpp"
#include "object.hpp"


using namespace feather;
using namespace feather::qml;

status command::init() {
    return add_node(node::Null,null::Root,0);
}

status command::add_node(int type, int node, int id)
{
    switch(type)
    {
        case node::Null:
            return scenegraph::add_node_to_sg<node::Null,null::N>::exec(node,id);
        case node::Camera:
            return scenegraph::add_node_to_sg<node::Camera,camera::N>::exec(node,id);
        case node::Light:
            return scenegraph::add_node_to_sg<node::Light,light::N>::exec(node,id);
        case node::Texture:
            return scenegraph::add_node_to_sg<node::Texture,texture::N>::exec(node,id);
        case node::Shader:
            return scenegraph::add_node_to_sg<node::Shader,shader::N>::exec(node,id);
        case node::Object:
            return scenegraph::add_node_to_sg<node::Object,object::N>::exec(node,id);
        default:
            break;
    }
    
    return status(FAILED, "no matching Type of Node found while trying to add node");
}

status command::draw_sg(QMatrix4x4& view)
{
    return scenegraph::update();
}
