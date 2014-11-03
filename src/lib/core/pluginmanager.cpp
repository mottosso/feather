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

}

status PluginManager::load_nodes()
{

  void *lib_handle;
   bool (*fn)(int *);
   int x;
   char *error;

   lib_handle = dlopen("/usr/local/feather/plugins/nodes/libpolyplaneshape.so", RTLD_LAZY);
   if (!lib_handle) 
   {
      fprintf(stderr, "%s\n", dlerror());
      exit(1);
   }

   fn = (bool(*)(int*))dlsym(lib_handle, "call_node");
   if ((error = dlerror()) != NULL)  
   {
      fprintf(stderr, "%s\n", error);
      exit(1);
   }

   (*fn)(&x);
   printf("Valx=%d\n",x);

   dlclose(lib_handle);
   return status(FAILED,"no nodes added");
}

status PluginManager::load_commands()
{
    return status(FAILED,"no commands added");
}
