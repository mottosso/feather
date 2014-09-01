// =====================================================================================
// 
//       Filename:  scenegraph.hpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/08/2014 05:02:24 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#ifndef SCENEGRAPH_HPP
#define SCENEGRAPH_HPP

#include "deps.hpp"
#include "types.hpp"
#include "node.hpp"
#include "field.hpp"
#include "singleton.hpp"

namespace feather
{

    namespace scenegraph
    {

        template <int NodeType>       
        status draw_gl(FAttributeArray* attrs) { return status(FAILED,"no node type for draw_gl()"); };
 
        template <int RendererType, int NodeType>
        status render(FAttributeArray* attrs) { return status(FAILED,"no node type for render()"); };

        template <int NodeType>
        status do_it(FAttributeArray* attrs) { return status(FAILED,"no node for do_it() for type"); };

    } // namespace scenegraph

} // namespace feather

#endif
