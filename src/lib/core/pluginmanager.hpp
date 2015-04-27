/***********************************************************************
 *
 * Filename: pluginmanager.hpp
 *
 * Description: Loads plugins and manages interaction with the scenegraph.
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

#ifndef PLUGINMANAGER_HPP
#define PLUGINMANAGER_HPP

#include "deps.hpp"
#include "types.hpp"
#include "command.hpp"
#include "parameter.hpp"
#include "field.hpp"

#define MAX_NODE_ID 900

namespace feather
{

    struct PluginInfo {
        std::string name;
        std::string description;
        std::string author;
    };

    struct PluginData {
        std::string path;
        void *handle;
        std::string (*name)();
        std::string (*description)();
        std::string (*author)();
        status (*do_it)(int,field::Fields&);
        void (*gl_init)(FNode&,FGlInfo&);
        void (*gl_draw)(FNode&,FGlInfo&);
        bool (*node_exist)(int); // is there a node with the given type and id in this plugin
        int (*node_type)(int);
        bool (*node_icon)(int,std::string&); // name of icon image in ui/icons path
        status(*create_fields)(int,field::Fields&); // creates a new instance of the nodes fields which will get deleted by the scenegraph when the node is removed.
        field::FieldBase* (*get_field)(int,int,field::Fields&);
        status (*get_fid_list)(int,field::connection::Type,field::Fields&,std::vector<int>&);
        bool (*command_exist)(std::string cmd);
        status (*command)(std::string cmd, parameter::ParameterList);
    };

    struct test_call {
        test_call(int t) {};
        void operator()() {};
    };

    struct get_name {
        get_name(std::vector<PluginInfo>& list) : m_list(list) {};
        void operator()(PluginData n) { 
            PluginInfo info;
            info.name = n.name();
            info.description = n.description();
            info.author = n.author();
            m_list.push_back(info);
        };

        private:
            std::vector<PluginInfo>& m_list; 
    };

    struct get_fids {
        get_fids(int nid, field::connection::Type conn, field::Fields& fields, std::vector<int>& list) : m_nid(nid),m_conn(conn),m_fields(fields),m_list(list) {};
        void operator()(PluginData n) {
            if(n.node_exist(m_nid))
                n.get_fid_list(m_nid,m_conn,m_fields,m_list); 
            else
                std::cout << "didn't find " << m_nid << std::endl;
        };

        private:
            int m_nid;
            field::connection::Type m_conn;
            field::Fields& m_fields;
            std::vector<int>& m_list; 
    };

    // DO_IT()

    template <int _Id>
    struct call_do_its {
        static status exec(int id, field::Fields& fields) { return call_do_its<_Id-1>::exec(id,fields); };
    };

    template <> struct call_do_its<0> { static status exec(int id, field::Fields& fields) { return status(FAILED,"could not find node"); }; };

    template <int _Id> status node_do_it(field::Fields& fields) { return status(FAILED,"no node found"); };
   
    struct call_do_it {
        call_do_it(int node,field::Fields& fields): m_node(node), m_fields(fields){};
        void operator()(PluginData n) { if(n.node_exist(m_node)) { std::cout << "found node " << m_node << std::endl; n.do_it(m_node,m_fields); } };
        private:
            int m_node;
            field::Fields& m_fields;
    };


    // GL INIT 

    template <int _Id>
    struct call_gl_inits {
        static void exec(FNode& node, FGlInfo& info) { call_gl_inits<_Id-1>::exec(node,info); };
    };

    template <> struct call_gl_inits<0> { static void exec(FNode& node, FGlInfo& fields) {}; };
 
    template <int _Id> void node_gl_init(FNode& node, FGlInfo& info) {};

    struct call_gl_init {
        call_gl_init(FNode& node, FGlInfo& info): m_node(node), m_info(info){};
        void operator()(PluginData n) { if(n.node_exist(m_node.node)) { /*std::cout << "found gl info for node " << m_node.uid << std::endl;*/ n.gl_init(m_node,m_info); } };

        private:
            FNode& m_node;
            FGlInfo& m_info;
    };


    // GL DRAW 

    template <int _Id>
    struct call_gl_draws {
        static void exec(FNode& node, FGlInfo& info) { call_gl_draws<_Id-1>::exec(node,info); };
    };

    template <> struct call_gl_draws<0> { static void exec(FNode& node, FGlInfo& fields) {}; };
 
    template <int _Id> void node_gl_draw(FNode& node, FGlInfo& info) {};

    struct call_gl_draw {
        call_gl_draw(FNode& node, FGlInfo& info): m_node(node), m_info(info){};
        void operator()(PluginData n) { if(n.node_exist(m_node.node)) { /*std::cout << "found gl info for node " << m_node.uid << std::endl;*/ n.gl_draw(m_node,m_info); } };

        private:
            FNode& m_node;
            FGlInfo& m_info;
    };



    // NODE MATCHING

    template <int _Id>
    struct find_nodes {
        static bool exec(int id) { return find_nodes<_Id-1>::exec(id); };
    };

    template <> struct find_nodes<0> { static bool exec(int id) { return false; }; };


    // NODE TYPE

    template <int _Id>
    struct find_node_type {
        static bool exec(int id) { return find_node_type<_Id-1>::exec(id); };
    };

    template <> struct find_node_type<0> { static bool exec(int id) { return false; }; };


    // NODE ICON 

    template <int _Id>
    struct find_node_icon {
        static bool exec(int id,std::string& file) { return find_node_icon<_Id-1>::exec(id,file); };
    };

    template <> struct find_node_icon<0> { static bool exec(int id,std::string& file) { return false; }; };



    // GET FIELD DATA

    template <int _NodeId, int _FieldId>
    field::FieldBase* field_data(field::Fields& fields) { return NULL; };  

    // remember that the StartFieldId has to be the last field id + 1
    template <int _NodeId, int _StartFieldId>
    struct find_field {
        static field::FieldBase* exec(int fid, field::Fields& fields) {
            return find_field<_NodeId,_StartFieldId-1>::exec(fid,fields);
        };
    };

    template <int _NodeId>
    struct find_field<_NodeId,0> {
        static field::FieldBase* exec(int fid, field::Fields& fields) {
            return NULL;
        };
    };

    template <int _EndNode, int _StartNode, int _StartField>
        struct find_node_field {
            static field::FieldBase* exec(int nid, int fid, field::Fields& fields) {
                if(nid==_StartNode) {
                    return find_field<_StartNode,_StartField>::exec(fid,fields);
                }
                else
                    return find_node_field<_EndNode,_StartNode-1,_StartField>::exec(nid,fid,fields);
            };
        };

    template <int _StartNode, int _StartField>
        struct find_node_field<_StartNode,_StartNode,_StartField> {
            static field::FieldBase* exec(int nid, int fid, field::Fields& fields) {
                if(nid==_StartNode)
                    return find_field<_StartNode,_StartField>::exec(fid,fields);
                else 
                    return NULL;
            }; 
        };


    // GET NODE'S FIDs

    template <int _Nid, int _StartFid>
    struct get_fid_list {
        static bool exec(int nid, field::Fields& fields, std::vector<int>& list) {
            if(nid==_Nid) {
                std::cout << "adding fid start\n";
                field::FieldBase* f = find_field<_Nid,_StartFid>::exec(_StartFid,fields);
                std::cout << "adding fid end\n";
                //std::cout << "adding fid "  << _StartFid << " type " << f->type << " to list\n";

                // FIX - why is f null??? 
                if(!f)
                    std::cout << "adding fid "  << _StartFid << " type " << f << " to list\n";
                else
                    std::cout << "FID NULL\n";

                list.push_back(_StartFid);
                return get_fid_list<_Nid,_StartFid-1>::exec(nid,fields,list);
            }
        };
    };

    template <int _Nid>
    struct get_fid_list<_Nid,0> {
        static bool exec(int nid, field::Fields& fields, std::vector<int>& list) {
            return false;
        };
    };

    template <int _EndNid, int _StartNid, int _StartFid>
    struct find_node_fid_list {
        static bool exec(int nid, field::Fields& fields, std::vector<int>& list) {
            if(nid==_StartNid) {
                std::cout << "find fid start\n";
                return get_fid_list<_StartNid,_StartFid>::exec(nid,fields,list);
                std::cout << "find fid end\n";
            }
            else
                return find_node_fid_list<_EndNid,_StartNid-1,_StartFid>::exec(nid,fields,list);
        };
    };

    template <int _StartNid, int _StartFid>
    struct find_node_fid_list<_StartNid,_StartNid,_StartFid> {
        static bool exec(int nid, field::Fields& fields, std::vector<int>& list) {
            if(nid==_StartNid)
                return get_fid_list<_StartNid,_StartFid>::exec(nid,fields,list);
            else
                return false;
        };
    };

    // CREATE FIELDS

    // Add Field is used to setup the Fields vector 
    template <int _Node, int _StartKey>
    struct add_fields {
        static status exec(field::Fields& fields) {
            return add_fields<_Node,_StartKey-1>::exec(fields);
        };
    };

    template <int _Node> struct add_fields<_Node,0> { static status exec(field::Fields& fields) { return status(); }; };

    // Create Fields is used to get the field into the sg node container

    template <int _Id>
    struct find_create_fields {
        static  status exec(int id, field::Fields& fields) { return find_create_fields<_Id-1>::exec(id,fields); };
    };

    template <> struct find_create_fields<0> { static status exec(int id, field::Fields& fields) { return status(FAILED,"No matching node fould to create fields in"); }; };


    // COMMANDS 

    struct call_command {
        call_command(std::string cmd, parameter::ParameterList params){ m_cmd = cmd; m_params = params; };
        void operator()(PluginData n) { if(n.command_exist(m_cmd)) { std::cout << "found command " << m_cmd << std::endl; n.command(m_cmd,m_params); } };
        private:
            std::string m_cmd;
            parameter::ParameterList m_params;
    };
    

    // NODE ICON IMAGE 

    template <int _Id>
    struct call_node_icons {
        static void exec(int nid, std::string& file) { call_node_icons<_Id-1>::exec(nid,file); };
    };

    template <> struct call_node_icons<0> { static void exec(int nid, std::string& file) {}; };
 
    template <int _Id> void node_icon(int nid, std::string& file) {};

    struct call_node_icon {
        call_node_icon(int nid, std::string& file) : m_nid(nid),m_file(file){};
        void operator()(PluginData n) { if(n.node_exist(m_nid)) { /*std::cout << "found gl info for node " << m_node.uid << std::endl;*/ n.node_icon(m_nid,m_file); } };

        private:
            int m_nid;
            std::string& m_file;
    };


    // PLUGIN MANAGER

    class PluginManager
    {
        public:
            PluginManager();
            ~PluginManager();
            status load_plugins();
            status do_it(int node,field::Fields& fields); // this is called by the scenegraph
            void gl_init(FNode& node, FGlInfo& info); 
            void gl_draw(FNode& node, FGlInfo& info); 
            status create_fields(int node, field::Fields& fields); // this will return a new instance of the node's fields 
            field::FieldBase* get_fieldBase(int uid, int node, int field, field::Fields& fields);
            status run_command(std::string cmd, parameter::ParameterList);
            int min_uid();
            int max_uid();
            status node_icon_file(int nid, std::string& file);
            void loaded_plugins(std::vector<PluginInfo>& list);
            status get_fid_list(int nid, field::connection::Type conn, field::Fields& fields, std::vector<int>& list);

        private:
            status load_node(PluginData &node);
            status load_command(PluginData &command);
            std::string m_pluginPath;
            std::vector<PluginData> m_plugins;
    };

} // namespace feather

