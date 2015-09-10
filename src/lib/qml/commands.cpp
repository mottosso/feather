/***********************************************************************
 *
 * Filename: commands.cpp
 *
 * Description: Used to give qml access to the core.
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
    add_node(node::Empty,1,"root"); // PolyCube
    //int uid1 = add_node(node::Polygon,320,"CubeShape"); // PolyShape
    //scenegraph::connect(0,4,uid1,1); // connect PolyCube.out to PolyShape.in

    smg::Instance()->add_state(selection::Node,0,0,0);
 
    // just testing the do_it plugin calls
    scenegraph::update();
    scenegraph::nodes_updated(); // clear out the uids to update
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

bool qml::command::nodes_added(std::vector<int>& uids)
{
    uids.assign(cstate.uid_update.begin(),cstate.uid_update.end());
    //cstate.clear_uid_update();

    std::cout << "there are " << cstate.uid_update.size() << "  in the added nodes\n";

    if(!uids.size())
        return false;
    
    return true;
}

void qml::command::nodes_updated()
{
    scenegraph::nodes_updated();
}

bool qml::command::node_exists(int uid)
{
    // TODO - this is a temp fix for the minute
    // This will need to be fixed in the future since nodes will be taken away
    // so the indics could jump
    return ( scenegraph::get_max_uid() >= uid) ? true : false;
}

status qml::command::connect_nodes(int n1, int f1, int n2, int f2)
{
    return scenegraph::connect(n1,f1,n2,f2);
}

status qml::command::get_node_icon(int nid, std::string& file)
{
    return scenegraph::get_node_icon(nid,file);
}

status qml::command::get_node_id(int uid, int& nid)
{
    return scenegraph::get_node_id(uid,nid);
}

status qml::command::get_node_connected_uids(int uid, std::vector<int>& uids)
{
    return scenegraph::get_node_connected_uids(uid,uids);
}

status qml::command::load_plugins()
{
    return scenegraph::load_plugins(); 
}

status qml::command::run_command(std::string cmd, feather::parameter::ParameterList params)
{
    return plugins.run_command(cmd, params);
}

status qml::command::run_command_string(std::string str)
{
    return plugins.run_command_string(str);
}


// Layer

status qml::command::add_layer(feather::FLayer layer)
{
    scenegraph::add_layer(layer);
    return status();
}

status qml::command::remove_layer(int lid)
{
    bool p = scenegraph::remove_layer(lid);
    return (!p) ? status(FAILED,"failed to remover layer: id out of range") : status();
}

status qml::command::move_layer(int sid, int tid)
{
    scenegraph::move_layer(sid,tid);
    return status();
}

status qml::command::get_layer(int lid, feather::FLayer &layer)
{
    bool p = scenegraph::layer(lid,layer);
    return (!p) ? status(FAILED,"failed to get layer: id out of range") :status();
}

void qml::command::set_layer_name(std::string name, int lid)
{
    scenegraph::layer(lid)->name = name;
}

void qml::command::set_layer_color(int r, int g, int b, int lid)
{
    scenegraph::layer(lid)->color = FColorRGB(static_cast<float>(r)/255.0,static_cast<float>(g)/255.0,static_cast<float>(b)/255.0);
}

void qml::command::set_layer_visible(bool v, int lid)
{
    scenegraph::layer(lid)->visible = v;
}

void qml::command::set_layer_locked(bool l, int lid)
{
    scenegraph::layer(lid)->locked = l;
}

int qml::command::layer_count()
{
    return scenegraph::layer_count();
}

void qml::command::add_node_to_layer(int uid, int lid)
{
    scenegraph::add_node_to_layer(uid,lid);
}


// FIELDS

// GET FIELD BASE
status qml::command::get_field_base(int uid, int field, feather::field::FieldBase* &f)
{
    //typedef field::Field<int,field::connection::In>* fielddata;
    //fielddata f = static_cast<fielddata>(scenegraph::get_fieldBase(uid,node,field));
    f = scenegraph::get_fieldBase(uid,sg[uid].node,field);
    if(!f) {
        //std::cout << "NULL FIELD\n";
        return status(FAILED,"null field base\n");
    }
    /*
    else  
        val=f->value;
    */
    return status();
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
        std::cout << uid << "," << node << "," << field << " NULL FIELD\n";
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

status qml::command::get_fid_list(int uid, int nid, field::connection::Type conn, std::vector<field::FieldBase*>& list)
{
    return scenegraph::get_fid_list(uid,nid,conn,list);
}


// SCENEGRAPH EDITOR

void qml::command::get_node_connections(int uid, std::vector<int>& nodes)
{
    typedef boost::graph_traits<FSceneGraph>::out_edge_iterator OutConn;
    std::pair<OutConn,OutConn> out = boost::out_edges(uid,sg);

    // this is a simple hack to check if a edge exist, I'm sure there's a better way to do this
    if(out.first==out.second){
        std::cout << "first and second edges match for " << uid << std::endl; 
        return;
    } else {
        std::cout << "edges don't match for " << uid << std::endl;
        boost::graph_traits<FSceneGraph>::edge_descriptor c = *out.first;
        nodes.push_back(sg[boost::target(c,sg)].uid);
    }
}

int qml::command::get_node_connection_count(int uid)
{
    // TODO - currently not used but would be helpful
    return 0; 
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

void qml::command::get_plugins(std::vector<PluginInfo>& list)
{
    return plugins.loaded_plugins(list); 
}

// SG SELECTION

status qml::command::select_node(int type, int uid)
{
    return scenegraph::add_selection(type,uid);
}

status qml::command::select_node(int type, int uid, int nid)
{
    return scenegraph::add_selection(type,uid,nid);
}

status qml::command::select_node(int type, int uid, int nid, int fid)
{
    return scenegraph::add_selection(type,uid,nid,fid);
}

status qml::command::get_selected_nodes(std::vector<int>& uids)
{
    return scenegraph::get_selected_nodes(uids);
}

void qml::command::clear_selection()
{
    scenegraph::clear_selection();
}

