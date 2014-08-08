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

namespace feather
{

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

    }



    class node_visitor : public boost::default_bfs_visitor
    {
        public:
            //typedef boost::on_finish_vertex event_filter;

            /*
             *  The order of update for a graph like this:
             *      A
             *     / \
             *  ->B-->C
             *  |/
             *  D 
             *
             *  would be this: 
             *      init vertex A
             *      init vertex B
             *      init vertex C
             *      init vertex D
             *      discover vertex A
             *      examine edge A->B
             *      tree edge A->B
             *      discover vertex B
             *      examine edge A->C
             *      tree edge A->C
             *      discover vertex C
             *      finish vertex A
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
                    std::cout << "init vertex " << sg[u].name << std::endl;
                }

            // Start Vertex
            /*
             * This should be called by the source vertex at the start but I haven't seen it yet.
             */
            template < typename Vertex, typename Graph >
                void start_vertex(Vertex u, const Graph & g) const
                {
                    std::cout << "start vertex " << sg[u].name << std::endl;
                }

            // Discover Vertex
            /*
             * This gets called each time a vertex is encountered
             */
            template < typename Vertex, typename Graph >
                void discover_vertex(Vertex u, const Graph & g) const
                {
                    std::cout << "discover vertex " << sg[u].name << std::endl;
                    scenegraph::do_it<node::StartNode>::exec(u);
                }

            // Finish Vertex
            /*
             * This gets called each time a vertex's child vertex are finished
             */
            template < typename Vertex, typename Graph >
                void finish_vertex(Vertex u, const Graph & g) const
                {
                    std::cout << "finish vertex " << sg[u].name << std::endl;
                }

            // EDGES

            // Examine Edge
            /*
             * This gets called after a vertex has been discovered and after a node has finished
             */
            template < typename Edge, typename Graph >
                void examine_edge(Edge u, const Graph & g) const
                {
                    std::cout << "examine edge " << sg[u].name << std::endl;
                }



            // Tree Edge
            /*
             * This gets called each after the examine edge and only for edges that will make a tree
             * This would be used to draw the Outliner graph
             */
            template < typename Edge, typename Graph >
                void tree_edge(Edge u, const Graph & g) const
                {
                    std::cout << "tree edge " << sg[u].name << std::endl;
                }

            // Forward or Cross  Edge
            /*
             * This should be called in forward or cross edges but I never saw it. 
             */
            template < typename Edge, typename Graph >
                void forward_or_cross_edge(Edge u, const Graph & g) const
                {
                    std::cout << "forward or cross edge " << sg[u].name << std::endl;
                }


    };

    namespace scenegraph
    {

        template <node::Type T>
            status add_node(std::string name)
            {
                return status(FAILED, "unknown node");
            };


        status update()
        {
            node_visitor vis;
            //node_d_visitor vis;
            std::cout << "\n*****GRAPH UPDATE*****\n";
            breadth_first_search(sg, vertex(0, sg), visitor(vis));
            //FNodeDescriptor s = vertex(0, scenegraph);
            /*
               dijkstra_shortest_paths(scenegraph, s,
               predecessor_map(boost::make_iterator_property_map(p.begin(),
               get(boost::vertex_index, scenegraph))).distance_map(boost::make_iterator_property_map(d.begin(),
               get(boost::vertex_index, scenegraph))));
               */
            std::cout << "*****UPDATE COMPLETE*****\n";
            return status();
        };



        bool connect(std::string n, FNodeDescriptor n1, FNodeDescriptor n2)
        {
            // f1 = parent
            // f2 = child
            FFieldConnection connection = boost::add_edge(n1, n2, sg);
            sg[connection.first].name = n;

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
