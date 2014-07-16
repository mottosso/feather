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

        typedef struct { int id; node::Type node; field::FieldContainer* fields; } sgNode;

        typedef std::vector<sgNode> SceneGraph;

        typedef Singleton<SceneGraph> SceneGraphSingleton;        
        
        status draw_gl() { return status(); };

        template <int _StartType, int _EndType>
        struct get_type
        {
            static int exec(sgNode& n) {
                if(n.node == _StartType)
                    return _StartType;
                else
                    return get_type<_StartType-1,_EndType>::exec(n);
            };
        };

        template <> int get_type<0,0>::exec(sgNode& n) { return 0; };


        /* ADD NODE TO SCENEGRAPH */
    
        template <int _Node, typename _Fields>
        struct add_node
        {
            static status exec(_Fields field) { return status(); };
        };


        /* DRAW SCENEGRAPH */

        status draw_sg() { return status(); };

        status update() { return status(); };

    } // namespace scenegraph

} // namespace feather

#endif
