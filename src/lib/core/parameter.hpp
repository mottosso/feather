// =====================================================================================
// 
//       Filename:  parameter.hpp
// 
//    Description:  Parameters hold the value of a data type. The difference between a
//                  parameter and a field is that fields are used by nodes and can be
//                  connected together but parameters are used to pass data to commands.
// 
//        Version:  1.0
//        Created:  12/17/2014 04:17:55 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#ifndef PARAMETER_HPP
#define PARAMETER_HPP

#include "types.hpp"
#include "deps.hpp"

namespace feather
{

    namespace parameter
    {

        enum Type {
            Null,
            Bool,
            Int,
            Real,
            String
        };

        template <typename _T> static Type get_type_id() { return Null; };
        template <> Type get_type_id<bool>() { return Bool; };
        template <> Type get_type_id<int>() { return Int; };
        template <> Type get_type_id<double>() { return Real; };
        template <> Type get_type_id<std::string>() { return String; };

        struct ParameterBase
        {
            ParameterBase(std::string n, Type t): name(n), type(t) {};
            std::string name;
            Type type;
        };

        template <typename _T>
            struct Parameter : public ParameterBase
        {
            Parameter(std::string n, _T v=0) : ParameterBase(name,get_type_id<_T>()){ value=v; };
            _T value;
        };

        typedef std::vector<ParameterBase*> ParameterList;

    } // namespace parameter

} // namespace feather

#endif
