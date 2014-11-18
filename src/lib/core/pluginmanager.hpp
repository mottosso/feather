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

namespace feather
{

    struct PluginInfo {
        std::string path;
        void *handle;
        int (*get_id)();
        bool (*call_node)(int*);
        status (*do_it)(int,int);
    };

    struct test_call {
        test_call(int t) {};
        void operator()() {};
    };

    template <int _Number>
    struct call_do_its {
        static status exec(int type, int id) { return call_do_its<_Number-1>::exec(); };
    };

    template <> struct call_do_its<0> { static status exec(int type, int id) { return status(FAILED,"could not find node"); }; };

    template <int _Type, int _Id> static status do_it() { return status(FAILED,"no node found"); };
    

    struct call_do_it {
        call_do_it(int node){ m_node = node; };
        void operator()(PluginInfo n) { if(n.get_id()==m_node) { std::cout << "found node " << m_node << std::endl; } };
        private:
            int m_node;
    };

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
