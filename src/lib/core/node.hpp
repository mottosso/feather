/***********************************************************************
 *
 * Filename: node.hpp
 *
 * Description: Describes the plugin nodes.
 *
 * Copyright (C) 2015 Richard Layman, rlayman2000@yahoo.com 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ***********************************************************************/

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

#define GL_INIT(__node_enum)\
    template <> void node_gl_init<__node_enum>(FNode& node, FGlInfo& info)

#define GL_DRAW(__node_enum)\
    template <> void node_gl_draw<__node_enum>(FNode& node, FGlInfo& info)

#define NODE_INIT(__node_enum,__node_type,__node_icon)\
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
        template <> struct call_gl_inits<__node_enum> {\
            static void exec(FNode& node, FGlInfo& info) {\
                /*std::cout << "call_gl_init\n";*/\
                if(node.node==__node_enum){\
                    node_gl_init<__node_enum>(node,info);\
                } else {\
                    call_gl_inits<__node_enum-1>::exec(node,info);\
                }\
            };\
        };\
        \
        template <> struct call_gl_draws<__node_enum> {\
            static void exec(FNode& node, FGlInfo& info) {\
                /*std::cout << "call_gl_draws\n";*/\
                if(node.node==__node_enum){\
                    node_gl_draw<__node_enum>(node,info);\
                } else {\
                    call_gl_draws<__node_enum-1>::exec(node,info);\
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
                    return find_node_type<__node_enum-1>::exec(id);\
                }\
            };\
        };\
        \
        template <> struct find_node_icon<__node_enum,__node_icon> {\
            static bool exec(int id,std::string& file) {\
                if(id==__node_enum){\
                    file=__node_icon;\
                } else {\
                    find_node_icon<__node_enum-1>::exec(id,file);\
                }\
            };\
        };\
        \
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
