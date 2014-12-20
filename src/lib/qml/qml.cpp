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

using namespace feather;
using namespace feather::qml;

SceneGraph::SceneGraph(QObject* parent)
{
}

SceneGraph::~SceneGraph()
{
}


Node::Node(QObject* parent)
{
}

Node::~Node()
{
}


Field::Field(QObject* parent)
{
}

Field::~Field()
{
}


Parameter::Parameter(QObject* parent)
{
}

Parameter::~Parameter()
{
}


Command::Command(QObject* parent)
{
}

Command::~Command()
{
}

QQmlListProperty<Parameter> Command::parameters()
{
    return QQmlListProperty<Parameter>(this,0,&Command::append_parameter,0,0,0);
}

void Command::append_parameter(QQmlListProperty<Parameter> *list, Parameter *param)
{
    Command *cmd = qobject_cast<Command*>(list->object);
    if(cmd) {
        param->setParentItem(cmd);
        cmd->m_parameters.append(param);
    }
}




