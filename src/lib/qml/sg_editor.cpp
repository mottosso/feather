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


int MouseInfo::clickX=0;
int MouseInfo::clickY=0;

SGState::Mode SGState::mode=SGState::Normal;
int SGState::srcUid=0;
int SGState::srcNid=0;
int SGState::srcFid=0;
int SGState::tgtUid=0;
int SGState::tgtNid=0;
int SGState::tgtFid=0;
SceneGraphEditor* SGState::pSge=NULL;


// SCENEGRAPH

SceneGraphConnection::SceneGraphConnection(SceneGraphConnection::Connection type, QQuickItem* parent) :
    QQuickPaintedItem(parent),
    m_type(type)
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
    if(m_type == In)
        m_connFillBrush = QBrush(QColor("#50C878"));
    else
        m_connFillBrush = QBrush(QColor("#9400D3"));
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
    MouseInfo::clickX = event->windowPos().x();
    MouseInfo::clickY = event->windowPos().y();
    SGState::mode = SGState::FieldConnection;
    connClicked(event->button(),m_type);
}

void SceneGraphConnection::mouseReleaseEvent(QMouseEvent* event)
{
    SGState::mode = SGState::Normal;
    update();
}

void SceneGraphConnection::hoverEnterEvent(QHoverEvent* event)
{
    m_connFillBrush.setColor(QColor("#FFBF00"));
    update();
}

void SceneGraphConnection::hoverLeaveEvent(QHoverEvent* event)
{
    if(m_type == In)
        m_connFillBrush = QBrush(QColor("#50C878"));
    else
        m_connFillBrush = QBrush(QColor("#9400D3"));
    update();
}

void SceneGraphConnection::mouseMoveEvent(QMouseEvent* event)
{
    MouseInfo::clickX = event->windowPos().x(); 
    MouseInfo::clickY = event->windowPos().y(); 
    SGState::pSge->update();
}


// Node
SceneGraphNode::SceneGraphNode(int _uid, int _node, QQuickItem* parent) : 
    QQuickPaintedItem(parent),
    m_uid(_uid),
    m_node(_node),
    m_x(0),
    m_y(0),
    m_imgDir("ui/icons/"),
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

    feather::qml::command::get_node_icon(m_node,m_imgFile);
    m_imgPath << m_imgDir << m_imgFile;
}

SceneGraphNode::~SceneGraphNode()
{

}

void SceneGraphNode::ConnPressed(Qt::MouseButton button, SceneGraphConnection::Connection conn)
{
    ConnClicked(button,conn,m_uid,m_node); 
}

void SceneGraphNode::paint(QPainter* painter)
{
    painter->setRenderHints(QPainter::Antialiasing, true);

    QPen trimPen = QPen(QColor(0,0,0),2);
    QPen textPen = QPen(QColor("#FFFAFA"),2);
    QFont textFont("DejaVuSans",8);

    //QBrush connInFillBrush = QBrush(QColor("#FF4500"));
    //QBrush connOutFillBrush = QBrush(QColor("#DA70D6"));

    // draw the node box
    painter->setPen(trimPen);
    painter->setBrush(m_nodeFillBrush);
    painter->drawRoundedRect(QRect(2,2,NODE_WIDTH,NODE_HEIGHT),2,2);

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


    // Node Label 
    painter->setPen(textPen);
    painter->setFont(textFont);
    painter->drawText(QRect(8,2,NODE_WIDTH-26,NODE_HEIGHT),Qt::AlignLeft|Qt::AlignVCenter,feather::qml::command::get_node_name(m_uid).c_str());
    //setX(m_x);
    //setY(m_y);

    // Node Icon
    QRectF tgt(NODE_WIDTH-26,4,24,24);
    QRectF src(0,0,48,48);
    QImage img(m_imgPath.str().c_str());
    painter->drawImage(tgt,img,src);
}

void SceneGraphNode::mousePressEvent(QMouseEvent* event)
{
    m_x = event->screenPos().x();
    m_y = event->screenPos().y();
    nodePressed(event->button(),m_uid,m_node);
}

void SceneGraphNode::mouseReleaseEvent(QMouseEvent* event)
{
    // clear selection
    //feather::qml::command::clear_selection();

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
   //update();
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
    SGState::pSge = this;
    setAcceptedMouseButtons(Qt::AllButtons);

    // for testing purposes I'm selecting the node from here.
    // later this will be done from the viewport or outliner
    feather::qml::command::select_node(0);
    updateGraph();
}

SceneGraphEditor::~SceneGraphEditor()
{

}

void SceneGraphEditor::ConnOption(Qt::MouseButton button, SceneGraphConnection::Connection conn, int uid, int nid)
{
    feather::field::FieldBase* pfield;
    int i=1;
    feather::qml::command::get_field_base(uid,i,pfield);

    m_connection->clear();
 
    while(pfield!=NULL)
    { 
        if(conn == SceneGraphConnection::In) {
            if(pfield->conn_type == feather::field::connection::In)
                m_connection->addField(uid,nid,i,pfield->type,true); 
        }

        if(conn == SceneGraphConnection::Out) {
            if(pfield->conn_type == feather::field::connection::Out)
                m_connection->addField(uid,nid,i,pfield->type,true); 
        }

        i++;
        feather::qml::command::get_field_base(uid,i,pfield);
    }

    m_connection->layoutChanged();
    openConnMenu();
}

void SceneGraphEditor::nodePressed(Qt::MouseButton button, int uid, int nid)
{
    nodeSelection(0,uid,nid); 
}

