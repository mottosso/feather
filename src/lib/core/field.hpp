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

        namespace Connection
        {
            enum Type {
                Null,
                In,
                Out,
                In_Out
            };
        } // namespace Connection

        enum Type {
            Null,
            Bool,
            Int,
            Float,
            Vertex,
            Vector,
            RGB,
            RGBA,
            BoolArray,
            IntArray,
            FloatArray,
            VertexArray,
            VectoryArray,
            RGBArray,
            RGBAArray
        };

    } // namespace field

#define CONNECT_FIELDS(_name,_n1,_n2)\
    FFieldConnection connection = boost::add_edge(_n1,_n2,sg);\
    sg[connection.first].name=_name; 

} // namespace feather 

#endif
