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
//#include "field.hpp"
#include "field_model.hpp"

#define NODE_WIDTH 100
#define NODE_HEIGHT 30
#define CONNECTION_WIDTH 10
#define CONNECTION_HEIGHT 10 

class SceneGraphEditor;

struct SGState {
    // Source Node Info
    // This is used for when connection node fields together
    // and keeping track of the currently selected nodes
    enum Mode { Normal, FieldConnection };
    static Mode mode;
    static int srcUid;
    static int srcNid;
    static int srcFid;
    static int tgtUid;
    static int tgtNid;
    static int tgtFid;
    static SceneGraphEditor* pSge;
};


struct MouseInfo {
        static int clickX;
        static int clickY;
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
        void ConnClicked(Qt::MouseButton button, SceneGraphConnection::Connection conn, int uid, int nid);
        void nodePressed(Qt::MouseButton button, int uid, int nid);

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
        std::string m_imgDir;
        std::string m_imgFile;
        std::stringstream m_imgPath;
        QBrush m_nodeFillBrush;
        SceneGraphConnection* m_pInConn;
        SceneGraphConnection* m_pOutConn;
};


// Link

class SceneGraphLink : public QQuickPaintedItem
{
    Q_OBJECT
    
    public:
        SceneGraphLink(SceneGraphNode* snode, SceneGraphNode* tnode, QQuickItem* parent=0);
        ~SceneGraphLink();
        void paint(QPainter* painter);

    private:
        SceneGraphNode* m_snode; // source node
        SceneGraphNode* m_tnode; // target node
};


// Editor

class SceneGraphEditor : public QQuickPaintedItem
{
    Q_OBJECT
         Q_PROPERTY(FieldModel* connection READ connection WRITE setConnection NOTIFY connectionChanged)
         Q_PROPERTY(int clickX READ clickX)
         Q_PROPERTY(int clickY READ clickY)
 
    public:
        SceneGraphEditor(QQuickItem* parent=0);
        ~SceneGraphEditor();

        void paint(QPainter* painter);
        Q_INVOKABLE void update_sg() { update(); }; 
        Q_INVOKABLE void startConnection() { SGState::mode=SGState::FieldConnection; };
        Q_INVOKABLE void connectionMousePressed(int button, int uid, int nid, int fid);
        Q_INVOKABLE void connectionMouseReleased(int button, int uid, int nid, int fid);
        Q_INVOKABLE void connectionMouseClicked(int button, int uid, int nid, int fid);

        // connection 
        void setConnection(FieldModel* c) {
            if(m_connection!= c) {
                m_connection=c;
                //m_connection->addField();
                connectionChanged();
            }
        }

        FieldModel* connection() { return m_connection; }
        int clickX() { return MouseInfo::clickX; }
        int clickY() { return MouseInfo::clickY; }

    protected slots:
        void ConnOption(Qt::MouseButton button, SceneGraphConnection::Connection conn, int uid, int nid);
        void nodePressed(Qt::MouseButton button, int uid, int nid);

    protected:
        void mousePressEvent(QMouseEvent* event);
        void mouseReleaseEvent(QMouseEvent* event);
        void hoverEnterEvent(QHoverEvent* event);
        void hoverLeaveEvent(QHoverEvent* event);
        void hoverMoveEvent(QHoverEvent* event);
        void mouseMoveEvent(QMouseEvent* event);

    signals:
        void sgUpdated();
        void openConnMenu();
        void connectionChanged();
        void nodeSelection(int type, int uid, int nid);

    private:
        void drawConnection(QPointF& snode, QPointF& tnode, feather::field::Type type, QPainter* painter);
        void drawConnection(int sx, int sy, int tx, int ty, QPainter* painter);
        void getConnectionPoint(feather::field::connection::Type conn, QPoint& npoint, QPoint& cpoint);
        void updateGraph();
        void updateLeaf(SceneGraphNode* pnode, int uid, int xpos, int ypos);

        int m_scale;
        int m_nodeWidth;
        int m_nodeHeight;

        std::vector<SceneGraphNode*> m_nodes;
        std::vector<SceneGraphLink*> m_links;
        std::vector<SceneGraphConnection*> m_connections;
        FieldModel* m_connection;

};


#endif
