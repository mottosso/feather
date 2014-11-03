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

#ifdef __cplusplus
extern "C" {
#endif

    bool call_node(int *);

#ifdef __cplusplus
}
#endif

bool call_node(int *) { std::cout << "plugin called\n"; return true; };
