// =====================================================================================
// 
//       Filename:  object.hpp
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
#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "types.hpp"
#include "deps.hpp"

namespace feather
{

    namespace object 
    {

        enum Type {
            Polygon,
            PolygonPlane,
            Curve,
            Point,
            N
        };

    } // namespace object 

} // namespace feather

#endif
