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
#include "parameter.hpp"
#include "field.hpp"

namespace feather
{

    namespace qml
    {

        class SceneGraph : public QObject
        {
            Q_OBJECT

            public:
                SceneGraph(QObject* parent=0);
                ~SceneGraph();

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
            Q_ENUMS(Type)

            public:
                Field(QObject* parent=0);
                ~Field();

                enum Type {
                    Bool=field::Bool,
                    Int=field::Int,
                    Float=field::Float,
                    Vertex=field::Vertex,
                    Vector=field::Vector,
                    Mesh=field::Mesh,
                    RGB=field::RGB,
                    RGBA=field::RGBA,
                    BoolArray=field::BoolArray,
                    IntArray=field::IntArray,
                    FloatArray=field::FloatArray,
                    VertexArray=field::VertexArray,
                    VectoryArray=field::VectoryArray,
                    RGBArray=field::RGBArray,
                    RGBAArray=field::RGBAArray
                };

            private:
                int m_id;
        };

        // Parameter
        class Parameter : public QQuickItem
        {
            Q_OBJECT
            Q_ENUMS(Type)
            Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
            Q_PROPERTY(Type type READ type WRITE setType NOTIFY typeChanged)
            Q_PROPERTY(bool boolValue READ boolValue WRITE setBoolValue NOTIFY boolValueChanged)
            Q_PROPERTY(int intValue READ intValue WRITE setIntValue NOTIFY intValueChanged)
            Q_PROPERTY(double realValue READ realValue WRITE setRealValue NOTIFY realValueChanged)
            Q_PROPERTY(QString stringValue READ stringValue WRITE setStringValue NOTIFY stringValueChanged)

            public:
                Parameter(QObject* parent=0);
                ~Parameter();

                enum Type {
                    Bool,
                    Int,
                    Real,
                    String
                };

                // Why can't the compiler find the parameter namespace
                /*
                enum Type {
                    Bool=parameter::Bool,
                    Int=parameter::Int,
                    Real=parameter::Real,
                    String=parameter::String
                };
                */

                // name
                void setName(QString& n) {
                    if(m_name != n) {
                        m_name=n;
                        emit nameChanged();
                    }
                }

                QString name() { return m_name; }

                // type 
                void setType(Type& t) {
                    if(m_type != t) {
                        m_type=t;
                        emit typeChanged();
                    }
                }

                Type type() { return m_type; }

                // boolValue 
                void setBoolValue(bool& v) {
                    if(m_bool != v) {
                        m_bool=v;
                        emit boolValueChanged();
                    }
                }

                bool boolValue() { return m_bool; }

                // intValue 
                void setIntValue(int& v) {
                    if(m_int != v) {
                        m_int=v;
                        emit intValueChanged();
                    }
                }

                int intValue() { return m_int; }

                // realValue 
                void setRealValue(double& v) {
                    if(m_real != v) {
                        m_real=v;
                        emit realValueChanged();
                    }
                }

                double realValue() { return m_real; }

                // stringValue 
                void setStringValue(QString& v) {
                    if(m_string != v) {
                        m_string=v;
                        emit stringValueChanged();
                    }
                }

                QString stringValue() { return m_string; }

            signals:
                void nameChanged();
                void typeChanged();
                void boolValueChanged();
                void intValueChanged();
                void realValueChanged();
                void stringValueChanged();

            private:
                QString m_name;
                Type m_type;
                bool m_bool;
                int m_int;
                double m_real;
                QString m_string;
        };

        // Command
        class Command : public QQuickItem
        {
            Q_OBJECT
            Q_PROPERTY(QQmlListProperty<Parameter> parameters READ parameters)

            public:
                Command(QObject* parent=0);
                ~Command();

                QQmlListProperty<Parameter> parameters();

                static void append_parameter(QQmlListProperty<Parameter> *list, Parameter *param);

            private:
                QString m_name;
                QList<Parameter*> m_parameters;
        };

    } // namespace qml

} // namespace feather

#endif
