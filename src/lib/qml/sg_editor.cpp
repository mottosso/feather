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
    painter->setBackgroundMode(Qt::OpaqueMode);
    painter->setBackground(QBrush(QColor(0,0,255)));
}
