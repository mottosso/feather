// =====================================================================================
// 
//       Filename:  commands.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  08/02/2014 09:47:41 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#include "commands.hpp"

using namespace feather;
using namespace feather::qml;

status command::make_cube() {
    std::cout << "make cube\n";
    return status();
}

