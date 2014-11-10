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
    boost::filesystem::path node_path("/usr/local/feather/plugins/nodes");
    typedef std::vector<boost::filesystem::path> files;
    files node_paths;

    if (boost::filesystem::exists(node_path))
    {
        if (boost::filesystem::is_regular_file(node_path))   
            std::cout << node_path << " size is " << boost::filesystem::file_size(node_path) << '\n';

        else if (boost::filesystem::is_directory(node_path)) {
            std::cout << node_path << "is a directory\n";
            std::copy(boost::filesystem::directory_iterator(node_path), boost::filesystem::directory_iterator(), std::back_inserter(node_paths));
            for (files::const_iterator it (node_paths.begin()); it != node_paths.end(); ++it)
            {
                if((*it).extension()==".so") {
                    // load plugin here
                    std::cout << "LOADING: " << *it << std::endl;
                    PluginInfo node;
                    node.path = (*it).string();
                    status s = load_node(node);
                    if(s.state){
                        m_nodes.push_back(node);
                        std::cout << node.path << " loaded\n";
                    }
                    else
                        std::cout << node.path << " " << s.msg << std::endl;
                }
            }
        }

        else
            std::cout << node_path << "exists, but is neither a regular file nor a directory\n";
    }
    else
        std::cout << node_path << "does not exist\n";

    return status();
}

status PluginManager::load_commands()
{
    return status(FAILED,"no commands added");
}

status PluginManager::do_it(int node)
{
    std::cout << "call node " << node << std::endl;
    std::for_each(m_nodes.begin(),m_nodes.end(), call_do_it(node) );
    return status();
}

status PluginManager::load_node(PluginInfo &node)
{
   char *error;

   node.handle = dlopen(node.path.c_str(), RTLD_LAZY);
    if (!node.handle) 
    {
        fprintf(stderr, "%s\n", dlerror());
        return status(FAILED,"loaded failed to load");
    }

    node.get_id = (int(*)())dlsym(node.handle, "get_id");
    node.call_node = (bool(*)(int*))dlsym(node.handle, "call_node");

    if ((error = dlerror()) != NULL)  
    {
        fprintf(stderr, "%s\n", error);
        return status(FAILED,"library error");
    }

    //std::cout << "node id=" << node.get_id() << std::endl; 
    //(*fn)(&x);
    //printf("Valx=%d\n",x);

    return status();
}

status PluginManager::load_command(PluginInfo &command)
{
    return status(FAILED,"no command to load");
}
