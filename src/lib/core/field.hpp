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

        /*
        struct Connection
        {
            int node; // unique plugin node id
            int field; // unique node field id
            int vertex; // unique sg node id
        };
        */

        struct FieldBase
        {
            int id;
            //Connection connection;
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

/*
#define MAKE_FIELD(_id,_type,connection,_nodetype,_node,_default)\

#define CONNECT_FIELDS(_id,_n1,_n2)\
    FFieldConnection connection = boost::add_edge(_n1,_n2,sg);\
    sg[connection.first].id=_id; 
*/

#define ADD_FIELD_TO_NODE(node,field_struct,field_attr,field_key)\
    namespace feather {\
        template <> field::FieldBase* field_data<node,field_key>(PluginNodeFields* fields)\
        {\
            field_struct* f = static_cast<field_struct*>(fields);\
            return f->field_attr;\
        };\
 \
        template <> struct find_field<node,field_key> {\
            static field::FieldBase* exec(int fid, PluginNodeFields* fields) {\
                if(fid==field_key)\
                    return field_data<node,field_key>(fields);\
                else\
                    return field_data<node,field_key-1>(fields);\
            };\
        };\
    }

} // namespace feather 

#endif
