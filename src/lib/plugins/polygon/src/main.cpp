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

/*
 ***************************************
 *              PLUGIN INIT            *
 ***************************************
 *
 * PLUGIN_INIT()
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

#define POLYGON_PLANE 325
#define POLYGON_CUBE 326

// THIS NEEDS TO BE FIXED
SET_NODE_ID(POLYGON_PLANE,325)
//SET_NODE_ID(POLYGON_CUBE,326)

/*
 ***************************************
 *              PLUGIN INIT            *
 ***************************************
 *
 * This macro handles some misc bindings
 * between the plugin and the pluginmanager.
 */ 
PLUGIN_INIT()

// get the field
feather::field::FieldBase* get_field(int nid, int fid, PluginNodeFields* fields) {
    switch(nid) {
        case POLYGON_PLANE:
            return find_field<POLYGON_PLANE,3>::exec(fid,fields);
        case POLYGON_CUBE:
            return find_field<POLYGON_CUBE,3>::exec(fid,fields);
        default:
            return NULL;
    }
};

namespace feather {

    // POLYGON PLANE NODE SETUP

    // FIELDS
    struct PolygonPlaneFields : public PluginNodeFields
    {
        field::Field<int> *subX;
        field::Field<int> *subY;
    };

    // FIELD DATA
    
    // subX
    template <> field::FieldBase* field_data<POLYGON_PLANE,1>(PluginNodeFields* fields)
    {
        PolygonPlaneFields* f = static_cast<PolygonPlaneFields*>(fields);
        return f->subX;   
    };
 
    // subY
    template <> field::FieldBase* field_data<POLYGON_PLANE,2>(PluginNodeFields* fields)
    {
        PolygonPlaneFields* f = static_cast<PolygonPlaneFields*>(fields);
        return f->subY;   
    };

    // FIND THE FIELD DATA
   
    // subX
    template <> struct find_field<POLYGON_PLANE,1> {
        static field::FieldBase* exec(int fid, PluginNodeFields* fields) {
            if(fid==1)
                return field_data<POLYGON_PLANE,1>(fields);
            else
                return field_data<POLYGON_PLANE,1-1>(fields);
        };
    };
      
    // subY
    template <> struct find_field<POLYGON_PLANE,2> {
        static field::FieldBase* exec(int fid, PluginNodeFields* fields) {
            if(fid==2)
                return field_data<POLYGON_PLANE,2>(fields);
            else
                return field_data<POLYGON_PLANE,2-1>(fields);
        };
    };

    // functions
 
    // do_it
    template <> status node_do_it<POLYGON_PLANE>(PluginNodeFields* fields) {
        PolygonPlaneFields* plane = static_cast<PolygonPlaneFields*>(fields);
        std::cout << "plane: subX:" << plane->subX << std::endl;

        // TESTING
        /*
        parameter::Parameter<int> *subx = new parameter::Parameter<int>("subx",10);

        parameter::ParameterList list;
        list.push_back(subx);
        */

        return status();
    };

    // POLYGON PLANE NODE CALLS

    // plugin call do it()
    template <> struct call_do_its<POLYGON_PLANE> {
        static status exec(int id, PluginNodeFields* fields) {
            if(id==POLYGON_PLANE){
                return node_do_it<POLYGON_PLANE>(fields);
            } else {
                return call_do_its<POLYGON_PLANE-1>::exec(id,fields);
            }
        };
    };

    // plugin find node
    template <> struct find_nodes<POLYGON_PLANE> {
        static bool exec(int id) {
            if(id==POLYGON_PLANE){
                return true; 
            } else {
                return find_nodes<POLYGON_PLANE-1>::exec(id);
            }
        };
    };

    
    // CUBE NODE

    struct PolygonCubeFields : public PluginNodeFields
    {
        int subX;
        int subY;
        int subZ;
    };

    // functions

    // do_it
    template <> status node_do_it<POLYGON_CUBE>(PluginNodeFields* fields) {
        PolygonCubeFields* cube = static_cast<PolygonCubeFields*>(fields);
        std::cout << "cube: subX:" << cube->subX << std::endl;
        return status();
    };

    // plugin call do_it()
    template <> struct call_do_its<POLYGON_CUBE> {
        static status exec(int id, PluginNodeFields* fields) {
            if(id==POLYGON_CUBE){
                return node_do_it<POLYGON_CUBE>(fields);
            } else {
                return call_do_its<POLYGON_CUBE-1>::exec(id,fields);
            }
        };
    }; 

    // plugin find node
    template <> struct find_nodes<POLYGON_CUBE> {
        static bool exec(int id) {
            if(id==POLYGON_CUBE){
                return true; 
            } else {
                return find_nodes<POLYGON_CUBE-1>::exec(id);
            }
        };
    };
} // namespace feather



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
        enum Command { N=0, IMPORT_OBJ, EXPORT_OBJ };

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
ADD_COMMAND("import_obj",IMPORT_OBJ,import_obj)
ADD_COMMAND("export_obj",EXPORT_OBJ,export_obj)


/*
 * INIT_COMMAND_CALLS([enum])
 * Make the command callable by the core.
 * This make takes the last enum of the
 * feather::command::Command enum.
 *
 * example:
 * INIT_COMMAND_CALLS(EXPORT_OBJ)
 */
INIT_COMMAND_CALLS(EXPORT_OBJ)
