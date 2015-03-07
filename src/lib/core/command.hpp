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

        // defaults

        template <> struct run<0> {
            static status exec(std::string cmd, parameter::ParameterList) { return status(FAILED,"no command found"); };
        }; 

        template <> struct exist<0> {
            static bool exec(std::string n) { return false; };
        };

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
bool command_exist(std::string cmd) { return feather::command::exist<feather::command::cmdenum>::exec(cmd); };


#endif
