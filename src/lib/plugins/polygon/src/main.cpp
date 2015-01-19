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

#define POLYGON_PLANE 325
#define POLYGON_CUBE 326

PLUGIN_INIT(POLYGON_PLANE,POLYGON_CUBE)

/*
 ***************************************
 *            POLYGON PLANE            *
 ***************************************
*/

namespace feather {

    struct PolygonPlaneFields : public PluginNodeFields
    {
        field::Field<int> *subX;
        field::Field<int> *subY;
    };

} // namespace feather

ADD_FIELD_TO_NODE(POLYGON_PLANE,PolygonPlaneFields,subX,1)
ADD_FIELD_TO_NODE(POLYGON_PLANE,PolygonPlaneFields,subY,2)


namespace feather
{

    DO_IT(POLYGON_PLANE)
    { 
        PolygonPlaneFields* plane = static_cast<PolygonPlaneFields*>(fields);
        std::cout << "plane: subX:" << plane->subX << std::endl;

        return status();
    };

} // namespace feather

NODE_INIT(POLYGON_PLANE)


/*
 ***************************************
 *            POLYGON CUBE             *
 ***************************************
*/

namespace feather
{
    struct PolygonCubeFields : public PluginNodeFields
    {
        field::Field<int> *subX;
        field::Field<int> *subY;
        field::Field<int> *subZ;
    };

} // namespace feather

ADD_FIELD_TO_NODE(POLYGON_CUBE,PolygonCubeFields,subX,1)
ADD_FIELD_TO_NODE(POLYGON_CUBE,PolygonCubeFields,subY,2)
ADD_FIELD_TO_NODE(POLYGON_CUBE,PolygonCubeFields,subZ,3)

namespace feather
{

    DO_IT(POLYGON_CUBE) 
    {
        PolygonCubeFields* cube = static_cast<PolygonCubeFields*>(fields);
        std::cout << "cube: subX:" << cube->subX << std::endl;
        return status();
    };

} // namespace feather

NODE_INIT(POLYGON_CUBE)


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
