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
        class QmlNode: public QObject
        {
            Q_OBJECT

                Q_ENUMS(Type)

            public:
                QmlNode(QObject* parent=0);
                ~QmlNode();

                enum Type {
                    Camera = node::Camera,
                    Light = node::Light,
                    Texture = node::Texture,
                    Shader = node::Shader,
                    Object = node::Object 
                };
        };

        // OBJECT NODE
        class QmlObject: public QObject
        {
            Q_OBJECT

                Q_ENUMS(Type)

            public:
                QmlObject(QObject* parent=0);
                ~QmlObject();

                enum Type {
                    Polygon = object::Polygon,
                    PolygonPlane = object::PolygonPlane,
                    Curve = object::Curve,
                    Point = object::Point
                };
        };

    } // namespace qml

} // namespace feather

#endif
