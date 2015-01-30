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
            Null,
            Camera,
            Light,
            Texture,
            Modifier,
            Deformer,
            Manipulator,
            Shader,
            Object,
            Curve,
            Polygon,
            N
        };

        /*
         * This is used by the PluginManager to find
         * out if the node is in the plugin.
         */
        template <int _Node>
        static bool exist() { return false; };

    } // namespace node

} // namespace feather

#define DO_IT(__node_enum)\
    template <> status node_do_it<__node_enum>(field::Fields& fields)

#define DRAW_GL(__node_enum)\
    template <> void node_draw_gl<__node_enum>(field::Fields& fields)

#define NODE_INIT(__node_enum,__node_type)\
    namespace feather {\
        template <> struct call_do_its<__node_enum> {\
            static status exec(int id, field::Fields& fields) {\
                if(id==__node_enum){\
                    return node_do_it<__node_enum>(fields);\
                } else {\
                    return call_do_its<__node_enum-1>::exec(id,fields);\
                }\
            };\
        };\
        \
        template <> struct call_draw_gls<__node_enum> {\
            static void exec(int id, field::Fields& fields) {\
                if(id==__node_enum){\
                    node_draw_gl<__node_enum>(fields);\
                } else {\
                    call_draw_gls<__node_enum-1>::exec(id,fields);\
                }\
            };\
        };\
        \
        template <> struct find_nodes<__node_enum> {\
            static bool exec(int id) {\
                if(id==__node_enum){\
                    return true;\
                } else {\
                    return find_nodes<__node_enum-1>::exec(id);\
                }\
            };\
        };\
        \
        template <> struct find_node_type<__node_enum> {\
            static bool exec(int id) {\
                if(id==__node_enum){\
                    return __node_type;\
                } else {\
                    return find_nodes<__node_enum-1>::exec(id);\
                }\
            };\
        };\
        template <> struct find_create_fields<__node_enum> {\
            static  status exec(int id, field::Fields& fields) {\
                if(id==__node_enum){\
                    return add_fields<__node_enum,600>::exec(fields);\
                } else {\
                    return find_create_fields<__node_enum-1>::exec(id,fields);\
                }\
                return status();\
            };\
        };\
    }

#endif