#define C_PLUGIN_WRAPPER()\
    std::string name();\
    std::string description();\
    std::string author();\
    feather::status do_it(int, feather::field::Fields&);\
    void gl_init(feather::FNode& node, feather::FGlInfo& info);\
    void gl_draw(feather::FNode& node, feather::FGlInfo& info);\
    bool node_exist(int);\
    int node_type(int);\
    bool node_icon(int,std::string&);\
    feather::status create_fields(int, feather::field::Fields&);\
    feather::field::FieldBase* get_field(int,int,feather::field::Fields&);\
    feather::status get_fid_list(int,feather::field::connection::Type,feather::field::Fields&,std::vector<int>&);\
    bool command_exist(std::string cmd);\
    feather::status command(std::string cmd, feather::parameter::ParameterList);\

#define PLUGIN_INIT(__name,__description,__author,startnode,endnode)\
    /* plugin name */\
    std::string name() { return __name; };\
    /* plugin description */\
    std::string description() { return __description; };\
    /* plugin name */\
    std::string author() { return __author; };\
    \
    /* call node do_it()'s */\
    feather::status do_it(int id, feather::field::Fields& fields) {\
        return call_do_its<MAX_NODE_ID>::exec(id,fields);\
    };\
    \
    void gl_init(feather::FNode& node, feather::FGlInfo& info) {\
        /*std::cout << "gl_init\n";*/\
        call_gl_inits<MAX_NODE_ID>::exec(node,info);\
    };\
    \
    void gl_draw(feather::FNode& node, feather::FGlInfo& info) {\
        /*std::cout << "gl_draw\n";*/\
        call_gl_draws<MAX_NODE_ID>::exec(node,info);\
    };\
    \
    /* see if the node is in the plugin */\
    bool node_exist(int id) {\
        return find_nodes<MAX_NODE_ID>::exec(id);\
    };\
    \
    /* get the node type */\
    int node_type(int id) {\
        return find_node_type<MAX_NODE_ID>::exec(id);\
    };\
    /* get the node icon */\
    bool node_icon(int id, std::string& file) {\
        return find_node_icon<MAX_NODE_ID>::exec(id,file);\
    };\
    \
    /* create a node field */\
    feather::status create_fields(int id,feather::field::Fields& fields) {\
        return find_create_fields<MAX_NODE_ID>::exec(id,fields);\
    };\
    \
    /* find the node's field */\
    feather::field::FieldBase* get_field(int nid, int fid, field::Fields& fields) {\
        return find_node_field<startnode,endnode,5>::exec(nid,fid,fields);\
    };\
    /* find the node's fid's*/\
    status get_fid_list(int nid, feather::field::connection::Type conn, feather::field::Fields& fields, std::vector<int>& list) {\
        find_node_fid_list<startnode,endnode,5>::exec(nid,fields,list);\
        return status();\
    };



#endif
