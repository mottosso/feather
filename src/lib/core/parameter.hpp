/***********************************************************************
 *
 * Filename: parameter.hpp
 *
 * Description: Holds values for attributes in commands.
 *
 * Copyright (C) 2015 Richard Layman, rlayman2000@yahoo.com 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ***********************************************************************/

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
