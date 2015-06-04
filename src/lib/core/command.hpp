/***********************************************************************
 *
 * Filename: command.hpp
 *
 * Description: Used to create custome commands in plugins.
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


#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "deps.hpp"
#include "types.hpp"
#include "parameter.hpp"

namespace feather
{

    namespace command
    {

        template <int _Command>
        struct run {
            static status exec(std::string cmd, parameter::ParameterList);
        };

        template <int _Command>
        struct exist {
            static bool exec(std::string n);
        };

        /*
        template <int _Command>
        struct find_id{
            static bool exec(std::string n, int& i);
        };
        */

        // defaults

        template <> struct run<0> {
            static status exec(std::string cmd, parameter::ParameterList) { return status(FAILED,"no command found"); };
        }; 

        template <> struct exist<0> {
            static bool exec(std::string n) { return false; };
        };

        /*
        template <int _Command>
        struct id {
            static const int exec(std::string n)
        };
        */

        // get command parameter name
        template <int _Parameter, int _Command>
        struct get_parameter_name {
            static status exec(std::string c, int k, std::string& n) {
                return get_parameter_name<_Parameter,_Command-1>::exec(c,k,n);
            }; 
        };

        template <int _Parameter>
        struct get_parameter_name<_Parameter,0> {
            static status exec(std::string c, int p, std::string& n) { return status(FAILED,"could not find parameter name"); };
        };

    
        // get command parameter type
        template <int _Parameter, int _Command>
        struct get_parameter_type {
            static status exec(std::string n, int k, parameter::Type& t) {
                return get_parameter_type<_Parameter,_Command-1>::exec(n,k,t);
            }; 
        };

        template <int _Parameter>
        struct get_parameter_type<_Parameter,0> {
            static status exec(std::string n, int p, parameter::Type& t) { return status(FAILED,"could not find parameter type"); };
        };

        /*
        template <int _Command>
        struct find_id {
            static status exec(std::string n);
        };

        template <> struct find_id<0> {
            static status exec(std::string n) { return status(FAILED,"was not able to find command"); };
        };
        */

        /*
        template <int _Command>
        struct find_command {
            static bool exec(std::string n);
        };
        
        template <> struct find_command<0> {
            static bool exec(std::string n) { return false; };
        };
        */

    } // namespace command

} // namespace feather


#define ADD_COMMAND(cmdstring,cmdenum,funct)\
namespace feather\
{\
    namespace command\
    {\
        template <> struct run<cmdenum> {\
            static status exec(std::string cmd, parameter::ParameterList params) {\
                if(cmd==cmdstring)\
                    return funct(params);\
                else\
                    return run<cmdenum-1>::exec(cmd, params);\
            };\
        };\
        \
        template <> struct exist<cmdenum> {\
            static bool exec(std::string n) {\
                if(n==cmdstring)\
                    return true;\
                else\
                    return exist<cmdenum-1>::exec(n);\
            };\
        };\
        \
        template <int _Parameter> struct get_parameter_name<_Parameter,cmdenum> {\
            static status exec(std::string c, int p, std::string& n) {\
                if(c==cmdstring)\
                    return parameter::get_name<20,cmdenum>::exec(p,n);\
                else\
                    return get_parameter_name<_Parameter,cmdenum-1>::exec(c,p,n);\
            };\
        };\
        \
        template <int _Parameter> struct get_parameter_type<_Parameter,cmdenum> {\
            static status exec(std::string n, int p, parameter::Type& t) {\
                if(n==cmdstring)\
                    return parameter::get_type<20,cmdenum>::exec(p,t);\
                else\
                    return get_parameter_type<_Parameter,cmdenum-1>::exec(n,p,t);\
            };\
        };\
    } /* namespace command */\
}  /* namespace feather */\

// check if the command exists
//bool command_exist(std::string cmd) { return (cmd==cmdstring) ? true : false; };


#define INIT_COMMAND_CALLS(cmdenum)\
/* call the command */\
feather::status command(std::string cmd, feather::parameter::ParameterList params) {\
    typedef feather::command::run<feather::command::cmdenum> call;\
    return call::exec(cmd, params);\
};\
\
/* check to see if the command exist */\
bool command_exist(std::string cmd) { return feather::command::exist<feather::command::cmdenum>::exec(cmd); };\
\
/* get the parameter name */\
feather::status parameter_name(std::string c, int k, std::string& n) {\
    return feather::command::get_parameter_name<20,feather::command::cmdenum>::exec(c,k,n);\
};\
\
/* get the parameter type */\
feather::status parameter_type(std::string n, int k, parameter::Type& t) {\
    return feather::command::get_parameter_type<20,feather::command::cmdenum>::exec(n,k,t);\
};\


#endif
