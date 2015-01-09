// =====================================================================================
// 
//       Filename:  main.cpp
// 
//    Description:  
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
#include "parameter.hpp"
#include "command.hpp"

#ifdef __cplusplus
extern "C" {
#endif

    int get_id();
    bool call_node(int *);
    feather::status do_it(int, feather::PluginNodeFields*);
    bool node_match(int,int);
    feather::status add_node(int, feather::PluginNodeFields*);
    feather::status remove_node(int, feather::PluginNodeFields*);
    feather::field::FieldBase* get_field(int,int);
    bool command_exist(std::string cmd);
    feather::status command(std::string cmd, feather::parameter::ParameterList);
#ifdef __cplusplus
}
#endif

using namespace feather;

// define nodes
#define POLYGON_PLANE 325
#define POLYGON_CUBE 326

int get_id() { return 325; };

bool call_node(int *) {
    std::cout << "plugin called\n"; return true;
};

// call node do_it()'s
feather::status do_it(int id, feather::PluginNodeFields* fields) {
    return call_do_its<MAX_NODE_ID>::exec(id,fields);
};

// see if the node is in the plugin
bool node_match(int id) {
    return find_nodes<MAX_NODE_ID>::exec(id);
};

feather::status add_node(int id, feather::PluginNodeFields* fields) {
    return feather::status(FAILED, "function not yet working");
};

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


    namespace command
    {
        enum Command { N=0, IMPORT_OBJ, EXPORT_OBJ };

        status import_obj(parameter::ParameterList params) {
            std::cout << "running import_obj command" << std::endl;
            return status();
        };

        status export_obj(parameter::ParameterList params) {
            std::cout << "running export_obj command" << std::endl;
            return status();
        };

       template <> struct run<IMPORT_OBJ> {
            static status exec(std::string cmd, parameter::ParameterList params) {
                if(cmd=="import_obj")
                    return import_obj(params);
                else
                    return run<IMPORT_OBJ-1>::exec(cmd, params); 
            };
        };
 
        template <> struct run<EXPORT_OBJ> {
            static status exec(std::string cmd, parameter::ParameterList params) {
                if(cmd=="export_obj")
                    return export_obj(params);
                else
                    return run<EXPORT_OBJ-1>::exec(cmd, params); 
            };
        };
    }
}

// check if the command exists
bool command_exist(std::string cmd) { return (cmd=="import_obj") ? true : false; };

// call the command
feather::status command(std::string cmd, feather::parameter::ParameterList params) {
    typedef feather::command::run<feather::command::EXPORT_OBJ> call;
    return call::exec(cmd, params);
};
