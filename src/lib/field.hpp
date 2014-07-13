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
            Real,
            String,
            StartField
        }

        template <int _Type>
            struct Field
            {
                static _Type value;
            };

    } // namespace field

#define MAKE_FIELD(_type,_name,_default,_min,_max)\
    typedef Field<_type> _name;\
    template <> _type _name::value=_default;

} // namespace feather

#endif
