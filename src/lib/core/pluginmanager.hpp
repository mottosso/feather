// =====================================================================================
// 
//       Filename:  pluginmanager.hpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  11/03/2014 03:22:04 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#ifndef PLUGINMANAGER_HPP
#define PLUGINMANAGER_HPP

#include "deps.hpp"
#include "types.hpp"
#include "command.hpp"
#include "parameter.hpp"

#define MAX_NODE_ID 900

namespace feather
{

    struct PluginNodeFields{};

    struct PluginInfo {
        std::string path;
        void *handle;
        status (*do_it)(int,PluginNodeFields*);
        void (*draw_gl)(int,PluginNodeFields*);
        bool (*node_exist)(int); // is there a node with the given type and id in this plugin
        int (*node_type)(int);
        status (*add_node)(int,PluginNodeFields*); // not used
        status (*remove_node)(int,PluginNodeFields*); // not used 
        PluginNodeFields* (*create_fields)(int); // creates a new instance of the nodes fields which will get deleted by the scenegraph when the node is removed.
        field::FieldBase* (*get_field)(int,int,PluginNodeFields*);
        bool (*command_exist)(std::string cmd);
        status (*command)(std::string cmd, parameter::ParameterList);
    };

    struct test_call {
        test_call(int t) {};
        void operator()() {};
    };


    // DO_IT()

    template <int _Id>
    struct call_do_its {
        static status exec(int id, PluginNodeFields* fields) { return call_do_its<_Id-1>::exec(id,fields); };
    };

    template <> struct call_do_its<0> { static status exec(int id, PluginNodeFields* fields) { return status(FAILED,"could not find node"); }; };


    template <int _Id> status node_do_it(PluginNodeFields* fields) { return status(FAILED,"no node found"); };
    
    struct call_do_it {
        call_do_it(int node){ m_node = node; };
        void operator()(PluginInfo n) { if(n.node_exist(m_node)) { std::cout << "found node " << m_node << std::endl; } };
        private:
            int m_node;
    };

   
    // DRAW_GL()

    template <int _Id>
    struct call_draw_gls {
        static void exec(int id, PluginNodeFields* fields) { call_draw_gls<_Id-1>::exec(id,fields); };
    };
 
    template <> struct call_draw_gls<0> { static void exec(int id, PluginNodeFields* fields) { }; };

    template <int _Id> void node_draw_gl(PluginNodeFields* fields) { };

    struct call_draw_gl {
        call_draw_gl(int node){ m_node = node; };
        void operator()(PluginInfo n) { if(n.node_exist(m_node)) { std::cout << "found node for drawing " << m_node << std::endl; } };
        private:
            int m_node;
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



    // GET FIELD DATA

    template <int _NodeId, int _FieldId>
    field::FieldBase* field_data(PluginNodeFields* fields) { return NULL; };  

    // remember that the StartFieldId has to be the last field id + 1
    template <int _NodeId, int _StartFieldId>
    struct find_field {
        static field::FieldBase* exec(int fid, PluginNodeFields* fields) {
            return find_field<_NodeId,_StartFieldId-1>::exec(fid,fields);
        };
    };

    template <int _NodeId>
    struct find_field<_NodeId,0> {
        static field::FieldBase* exec(int fid, PluginNodeFields* fields) {
            return NULL;
        };
    };

    template <int _EndNode, int _StartNode, int _StartField>
        struct find_node_field {
            static field::FieldBase* exec(int nid, int fid, PluginNodeFields* fields) {
                if(nid==_StartNode)
                    return find_field<_StartNode,_StartField>::exec(fid,fields);
                else if(_EndNode > _StartNode)
                    return NULL;
                else
                    return find_node_field<_EndNode,_StartNode-1,_StartField>::exec(nid,fid,fields);
            };
        };

    template <int _StartNode, int _StartField>
        struct find_node_field<_StartNode,_StartNode,_StartField> {
            static field::FieldBase* exec(int nid, int fid, PluginNodeFields* fields) {
                if(nid==_StartNode)
                    return find_field<_StartNode,_StartField>::exec(fid,fields);
                else
                    return NULL;
            }; 
        };


    // CREATE FIELDS

    template <int _Id>
    struct find_create_fields {
        static PluginNodeFields* exec(int id) { return find_create_fields<_Id-1>::exec(id); };
    };

    template <> struct find_create_fields<0> { static PluginNodeFields* exec(int id) { return NULL; }; };


    // COMMANDS 

    struct call_command {
        call_command(std::string cmd, parameter::ParameterList params){ m_cmd = cmd; m_params = params; };
        void operator()(PluginInfo n) { if(n.command_exist(m_cmd)) { std::cout << "found command " << m_cmd << std::endl; n.command(m_cmd,m_params); } };
        private:
            std::string m_cmd;
            parameter::ParameterList m_params;
    };
    


    // PLUGIN MANAGER

    class PluginManager
    {
        public:
            PluginManager();
            ~PluginManager();
            status load_plugins();
            status do_it(int node); // this is called by the scenegraph
            void draw_gl(int node); // this is called by the scenegraph
            PluginNodeFields* create_fields(int node); // this will return a new instance of the node's fields 
            status run_command(std::string cmd, parameter::ParameterList);

        private:
            status load_node(PluginInfo &node);
            status load_command(PluginInfo &command);
            std::string m_pluginPath;
            std::vector<PluginInfo> m_plugins;
    };

} // namespace feather

#define C_PLUGIN_WRAPPER()\
    feather::status do_it(int, feather::PluginNodeFields*);\
    void draw_gl(int, feather::PluginNodeFields*);\
    bool node_exist(int);\
    int node_type(int);\
    feather::status add_node(int, feather::PluginNodeFields*);\
    feather::status remove_node(int, feather::PluginNodeFields*);\
    feather::PluginNodeFields* create_fields(int);\
    feather::field::FieldBase* get_field(int,int);\
    bool command_exist(std::string cmd);\
    feather::status command(std::string cmd, feather::parameter::ParameterList);\

#define PLUGIN_INIT(startnode,endnode)\
    /* call node do_it()'s */\
    feather::status do_it(int id, feather::PluginNodeFields* fields) {\
        return call_do_its<MAX_NODE_ID>::exec(id,fields);\
    };\
    \
    /* call node draw_gl()'s */\
    void draw_gl(int id, feather::PluginNodeFields* fields) {\
        call_draw_gls<MAX_NODE_ID>::exec(id,fields);\
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
    \
    feather::status add_node(int id, feather::PluginNodeFields* fields) {\
        return feather::status(FAILED, "function not yet working");\
    };\
    feather::PluginNodeFields* create_fields(int id) {\
        return find_create_fields<MAX_NODE_ID>::exec(id);\
    };\
    feather::field::FieldBase* get_field(int nid, int fid, PluginNodeFields* fields) {\
        return find_node_field<startnode,endnode,5>::exec(nid,fid,fields);\
    };


#endif
