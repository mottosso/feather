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
//#define POLYGON_PLANE 325
//#define POLYGON_CUBE 326

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
PLUGIN_INIT(0,0)


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
