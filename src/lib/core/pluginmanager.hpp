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
#include "parameter.hpp"

#define MAX_NODE_ID 900

namespace feather
{

    struct PluginNodeFields{};

    struct PluginInfo {
        std::string path;
        void *handle;
        int (*get_id)();
        bool (*call_node)(int*);
        status (*do_it)(int,PluginNodeFields*);
        bool (*node_match)(int); // is there a node with the given type and id in this plugin
        status (*add_node)(int,PluginNodeFields*);
        status (*remove_node)(int,PluginNodeFields*);
        field::FieldBase* (*get_field)(int,int,PluginNodeFields*);
        status (*import_data)(int,parameter::ParameterList);
        status (*export_data)(int,parameter::ParameterList);
        status (*render)(int,parameter::ParameterList);
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
        void operator()(PluginInfo n) { if(n.get_id()==m_node) { std::cout << "found node " << m_node << std::endl; } };
        private:
            int m_node;
    };
    
    // NODE MATCHING

    template <int _Id>
    struct find_nodes {
        static bool exec(int id) { return find_nodes<_Id-1>::exec(id); };
    };

    template <> struct find_nodes<0> { static bool exec(int id) { return false; }; };


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


    // PLUGIN MANAGER

    class PluginManager
    {
        public:
            PluginManager();
            ~PluginManager();
            status load_plugins();
            status do_it(int node); // this is called by the scenegraph
        private:
            status load_node(PluginInfo &node);
            status load_command(PluginInfo &command);
            std::string m_pluginPath;
            std::vector<PluginInfo> m_plugins;
    };

} // namespace feather

#endif
