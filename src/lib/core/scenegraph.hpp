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
#include "selection.hpp"
#include "data.hpp"

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
     */

    static FSceneGraph sg;

    static std::vector<FNodeDescriptor> node_selection;


    namespace scenegraph
    {

        template <const int T>
            //status do_it(FNodeDescriptor node) { std::cout << "base do_it() called\n"; return status(false,"missing node"); };
            struct do_it {
                static status exec(FNodeDescriptor node)
                {
                    return do_it<T-1>::exec(node);
                };
            };

        template <> status do_it<node::Null>::exec(FNodeDescriptor node) { return status(FAILED, "no node do_it found"); };

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
             *      examine edge A->B // send the field value to the target node's fields - this will probably not be needed send the target will just hold a pointer to the source field  
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
                    //std::cout << "init vertex " << sg[u].id << std::endl;
                }

            // Start Vertex
            /*
             * This should be called by the source vertex at the start but I haven't seen it yet.
             */
            template < typename Vertex, typename Graph >
                void start_vertex(Vertex u, const Graph & g) const
                {
                    //std::cout << "start vertex " << sg[u].id << std::endl;
                }

            // Discover Vertex
            /*
             * This gets called each time a vertex is encountered
             */
            template < typename Vertex, typename Graph >
                void discover_vertex(Vertex u, const Graph & g) const
                {
                    //std::cout << "discover vertex " << sg[u].id << std::endl;
                    scenegraph::do_it<node::N>::exec(u);
                }

            // Finish Vertex
            /*
             * This gets called each time a vertex's child vertex are finished
             */
            template < typename Vertex, typename Graph >
                void finish_vertex(Vertex u, const Graph & g) const
                {
                    //std::cout << "finish vertex " << sg[u].id << std::endl;
                }

            // EDGES

            // Examine Edge
            /*
             * This gets called after a vertex has been discovered and after a node has finished
             */
            template < typename Edge, typename Graph >
                void examine_edge(Edge u, const Graph & g) const
                {
                    //std::cout << "examine edge " << sg[u].id << std::endl;
                }



            // Tree Edge
            /*
             * This gets called each after the examine edge and only for edges that will make a tree
             * This would be used to draw the Outliner graph
             */
            template < typename Edge, typename Graph >
                void tree_edge(Edge u, const Graph & g) const
                {
                    //std::cout << "tree edge " << sg[u].id << std::endl;
                }

            // Forward or Cross  Edge
            /*
             * This should be called in forward or cross edges but I never saw it. 
             */
            template < typename Edge, typename Graph >
                void forward_or_cross_edge(Edge u, const Graph & g) const
                {
                    std::cout << "forward or cross edge " << sg[u].id << std::endl;
                }


    };


    namespace scenegraph
    {

        template <int T>
            status add_node(int id)
            {
                return status(FAILED, "unknown node");
            };


        template <int _Node>
        struct add_sgnode {
            static status exec(int node, int id) {
                if(node == _Node) {
                    add_node<_Node>(id);
                    return status();
                }
                return add_sgnode<_Node-1>::exec(node,id);
            };
        };

        template <> struct add_sgnode<0> {
            static status exec(int node, int id) { return status(FAILED,"no known node found"); };
        };


        status update()
        {
            node_visitor vis;
            //node_d_visitor vis;
            //std::cout << "\n*****GRAPH UPDATE*****\n";
            breadth_first_search(sg, vertex(0, sg), visitor(vis));
            //FNodeDescriptor s = vertex(0, scenegraph);
            /*
               dijkstra_shortest_paths(scenegraph, s,
               predecessor_map(boost::make_iterator_property_map(p.begin(),
               get(boost::vertex_index, scenegraph))).distance_map(boost::make_iterator_property_map(d.begin(),
               get(boost::vertex_index, scenegraph))));
               */
            //std::cout << "*****UPDATE COMPLETE*****\n";
            return status();
        };


        status draw_gl()
        {
            node_visitor vis;
            //node_d_visitor vis;
            //std::cout << "\n*****DRAW GL START*****\n";
            breadth_first_search(sg, vertex(0, sg), visitor(vis));
            //std::cout << "*****DRAW GL COMPLETE*****\n";
            return status();
        }


        bool connect(int id, FNodeDescriptor n1, FNodeDescriptor n2)
        {
            // f1 = parent
            // f2 = child
            FFieldConnection connection = boost::add_edge(n1, n2, sg);
            sg[connection.first].id = id;

            return true;
            //return f2->connect(f1);
        };

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



} // namespace feather

#endif
