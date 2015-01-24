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

SceneGraphEditor::SceneGraphEditor(QQuickItem* parent) : QQuickPaintedItem(parent), m_scale(100), m_nodeWidth(100), m_nodeHeight(50)
{

}

SceneGraphEditor::~SceneGraphEditor()
{

}

void SceneGraphEditor::paint(QPainter* painter)
{
    QPoint snode = QPoint(20,20);
    QPoint tnode = QPoint(200,300);
    drawNode(snode,painter);
    drawNode(tnode,painter);
    setFillColor(QColor(125,125,125));
}

void SceneGraphEditor::drawNode(QPoint& point, QPainter* painter)
{
    int w = m_nodeWidth;
    int h = m_nodeHeight;
    int x = point.x();
    int y = point.y();

    QPen trimPen = QPen(QColor(0,0,0),2);
    QPen textPen = QPen(QColor(0,0,155),2);
    QBrush nodeFillBrush = QBrush(QColor(175,175,175));
    QBrush connInFillBrush = QBrush(QColor(175,175,0));
    QBrush connOutFillBrush = QBrush(QColor(0,175,175));
    painter->setRenderHints(QPainter::Antialiasing, true);

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
    painter->drawEllipse(sConnPoint,10,10);
    painter->setBrush(connOutFillBrush);
    painter->drawEllipse(tConnPoint,10,10);

    // draw the node's name
    painter->setPen(textPen);
    painter->drawText(QRect(x,y,w,h),Qt::AlignCenter,"TestNode");
 
}

void SceneGraphEditor::drawConnection(QPoint& snode, QPoint& tnode, feather::field::Type type, QPainter* painter)
{

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
