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
        Q_INVOKABLE int connect_nodes(int n1, int f1, int n2, int f2) { status p = qml::command::connect_nodes(n1,f1,n2,f2); return p.state; };
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
        Q_PROPERTY(int uid READ uid WRITE setUid)
        Q_PROPERTY(int node READ node WRITE setNode)
        Q_PROPERTY(int field READ field WRITE setField)
        Q_PROPERTY(bool boolVal READ boolVal WRITE setBoolVal NOTIFY boolValChanged)
        Q_PROPERTY(int intVal READ intVal WRITE setIntVal NOTIFY intValChanged)
        Q_PROPERTY(float floatVal READ floatVal WRITE setFloatVal NOTIFY floatValChanged)
 
    public:
        Field(QObject* parent=0);
        ~Field();

        // uid 
        void setUid(int& i) {
            if(m_uid != i) {
                m_uid=i;
            }
        }

        int uid() { return m_uid; }

        // node 
        void setNode(int& n) {
            if(m_node != n) {
                m_node=n;
            }
        }

        int node() { return m_node; }

        // field 
        void setField(int& f) {
            if(m_field != f) {
                m_field=f;
            }
        }

        int field() { return m_field; }

        // boolVal 
        void setBoolVal(bool& v) {
            if(m_boolVal != v) {
                m_boolVal = v;
                emit boolValChanged();
            }
        }

        bool boolVal() { return m_boolVal; }

        // intVal 
        void setIntVal(int& v) {
            if(m_intVal != v) {
                m_intVal = v;
                set_int_val(); 
                emit intValChanged();
            }
        }

        int intVal() { get_int_val(); return m_intVal; }

        // floatVal 
        void setFloatVal(float& v) {
            if(m_floatVal != v) {
                m_floatVal = v;
                emit floatValChanged();
            }
        }

        float floatVal() { return m_floatVal; };

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
            VectorArray=field::VectorArray,
            RGBArray=field::RGBArray,
            RGBAArray=field::RGBAArray
        };

    signals:
        void boolValChanged();
        void intValChanged();
        void floatValChanged();

    private:
        // get field value
        void get_bool_val();
        void get_int_val();
        void get_float_val();
        // set feild value
        void set_bool_val();
        void set_int_val();
        void set_float_val();

        int m_uid; // unique number of the node in the sg
        int m_node; // node key
        int m_field; // field key
        bool m_boolVal;
        int m_intVal;
        float m_floatVal;
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
