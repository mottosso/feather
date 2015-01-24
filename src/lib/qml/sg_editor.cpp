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

SceneGraphEditor::SceneGraphEditor(QQuickItem* parent) : QQuickPaintedItem(parent)
{

}

SceneGraphEditor::~SceneGraphEditor()
{

}

void SceneGraphEditor::paint(QPainter* painter)
{
    drawNode(20,20,painter);
    setFillColor(QColor(125,125,125));
}

void SceneGraphEditor::drawNode(int x, int y, QPainter* painter)
{
    int w=100;
    int h=50;
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
    painter->setBrush(connInFillBrush);
    painter->drawEllipse(QPoint(x,y+(h/2)),10,10);
    painter->setBrush(connOutFillBrush);
    painter->drawEllipse(QPoint(x+w,y+(h/2)),10,10);

    // draw the node's name
    painter->setPen(textPen);
    painter->drawText(QRect(x,y,w,h),Qt::AlignCenter,"TestNode");
 
}

void SceneGraphEditor::drawConnection(int sx, int sy, int tx, int ty, feather::field::Type type, QPainter* painter)
{

}
