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
    feather::status do_it(int, int);

#ifdef __cplusplus
}
#endif

using namespace feather;

#define POLYGON_PLANE 325
#define POLYGON_CUBE 326

int get_id() { return 325; };

bool call_node(int *) { std::cout << "plugin called\n"; return true; };

feather::status do_it(int type, int id) {
    return status();
};

namespace feather {

template <> status do_it<1,POLYGON_PLANE>() { std::cout << "plane node doit\n"; return status(); };
template <> status do_it<1,POLYGON_CUBE>() { std::cout << "cube node doit\n"; return status(); };

}
