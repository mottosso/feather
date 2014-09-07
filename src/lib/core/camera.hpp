// =====================================================================================
// 
//       Filename:  camera.hpp
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
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "types.hpp"
#include "deps.hpp"

namespace feather
{

    namespace camera 
    {

        enum Type {
            Null,
            Orthographic,
            Perspective,
            N
        };

    } // namespace camera 

} // namespace feather

#endif
