// =====================================================================================
// 
//       Filename:  main.cpp
// 
//    Description:  This plugin holds common nodes and commands for the scenegraph and ui. 
// 
//        Version:  1.0
//        Created:  01/18/2015 04:44:11 AM
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

/*
 ***************************************
 *           C PLUGIN WRAPPER          *
 ***************************************
 *
 * C_PLUGIN_WRAPPER()
 * 
 * This macro is needed to make it callable
 * by the core.
 * Every plugin needs it and it's always
 * the same so you should never have to
 * edit the below code.
 *
 */

#ifdef __cplusplus
extern "C" {
#endif
    C_PLUGIN_WRAPPER()
#ifdef __cplusplus
}
#endif

using namespace feather;

// Define all of our nodes
// with id's here.
#define SHAPE 5
#define TRANSFORM 6

/*
 ***************************************
 *              PLUGIN INIT            *
 ***************************************
 * PLUGIN_INIT(startnode,endnode)
 * startnode = id of the first node
 * endnode = id of the last node
 * This macro handles some misc bindings
 * between the plugin and the pluginmanager.
 */ 
PLUGIN_INIT(SHAPE,TRANSFORM)

/*
 ***************************************
 *            POLYGON PLANE            *
 ***************************************
*/

namespace feather {

    /*
     ***************************************
     *              NODE FIELDS            *
     ***************************************
     *
     * You need to make a struct that uses
     * PluginNodeFields as it's base class.
     * This struct will hold all input and
     * outout fields. These fields will be
     * used to connect nodes together 
     */
    struct ShapeFields : public PluginNodeFields
    {
        field::Field<FMesh,field::connection::In> *meshIn;
        field::Field<FMesh,field::connection::Out> *meshOut;
    };

} // namespace feather


/*
 ***************************************
 *          ADD_FIELD_TO_NODE          *
 ***************************************
 * ADD_FIELD_TO_NODE(node,struct,attr,key)
 * node = Enum of the node that the field
 *      will be put into.
 * struct = Name of the struct that holds
 *      the fields.
 * attr = Name of the field attr in the
 *      struct.
 * key = Starting from 1, the number of
 *      the field in the attribute.
 *
 * The macro will tie the field to the node
 * so that it's value can be used by the
 * node's do_it command.
 */
ADD_FIELD_TO_NODE(SHAPE,ShapeFields,meshIn,1)
ADD_FIELD_TO_NODE(SHAPE,ShapeFields,meshOut,2)
//ADD_FIELD_TO_NODE(POLYGON_PLANE,PolygonPlaneFields,subY,2)


namespace feather
{
    /*
     ***************************************
     *              DO_IT                  *
     ***************************************
     * DO_IT(node)
     * node = Enum of the node that the field
     *      will be put into.
     *
     * This function will be call everytime
     * the node updates in the scenegraph.
     * A node will get updated when it's
     * input field changes. This can be from
     * the user or another node's field that's
     * connected to the node's input field. 
     */

    DO_IT(SHAPE)
    { 
        ShapeFields* shape = static_cast<ShapeFields*>(fields);
        std::cout << "shape: meshIn:" << shape->meshIn << std::endl;

        return status();
    };

} // namespace feather

/*
 ***************************************
 *              NODE_INIT              *
 ***************************************
 * NODE_INIT(node)
 * node = Enum of the node that the field
 *      will be put into.
 *
 * This macro will setup the node so that
 * it can be called by the scenegraph.
 */
NODE_INIT(SHAPE,ShapeFields)



/*
 ***************************************
 *              TRANSFORM              *
 ***************************************
*/

namespace feather
{
    struct TransformFields : public PluginNodeFields
    {
        field::Field<FDouble,field::connection::Out> *tx;
        field::Field<FDouble,field::connection::Out> *ty;
        field::Field<FDouble,field::connection::Out> *tz;
        field::Field<FDouble,field::connection::Out> *rx;
        field::Field<FDouble,field::connection::Out> *ry;
        field::Field<FDouble,field::connection::Out> *rz;
        field::Field<FDouble,field::connection::Out> *sx;
        field::Field<FDouble,field::connection::Out> *sy;
        field::Field<FDouble,field::connection::Out> *sz;
    };

} // namespace feather

ADD_FIELD_TO_NODE(TRANSFORM,TransformFields,tx,1)
ADD_FIELD_TO_NODE(TRANSFORM,TransformFields,ty,2)
ADD_FIELD_TO_NODE(TRANSFORM,TransformFields,tz,3)
ADD_FIELD_TO_NODE(TRANSFORM,TransformFields,rx,4)
ADD_FIELD_TO_NODE(TRANSFORM,TransformFields,ry,5)
ADD_FIELD_TO_NODE(TRANSFORM,TransformFields,rz,6)
ADD_FIELD_TO_NODE(TRANSFORM,TransformFields,sx,7)
ADD_FIELD_TO_NODE(TRANSFORM,TransformFields,sy,8)
ADD_FIELD_TO_NODE(TRANSFORM,TransformFields,sz,9)

namespace feather
{

    // do_it
    DO_IT(TRANSFORM) 
    {
        TransformFields* xform = static_cast<TransformFields*>(fields);
        std::cout << "xform: tx:" << xform->tx << std::endl;
        return status();
    };

} // namespace feather

NODE_INIT(TRANSFORM,TransformFields)


/*
 ***************************************
 *              COMMANDS               *
 ***************************************
 * Put all your commands here.
 * Commands are functions that can
 * be called from the interface and
 * are only called once. An example
 * of this would be something like
 * render() or import_obj().
 * You will still need to edit the
 * qml interface to call an commands
 * that you've created.
 */

namespace feather
{
    namespace command
    {
        /*
         * Here you will add enums for every
         * command that you need to call.
         * The first enum must always be N.
         * example:
         * enum Command { N=0, IMPORT_OBJ, EXPORT_OBJ };
         */
        enum Command { N=0 };

        /*
         * Here you will add all the commands that
         * will be linked the the above enums.
         * You need to have a function for each
         * enum above and they need to be formated
         * this way:
         *      status [name](parameter::ParameterList params)
         *      {
         *              ...
         *      };
         * example:
         *      status import_obj(parameter::ParameterList params)
         *      {
         *              // code to import obj file
         *      };
         */
        /*
        status import_obj(parameter::ParameterList params) {
            std::string filename = params.getParameterValue<std::string>("filename");
            bool selection = params.getParameterValue<bool>("selection");

            std::cout << "running import_obj command\nfilename: " << filename << "\n\tselection: " << selection << std::endl;
            return status();
        };

        status export_obj(parameter::ParameterList params) {
            std::cout << "running export_obj command" << std::endl;
            return status();
        };
        */
    } // namespace command

} // namespace feather

/*
 * ADD_COMMAND([name],[enum],[function])
 * Add all the commands that can be called from
 * the qml interface.
 *
 * example:
 * ADD_COMMAND("import_obj",IMPORT_OBJ,import_obj)
 */
//ADD_COMMAND("import_obj",IMPORT_OBJ,import_obj)
//ADD_COMMAND("export_obj",EXPORT_OBJ,export_obj)


/*
 * INIT_COMMAND_CALLS([enum])
 * Make the command callable by the core.
 * This make takes the last enum of the
 * feather::command::Command enum.
 *
 * example:
 * INIT_COMMAND_CALLS(EXPORT_OBJ)
 */
INIT_COMMAND_CALLS(N)
