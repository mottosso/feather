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

        struct sgNode
        {
            sgNode(int _id, node::Type _node, Fields* _fields=NULL):id(_id),node(_node),fields(_fields){};
            int id;
            node::Type node;
            Fields* fields;
        };

        typedef std::vector<sgNode> SceneGraph;

        typedef Singleton<SceneGraph> SceneGraphSingleton;        
        
        inline status add_node(int id, node::Type node, Fields* fields=NULL)
        {
            SceneGraphSingleton::Instance()->push_back(sgNode(id,node,fields));
            return status();
        };

        /* DRAW SCENEGRAPH */

        inline status draw_sg()
        {
            //std::cout << "sg size:" << SceneGraphSingleton::Instance()->size() << std::endl;

            for(uint i=0; i<SceneGraphSingleton::Instance()->size(); i++)
            {
                sgNode n = SceneGraphSingleton::Instance()->at(i);
//                std::cout << "draw_sg()\n";
                switch(n.node)
                {
                    case node::PolygonMesh :
//                        std::cout << "draw polgon mesh\n";
                        node::Node<node::PolygonMesh>::do_it(n.fields);
                        break;

                    default :
                        break;
                }
            }

            return status();
        };

        inline status update() { return status(); };

    } // namespace scenegraph

} // namespace feather

#endif
