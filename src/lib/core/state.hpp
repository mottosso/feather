// =====================================================================================
// 
//       Filename:  state.hpp
// 
//    Description:  Holds the current state of the core and ui
// 
//        Version:  1.0
//        Created:  01/25/2015 03:48:48 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#ifndef STATE_HPP
#define STATE_HPP

#include "deps.hpp"
#include "types.hpp"

namespace feather
{

    namespace state
    {

        enum SGMode { None, DoIt, DrawGL, DrawSelection };

        struct FState {
            FState() : sgmode(None) { };
            SGMode sgmode;
        };

    } // namespace state

} // namespace feather

#endif
