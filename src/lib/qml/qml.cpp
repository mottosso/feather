/***********************************************************************
 *
 * Filename: qml.hpp
 *
 * Description: Frontend of the QML wrapper.
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

#include "qml.hpp"
#include "parameter.hpp"

using namespace feather;


// SceneGraph
SceneGraph::SceneGraph(QObject* parent)
{
}

SceneGraph::~SceneGraph()
{
}


// Node
Node::Node(QObject* parent)
{
}

Node::~Node()
{
}


// Field
Field::Field(QObject* parent): m_uid(0),m_node(0),m_field(0),m_boolVal(false),m_intVal(0),m_floatVal(0.0),m_connected(false)
{
}

Field::~Field()
{
}

// GET FIELD VALUES

void Field::get_bool_val()
{
    qml::command::get_field_val(m_uid,m_node,m_field,m_boolVal);
}

void Field::get_int_val()
{
    qml::command::get_field_val(m_uid,m_node,m_field,m_intVal);
}

void Field::get_float_val()
{
    qml::command::get_field_val(m_uid,m_node,m_field,m_floatVal);
}

// SET FEILD VALUES

void Field::set_bool_val()
{
    qml::command::set_field_val(m_uid,m_node,m_field,m_boolVal);
}

void Field::set_int_val()
{
    qml::command::set_field_val(m_uid,m_node,m_field,m_intVal);
}

void Field::set_float_val()
{
    qml::command::set_field_val(m_uid,m_node,m_field,m_floatVal);
}

// GET CONNECTED

void Field::get_connected()
{
    qml::command::get_field_connection_status(m_uid,m_node,m_field,m_connected);
}


// Parameter
Parameter::Parameter(QObject* parent) : QObject(parent)
{
}

Parameter::~Parameter()
{
}


// Command
Command::Command(QObject* parent) : QObject(parent)
{
}

Command::~Command()
{
}

bool Command::exec()
{
    parameter::ParameterList params;
    for(int i=0; i < m_parameters.size(); i++)
    {
        Parameter* p = m_parameters.at(i);

        switch(p->type())
        {
            case Parameter::Bool:
                params.addBoolParameter(p->name().toStdString(), p->boolValue()); 
                break;

            case Parameter::Int:
                params.addIntParameter(p->name().toStdString(), p->intValue()); 
                break;

            case Parameter::Real:
                params.addRealParameter(p->name().toStdString(), p->realValue()); 
                break;

            case Parameter::String:
                params.addStringParameter(p->name().toStdString(), p->stringValue().toStdString()); 
                break;

            default:
                break; 
        }

    }

    qml::command::run_command(m_name.toStdString(), params);  

    return false;
}


QQmlListProperty<Parameter> Command::parameters()
{
    return QQmlListProperty<Parameter>(this,0,&Command::append_parameter,0,0,0);
}

void Command::append_parameter(QQmlListProperty<Parameter> *list, Parameter *parameter)
{
    Command *cmd = qobject_cast<Command*>(list->object);
    if(cmd) {
        cmd->m_parameters.append(parameter);
    }
}
