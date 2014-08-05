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
            sgNode(int _id, node::Type _ntype, node::NodeAttributes* _nattr=NULL, Fields* _fields=NULL):id(_id),ntype(_ntype),nattr(_nattr),fields(_fields){};
            int id;
            node::Type ntype;
            node::NodeAttributes* nattr;
            Fields* fields;
        };

        typedef std::vector<sgNode> SceneGraph;

        typedef Singleton<SceneGraph> SceneGraphSingleton;        
        
        inline status add_node(int id, node::Type ntype, node::NodeAttributes* nattr=NULL, Fields* fields=NULL)
        {
            SceneGraphSingleton::Instance()->push_back(sgNode(id,ntype,nattr,fields));
            return status();
        };

        /* DRAW SCENEGRAPH */

        inline status draw_sg(QMatrix4x4 view)
        {
            //std::cout << "sg size:" << SceneGraphSingleton::Instance()->size() << std::endl;

            for(uint i=0; i<SceneGraphSingleton::Instance()->size(); i++)
            {
                sgNode n = SceneGraphSingleton::Instance()->at(i);
                n.nattr->view=view;
                switch(n.ntype)
                {
                    case node::PolygonMesh :
                        node::Node<node::PolygonMesh>::draw_gl(n.nattr,n.fields);
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
