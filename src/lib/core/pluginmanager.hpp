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
    };

    class PluginManager
    {
        public:
            PluginManager();
            ~PluginManager();
            status load_nodes();
            status load_commands();
        private:
            status load_node(PluginInfo &node);
            status load_command(PluginInfo &command);
            std::string m_nodePath;
            std::string m_commandPath;
            std::vector<PluginInfo> m_nodes;
    };

} // namespace feather

#endif
