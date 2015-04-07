/***********************************************************************
 *
 * Filename: sg_editor.hpp
 *
 * Description: Editor widget for scenegraph.
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

#ifndef SG_EDITOR_HPP
#define SG_EDITOR_HPP

#include "deps.hpp"
#include "qml_deps.hpp"
#include "field.hpp"


#define NODE_WIDTH 100
#define NODE_HEIGHT 30
#define CONNECTION_WIDTH 10
#define CONNECTION_HEIGHT 10 

// FieldInfo
class FieldInfo : public QObject
{
    Q_OBJECT
        Q_ENUMS(Type)
        Q_PROPERTY(QString name READ name)
        Q_PROPERTY(Type type READ type)
        Q_PROPERTY(bool locked READ locked)

    public:
        enum Type {
            Bool=feather::field::Bool,
            Int=feather::field::Int,
            Double=feather::field::Double
        };

        FieldInfo(QString _name, Type _type, bool _locked, QObject* parent=0);
        ~FieldInfo();

        QString name() const { return m_name; };

        Type type() { return m_type; };

        bool locked() { return m_locked; };

    private:
        QString m_name;
        Type m_type;
        bool m_locked;
};


class SceneGraphConnection : public QQuickPaintedItem
{
    Q_OBJECT

    public:
        enum Connection { In, Out };

        SceneGraphConnection(Connection type, QQuickItem* parent=0);
        ~SceneGraphConnection();
        void paint(QPainter* painter);

    protected:
        void mousePressEvent(QMouseEvent* event);
        void mouseReleaseEvent(QMouseEvent* event);
        void hoverEnterEvent(QHoverEvent* event);
        void hoverLeaveEvent(QHoverEvent* event);
        void mouseMoveEvent(QMouseEvent* event);

    signals:
        void connClicked(Qt::MouseButton button, SceneGraphConnection::Connection conn);

    private:
        int m_srcUid;
        int m_srcField;
        int m_tgtUid;
        int m_tgtField;
        Connection m_type;
        QBrush m_connFillBrush;
};

class SceneGraphNode : public QQuickPaintedItem
{
    Q_OBJECT

    public:
        SceneGraphNode(int _uid, int _node, QQuickItem* parent=0);
        ~SceneGraphNode();
        void paint(QPainter* painter);
        void inConnectionPoint(QPointF& point);
        void outConnectionPoint(QPointF& point);
    
    protected slots:
        void ConnPressed(Qt::MouseButton button,SceneGraphConnection::Connection conn);
 
    signals:
        void ConnClicked(Qt::MouseButton button, SceneGraphConnection::Connection conn, int id);

    protected:
        void mousePressEvent(QMouseEvent* event);
        void mouseReleaseEvent(QMouseEvent* event);
        void hoverEnterEvent(QHoverEvent* event);
        void hoverLeaveEvent(QHoverEvent* event);
        void mouseMoveEvent(QMouseEvent* event);

    private:
        void getConnectionPoint(feather::field::connection::Type conn, QPoint& npoint, QPoint& cpoint);
        int m_uid;
        int m_node;
        int m_x;
        int m_y;
        QBrush m_nodeFillBrush;
        SceneGraphConnection* m_pInConn;
        SceneGraphConnection* m_pOutConn;
};

class SceneGraphEditor : public QQuickPaintedItem
{
    Q_OBJECT
        Q_PROPERTY(QQmlListProperty<FieldInfo> feilds READ fields)
 
    public:
        SceneGraphEditor(QQuickItem* parent=0);
        ~SceneGraphEditor();

        void paint(QPainter* painter);
        Q_INVOKABLE void update_sg() { update(); }; 
        QQmlListProperty<FieldInfo> fields();


    protected slots:
        void ConnOption(Qt::MouseButton button, SceneGraphConnection::Connection conn, int id);

    protected:
        void mousePressEvent(QMouseEvent* event);
        void mouseReleaseEvent(QMouseEvent* event);
        void hoverEnterEvent(QHoverEvent* event);
        void hoverLeaveEvent(QHoverEvent* event);
        void mouseMoveEvent(QMouseEvent* event);

    signals:
        void sgUpdated();
        void openInConnMenu(int id);
        void openOutConnMenu(int id);

    private:
        void drawNode(QPoint& point, QPainter* painter);
        void drawConnection(QPointF& snode, QPointF& tnode, feather::field::Type type, QPainter* painter);
        void getConnectionPoint(feather::field::connection::Type conn, QPoint& npoint, QPoint& cpoint);

        int m_scale;
        int m_nodeWidth;
        int m_nodeHeight;

        std::vector<SceneGraphNode*> m_nodes;
        std::vector<SceneGraphConnection*> m_connections;

        static void append_field(QQmlListProperty<FieldInfo> *list, FieldInfo *field);
        QList<FieldInfo*> m_fields;
};

#endif
