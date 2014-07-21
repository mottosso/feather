// =====================================================================================
// 
//       Filename:  qml.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/14/2014 05:45:21 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#include "qml.hpp"
#include "polygon_mesh.hpp"
#include "scenegraph.hpp"

using namespace feather::qml;

QmlSceneGraph::QmlSceneGraph(QObject* parent)
{

}

QmlSceneGraph::~QmlSceneGraph()
{

}

void QmlSceneGraph::make_cube()
{
    std::cout << "make cube\n";

    // create a sgNode
    scenegraph::sgNode sgnode;

    // setup the node 
    sgnode.id=0;
    sgnode.node = node::PolygonMesh;    
    //sgnode.fields.v

    scenegraph::SceneGraphSingleton::Instance()->push_back(sgnode);
    scenegraph::update();
}
