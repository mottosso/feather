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
#include "field.hpp"
#include "scenegraph.hpp"
#include "selection.hpp"

using namespace feather;

static PluginManager plugins;

status qml::command::init() {
    load_plugins();
    cstate.sgState.minUid=0;
    cstate.sgState.maxUid=0;
    //add_node(node::Null,null::Root);
    add_node(node::Polygon,322,"Cube01"); // PolyCube
    add_node(node::Polygon,320,"CubeShape"); // PolyShape
    scenegraph::connect(0,4,1,2); // connect PolyCube.out to PolyShape.in

    smg::Instance()->add_state(selection::Node,0,0);
 
    // just testing the do_it plugin calls
    scenegraph::update();
    return status();
}

int qml::command::add_node(int type, int node, std::string name)
{
    int uid =  scenegraph::add_node(type,node,name);
    cstate.sgState.maxUid = uid;
    return uid;
    /*
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
    */

    // need to put a check here 
    //return status();
}

bool qml::command::node_exists(int uid)
{
    // TODO
    return true;
}

status qml::command::connect_nodes(int n1, int f1, int n2, int f2)
{
    return scenegraph::connect(n1,f1,n2,f2);
}

status qml::command::load_plugins()
{
    return scenegraph::load_plugins(); 
}

status qml::command::run_command(std::string cmd, feather::parameter::ParameterList params)
{
    return plugins.run_command(cmd, params);
}

// GET FIELD VALUE

status qml::command::get_field_val(int uid, int node, int field, bool& val)
{
    val=false;
    
    return status();
}

status qml::command::get_field_val(int uid, int node, int field, int& val)
{
    typedef field::Field<int,field::connection::In>* fielddata;
    fielddata f = static_cast<fielddata>(scenegraph::get_fieldBase(uid,node,field));
    if(!f)
        std::cout << "NULL FIELD\n";
    else  
        val=f->value;
    return status();
}

status qml::command::get_field_val(int uid, int node, int field, float& val)
{
    val=0.0;
    return status();
}

// SET FIELD VALUE

status qml::command::set_field_val(int uid, int node, int field, bool& val)
{
    return status();
}

status qml::command::set_field_val(int uid, int node, int field, int& val)
{
    typedef field::Field<int,field::connection::In>* fielddata;
    fielddata f = static_cast<fielddata>(scenegraph::get_fieldBase(uid,node,field));
    if(!f)
        std::cout << "NULL FIELD\n";
    else  
        f->value=val;
    return status();
}

status qml::command::set_field_val(int uid, int node, int field, float& val)
{
    return status();
}

status qml::command::get_field_connection_status(int uid, int node, int field, bool& val)
{
    field::FieldBase* f = scenegraph::get_fieldBase(uid,node,field);
    val = f->connected;
    return status();
}

void qml::command::get_node_connections(int uid, std::vector<int>& nodes)
{
    typedef boost::graph_traits<FSceneGraph>::out_edge_iterator OutConn;
    std::pair<OutConn,OutConn> out = boost::out_edges(uid,sg);
    boost::graph_traits<FSceneGraph>::edge_descriptor c = *out.first;
    nodes.push_back(sg[boost::target(c,sg)].uid);
}

std::string qml::command::get_node_name(int uid)
{
    return sg[uid].name;
}

void qml::command::gl_init(int uid, FGlInfo& info)
{
    scenegraph::gl_init(sg[uid],info);
}

void qml::command::gl_draw(int uid, FGlInfo& info)
{
    scenegraph::gl_draw(sg[uid],info);
}

int qml::command::get_min_uid()
{
    return cstate.sgState.minUid; 
}

int qml::command::get_max_uid()
{
    return cstate.sgState.maxUid; 
}

