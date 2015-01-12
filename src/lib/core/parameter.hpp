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
//         Author:  Richard Layman (), rlayman2000@yahoo.com //        Company:  
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
            ~ParameterBase(){};
            std::string name;
            Type type;
        };

        template <typename _T>
            struct Parameter : public ParameterBase
        {
            Parameter(std::string n, _T v=0) : ParameterBase(n,get_type_id<_T>()){ value=v; };
            ~Parameter() {};
            _T value;
        };

        struct ParameterList
        {
            ParameterList(){};
            ~ParameterList(){ m_params.clear(); };

            void addBoolParameter(std::string name, bool val) { m_params.push_back(new Parameter<bool>(name,val)); };

            void addIntParameter(std::string name, int val) { m_params.push_back(new Parameter<int>(name,val)); };

            void addRealParameter(std::string name, double val) { m_params.push_back(new Parameter<double>(name,val)); };

            void addStringParameter(std::string name, std::string val) { 
                m_params.push_back(new Parameter<std::string>(name,val));
            };

            template <typename _T>
                _T getParameterValue(std::string n) {
                    for(int i=0; m_params.size(); i++) {
                        if(m_params.at(i)->name==n)
                            return static_cast<Parameter<_T>*>(m_params.at(i))->value;
                    }
                    return 0;
                }

            private:
            std::vector<ParameterBase*> m_params;
        };

    } // namespace parameter

} // namespace feather

#endif
