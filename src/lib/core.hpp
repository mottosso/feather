// =====================================================================================
// 
//       Filename:  core.hpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  09/06/2012 08:00:10 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#ifndef CORE_HPP
#define CORE_HPP

#include "deps.hpp"
#include "types.hpp"

namespace Feather
{

namespace Keys
{
enum {a,A,b,B,c,C}; 
}

namespace Location
{
enum { MenuBar, Popup, ToolBar };
}

struct IO;
struct Modify;
struct Deform;
struct Render;

template < typename T >
FStatus doIt(T node) { return FStatus(); };

};

#endif
