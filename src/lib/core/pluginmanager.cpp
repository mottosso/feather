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

PluginManager::PluginManager():m_pluginPath("~/.feather/plugins")
{

}

PluginManager::~PluginManager()
{
    for(auto n : m_plugins)
        dlclose(n.handle);
}

status PluginManager::load_plugins()
{
    boost::filesystem::path plugin_path("/usr/local/feather/plugins");
    typedef std::vector<boost::filesystem::path> files;
    files plugin_paths;

    if (boost::filesystem::exists(plugin_path))
    {
        if (boost::filesystem::is_regular_file(plugin_path))   
            std::cout << plugin_path << " size is " << boost::filesystem::file_size(plugin_path) << '\n';

        else if (boost::filesystem::is_directory(plugin_path)) {
            std::cout << plugin_path << "is a directory\n";
            std::copy(boost::filesystem::directory_iterator(plugin_path), boost::filesystem::directory_iterator(), std::back_inserter(plugin_paths));
            for (files::const_iterator it (plugin_paths.begin()); it != plugin_paths.end(); ++it)
            {
                if((*it).extension()==".so") {
                    // load plugin here
                    std::cout << "LOADING: " << *it << std::endl;
                    PluginInfo node;
                    node.path = (*it).string();
                    status s = load_node(node);
                    if(s.state){
                        m_plugins.push_back(node);
                        std::cout << node.path << " loaded\n";
                    }
                    else
                        std::cout << node.path << " " << s.msg << std::endl;
                }
            }
        }

        else
            std::cout << plugin_path << "exists, but is neither a regular file nor a directory\n";
    }
    else
        std::cout << plugin_path << "does not exist\n";

    return status();
}

status PluginManager::do_it(int node)
{
    std::cout << "call node " << node << std::endl;
    std::for_each(m_plugins.begin(),m_plugins.end(), call_do_it(node) );
    return status();
}

void PluginManager::draw_gl(int node)
{
    std::cout << "draw node " << node << std::endl;
    std::for_each(m_plugins.begin(),m_plugins.end(), call_draw_gl(node) );
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

    node.do_it = (status(*)(int,field::Fields&))dlsym(node.handle, "do_it");
    node.draw_gl = (void(*)(int,field::Fields&))dlsym(node.handle, "draw_gl");
    node.node_exist = (bool(*)(int))dlsym(node.handle, "node_exist");
    node.node_type = (int(*)(int))dlsym(node.handle, "node_type");
    node.create_fields = (status(*)(int,field::Fields&))dlsym(node.handle,"create_fields");
    node.get_field = (field::FieldBase*(*)(int,int,field::Fields&))dlsym(node.handle, "get_field");
    node.command_exist = (bool(*)(std::string))dlsym(node.handle, "command_exist");
    node.command = (status(*)(std::string,parameter::ParameterList))dlsym(node.handle, "command");

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

status PluginManager::create_fields(int node, field::Fields& fields)
{
    std::cout << "create field for node " << node << std::endl;
    for(uint i=0; i < m_plugins.size(); i++) {
        if(m_plugins[i].node_exist(node))
            return m_plugins[i].create_fields(node,fields);
    }
    return status();
}

field::FieldBase* PluginManager::get_fieldBase(int uid, int node, int field, field::Fields& fields)
{
    for(uint i=0; i < m_plugins.size(); i++) {
        if(m_plugins[i].node_exist(node)) {
            // TODO - I need to verify that the field data actually exists
            //return m_plugins[i].get_field(node,field,fields);
        }
    }
    return NULL;
}

status PluginManager::load_command(PluginInfo &command)
{
    return status(FAILED,"no command to load");
}

status PluginManager::run_command(std::string cmd, parameter::ParameterList params)
{
    std::for_each(m_plugins.begin(),m_plugins.end(), call_command(cmd,params) );
    return status();
}
