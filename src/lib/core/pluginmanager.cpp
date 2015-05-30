/***********************************************************************
 *
 * Filename: pluginmanager.cpp
 *
 * Description: Loads plugins and manages interaction with the scenegraph.
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

#include "pluginmanager.hpp"
#include "types.hpp"

using namespace feather;

PluginManager::PluginManager():m_pluginPath("~/.feather/plugins")
{

}

PluginManager::~PluginManager()
{
    for(auto n : m_plugins)
        dlclose(n.handle);
}

status PluginManager::load_plugins()
{
    boost::filesystem::path plugin_path("/usr/local/feather/plugins");
    typedef std::vector<boost::filesystem::path> files;
    files plugin_paths;

    if (boost::filesystem::exists(plugin_path))
    {
        if (boost::filesystem::is_regular_file(plugin_path))   
            std::cout << plugin_path << " size is " << boost::filesystem::file_size(plugin_path) << '\n';

        else if (boost::filesystem::is_directory(plugin_path)) {
            std::cout << plugin_path << "is a directory\n";
            std::copy(boost::filesystem::directory_iterator(plugin_path), boost::filesystem::directory_iterator(), std::back_inserter(plugin_paths));
            for (files::const_iterator it (plugin_paths.begin()); it != plugin_paths.end(); ++it)
            {
                if((*it).extension()==".so") {
                    // load plugin here
                    std::cout << "LOADING: " << *it << std::endl;
                    PluginData node;
                    node.path = (*it).string();
                    status s = load_node(node);
                    if(s.state){
                        m_plugins.push_back(node);
                        std::cout << node.path << " loaded\n";
                    }
                    else
                        std::cout << node.path << " " << s.msg << std::endl;
                }
            }
        }

        else
            std::cout << plugin_path << "exists, but is neither a regular file nor a directory\n";
    }
    else
        std::cout << plugin_path << "does not exist\n";

    return status();
}

status PluginManager::do_it(int node, field::Fields&  fields)
{
    std::cout << "call node " << node << std::endl;
    std::for_each(m_plugins.begin(),m_plugins.end(), call_do_it(node,fields) );
    return status();
}

void PluginManager::gl_init(FNode& node, FGlInfo& info)
{
    //std::cout << "call node gl info " << node << std::endl;
    std::for_each(m_plugins.begin(),m_plugins.end(), call_gl_init(node,info) );
}

void PluginManager::gl_draw(FNode& node, FGlInfo& info)
{
    //std::cout << "call node gl info " << node << std::endl;
    std::for_each(m_plugins.begin(),m_plugins.end(), call_gl_draw(node,info) );
}

status PluginManager::load_node(PluginData &node)
{
   char *error;

   node.handle = dlopen(node.path.c_str(), RTLD_LAZY);
    if (!node.handle) 
    {
        fprintf(stderr, "%s\n", dlerror());
        return status(FAILED,"loaded failed to load");
    }

    node.name = (std::string(*)())dlsym(node.handle, "name");
    node.description = (std::string(*)())dlsym(node.handle, "description");
    node.author = (std::string(*)())dlsym(node.handle, "author");
    node.do_it = (status(*)(int,field::Fields&))dlsym(node.handle, "do_it");
    node.gl_init = (void(*)(FNode&,FGlInfo&))dlsym(node.handle, "gl_init");
    node.gl_draw = (void(*)(FNode&,FGlInfo&))dlsym(node.handle, "gl_draw");
    node.node_exist = (bool(*)(int))dlsym(node.handle, "node_exist");
    node.node_type = (int(*)(int))dlsym(node.handle, "node_type");
    node.node_icon = (bool(*)(int,std::string&))dlsym(node.handle, "node_icon");
    node.create_fields = (status(*)(int,field::Fields&))dlsym(node.handle,"create_fields");
    node.get_field = (field::FieldBase*(*)(int,int,field::Fields&))dlsym(node.handle, "get_field");
    node.get_fid_list = (status(*)(int,field::connection::Type,field::Fields&,std::vector<field::FieldBase*>&))dlsym(node.handle, "get_fid_list");
    node.command_exist = (bool(*)(std::string))dlsym(node.handle, "command_exist");
    node.command = (status(*)(std::string,parameter::ParameterList))dlsym(node.handle, "command");

    if ((error = dlerror()) != NULL)  
    {
        fprintf(stderr, "%s\n", error);
        return status(FAILED,"library error");
    }

    //std::cout << "node id=" << node.get_id() << std::endl; 
    //(*fn)(&x);
    //printf("Valx=%d\n",x);

    return status();
}

status PluginManager::create_fields(int node, field::Fields& fields)
{
    std::cout << "create field for node " << node << std::endl;
    for(uint i=0; i < m_plugins.size(); i++) {
        if(m_plugins[i].node_exist(node))
            return m_plugins[i].create_fields(node,fields);
    }
    return status();
}

field::FieldBase* PluginManager::get_fieldBase(int uid, int node, int field, field::Fields& fields)
{
    for(uint i=0; i < m_plugins.size(); i++) {
        if(m_plugins[i].node_exist(node)) {
            // TODO - I need to verify that the field data actually exists
            //std::cout << "PluginManager::get_fieldBase(" << uid << "," << node << "," << field << "," << &fields << ")\n";
            return m_plugins[i].get_field(node,field,fields);
        }
    }
    return NULL;
}

status PluginManager::load_command(PluginData &command)
{
    return status(FAILED,"no command to load");
}

status PluginManager::run_command(std::string cmd, parameter::ParameterList params)
{
    std::for_each(m_plugins.begin(),m_plugins.end(), call_command(cmd,params) );
    return status();
}

status PluginManager::run_command_string(std::string str)
{
    std::string cmd;
    parameter::ParameterList params;

    using boost::spirit::ascii::string;
    using boost::spirit::ascii::char_;
    using boost::spirit::qi::lexeme;
    using boost::spirit::qi::int_;
    using boost::spirit::qi::_1;
    using boost::spirit::qi::lit;
    using boost::spirit::qi::eol;
    using boost::spirit::qi::phrase_parse;
    using boost::spirit::ascii::space;
    using boost::phoenix::ref;
    using boost::phoenix::val;

    std::string cmdstr;
    std::string paramstr;
    std::vector<std::string> parameters;
    std::string::iterator first = str.begin();
    std::string::iterator last = str.end();

    bool r = phrase_parse(first, last, ( *(char_-'(') >> '(' >> *(char_-')') >> ')' ), space, cmdstr, paramstr);

    if(!r)
    {
        std::cout << "command failed\n";
        return status(FAILED,"Failed to parse command");
    }

    std::cout << "the command is " << cmdstr << ", the params are " << paramstr << std::endl;

    first = paramstr.begin();
    last = paramstr.end();
    r = phrase_parse(first, last, *( *(char_ - ',') >> ',' || eol ), space, parameters);

    if(!r)
    {
        std::cout << "params failed\n";
        return status(FAILED,"Failed to parse parameters");
    }

    // they and get the parameter type
    bool passed=true;
    std::for_each(parameters.begin(), parameters.end(), [this,&passed,&params](std::string val){ bool r = add_parameter_to_list(val,params); if(!r){ passed=false; } } );
    
    if(!passed)
        return status(FAILED,"unable to get parse parameters");

    std::for_each(m_plugins.begin(),m_plugins.end(), call_command(cmd,params) );
    return status();
}

int PluginManager::min_uid()
{
    return 0;
}

int PluginManager::max_uid()
{
    return 2;
}

status PluginManager::node_icon_file(int nid, std::string& file)
{
    std::for_each(m_plugins.begin(),m_plugins.end(), call_node_icon(nid,file) );
    return status();
}

void PluginManager::loaded_plugins(std::vector<PluginInfo>& list)
{
    get_name info(list);
    std::for_each(m_plugins.begin(), m_plugins.end(), info);
}

status PluginManager::get_fid_list(int nid, field::connection::Type conn, field::Fields& fields, std::vector<field::FieldBase*>& list)
{
    get_fids plugin(nid,conn,fields,list);
    std::for_each(m_plugins.begin(), m_plugins.end(), plugin);
    return status(); 
}

bool PluginManager::add_parameter_to_list(std::string val, parameter::ParameterList& list)
{
    bool r;

    using boost::spirit::qi::int_;
    using boost::spirit::qi::char_;
    using boost::spirit::qi::float_;
    using boost::spirit::qi::phrase_parse;
    using boost::spirit::qi::parse;
    using boost::spirit::ascii::space;

    std::string::iterator first,last;
    first = val.begin();
    last = val.end();

    // see if the value is a int
    int ival=0;
    r = parse(first,last, int_, ival);
    if(r && first==last) {
        list.addIntParameter("",ival);
        return true;
    }

    // see if the val is a float
    first = val.begin();
    last = val.end();
    float fval=0.0;
    r = parse(first, last, float_, fval);
    if(r && first==last) {
        list.addRealParameter("",fval);
        return true;
    }

    // see if the val is a float
    first = val.begin();
    last = val.end();
    std::string sval;
    r = phrase_parse(first, last, ( '"' >> *(char_ - '"') >> '"' ), space, sval);
    if(r && first==last) {
        list.addStringParameter("",sval);
        return true;
    }

    return false;
}
