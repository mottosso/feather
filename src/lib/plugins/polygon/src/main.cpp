// =====================================================================================
// 
//       Filename:  main.cpp
// 
//    Description:  This plugin holds the POLYGON_PLANE, POLYGON_CUBE scenegraph nodes.
// 
//        Version:  1.0
//        Created:  11/03/2014 04:44:11 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#include "deps.hpp"
#include "pluginmanager.hpp"
#include "field.hpp"
#include "node.hpp"
#include "parameter.hpp"
#include "command.hpp"

#ifdef __cplusplus
extern "C" {
#endif
    C_PLUGIN_WRAPPER()
#ifdef __cplusplus
}
#endif

using namespace feather;

#define POLYGON_SHAPE 320
#define POLYGON_PLANE 321
#define POLYGON_CUBE 322


PLUGIN_INIT(POLYGON_SHAPE,POLYGON_CUBE)


/*
 ***************************************
 *            POLYGON SHAPE            *
 ***************************************
*/

// meshIn
ADD_FIELD_TO_NODE(POLYGON_SHAPE,FMesh,field::Mesh,field::connection::In,FMesh(),1)
// testIn
ADD_FIELD_TO_NODE(POLYGON_SHAPE,int,field::Int,field::connection::In,10,2)


namespace feather
{

    DO_IT(POLYGON_SHAPE)
    { 
        //PolygonShapeFields* shape = static_cast<PolygonShapeFields*>(fields);
        typedef field::Field<int,field::connection::In>* fielddata;
    fielddata f = static_cast<fielddata>(fields.at(0));
  
        std::cout << "value from polycube field:" << f->value << std::endl;

        return status();
    };

    GL_DRAW(POLYGON_SHAPE)
    {
        std::cout << "polygonshape glinfo\n";
    }; 

    /*
    DRAW_GL(POLYGON_SHAPE)
    { 
        //PolygonShapeFields* plane = static_cast<PolygonShapeFields*>(fields);
        //std::cout << "drawing shape mesh:" << plane->meshIn << std::endl;
    };
    */

} // namespace feather

NODE_INIT(POLYGON_SHAPE,node::Polygon)


/*
 ***************************************
 *            POLYGON PLANE            *
 ***************************************
*/

ADD_FIELD_TO_NODE(POLYGON_PLANE,int,field::Int,field::connection::In,2,1)
ADD_FIELD_TO_NODE(POLYGON_PLANE,int,field::Int,field::connection::In,2,2)



namespace feather
{

    DO_IT(POLYGON_PLANE)
    { 
        //PolygonPlaneFields* plane = static_cast<PolygonPlaneFields*>(fields);
        //std::cout << "plane: subX:" << plane->subX << std::endl;

        return status();
    };

} // namespace feather

NODE_INIT(POLYGON_PLANE,node::Polygon)


/*
 ***************************************
 *            POLYGON CUBE             *
 ***************************************
*/

ADD_FIELD_TO_NODE(POLYGON_CUBE,int,field::Int,field::connection::In,0,1)
ADD_FIELD_TO_NODE(POLYGON_CUBE,int,field::Int,field::connection::In,0,2)
ADD_FIELD_TO_NODE(POLYGON_CUBE,int,field::Int,field::connection::In,0,3)
ADD_FIELD_TO_NODE(POLYGON_CUBE,int,field::Int,field::connection::Out,5,4)

namespace feather
{

    DO_IT(POLYGON_CUBE) 
    {
        //PolygonCubeFields* cube = static_cast<PolygonCubeFields*>(fields);
        //std::cout << "cube: subX:" << cube->subX << std::endl;
        return status();
    };

} // namespace feather

NODE_INIT(POLYGON_CUBE,node::Polygon)


/*
 ***************************************
 *              COMMANDS               *
 ***************************************
*/

namespace feather
{
    namespace command
    {
        enum Command { N=0 };
    } // namespace command

} // namespace feather

INIT_COMMAND_CALLS(N)
