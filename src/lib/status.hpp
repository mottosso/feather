// =====================================================================================
// 
//       Filename:  status.hpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/08/2014 04:58:46 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#ifndef STATUS_HPP
#define STATUS_HPP

#include "deps.hpp"

namespace feather 
{

    enum StatusState { FAILED, PASSED, WARNING };

    struct status
    {
        status(StatusState _state=PASSED, std::string _msg="") : state(_state),msg(_msg) {};
        StatusState state;
        std::string msg;
    };

}; // namespace feather

#endif
