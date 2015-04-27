/***********************************************************************
 *
 * Filename: scenegraph.hpp
 *
 * Description: Holds the nodes and handles how they interact with the ui.
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

#ifndef SCENEGRAPH_HPP
#define SCENEGRAPH_HPP

#include "deps.hpp"
#include "types.hpp"
#include "node.hpp"
#include "field.hpp"
#include "singleton.hpp"
#include "selection.hpp"
#include "data.hpp"
#include "object.hpp"
#include "camera.hpp"
#include "light.hpp"
#include "texture.hpp"
#include "shader.hpp"
#include "pluginmanager.hpp"
#include "state.hpp"

namespace feather
{

    /*
     * The SceneGraph holds the node tree. There is no node data stored in the
     * SceneGraph; only the node type and id. The id is mapped to the data so 
     * that the scenegraph can lookup it's values and then view or modify them
     * depending on the command. The scenegraph will manage when and in what order
     * the nodes will get called in. The scenegraph will also call the functions
     * for various stages of the update.
     *
     * When working with nodes 3 things are used - the scenegraph, data, and selection.
     * The scenegraph manages the order the nodes are updated.
     * The data holds each nodes value.
     * The selection tells the components and indics of what is to be worked on.
     * 
     * The scenegraph will call the node's doit() which will take the node's data
     * and work on it based on the selection.
     * A selection is not tied to any node. When a user clicks on a node's component,
     * a new SelectionState is added to the SelectionManager and is setup based on that node's
     * data. As the more vertex's are selected, the SelectionState is modified to match it.
     * This SelectionState is also used to draw the selections during the viewport's update.
     *
     * When a new node is added to the scenegraph a scenegraph vertex and datablock is created.
     * The datablock location is kept in sync with the vertex number by the datamanager.
     */

    static state::FState cstate;
    static FSceneGraph sg;

    static PluginManager plugins;

    static std::vector<FNodeDescriptor> node_selection;

    namespace scenegraph
    {

        int get_min_uid() { return plugins.min_uid(); };
        int get_max_uid() { return plugins.max_uid(); };

        void gl_init(FNode& node, FGlInfo& info) {
            plugins.gl_init(node,info); 
        };

        void gl_draw(FNode& node, FGlInfo& info) {
            plugins.gl_draw(node,info); 
        };

        status load_plugins() {
            return plugins.load_plugins();
        };
        
        /* Add Node
         * This function is called during specialization of nodes when
         * a new node is added to the scenegraph. It's called by add_node_to_sg
         * and is specialized by each node.
         */
        /* 
        template <int _Type, int _Node>
        static status add_node(int id) { return status(FAILED,"no matching node for add_node"); };
        */

        int add_node(int t, int n, std::string name) {
            std::cout << "add node: " << n << ", type: " << t << std::endl;

            // TODO
            // Here I need to ask the plugin manager if the node exists
 
            FNodeDescriptor uid = boost::add_vertex(sg);
            sg[uid].type = static_cast<feather::node::Type>(t);
            sg[uid].uid = uid;
            sg[uid].node = n;
            sg[uid].name = name;
            plugins.create_fields(n,sg[uid].fields);
            node_selection.push_back(n); 

            // Return the node number
            return static_cast<int>(uid);
        };

        /*  Get Node Connections 
         *  will add all the nodes connected to the
         *  uid to the nodes reference
         */
        void get_node_connections(int uid, std::vector<int>& nodes) {
            boost::edges(sg);    
        };

        status get_node_icon(int nid, std::string& file) {
            return plugins.node_icon_file(nid,file);
        };

        field::FieldBase* get_fieldBase(int uid, int node, int field) {
            field::FieldBase* f = plugins.get_fieldBase(uid,node,field,sg[uid].fields); 
            if(!f)
                return f;

            if(f->connected){
                //std::cout << "field is connected to uid:" << f->puid << ", node:" << f->pn << ", field " << f->pf << std::endl;
                return get_fieldBase(f->puid,f->pn,f->pf);
            } else {
                //std::cout << "field is not connected, returning the default field\n";
                return f;
            }
        };


        status add_selection(int type, int uid, int nid, int fid) {
            // status was returned here because we'll probably use it later
            smg::Instance()->add_state(static_cast<selection::Type>(type),uid,nid,fid);
            return status();
        };


        status node_selection(int type, int uid, int nid) {
            // status was returned here because we'll probably use it later
            smg::Instance()->add_state(static_cast<selection::Type>(type),uid,nid,0);
            return status();
        };

        status get_fid_list(int uid, int nid, field::connection::Type conn, std::vector<int>& list) {
            return plugins.get_fid_list(nid,conn,sg[uid].fields,list);
        }

        /* Add Node to SceneGraph
         * This is the recursive function that will keep going till
         * finds a match for the node or fail.
         * If a match is found the add_node function is called which
         * is specialized by each node.
         */
        /*
        template <int _Type, int _Node>
            struct add_node_to_sg {
                static status exec(int node)
                {
                    if(node==_Node)
                        return add_node<_Type,_Node>(node);
                    else
                        return add_node_to_sg<_Type,_Node-1>::exec(node);
                };
            };

        template <int _Type>
            struct add_node_to_sg<_Type,0> { static status exec(int node) { return status(FAILED, "could not add unknown node to scenegraph"); }; };
        */


        /* DoIt
         * This gets called during the scenegraph update and
         * currently is used to display the data but this may
         * change.
         */
        /* 
        template <int _Type, int _Node>
            struct do_it {
                static status exec(FNodeDescriptor node)
                {
                    return plugins.do_it(node);
                    // used this if you need to call a specific node
                    //return plugins.do_it(325);
                    // old test
                    //return do_it<_Type,_Node-1>::exec(node);
                };
            };

        template <int _Type> struct do_it<_Type,-1> { static status exec(FNodeDescriptor node) { return status(FAILED, "no node do_it found"); }; };
        */

    } // namespace scenegraph

    class node_visitor : public boost::default_bfs_visitor
    {
        public:
            //typedef boost::on_finish_vertex event_filter;

            /*
             *  The order of update for a graph like this:
             *      A
             *     / \
             *  ->B-->C
             *  |  \ /
             *  ----D
             *
             *  would be this: 
             *      init vertex A // do any setup that is needed for the node
             *      init vertex B
             *      init vertex C
             *      init vertex D
             *      discover vertex A // discover will call the parent and it's children nodes
             *      examine edge A->B // send the field value to the target node's fields - this will probably not be needed since the target will just hold a pointer to the source field  
             *      tree edge A->B
             *      discover vertex B
             *      examine edge A->C
             *      tree edge A->C
             *      discover vertex C
             *      finish vertex A // call the nodes do_it() 
             *      examine edge A->B
             *      examine edge B->C
             *      examine edge B->D
             *      tree edge B->D
             *      discover vertex D
             *      examine edge D->B
             *      finish vertex B
             *      examine edge A->C
             *      examine edge B->C
             *      examine edge C->D
             *      finish vertex C
             *      examine edge B->D
             *      examine edge C->D
             *      examine edge D->B
             *      finish vertex D
             */

            /*
             * The way node fields are handled are like this:
             *  ________                ________
             * | NODE A |  bgl edge    | NODE B |
             * |        |------------->|        |
             * |________|              |________|
             *
             * When a node is adjusted it will call Boost::BGL and tell
             * it that it has changed and to start the update at that node.
             * BGL will first call all the node::init() functions for
             * every node connected to the start node.
             * Then the graph walking begins.
             *      1: the node::discover() gets called for parent node followed by:
             *              node::examine() [parent to child]
             *              node::tree() [parent to child]
             *              node::discover() [child node]
             *              {THE ABOVE THREE STEPS ARE REPEATED FOR EACH CHILD}
             *      2: the node::do_it() for the parent is called since everything is safe for it to update
             *      3: move on to the next child node and repeat steps 1 and 2
             *
             * The opengl update is done the same except it always starts at
             * the root node and node::finish() is where the specialized draw()
             * function will be found.
             *
             * To handle these different states the scenegraph holds a State value
             * that will tell wheither the graph is in UPDATE, DRAW, or RENDER.
             *
             */

            /*
             * Update Process:
             */

            // VERTEX


            // Init Vertex
            /*
             * This gets called by all vertex at the beginning of an update.
             */
            template < typename Vertex, typename Graph >
                void initialize_vertex(Vertex u, const Graph & g) const
                {
                    std::cout << "init node " << sg[u].node << std::endl;
                    /*
                    if(cstate.sgMode==state::DrawGL)
                            plugins.draw_gl(sg[u].node);
                    */
                }

            // Start Vertex
            /*
             * This should be called by the source vertex at the start but I haven't seen it yet.
             */
            template < typename Vertex, typename Graph >
                void start_vertex(Vertex u, const Graph & g) const
                {
                    std::cout << "start node " << sg[u].node << std::endl;
                }

            // Discover Vertex
            /*
             * This gets called each time a vertex is encountered
             */
            template < typename Vertex, typename Graph >
                void discover_vertex(Vertex u, const Graph & g) const
                {
                    std::cout << "discover vertex:" << u << " node:" << sg[u].node << std::endl;
                    //scenegraph::do_it<node::N>::exec(u);

                    if(cstate.sgMode==state::DoIt)
                    {
                        status p = plugins.do_it(sg[u].node,sg[u].fields);
                        if(!p.state)
                            std::cout << "NODE FAILED! : \"" << p.msg << "\"\n";
                    }
 
                    // This might still come in handy later on
                    /*
                    switch(sg[u].type)
                    {
                        case node::Null:
                            scenegraph::do_it<node::Null,null::N>::exec(u);
                            break;
                        case node::Camera:
                            scenegraph::do_it<node::Camera,camera::N>::exec(u);
                            break;
                        case node::Light:
                            scenegraph::do_it<node::Light,light::N>::exec(u);
                            break;
                        case node::Texture:
                            scenegraph::do_it<node::Texture,texture::N>::exec(u);
                            break;
                        case node::Shader:
                            scenegraph::do_it<node::Shader,shader::N>::exec(u);
                            break;
                        case node::Object:
                            scenegraph::do_it<node::Object,object::N>::exec(u);
                            break;
                        default:
                            break;
                    }
                    */
                }

            // Finish Vertex
            /*
             * This gets called each time a vertex's child vertex are finished
             */
            template < typename Vertex, typename Graph >
                void finish_vertex(Vertex u, const Graph & g) const
                {
                    std::cout << "finish vertex " << sg[u].node << std::endl;
                }

            // EDGES

            // Examine Edge
            /*
             * This gets called after a vertex has been discovered and after a node has finished
             */
            template < typename Edge, typename Graph >
                void examine_edge(Edge u, const Graph & g) const
                {
                    std::cout << "examine edge - n1:" << sg[u].n1 
                        << " f1:" << sg[u].f1
                        << " n2:" << sg[u].n2
                        << " f2:" << sg[u].f2
                        << std::endl;
                }



            // Tree Edge
            /*
             * This gets called each after the examine edge and only for edges that will make a tree
             * This would be used to draw the Outliner graph
             */
            template < typename Edge, typename Graph >
                void tree_edge(Edge u, const Graph & g) const
                {
                    std::cout << "tree edge - n1:" << sg[u].n1 
                        << " f1:" << sg[u].f1
                        << " n2:" << sg[u].n2
                        << " f2:" << sg[u].f2
                        << std::endl;
                }

            // Forward or Cross  Edge
            /*
             * This should be called in forward or cross edges but I never saw it. 
             */
            template < typename Edge, typename Graph >
                void forward_or_cross_edge(Edge u, const Graph & g) const
                {
                    std::cout << "forward or cross edge " << sg[u].node << std::endl;
                }


    };


    namespace scenegraph
    {

        status update()
        {
            // Temporary turn off do_it updating for testing
            // set the state node update 
            cstate.sgMode = state::DoIt;

            node_visitor vis;
            //node_d_visitor vis;
            std::cout << "\n*****GRAPH UPDATE*****\n";
            breadth_first_search(sg, vertex(0, sg), visitor(vis));
            //FNodeDescriptor s = vertex(0, scenegraph);
               
               //dijkstra_shortest_paths(scenegraph, s,
               //predecessor_map(boost::make_iterator_property_map(p.begin(),
               //get(boost::vertex_index, scenegraph))).distance_map(boost::make_iterator_property_map(d.begin(),
               //get(boost::vertex_index, scenegraph))));
            std::cout << "*****UPDATE COMPLETE*****\n";

            //draw_gl();
            return status();
        };


        status connect(FNodeDescriptor n1, int f1, FNodeDescriptor n2, int f2)
        {
            // see if the two types can be connected
            int src_node = sg[n1].node;
            int tgt_node = sg[n2].node;
            field::FieldBase* sfield = get_fieldBase(n1,src_node,f1);
            field::FieldBase* tfield = get_fieldBase(n2,tgt_node,f2);
            std::cout 
                << "sn=" << src_node 
                << ", sfield=" << sfield->id 
                << ", sfieldtype=" << sfield->type
                << ", tn=" << tgt_node 
                << ", tfield=" << tfield->id 
                << ", tfieldtype=" << tfield->type
                << std::endl;

            // check to see if another field is already connected
            if(field::can_types_connect<field::START,field::START>::exec(sfield->type,tfield->type)) {
                FFieldConnection connection = boost::add_edge(n1, n2, sg);
                sg[connection.first].n1 = n1;
                sg[connection.first].f1 = f1;
                sg[connection.first].n2 = n2;
                sg[connection.first].f2 = f2;
                sg[connection.first].sfield = sfield;
                sg[connection.first].tfield = tfield;
                tfield->connected = true;
                tfield->puid = n1;
                tfield->pn = src_node;
                tfield->pf = f1;
            } else {
                return status(FAILED,"field types can not be connected");
            }

            return status();
        };

        
        //template <int _Type, int _Node>
        //status add_node(int id) { return status(FAILED,"no matching node for add_node"); };

        /* 
           status connect(FNodeDescriptor n1, FNodeDescriptor n2)
           {

        //FFieldConnection connection = boost::add_edge(n1, n2, scenegraph);
        //scenegraph[connection.first].name = "test1";
        return status(true,"");
        };
        */

        // template <> status do_it() { std::cout << "missing node" << std::endl; return status(false,"failed"); };

    } // namespace scenegraph

    #define GET_NODE_DATA(nodedata)\
    template <> nodedata* DataObject::get_data<nodedata>(FNodeDescriptor node) { return static_cast<nodedata*>(sg[node].data); };

 
} // namespace feather

#endif
