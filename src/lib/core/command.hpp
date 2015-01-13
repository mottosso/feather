// =====================================================================================
// 
//       Filename:  command.hpp
// 
//    Description:  These are core commands that can be used in plugins and called
//                  by the UI.
// 
//        Version:  1.0
//        Created:  11/11/2014 02:45:22 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
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

        template <> struct run<0> {
            static status exec(std::string cmd, parameter::ParameterList) { return status(FAILED,"no command found"); };
        }; 


#define ADD_COMMAND(cmdstring,cmdenum,funct)\
        template <> struct run<cmdenum> {\
            static status exec(std::string cmd, parameter::ParameterList params) {\
                if(cmd==cmdstring)\
                return funct(params);\
                else\
                return run<cmdenum-1>::exec(cmd, params);\
            };\
        };


    } // namespace command

} // namespace feather

#endif
