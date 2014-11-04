// =====================================================================================
// 
//       Filename:  pluginmanager.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  11/03/2014 03:23:54 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#include "pluginmanager.hpp"

using namespace feather;

PluginManager::PluginManager():m_nodePath("~/.feather/plugins/nodes"),m_commandPath("~/.feather/plugins/commands")

{

}

PluginManager::~PluginManager()
{
    for(auto n : m_nodes)
        dlclose(n.handle);
}

status PluginManager::load_nodes()
{
    //int x;
    char *error;

    PluginInfo node;

    node.handle = dlopen("/usr/local/feather/plugins/nodes/libpolyplaneshape.so", RTLD_LAZY);
    if (!node.handle) 
    {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }

    node.get_id = (int(*)())dlsym(node.handle, "get_id");
    node.call_node = (bool(*)(int*))dlsym(node.handle, "call_node");

    if ((error = dlerror()) != NULL)  
    {
        fprintf(stderr, "%s\n", error);
        exit(1);
    }

    std::cout << "node id=" << node.get_id() << std::endl; 
    //(*fn)(&x);
    //printf("Valx=%d\n",x);

    m_nodes.push_back(node);
    return status(FAILED,"no nodes added");
}

status PluginManager::load_commands()
{
    return status(FAILED,"no commands added");
}
