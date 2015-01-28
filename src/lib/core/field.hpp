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
            bool update; // this is used to optimize the scenegraph update process - the sg won't call a node's do_it unless one of it's input's fields update flags are set to true.
        };

        template <typename _Type, int _Conn>
        struct Field : public FieldBase
        {
            Field():conn(_Conn){ update=true; };
            typedef _Type type;
            int conn;
        };

        namespace connection
        {
            enum Type {
                In,
                Out
            };
        } // namespace connection

        enum Type {
            N,
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
            START
        };


        template <int _Type1, int _Type2>
        bool can_connect() { return false; };

        template <int _Type1, int _Type2>
        struct can_types_connect {
            static bool exec(int t1, int t2) {
                if(t1==_Type1 && t2==_Type2)
                    return can_connect<_Type1,_Type2>();
                else if(_Type2 == N)
                    return can_types_connect<_Type1-1,START>::exec(t1,t2);
                else 
                    return can_types_connect<_Type1,_Type2-1>::exec(t1,t2);
            };
        };
   
        template <> struct can_types_connect<N,N> {
            static bool exec(int t1, int t2) { return false; };
        };

    } // namespace field

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
