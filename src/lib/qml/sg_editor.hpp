// =====================================================================================
// 
//       Filename:  sg_editor.hpp
// 
//    Description:  SceneGraph editor for qml interface
// 
//        Version:  1.0
//        Created:  01/21/2015 05:16:16 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#ifndef SG_EDITOR_HPP
#define SG_EDITOR_HPP

#include "deps.hpp"
#include "qml_deps.hpp"
#include "field.hpp"

#define NODE_WIDTH 100
#define NODE_HEIGHT 30
#define CONNECTION_WIDTH 10
#define CONNECTION_HEIGHT 10 


class SceneGraphConnection : public QQuickPaintedItem
{
    Q_OBJECT

    public:
        SceneGraphConnection(QQuickItem* parent=0);
        ~SceneGraphConnection();
        void paint(QPainter* painter);

    protected:
        void mousePressEvent(QMouseEvent* event);
        void mouseReleaseEvent(QMouseEvent* event);
        void hoverEnterEvent(QHoverEvent* event);
        void hoverLeaveEvent(QHoverEvent* event);
        void mouseMoveEvent(QMouseEvent* event);

    private:
        int m_srcUid;
        int m_srcField;
        int m_tgtUid;
        int m_tgtField;
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

    public:
        SceneGraphEditor(QQuickItem* parent=0);
        ~SceneGraphEditor();

        void paint(QPainter* painter);
        Q_INVOKABLE void update_sg() { update(); }; 

    protected:
        void mousePressEvent(QMouseEvent* event);
        void mouseReleaseEvent(QMouseEvent* event);
        void hoverEnterEvent(QHoverEvent* event);
        void hoverLeaveEvent(QHoverEvent* event);
        void mouseMoveEvent(QMouseEvent* event);

    signals:
        void sgUpdated();

    private:
        void drawNode(QPoint& point, QPainter* painter);
        void drawConnection(QPointF& snode, QPointF& tnode, feather::field::Type type, QPainter* painter);
        void getConnectionPoint(feather::field::connection::Type conn, QPoint& npoint, QPoint& cpoint);

        int m_scale;
        int m_nodeWidth;
        int m_nodeHeight;

        std::vector<SceneGraphNode*> m_nodes;
        std::vector<SceneGraphConnection*> m_connections;
};

#endif
