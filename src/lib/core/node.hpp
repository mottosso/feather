// =====================================================================================
// 
//       Filename:  node.hpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/08/2014 04:46:04 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#ifndef NODE_HPP
#define NODE_HPP

#include "deps.hpp"
#include "types.hpp"
#include "status.hpp"
#include "object.hpp"
#include "field.hpp"

namespace feather
{

    namespace node
    {

        enum Type {
            Root,
            Null,
            Camera,
            Light,
            Texture,
            Shader,
            Transform,
            Shading,
            PolygonMesh,
            PolygonPlane,
            StartNode
        };

    } // namespace node

#define SET_NODE_DATA(_data_)\
    template <> _data_* DataObject::get_data<_data_>(FNodeDescriptor node) { return static_cast<_data_*>(sg[node].data); };

#define GET_NODE_DATA(_data_)\
    _data_* pdata = sg[node].data->get_data<_data_>(node);


} // namespace feather

#endif
