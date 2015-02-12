// =====================================================================================
// 
//       Filename:  sg_editor.cpp
// 
//    Description:  SceneGraph editor for qml interface
// 
//        Version:  1.0
//        Created:  01/21/2015 05:17:31 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#include "sg_editor.hpp"

// Node
SceneGraphNode::SceneGraphNode(int _uid, int _node, QQuickItem* parent) : QQuickPaintedItem(parent), m_uid(_uid), m_node(_node), m_x(0), m_y(0), m_initPos(false)
{
    setWidth(NODE_WIDTH+4);
    setHeight(NODE_HEIGHT+4);
    setAcceptedMouseButtons(Qt::AllButtons);
}

SceneGraphNode::~SceneGraphNode()
{

}

void SceneGraphNode::paint(QPainter* painter)
{
    painter->setRenderHints(QPainter::Antialiasing, true);

    QPen trimPen = QPen(QColor(0,0,0),2);
    QPen textPen = QPen(QColor("#FFFAFA"),2);
    QBrush nodeFillBrush = QBrush(QColor("#6A5ACD"));
    QBrush connInFillBrush = QBrush(QColor("#FF4500"));
    QBrush connOutFillBrush = QBrush(QColor("#DA70D6"));

    // draw the node box
    painter->setPen(trimPen);
    painter->setBrush(nodeFillBrush);
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
    painter->drawText(QRect(2,2,NODE_WIDTH,NODE_HEIGHT),Qt::AlignCenter,"TestNode");
    //setX(m_x);
    //setY(m_y);
}

void SceneGraphNode::mousePressEvent(QMouseEvent* event)
{
    //QQuickItem::mousePressEvent(event);
    m_initPos = true;
}

void SceneGraphNode::mouseReleaseEvent(QMouseEvent* event)
{
    m_initPos = false;
    //QQuickItem::mousePressEvent(event);
}

void SceneGraphNode::mouseMoveEvent(QMouseEvent* event)
{
    if(m_initPos) {
        m_x = event->screenPos().x();
        m_y = event->screenPos().y();
        m_initPos = false;
    } else {
        setX(x() + (event->screenPos().x() - m_x));
        setY(y() + (event->screenPos().y() - m_y));
        m_x = event->screenPos().x();
        m_y = event->screenPos().y();
    }
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


// Connection
SceneGraphConnection::SceneGraphConnection(int _srcUid, int _srcField, int _tgtUid, int _tgtField, QQuickItem* parent) : QQuickPaintedItem(parent), m_srcUid(_srcUid), m_srcField(_srcField), m_tgtUid(_tgtUid), m_tgtField(_tgtField)
{

}

SceneGraphConnection::~SceneGraphConnection()
{

}

void SceneGraphConnection::paint(QPainter* painter)
{

}

// Editor
SceneGraphEditor::SceneGraphEditor(QQuickItem* parent) : QQuickPaintedItem(parent), m_scale(100), m_nodeWidth(80), m_nodeHeight(30)
{
    setAcceptedMouseButtons(Qt::AllButtons);
    m_nodes.push_back(new SceneGraphNode(0,320,this));
    //m_nodes.push_back(new SceneGraphNode(1,322));
}

SceneGraphEditor::~SceneGraphEditor()
{

}

void SceneGraphEditor::paint(QPainter* painter)
{
    setFillColor(QColor("#4682B4"));
    painter->setRenderHints(QPainter::Antialiasing, true);

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

void SceneGraphEditor::drawConnection(QPoint& snode, QPoint& tnode, feather::field::Type type, QPainter* painter)
{
    QPainterPath path;
    QPoint sPoint;
    QPoint tPoint;
    QBrush brush = painter->brush();
    brush.setStyle(Qt::NoBrush);

    getConnectionPoint(feather::field::connection::Out,snode,sPoint);
    getConnectionPoint(feather::field::connection::In,tnode,tPoint);

    QPen pathPen = QPen(QColor("#9ACD32"),2);
    path.moveTo(sPoint.x(),sPoint.y());
    path.cubicTo(tPoint.x(),sPoint.y(),sPoint.x(),tPoint.y(),tPoint.x(),tPoint.y());
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

/*
bool SceneGraphEditor::event(QMouseEvent* event)
{
    return QQuickItem::event(event);
}
*/
