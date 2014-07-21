// =====================================================================================
// 
//       Filename:  field.hpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/13/2014 05:56:46 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#ifndef FIELD_HPP
#define FIELD_HPP

#include "deps.hpp"
#include "types.hpp"
#include "status.hpp"

namespace feather
{

    namespace field
    {

        enum Type {
            EndField,
            Bool,
            Int,
            Double,
            String,
            ColorRGB,
            ColorRGBA,
            Vertex2D,
            Vertex3D,
            Normal3D,
            TextureCoord,
            Matrix4x4,
            IntArray,
            DoubleArray,
            ColorRGBArray,
            ColorRGBAArray,
            Vertex2DArray,
            Vertex3DArray,
            NormalArray,
            TextureCoordArray,
            Matrix4x4Array,
            StartField
        };

        template <typename _Field>
            struct Field
            {
                _Field value;            
            };

    } // namespace field

} // namespace feather

#endif
