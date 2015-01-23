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
    drawNode(painter);
    setFillColor(QColor(125,125,125));
}

void SceneGraphEditor::drawNode(QPainter* painter)
{
    QPen trimPen = QPen(QColor(0,0,0),2);
    QPen textPen = QPen(QColor(0,255,0),2);
    QBrush fillBrush = QBrush(QColor(175,175,175));
    painter->setRenderHints(QPainter::Antialiasing, true);

    painter->setPen(trimPen);
    //painter->drawText(QRect(0,0,200,100),"TestNode");
    //painter->setPen(trimPen);
    painter->drawRect(QRect(0,0,200,100));
    painter->fillRect(QRect(0,0,200,100),fillBrush);
    painter->setPen(textPen);
    painter->drawText(QRect(0,0,200,100),"TestNode");
 
}
