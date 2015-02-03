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
            _Type value;
        };

        typedef std::vector<FieldBase*> Fields;

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

#define ADD_FIELD_TO_NODE(__node,__type,__connection,__default_value,__field_key)\
    namespace feather {\
        template <> struct add_fields<__node,__field_key> {\
            static status exec(field::Fields& fields) {\
                 field::Field<__type,__connection>* f = new field::Field<__type,__connection>();\
                f->id=__field_key;\
                f->value=__default_value;\
                fields.push_back(f);\
                return add_fields<__node,__field_key-1>::exec(fields);\
            };\
        };\
\
        template <> field::FieldBase* field_data<__node,__field_key>(field::Fields& fields)\
        {\
            /*This is a cheap easy way to get FieldBase*\
            But it's needs to be changed later so we\
            don't have to scan the field every time\
            to get the pointer.*/\
            for(uint i=0; i < fields.size(); i++) {\
                if(fields.at(i)->id == __field_key){\
                    return fields.at(i);\
                }\
            }\
            /*std::cout << "never found matching key in field_data\n";*/\
            return NULL;\
        };\
 \
        template <> struct find_field<__node,__field_key> {\
            static field::FieldBase* exec(int fid, field::Fields& fields) {\
                /*std::cout << "find field - node:" << __node << ", fid:" << fid << ", field:" << __field_key << std::endl;*/\
                if(fid==__field_key){\
                    return field_data<__node,__field_key>(fields);\
                }else\
                    return find_field<__node,__field_key-1>::exec(fid,fields);\
            };\
        };\
    }

} // namespace feather 

#endif
