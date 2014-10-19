// =====================================================================================
// 
//       Filename:  shader.hpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/13/2014 04:42:31 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#ifndef SHADER_HPP
#define SHADER_HPP

#include "deps.hpp"
#include "types.hpp"
#include "status.hpp"

namespace feather
{

    namespace shader
    {

        enum Type {
            End=0,
            Matte,
            Phong,
            Blinn,
            N 
        };

    } // namespace shader

} // namespace feather

#endif