void SceneGraphEditor::connectionMousePressed(int button, int uid, int nid, int fid)
{
    std::cout << "connection mouse pressed, button " << button << " uid " << uid << " nid " << nid << " fid " << fid << std::endl;
}

void SceneGraphEditor::connectionMouseReleased(int button, int uid, int nid, int fid)
{
    std::cout << "connection mouse released, button " << button << " uid " << uid << " nid " << nid << " fid " << fid << std::endl;
}

void SceneGraphEditor::connectionMouseClicked(int button, int uid, int nid, int fid)
{
    std::cout << "connection mouse clicked, button " << button << " uid " << uid << " nid " << nid << " fid " << fid << std::endl;
    
    if(SGState::mode==SGState::Normal)
        SGState::mode=SGState::FieldConnection;
    else
        SGState::mode=SGState::Normal;
}

void SceneGraphEditor::paint(QPainter* painter)
{
    setFillColor(QColor("#696969"));
    painter->setRenderHints(QPainter::Antialiasing, true);

    //m_nodes.at(0)->outConnectionPoint(n1);
    //m_nodes.at(1)->inConnectionPoint(n2);
    //drawConnection(n1,n2,feather::field::Double,painter);
}

void SceneGraphEditor::drawConnection(QPointF& snode, QPointF& tnode, feather::field::Type type, QPainter* painter)
{
    QPainterPath path;
    QBrush brush = painter->brush();
    brush.setStyle(Qt::NoBrush);

    //std::cout << "snode x:" << snode.x() << ", y:" << snode.y() << ", tnode x: " << tnode.x() << ", y:" << tnode.y() << std::endl;
    QPen pathPen;
    if(SGState::mode==SGState::Normal)
        pathPen = QPen(QColor("#99BADD"),1);
    else
        pathPen = QPen(QColor("#FFEF00"),2);

    path.moveTo(snode.x()+2,snode.y()+2);

    if(SGState::mode==SGState::Normal)
        path.cubicTo(tnode.x(),snode.y(),
                snode.x(),tnode.y(),
                tnode.x()-2,tnode.y()+2);
    else 
        path.cubicTo(MouseInfo::clickX,snode.y(),
                snode.x(),MouseInfo::clickY-35,
                MouseInfo::clickX-2,MouseInfo::clickY-35);

    painter->setPen(pathPen);
    painter->drawPath(path);
}

void SceneGraphEditor::drawConnection(int sx, int sy, int tx, int ty, QPainter* painter)
{
    QPainterPath path;
    QBrush brush = painter->brush();
    brush.setStyle(Qt::NoBrush);

    //std::cout << "snode x:" << snode.x() << ", y:" << snode.y() << ", tnode x: " << tnode.x() << ", y:" << tnode.y() << std::endl;
    QPen pathPen;
    if(SGState::mode==SGState::Normal)
        pathPen = QPen(QColor("#99BADD"),1);
    else
        pathPen = QPen(QColor("#FFEF00"),2);

    path.moveTo(sx+2,sy+2);

    if(SGState::mode==SGState::Normal)
        path.cubicTo(tx,sy,sx,ty,tx-2,ty+2);
    else 
        path.cubicTo(MouseInfo::clickX,sy,sx,MouseInfo::clickY-35,MouseInfo::clickX-2,MouseInfo::clickY-35);

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

void SceneGraphEditor::updateGraph()
{
    int xpos = 100;
    int ypos = 50;

    std::vector<int> uids;
    feather::qml::command::get_selected_nodes(uids);

    std::cout << uids.size() << " nodes are selected\n";

    std::for_each(uids.begin(),uids.end(),[](int& n){ std::cout << n << ","; });

    // for each selected uid we will draw all the nodes connected to it.
    for(uint i=0; i < uids.size(); i++) {
        updateLeaf(uids[i],xpos,ypos+=100);
    }

}


void SceneGraphEditor::updateLeaf(int uid, int xpos, int ypos)
{
    int nid=0;
    feather::status s = feather::qml::command::get_node_id(uid,nid);

    SceneGraphNode *node = new SceneGraphNode(uid,nid,this);

    node->setX(xpos);
    node->setY(ypos);

    connect(node,SIGNAL(ConnClicked(Qt::MouseButton,SceneGraphConnection::Connection,int,int)),this,SLOT(ConnOption(Qt::MouseButton,SceneGraphConnection::Connection,int,int)));
    connect(node,SIGNAL(nodePressed(Qt::MouseButton,int,int)),this,SLOT(nodePressed(Qt::MouseButton,int,int)));

    m_nodes.push_back(node);

    std::vector<int> cuids;
    // update each connected node as a separate leaf 
    feather::qml::command::get_node_connected_uids(uid,cuids);
    std::for_each(cuids.begin(),cuids.end(),[&xpos,&ypos,this](int key){
        std::cout << "drawing leaf " << key << std::endl;
        updateLeaf(key,xpos+100,ypos+100);
    });
}


void SceneGraphEditor::mousePressEvent(QMouseEvent* event){};
void SceneGraphEditor::mouseReleaseEvent(QMouseEvent* event){};
void SceneGraphEditor::hoverEnterEvent(QHoverEvent* event){};
void SceneGraphEditor::hoverLeaveEvent(QHoverEvent* event){};
void SceneGraphEditor::hoverMoveEvent(QHoverEvent* event){ std::cout << "hover move\n"; };
void SceneGraphEditor::mouseMoveEvent(QMouseEvent* event){ std::cout << "mouse move\n"; };

