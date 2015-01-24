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

class SceneGraphEditor : public QQuickPaintedItem
{

    Q_OBJECT

    public:
        SceneGraphEditor(QQuickItem* parent=0);
        ~SceneGraphEditor();

        void paint(QPainter* painter);
        Q_INVOKABLE void update_sg() { update(); }; 

    private:
        void drawNode(int x, int y, QPainter* painter);
        void drawConnection(int sx, int sy, int tx, int ty, feather::field::Type type, QPainter* painter);
};

#endif
