// =====================================================================================
// 
//       Filename:  light.hpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  09/07/2014 05:45:56 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "types.hpp"
#include "deps.hpp"

namespace feather
{

    namespace light 
    {

        enum Type {
            Null,
            Point,
            Spot,
            Area,
            HDR,
            N
        };

    } // namespace light 

} // namespace feather

#endif
