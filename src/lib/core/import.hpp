// =====================================================================================
// 
//       Filename:  import.hpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  12/17/2014 03:58:18 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#ifndef IMPORT_HPP
#define IMPORT_HPP

#include "types.hpp"
#include "deps.hpp"

namespace feather
{

    namespace import
    {

        enum Format {
            Obj,
            3ds,
            Dxf,
            Wings,
            Blender
        };

        template <int _Format> status import() { return Status(Failed,"format not supported"); };

    } // namespace import

} // namespace feather

#endif
