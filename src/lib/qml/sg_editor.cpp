/***********************************************************************
 *
 * Filename: sg_editor.cpp
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

#include "sg_editor.hpp"
#include "commands.hpp"
#include "selection.hpp"


// Connection
SceneGraphConnection::SceneGraphConnection(SceneGraphConnection::Connection type, QQuickItem* parent) :
    QQuickPaintedItem(parent),
    m_type(type),
    m_connFillBrush(QBrush(QColor("#DA70D6")))
{
    setWidth(CONNECTION_WIDTH);
    setHeight(CONNECTION_HEIGHT);
    setAcceptedMouseButtons(Qt::AllButtons);
    setAcceptHoverEvents(true);

    std::vector<int> edges;
    feather::qml::command::get_node_connections(0,edges);
    //feather::FNodeDescriptor n = 0;
    //feather::FFieldConnection connection = boost::edge(n);
    //std::cout << "EDGE for node 0 is " << feather::sg[connection.first].n1 << "=>" << feather::sg[connection.first].n2 << std::endl;
 
}

SceneGraphConnection::~SceneGraphConnection()
{

}

void SceneGraphConnection::paint(QPainter* painter)
{
    
    painter->setRenderHints(QPainter::Antialiasing, true);

    painter->setBrush(m_connFillBrush);
    painter->drawEllipse(QPoint(5,5),CONNECTION_WIDTH/2,CONNECTION_HEIGHT/2);
}

void SceneGraphConnection::mousePressEvent(QMouseEvent* event)
{
        connClicked(event->button(),m_type);
}

void SceneGraphConnection::mouseReleaseEvent(QMouseEvent* event)
{
}

void SceneGraphConnection::hoverEnterEvent(QHoverEvent* event)
{
    m_connFillBrush.setColor(QColor("#FFBF00"));
    update();
}

void SceneGraphConnection::hoverLeaveEvent(QHoverEvent* event)
{
    m_connFillBrush.setColor(QColor("#DA70D6"));
    update();
}

void SceneGraphConnection::mouseMoveEvent(QMouseEvent* event)
{

}


// Node
SceneGraphNode::SceneGraphNode(int _uid, int _node, QQuickItem* parent) : 
    QQuickPaintedItem(parent),
    m_uid(_uid),
    m_node(_node),
    m_x(0),
    m_y(0),
    m_nodeFillBrush(QBrush(QColor("#6A5ACD"))),
    m_pInConn(new SceneGraphConnection(SceneGraphConnection::In,this)),
    m_pOutConn(new SceneGraphConnection(SceneGraphConnection::Out,this))
{
    if(feather::smg::Instance()->selected(m_uid)){
        m_nodeFillBrush.setColor(QColor("#FF007F"));
        update();
    }
    setWidth(NODE_WIDTH+4);
    setHeight(NODE_HEIGHT+4);
    m_pOutConn->setX(NODE_WIDTH-2);
    m_pOutConn->setY((NODE_HEIGHT/2)-2);
    m_pInConn->setX(-2);
    m_pInConn->setY((NODE_HEIGHT/2)-2);
    setAcceptedMouseButtons(Qt::AllButtons);
    setAcceptHoverEvents(true);

    connect(m_pInConn,SIGNAL(connClicked(Qt::MouseButton,SceneGraphConnection::Connection)),this,SLOT(ConnPressed(Qt::MouseButton,SceneGraphConnection::Connection)));
    connect(m_pOutConn,SIGNAL(connClicked(Qt::MouseButton,SceneGraphConnection::Connection)),this,SLOT(ConnPressed(Qt::MouseButton,SceneGraphConnection::Connection)));
}

SceneGraphNode::~SceneGraphNode()
{

}

void SceneGraphNode::ConnPressed(Qt::MouseButton button, SceneGraphConnection::Connection conn)
{
    ConnClicked(button,conn,m_uid); 
}

void SceneGraphNode::paint(QPainter* painter)
{
    painter->setRenderHints(QPainter::Antialiasing, true);

    QPen trimPen = QPen(QColor(0,0,0),2);
    QPen textPen = QPen(QColor("#FFFAFA"),2);
    //QBrush connInFillBrush = QBrush(QColor("#FF4500"));
    //QBrush connOutFillBrush = QBrush(QColor("#DA70D6"));

    // draw the node box
    painter->setPen(trimPen);
    painter->setBrush(m_nodeFillBrush);
    painter->drawRoundedRect(QRect(2,2,NODE_WIDTH,NODE_HEIGHT),5,5);

    // draw the input and output connectors
    //QPoint sConnPoint;
    //QPoint tConnPoint;
    //QPoint point; 
    //getConnectionPoint(feather::field::connection::In,point,sConnPoint);
    //getConnectionPoint(feather::field::connection::Out,point,tConnPoint);
    //painter->setBrush(connInFillBrush);
    //painter->drawEllipse(sConnPoint,6,6);
    //painter->setBrush(connOutFillBrush);
    //painter->drawEllipse(tConnPoint,6,6);

    // draw the node's name
    painter->setPen(textPen);
    painter->drawText(QRect(2,2,NODE_WIDTH,NODE_HEIGHT),Qt::AlignCenter,feather::qml::command::get_node_name(m_uid).c_str());
    //setX(m_x);
    //setY(m_y);
}

void SceneGraphNode::mousePressEvent(QMouseEvent* event)
{
    m_x = event->screenPos().x();
    m_y = event->screenPos().y();
}

void SceneGraphNode::mouseReleaseEvent(QMouseEvent* event)
{
    if(feather::smg::Instance()->selected(m_uid)){
        m_nodeFillBrush.setColor(QColor("#FF007F"));
        update();
    } else {
        m_nodeFillBrush.setColor(QColor("#6A5ACD"));
        update();
    }
}

void SceneGraphNode::hoverEnterEvent(QHoverEvent* event)
{
    m_nodeFillBrush.setColor(QColor("#318CE7"));
    update();
}

void SceneGraphNode::hoverLeaveEvent(QHoverEvent* event)
{
    if(feather::smg::Instance()->selected(m_uid)){
        m_nodeFillBrush.setColor(QColor("#FF007F"));
        update();
    } else {
        m_nodeFillBrush.setColor(QColor("#6A5ACD"));
        update();
    }
   update();
}

void SceneGraphNode::mouseMoveEvent(QMouseEvent* event)
{
    setX(x() + (event->screenPos().x() - m_x));
    setY(y() + (event->screenPos().y() - m_y));
    m_x = event->screenPos().x();
    m_y = event->screenPos().y();
    parentItem()->update();
}

void SceneGraphNode::inConnectionPoint(QPointF& point)
{
    point = mapToItem(parentItem(),QPoint(m_pInConn->x(),m_pInConn->y()));
}

void SceneGraphNode::outConnectionPoint(QPointF& point)
{
    point = mapToItem(parentItem(),QPoint(m_pOutConn->x(),m_pOutConn->y()));
}


void SceneGraphNode::getConnectionPoint(feather::field::connection::Type conn, QPoint& npoint, QPoint& cpoint)
{
    if(conn == feather::field::connection::In)
    {
        cpoint.setX(npoint.x()+5);
        cpoint.setY((npoint.y()+5)+((NODE_HEIGHT+5)/2));
 
    }
    else
    {
        cpoint.setX((npoint.x()+5)+(NODE_WIDTH+5));
        cpoint.setY((npoint.y()+5)+((NODE_HEIGHT+5)/2));
    }
}


// Editor
SceneGraphEditor::SceneGraphEditor(QQuickItem* parent) : QQuickPaintedItem(parent), m_scale(100), m_nodeWidth(80), m_nodeHeight(30)
{
    setAcceptedMouseButtons(Qt::AllButtons);
    SceneGraphNode *nodeA = new SceneGraphNode(0,322,this);
    connect(nodeA,SIGNAL(ConnClicked(Qt::MouseButton,SceneGraphConnection::Connection,int)),this,SLOT(ConnOption(Qt::MouseButton,SceneGraphConnection::Connection,int)));
    SceneGraphNode *nodeB = new SceneGraphNode(1,320,this);
    connect(nodeB,SIGNAL(ConnClicked(Qt::MouseButton,SceneGraphConnection::Connection,int)),this,SLOT(ConnOption(Qt::MouseButton,SceneGraphConnection::Connection,int)));
    m_nodes.push_back(nodeA);
    nodeA->setX(50);
    nodeA->setY(50);
    m_nodes.push_back(nodeB);
    nodeB->setX(250);
    nodeB->setY(250);
    //setAcceptHoverEvents(true);
}

SceneGraphEditor::~SceneGraphEditor()
{

}

void SceneGraphEditor::ConnOption(Qt::MouseButton button, SceneGraphConnection::Connection conn, int id)
{
    if(conn == SceneGraphConnection::In)
        openInConnMenu(id);
    else
        openOutConnMenu(id);
    
    //std::cout << "node option " << button << " " << conn << " " << id << "\n";
}

void SceneGraphEditor::paint(QPainter* painter)
{
    setFillColor(QColor("#4682B4"));
    painter->setRenderHints(QPainter::Antialiasing, true);
    QPointF n1;
    QPointF n2;
    m_nodes.at(0)->outConnectionPoint(n1);
    m_nodes.at(1)->inConnectionPoint(n2);
    drawConnection(n2,n1,feather::field::Double,painter);
}

void SceneGraphEditor::drawNode(QPoint& point, QPainter* painter)
{
    int w = m_nodeWidth;
    int h = m_nodeHeight;
    int x = point.x();
    int y = point.y();

    QPen trimPen = QPen(QColor(0,0,0),2);
    QPen textPen = QPen(QColor("#FFFAFA"),2);
    QBrush nodeFillBrush = QBrush(QColor("#6A5ACD"));
    QBrush connInFillBrush = QBrush(QColor("#FF4500"));
    QBrush connOutFillBrush = QBrush(QColor("#DA70D6"));

    // draw the node box
    painter->setPen(trimPen);
    painter->setBrush(nodeFillBrush);
    painter->drawRoundedRect(QRect(x,y,w,h),5,5);

    // draw the input and output connectors
    QPoint sConnPoint;
    QPoint tConnPoint;
    getConnectionPoint(feather::field::connection::In,point,sConnPoint);
    getConnectionPoint(feather::field::connection::Out,point,tConnPoint);
    painter->setBrush(connInFillBrush);
    painter->drawEllipse(sConnPoint,6,6);
    painter->setBrush(connOutFillBrush);
    painter->drawEllipse(tConnPoint,6,6);

    // draw the node's name
    painter->setPen(textPen);
    painter->drawText(QRect(x,y,w,h),Qt::AlignCenter,"TestNode");
 
}

void SceneGraphEditor::drawConnection(QPointF& snode, QPointF& tnode, feather::field::Type type, QPainter* painter)
{
    QPainterPath path;
    QBrush brush = painter->brush();
    brush.setStyle(Qt::NoBrush);

    //std::cout << "snode x:" << snode.x() << ", y:" << snode.y() << ", tnode x: " << tnode.x() << ", y:" << tnode.y() << std::endl;
    QPen pathPen = QPen(QColor("#9ACD32"),2);
    path.moveTo(snode.x()+2,snode.y()+2);
    path.cubicTo(tnode.x(),snode.y(),snode.x(),tnode.y(),tnode.x()-2,tnode.y()+2);
    painter->setPen(pathPen);
    painter->drawPath(path);
}

void SceneGraphEditor::getConnectionPoint(feather::field::connection::Type conn, QPoint& npoint, QPoint& cpoint)
{
    if(conn == feather::field::connection::In)
    {
        cpoint.setX(npoint.x());
        cpoint.setY(npoint.y()+(m_nodeHeight/2));
    }
    else
    {
        cpoint.setX(npoint.x()+m_nodeWidth);
        cpoint.setY(npoint.y()+(m_nodeHeight/2));
    }
}

void SceneGraphEditor::mousePressEvent(QMouseEvent* event){};
void SceneGraphEditor::mouseReleaseEvent(QMouseEvent* event){};
void SceneGraphEditor::hoverEnterEvent(QHoverEvent* event){};
void SceneGraphEditor::hoverLeaveEvent(QHoverEvent* event){};
void SceneGraphEditor::mouseMoveEvent(QMouseEvent* event){};


// Connection Model
ConnectionModel::ConnectionModel(QObject* parent) : QAbstractListModel(parent)
{
    m_fields.append(new FieldInfo("A",0,true));
    m_fields.append(new FieldInfo("B",0,false));
}

ConnectionModel::~ConnectionModel()
{

}                                                                        

QHash<int, QByteArray> ConnectionModel::roleNames() const
{

    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles.insert(NameRole, QByteArray("name"));
    roles.insert(TypeRole, QByteArray("type"));
    roles.insert(LockedRole, QByteArray("locked"));
    return roles;
}

int ConnectionModel::rowCount(const QModelIndex& parent) const
{
    return m_fields.size();
}

QVariant ConnectionModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant(); // Return Null variant if index is invalid
    if (index.row() > (m_fields.size()-1) )
        return QVariant();
    FieldInfo *dobj = m_fields.at(index.row());
    switch (role) {
        case Qt::DisplayRole: // The default display role now displays the first name as well
        case NameRole:
            return QVariant::fromValue(dobj->name);
        case TypeRole:
            return QVariant::fromValue(dobj->type);
        case LockedRole:
            return QVariant::fromValue(dobj->locked);
        default:
            return QVariant();
    }
}

