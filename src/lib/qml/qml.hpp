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
#include "field.hpp"
#include <QtQuick/QQuickPaintedItem>

using namespace feather;

class SceneGraph : public QObject
{
    Q_OBJECT

    public:
        SceneGraph(QObject* parent=0);
        ~SceneGraph();

        // commands
        Q_INVOKABLE int add_node(int type, int node) { return qml::command::add_node(type,node); };
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
class Parameter : public QObject
{
    Q_OBJECT
        Q_ENUMS(Type)
        Q_PROPERTY(QString name READ name WRITE setName)
        Q_PROPERTY(Type type READ type WRITE setType)
        Q_PROPERTY(bool boolValue READ boolValue WRITE setBoolValue)
        Q_PROPERTY(int intValue READ intValue WRITE setIntValue)
        Q_PROPERTY(double realValue READ realValue WRITE setRealValue)
        Q_PROPERTY(QString stringValue READ stringValue WRITE setStringValue)

    public:
        Parameter(QObject* parent=0);
        ~Parameter();

        enum Type {
            Bool=parameter::Bool,
            Int=parameter::Int,
            Real=parameter::Real,
            String=parameter::String
        };

        // name
        void setName(const QString& n) {
            if(m_name != n) {
                m_name=n;
            }
        }

        QString name() const { return m_name; }

        // type 
        void setType(Type& t) {
            if(m_type != t) {
                m_type=t;
            }
        }

        Type type() { return m_type; }

        // boolValue 
        void setBoolValue(bool& v) {
            if(m_bool != v) {
                m_bool=v;
            }
        }

        bool boolValue() { return m_bool; }

        // intValue 
        void setIntValue(int& v) {
            if(m_int != v) {
                m_int=v;
            }
        }

        int intValue() { return m_int; }

        // realValue 
        void setRealValue(double& v) {
            if(m_real != v) {
                m_real=v;
            }
        }

        double realValue() { return m_real; }

        // stringValue 
        void setStringValue(QString& v) {
            if(m_string != v) {
                m_string=v;
            }
        }

        QString stringValue() { return m_string; }

    private:
        QString m_name;
        Type m_type;
        bool m_bool;
        int m_int;
        double m_real;
        QString m_string;
};

// Command
class Command : public QObject
{
    Q_OBJECT
        Q_PROPERTY(QQmlListProperty<Parameter> parameters READ parameters)
        Q_PROPERTY(QString name READ name WRITE setName)

    public:
        Command(QObject* parent=0);
        ~Command();

        void setName( const QString& n) {
            m_name=n;
        };

        QString name() const { return m_name; };

        QQmlListProperty<Parameter> parameters();

        Q_INVOKABLE bool exec();

    private:
        QString m_name;
        static void append_parameter(QQmlListProperty<Parameter> *list, Parameter *parameter);
        QList<Parameter *> m_parameters;
};

#endif
