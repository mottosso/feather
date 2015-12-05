/***********************************************************************
 *
 * Filename: main.cpp
 *
 * Description: This is for testing of the Core.
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

#include "deps.hpp"
#include "scenegraph.hpp"


// options
#define PRINT_OPTIONS 0
#define ADD_NODE 1
#define REMOVE_NODE 2
#define CONNECT_NODE_FIELDS 3
#define DISCONNECT_NODE_FIELDS 4
#define AUTO_TEST 5
#define UPDATE_SCENEGRAPH 6
#define CLEAR_SCENEGRAPH 7
#define EXIT 8 


void print_menu()
{
    std::cout << "Welcome to Feather3D core tester application\n\tHit \"h\" for the options menu.\n\tSelect an option\n";
};


unsigned int get_option()
{
    unsigned int o;
    std::cout << "Select Option: ";
    std::cin >> o;
    return o;    
};


void print_options()
{
    std::cout << "OPTIONS:\n"
        << "\t==========================\n"
        << "\t0: Print Options\n"
        << "\t1: Add Node\n"
        << "\t2: Remove Node\n"
        << "\t3: Connect Node Fields\n"
        << "\t4: Disconnect Node Fields\n"
        << "\t5: Auto Test\n"
        << "\t6: Update Scenegraph\n"
        << "\t7: Clear Scenegraph\n"
        << "\t8: Exit\n"
        << "\t==========================\n";
};


void add_node()
{
    feather::status e;

    std::cout << "Select Node Type:\n"
        << "\t==========================\n"
        << "\t1: Empty\n"
        << "\t320: Polygon Shape\n"
        << "\t321: Polygon Plane\n"
        << "\t322: Polygon Cube\n"
        << "\t0: Exit\n"
        << "\t==========================\n"
        << "\t:";

    unsigned int n;
    std::cin >> n;

    if(!n)
        return;

    if( n == 1 ||
            n == 320 ||
            n == 321 ||
            n == 322
      ){
        std::cout << "\tNode Name: ";
        std::string name;
        std::cin >> name;
        feather::scenegraph::add_node(n,name,e);
    }

};


void remove_node()
{
    feather::status e;
    std::vector<unsigned int> uids;
    feather::scenegraph::get_nodes(uids);

    std::cout << "Select UID to remove:\n"
        << "\t==========================\n";

    for(auto uid : uids) {
        std::string n;
        feather::scenegraph::get_node_name(uid,n);
        std::cout << "\t" << uid << " \"" << n << "\"\n";
    }

    std::cout << "\t==========================\n"
        << "\t:";

    unsigned int suid;
    std::cin >> suid;

    if(!suid)
        return;

    for(auto uid : uids) {
        if(uid == suid) {
            std::cout << "Removing Node " << uid << std::endl;
            feather::scenegraph::remove_node(uid,e);
            return;
        }
    }

    std::cout << "Node " << suid << " not found\n";
};


void connect_node_fields()
{
    std::vector<unsigned int> uids;
    std::vector<unsigned int> fids;

    feather::scenegraph::get_nodes(uids);

    std::cout << "Select Source Node:\n"
        << "\t==========================\n";
 
    for(auto uid : uids) {
        std::string n;
        feather::scenegraph::get_node_name(uid,n);
        std::cout << "\t" << uid << " \"" << n << "\"\n";
    }

    std::cout << "\t==========================\n"
        << "\t:";

    unsigned int suid;
    std::cin >> suid;

    // verify the uid is in the sg
    if(!feather::scenegraph::node_exist(suid)) {
        std::cout << "Node " << suid << " does not exist\n";
        return;
    }
    
    feather::scenegraph::get_out_fields(suid,fids);
 
    std::cout << "Select Node's Out Field:\n"
        << "\t==========================\n";
 
    for(auto fid : fids) {
        std::string n;
        //feather::scenegraph::get_node_name(uid,n);
        std::cout << "\t" << fid << " \"" << n << "\"\n";
    }

    std::cout << "\t==========================\n"
        << "\t:";
    
    unsigned int sfid;
    std::cin >> sfid;


    std::cout << "Select Target Node:\n"
        << "\t==========================\n";
 
    for(auto uid : uids) {
        std::string n;
        feather::scenegraph::get_node_name(uid,n);
        if(suid != uid)
            std::cout << "\t" << uid << " \"" << n << "\"\n";
    }

    std::cout << "\t==========================\n"
        << "\t:";

    unsigned int tuid;
    std::cin >> tuid;

    // verify the uid is in the sg
    if(!feather::scenegraph::node_exist(tuid)) {
        std::cout << "Node " << tuid << " does not exist\n";
        return;
    }
   
    fids.clear(); 
    feather::scenegraph::get_in_fields(tuid,fids);
 
    std::cout << "Select Node's In Field:\n"
        << "\t==========================\n";
 
    for(auto fid : fids) {
        std::string n;
        //feather::scenegraph::get_node_name(uid,n);
        std::cout << "\t" << fid << " \"" << n << "\"\n";
    }

    std::cout << "\t==========================\n"
        << "\t:";
    
    unsigned int tfid;
    std::cin >> tfid;

    feather::status p = feather::scenegraph::connect(suid,sfid,tuid,tfid);

    if(!p.state) {
        std::cout << "Connection Failed: " << p.msg << std::endl;
        return;
    }
};


void disconnect_node_fields()
{
    std::vector<unsigned int> uids;
    std::vector<unsigned int> fids;

    feather::scenegraph::get_nodes(uids);

    std::cout << "Select Source Node:\n"
        << "\t==========================\n";
 
    for(auto uid : uids) {
        std::string n;
        feather::scenegraph::get_node_name(uid,n);
        std::cout << "\t" << uid << " \"" << n << "\"\n";
    }

    std::cout << "\t==========================\n"
        << "\t:";

    unsigned int suid;
    std::cin >> suid;

    // verify the uid is in the sg
    if(!feather::scenegraph::node_exist(suid)) {
        std::cout << "Node " << suid << " does not exist\n";
        return;
    }
    
    feather::scenegraph::get_out_fields(suid,fids);
 
    std::cout << "Select Node's Out Field:\n"
        << "\t==========================\n";
 
    for(auto fid : fids) {
        std::string n;
        //feather::scenegraph::get_node_name(uid,n);
        std::cout << "\t" << fid << " \"" << n << "\"\n";
    }

    std::cout << "\t==========================\n"
        << "\t:";
    
    unsigned int sfid;
    std::cin >> sfid;


    std::cout << "Select Target Node:\n"
        << "\t==========================\n";
 
    for(auto uid : uids) {
        std::string n;
        feather::scenegraph::get_node_name(uid,n);
        if(suid != uid)
            std::cout << "\t" << uid << " \"" << n << "\"\n";
    }

    std::cout << "\t==========================\n"
        << "\t:";

    unsigned int tuid;
    std::cin >> tuid;

    // verify the uid is in the sg
    if(!feather::scenegraph::node_exist(tuid)) {
        std::cout << "Node " << tuid << " does not exist\n";
        return;
    }
   
    fids.clear(); 
    feather::scenegraph::get_in_fields(tuid,fids);
 
    std::cout << "Select Node's In Field:\n"
        << "\t==========================\n";
 
    for(auto fid : fids) {
        std::string n;
        //feather::scenegraph::get_node_name(uid,n);
        std::cout << "\t" << fid << " \"" << n << "\"\n";
    }

    std::cout << "\t==========================\n"
        << "\t:";
    
    unsigned int tfid;
    std::cin >> tfid;

    feather::status p = feather::scenegraph::disconnect(suid,sfid,tuid,tfid);

    if(!p.state) {
        std::cout << "Disconnect Failed: " << p.msg << std::endl;
        return;
    }

};


int auto_test()
{
    feather::status e;

    // add node tests
    std::cout << "FEATHER AUTO TEST STARTING:\n\tAdding plane and shape nodes to the SG: ";
    unsigned int plane=0;
    unsigned int shape=0;
    plane = feather::scenegraph::add_node(321,"plane",e); // polygon plane
    std::cout << " plane uid:" << plane;
    shape = feather::scenegraph::add_node(320,"shape",e); // polygon shape
    std::cout << " shape uid:" << shape;
    std::cout << "\nNODES ADDED\n\n";
 
    feather::scenegraph::update();
    std::cout << "\n\n";


    // CONNECT NODES


    // node connection tests
    std::cout << "CONNECTING NODES:\n\tConnecting root.child->plane.parent: ";
    // root.child->plane.parent
    e = feather::scenegraph::connect(0,2,plane,1);
    if(!e.state){
        std::cout << "failed" << std::endl;
        return 1; 
    } else {
        std::cout << "passed" << std::endl;
    }
    // plane.child->shape.parent
    e = feather::scenegraph::connect(plane,2,shape,1);
    std::cout << "\tConnecting plane.child->shape.parent: " << ((!e.state) ? "failed" : "passed") << std::endl;
    if(!e.state){
        std::cout << "failed" << std::endl;
        return 1; 
    } else {
        std::cout << "passed" << std::endl;
    }
    // plane.mesh->plane.mesh
    e = feather::scenegraph::connect(plane,5,shape,3);
    std::cout << "\tConnecting plane.mesh->shape.mesh: ";
    if(!e.state){
        std::cout << "failed" << std::endl;
        return 1; 
    } else {
        std::cout << "passed" << std::endl;
    }
    std::cout << "CONNECTION TESTS COMPLETE\n\n"; 

    feather::scenegraph::update();
    std::cout << "\n\n";

    
    // DISCONNECTING NODES

    // TODO for now removing a node should get rid of all it's in and out connections

    // REMOVING NODES
    std::cout << "REMOVING NODES:\n\tremoving shape node: ";
    // root.child->plane.parent
    feather::scenegraph::remove_node(shape,e);
    if(!e.state){
        std::cout << "failed" << std::endl;
        return 1; 
    } else {
        std::cout << "passed" << std::endl;
    }
    std::cout << "REMOVING TEST COMPLETE\n\n";

    feather::scenegraph::update();
    std::cout << "\n\n";
};


void update_scenegraph()
{
    feather::scenegraph::update();
};


void clear_scenegraph()
{
    feather::scenegraph::clear();
};


void run_option(unsigned int o)
{
    switch(o){
        case PRINT_OPTIONS:
            print_options();
        break;
        case ADD_NODE:
            add_node();
        break;
        case REMOVE_NODE:
            remove_node();
        break;
        case CONNECT_NODE_FIELDS:
            connect_node_fields();
        break;
        case DISCONNECT_NODE_FIELDS:
            disconnect_node_fields();
        break;
        case AUTO_TEST:
            auto_test();
        break;
        case UPDATE_SCENEGRAPH:
            update_scenegraph();
        break;
        case CLEAR_SCENEGRAPH:
            clear_scenegraph();
        break;
        case EXIT:
        break;
        default:
            std::cout << "*** NOT A VALID OPTION ***\n";
        break;
    }
};


int main(int argc, char **argv)
{
    feather::status e;
    feather::scenegraph::load_plugins();
    feather::scenegraph::add_node(1,"root",e); 
 
    print_menu();
    print_options();
    unsigned int option=0;
   
    while(option!=EXIT){
        option = get_option();
        run_option(option);
    } 

    std::cout << "FEATHER CORE TESTING COMPLETE\n";
    return 0;
};
