// =====================================================================================
// 
//       Filename:  field.hpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  09/07/2013 05:48:43 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#ifndef FIELD_HPP
#define FIELD_HPP

namespace feather 
{
    
    namespace field
    {

        struct FieldBase
        {
            int id;
        };

        template <typename _T>
        struct Field : public FieldBase
        {
            typedef _T type;
        };

        namespace Connection
        {
            enum Type {
                In,
                Out
            };
        } // namespace Connection

        enum Type {
            Bool,
            Int,
            Float,
            Vertex,
            Vector,
            Mesh,
            RGB,
            RGBA,
            BoolArray,
            IntArray,
            FloatArray,
            VertexArray,
            VectoryArray,
            RGBArray,
            RGBAArray,
            N
        };


    } // namespace field

#define MAKE_FIELD(_id,_type,connection,_nodetype,_node,_default)\
    

#define CONNECT_FIELDS(_id,_n1,_n2)\
    FFieldConnection connection = boost::add_edge(_n1,_n2,sg);\
    sg[connection.first].id=_id; 

} // namespace feather 

#endif
