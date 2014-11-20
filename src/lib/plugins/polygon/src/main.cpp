// =====================================================================================
// 
//       Filename:  main.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  11/03/2014 04:44:11 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#include "deps.hpp"
#include "pluginmanager.hpp"

#ifdef __cplusplus
extern "C" {
#endif

    int get_id();
    bool call_node(int *);
    feather::status do_it(int, int, feather::PluginNodeFields*);

#ifdef __cplusplus
}
#endif

using namespace feather;

#define POLYGON_PLANE 325
#define POLYGON_CUBE 326

int get_id() { return 325; };

bool call_node(int *) {
    std::cout << "plugin called\n"; return true;
};

feather::status do_it(int type, int id, feather::PluginNodeFields* fields) {
    return call_do_its<3>::exec(type,id,fields);
};

namespace feather {

    // functions
 
    
    // do_it
    template <> status node_do_it<1,POLYGON_PLANE>(PluginNodeFields* fields) { std::cout << "plane node doit\n"; return status(); };

   
    // do_it
    template <> status node_do_it<1,POLYGON_CUBE>(PluginNodeFields* fields) { std::cout << "cube node doit\n"; return status(); };

    // PLANE NODE
    template <> struct call_do_its<1> {
        static status exec(int type, int id, PluginNodeFields* fields) {
            if(type==1 && id==POLYGON_PLANE){
                return node_do_it<1,POLYGON_PLANE>(fields);
            } else {
                return call_do_its<1-1>::exec(type,id,fields);
            }
        };
    };

    // functions

    // CUBE NODE
    template <> struct call_do_its<2> {
        static status exec(int type, int id, PluginNodeFields* fields) {
            if(type==1 && id==POLYGON_CUBE){
                return node_do_it<1,POLYGON_CUBE>(fields);
            } else {
                return call_do_its<2-1>::exec(type,id,fields);
            }
        };
    }; 

}


