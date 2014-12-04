// =====================================================================================
// 
//       Filename:  qml.hpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/14/2014 05:41:06 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#ifndef QML_HPP
#define QML_HPP

#include "deps.hpp"
#include "qml_deps.hpp"
#include "types.hpp"
#include "status.hpp"
#include "commands.hpp"
#include "node.hpp"
#include "object.hpp"


namespace feather
{

    namespace qml
    {

        class QmlSceneGraph : public QObject
        {
            Q_OBJECT

            public:
                QmlSceneGraph(QObject* parent=0);
                ~QmlSceneGraph();

                // commands
                Q_INVOKABLE void add_node(int type, int node, int id) { command::add_node(type,node,id); };
        };

        // NODE
        class Node: public QObject
        {
            Q_OBJECT

                Q_ENUMS(Type)

            public:
                Node(QObject* parent=0);
                ~Node();

                enum Type {
                    Camera = node::Camera,
                    Light = node::Light,
                    Texture = node::Texture,
                    Shader = node::Shader,
                    Object = node::Object 
                };

            private:
                int m_id; // node id
                int m_uid; // scenegraph vertex
        };

        // FIELD 
        class Field: public QObject
        {
            Q_OBJECT

            public:
                Field(QObject* parent=0);
                ~Field();
            
            private:
                int m_id;
        };

    } // namespace qml

} // namespace feather

#endif
