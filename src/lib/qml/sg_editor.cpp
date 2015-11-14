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
#include "field.hpp"

#define BACKGROUND_COLOR "#696969"
#define NODE_TEXT_COLOR "#000000"
#define SELECTED_NODE_COLOR "#FF007F"
#define DESELECTED_NODE_COLOR "#6A5ACD"
#define NODE_TITLE_BLOCK_COLOR "#66CCFF"
#define HOVER_NODE_COLOR "#FF8C00"
#define SELECTED_IN_CONNECTOR_COLOR "" // TODO
#define DESELECTED_IN_CONNECTOR_COLOR "#50C878"
#define HOVER_CONNECTOR_COLOR "#FFBF00"
#define SELECTED_OUT_CONNECTOR_COLOR "" // TODO
#define DESELECTED_OUT_CONNECTOR_COLOR "#9400D3"
#define SELECTED_CONNECTION_COLOR "#FFEF00"
#define DESELECTED_CONNECTION_COLOR "#99BADD"
#define HOVER_CONNECTION_COLOR ""  // TODO


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

SceneGraphConnection::SceneGraphConnection(unsigned int fid, QString name, SceneGraphConnection::Connection type, QQuickItem* parent) :
    QQuickPaintedItem(parent),
    m_type(type),
    m_fid(fid),
    m_name(name)
{
    setWidth(NODE_WIDTH/2);
    setHeight(20);
    setAcceptedMouseButtons(Qt::AllButtons);
    setAcceptHoverEvents(true);

    //int nedges = feather::qml::command::get_node_connection_count(0);
    std::vector<int> edges;
    feather::qml::command::get_node_out_connections(0,edges);
    //feather::FNodeDescriptor n = 0;
    //feather::FFieldConnection connection = boost::edge(n);
    //std::cout << "EDGE for node 0 is " << feather::sg[connection.first].n1 << "=>" << feather::sg[connection.first].n2 << std::endl;
    if(m_type == In)
        m_connFillBrush = QBrush(QColor(DESELECTED_IN_CONNECTOR_COLOR));
    else
        m_connFillBrush = QBrush(QColor(DESELECTED_OUT_CONNECTOR_COLOR));
}

SceneGraphConnection::~SceneGraphConnection()
{
}

void SceneGraphConnection::paint(QPainter* painter)
{
    painter->setRenderHints(QPainter::Antialiasing, true);
    painter->setBrush(m_connFillBrush);
    //painter->drawEllipse(QPoint(5,5),CONNECTION_WIDTH/2,CONNECTION_HEIGHT/2);
    painter->drawRoundedRect(QRect(0,3,NODE_WIDTH/2,14),4,4);

    QFont font("DejaVuSans",8);
    painter->setFont(font);
    /*
    if(m_type == In)
        painter->drawText(QRect(2,0,NODE_WIDTH/2,20),Qt::AlignLeft|Qt::AlignVCenter,m_name.toStdString().c_str());
    else
        painter->drawText(QRect(0,0,NODE_WIDTH/2-2,20),Qt::AlignRight|Qt::AlignVCenter,m_name.toStdString().c_str());
    */
    painter->drawText(QRect(0,0,NODE_WIDTH/2,20),Qt::AlignHCenter|Qt::AlignVCenter,m_name.toStdString().c_str());
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
    //update();
}

void SceneGraphConnection::hoverEnterEvent(QHoverEvent* event)
{
    m_connFillBrush.setColor(QColor(HOVER_CONNECTOR_COLOR));
    //update();
}

void SceneGraphConnection::hoverLeaveEvent(QHoverEvent* event)
{
    if(m_type == In)
        m_connFillBrush = QBrush(QColor(DESELECTED_IN_CONNECTOR_COLOR));
    else
        m_connFillBrush = QBrush(QColor(DESELECTED_OUT_CONNECTOR_COLOR));
    //update();
}

void SceneGraphConnection::mouseMoveEvent(QMouseEvent* event)
{
    std::cout << "connection mouse move event\n";
    MouseInfo::clickX = event->windowPos().x(); 
    MouseInfo::clickY = event->windowPos().y(); 
    //parentItem()->update();
    //SGState::pSge->update();
}


// Node
SceneGraphNode::SceneGraphNode(int _uid, int _node, QQuickItem* parent) : 
    QQuickPaintedItem(parent),
    m_uid(_uid),
    m_node(_node),
    m_x(0),
    m_y(0),
    m_imgDir("ui/icons/"),
    m_nodeFillBrush(QBrush(QColor(DESELECTED_NODE_COLOR))),
    m_nodeTitleBrush(QBrush(QColor(NODE_TITLE_BLOCK_COLOR)))
{
    if(feather::smg::Instance()->selected(m_uid))
        m_nodeFillBrush.setColor(QColor(SELECTED_NODE_COLOR));
    else
        m_nodeFillBrush.setColor(QColor(DESELECTED_NODE_COLOR));

    setWidth(NODE_WIDTH+4);
    setHeight(NODE_HEIGHT+4);
    /*
    m_pOutConn->setX(NODE_WIDTH-2);
    m_pOutConn->setY((NODE_HEIGHT/2)-2);
    m_pInConn->setX(-2);
    m_pInConn->setY((NODE_HEIGHT/2)-2);
    */
    setAcceptedMouseButtons(Qt::AllButtons);
    setAcceptHoverEvents(true);

    m_inConnCount = feather::qml::command::get_in_field_count(m_uid);
    m_outConnCount = feather::qml::command::get_out_field_count(m_uid);
    m_connCount = feather::qml::command::get_field_count(m_uid);
    m_nodeHeight = 20 + (20 * std::max(m_inConnCount,m_outConnCount));
 
    int yin=15;
    int yout=15;
    for(int i=1; i <= m_connCount; i++){
        if(feather::qml::command::get_field_connection_type(m_uid,i)==feather::field::connection::In){
            std::cout << "IN - Node " << m_node << " FID " << i << " name " << FieldModel::getFieldName(m_node,i).toStdString().c_str() << std::endl;
            m_pInConns.push_back(new SceneGraphConnection(i,FieldModel::getFieldName(m_node,i),SceneGraphConnection::In,this));
            m_pInConns.at(m_pInConns.size()-1)->setX(-2);
            m_pInConns.at(m_pInConns.size()-1)->setY((NODE_HEIGHT/2+yin)-2);
            yin+=20;
            connect(m_pInConns.at(m_pInConns.size()-1),SIGNAL(connClicked(Qt::MouseButton,SceneGraphConnection::Connection)),this,SLOT(ConnPressed(Qt::MouseButton,SceneGraphConnection::Connection)));
        } else {
            std::cout << "OUT - Node " << m_node << " FID " << i << " name " << FieldModel::getFieldName(m_node,i).toStdString().c_str() << std::endl;
            m_pOutConns.push_back(new SceneGraphConnection(i,FieldModel::getFieldName(m_node,i),SceneGraphConnection::Out,this));  
            m_pOutConns.at(m_pOutConns.size()-1)->setX(NODE_WIDTH/2+6);
            m_pOutConns.at(m_pOutConns.size()-1)->setY((NODE_HEIGHT/2)-2+yout);
            yout+=20;
            connect(m_pOutConns.at(m_pOutConns.size()-1),SIGNAL(connClicked(Qt::MouseButton,SceneGraphConnection::Connection)),this,SLOT(ConnPressed(Qt::MouseButton,SceneGraphConnection::Connection)));
        }
    }

    feather::qml::command::get_node_icon(m_node,m_imgFile);
    m_imgPath << m_imgDir << m_imgFile;
}

SceneGraphNode::~SceneGraphNode()
{
    for(auto c : m_pInConns)
        delete c;
    m_pInConns.clear();

    for(auto c : m_pOutConns)
        delete c;
    m_pOutConns.clear();
}

void SceneGraphNode::ConnPressed(Qt::MouseButton button, SceneGraphConnection::Connection conn)
{
    ConnClicked(button,conn,m_uid,m_node); 
}

void SceneGraphNode::paint(QPainter* painter)
{
    painter->setRenderHints(QPainter::Antialiasing, true);

    QPen trimPen = QPen(QColor(0,0,0),1);
    QPen textPen = QPen(QColor(NODE_TEXT_COLOR),2);
    QFont textFont("DejaVuSans",12);

    if(feather::smg::Instance()->selected(m_uid))
        m_nodeFillBrush.setColor(QColor(SELECTED_NODE_COLOR));
    else
        m_nodeFillBrush.setColor(QColor(DESELECTED_NODE_COLOR));

    textFont.setBold((feather::smg::Instance()->selected(m_uid)) ? true : false);

    QFont connFont("DejaVuSans",8);

    QBrush connInFillBrush = QBrush(QColor("#FF4500"));
    QBrush connOutFillBrush = QBrush(QColor("#DA70D6"));

    setHeight(m_nodeHeight+44);

    // node trim 
    painter->setPen(trimPen);

    // this is the main block
    painter->setBrush(m_nodeFillBrush);
    painter->drawRoundedRect(QRect(2,12,NODE_WIDTH,m_nodeHeight),2,2);

    // this is the title block
    painter->setBrush(m_nodeTitleBrush);
    painter->drawRoundedRect(QRect(12,2,NODE_WIDTH-20,20),6,6);

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


    // node label 
    painter->setPen(textPen);
    painter->setFont(textFont);
    painter->drawText(QRect(0,2,NODE_WIDTH,m_nodeHeight),Qt::AlignHCenter|Qt::AlignTop,feather::qml::command::get_node_name(m_uid).c_str());

    // node icon
    QRectF tgt(NODE_WIDTH/2-12,m_nodeHeight+12,24,24);
    QRectF src(0,0,48,48);
    QImage img(m_imgPath.str().c_str());
    painter->drawImage(tgt,img,src);
}

void SceneGraphNode::mousePressEvent(QMouseEvent* event)
{
    m_x = event->screenPos().x();
    m_y = event->screenPos().y();
    // had nodePressed() here but found out that it would
    // block mouseMoveEvent from ever being called
}

void SceneGraphNode::mouseDoubleClickEvent(QMouseEvent* event)
{
    emit nodePressed(event->button(),m_uid,m_node);
}

void SceneGraphNode::mouseReleaseEvent(QMouseEvent* event)
{
    // this is triggered but not currently used
}

void SceneGraphNode::hoverEnterEvent(QHoverEvent* event)
{
    m_nodeFillBrush.setColor(QColor(HOVER_NODE_COLOR));
    update();
}

void SceneGraphNode::hoverLeaveEvent(QHoverEvent* event)
{
    if(feather::smg::Instance()->selected(m_uid)){
        m_nodeFillBrush.setColor(QColor(SELECTED_NODE_COLOR));
    } else {
        m_nodeFillBrush.setColor(QColor(DESELECTED_NODE_COLOR));
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

void SceneGraphNode::inConnectionPoint(unsigned int fid, QPointF& point)
{
    for(auto c : m_pInConns){
        if(c->fid()==fid)
            point = mapToItem(parentItem(),QPoint(c->x(),c->y()+10));
    }
}

void SceneGraphNode::outConnectionPoint(unsigned int fid, QPointF& point)
{
    for(auto c : m_pOutConns){
        if(c->fid()==fid)
            point = mapToItem(parentItem(),QPoint(c->x()+(NODE_WIDTH/2),c->y()+10));
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


// Link

SceneGraphLink::SceneGraphLink(SceneGraphNode* snode, unsigned int sfid, SceneGraphNode* tnode, unsigned int tfid, QQuickItem* parent) :
QQuickPaintedItem(parent),
m_snode(snode),
m_sfid(sfid),
m_tnode(tnode),
m_tfid(tfid)
{

}

SceneGraphLink::~SceneGraphLink()
{

}

void SceneGraphLink::paint(QPainter* painter)
{
    QPainterPath path;
    QBrush brush = painter->brush();
    brush.setStyle(Qt::NoBrush);

    QPointF sp;
    QPointF tp;
    m_snode->outConnectionPoint(m_sfid,sp);
    m_tnode->inConnectionPoint(m_tfid,tp);

    QPen pathPen;
    if(SGState::mode==SGState::Normal)
        pathPen = QPen(QColor(DESELECTED_CONNECTION_COLOR),1);
    else
        pathPen = QPen(QColor(SELECTED_CONNECTION_COLOR),2);

    path.moveTo(sp.x(),sp.y());

    int midSX = sp.x() + (abs(tp.x()-sp.x())/2);
    int midTX = tp.x() - (abs(tp.x()-sp.x())/2);

    if(SGState::mode==SGState::Normal)
        path.cubicTo(midSX,sp.y(),
                midTX,tp.y(),
                tp.x(),tp.y());
    else 
        path.cubicTo(MouseInfo::clickX,sp.y(),
                midTX,MouseInfo::clickY-35,
                MouseInfo::clickX-2,MouseInfo::clickY-35);

    painter->setPen(pathPen);
    painter->drawPath(path);
}


// Editor

SceneGraphEditor::SceneGraphEditor(QQuickItem* parent) : QQuickPaintedItem(parent), m_scale(100), m_nodeWidth(80), m_nodeHeight(30)
{
    SGState::pSge = this;
    setAcceptedMouseButtons(Qt::AllButtons);

    // for testing purposes I'm selecting the node from here.
    // later this will be done from the viewport or outliner
    feather::qml::command::select_node(0,0);
    updateGraph();
    //update();
}

SceneGraphEditor::~SceneGraphEditor()
{
    clearGraph();
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
    // for now we'll have it so only one node can be selected at a time
    feather::qml::command::clear_selection();
    feather::qml::command::select_node(uid);
    emit nodeSelection(0,uid,nid);
    updateNodes();
}

void SceneGraphEditor::connectionMousePressed(int button, unsigned int uid, unsigned int nid, unsigned int fid)
{
    std::cout << "connection mouse pressed, button " << button << " uid " << uid << " nid " << nid << " fid " << fid << std::endl;
}

void SceneGraphEditor::connectionMouseReleased(int button, unsigned int uid, unsigned int nid, unsigned int fid)
{
    std::cout << "connection mouse released, button " << button << " uid " << uid << " nid " << nid << " fid " << fid << std::endl;
}

void SceneGraphEditor::connectionMouseClicked(int button, unsigned int uid, unsigned int nid, unsigned int fid)
{
    std::cout << "connection mouse clicked, button " << button << " uid " << uid << " nid " << nid << " fid " << fid << std::endl;
    
    if(SGState::mode==SGState::Normal)
        SGState::mode=SGState::FieldConnection;
    else
        SGState::mode=SGState::Normal;
}

void SceneGraphEditor::clearGraph()
{
    std::for_each(m_links.begin(), m_links.end(), [](SceneGraphLink* link){ delete link; });
    m_links.clear();
    std::for_each(m_nodes.begin(), m_nodes.end(), [](SceneGraphNode* node){ delete node; });
    m_nodes.clear();
}

void SceneGraphEditor::updateNodes()
{
    for(auto n : m_nodes)
        n->update();
}

void SceneGraphEditor::paint(QPainter* painter)
{
    setFillColor(QColor(BACKGROUND_COLOR));
    painter->setRenderHints(QPainter::Antialiasing, true);

    //std::for_each(m_nodes.begin(),m_nodes.end(),[painter](SceneGraphNode* n){ n->paint(painter); });
    std::for_each(m_links.begin(),m_links.end(),[painter](SceneGraphLink* l){ l->paint(painter); });
}

void SceneGraphEditor::updateGraph()
{
    int xpos = 50;
    int ypos = 50;

    clearGraph();

    std::vector<int> uids;

    // disabled selection as root for testing
    //feather::qml::command::get_selected_nodes(uids);
    uids.push_back(0);

    std::cout << uids.size() << " nodes are selected\n";

    std::for_each(uids.begin(),uids.end(),[](int& n){ std::cout << n << ","; });

    // for each selected uid we will draw all the nodes connected to it.
    //for(uint i=0; i < uids.size(); i++) {
    //    updateLeaf(nullptr,uids[i],xpos,ypos);
    //}
    updateLeaf(nullptr,0,xpos,ypos);
}


void SceneGraphEditor::updateLeaf(SceneGraphNode* pnode, int uid, int xpos, int ypos)
{
    int nid=0;
    feather::status s = feather::qml::command::get_node_id(uid,nid);

    // if the node is already in the draw list, don't add a new one
    SceneGraphNode *node = getNode(uid);
    if(!node){
        std::cout << "ADDING NODE TO SG EDITOR\n";
        node = new SceneGraphNode(uid,nid,this);
        m_nodes.push_back(node);
        // setup the node qt connections
        connect(node,SIGNAL(ConnClicked(Qt::MouseButton,SceneGraphConnection::Connection,int,int)),this,SLOT(ConnOption(Qt::MouseButton,SceneGraphConnection::Connection,int,int)));
        connect(node,SIGNAL(nodePressed(Qt::MouseButton,int,int)),this,SLOT(nodePressed(Qt::MouseButton,int,int)));

        // place the node in the scenegraph
        node->setX(xpos);
        node->setY(ypos);

        // if the parent is null, there is no need to get any connections between the two nodes
        if(pnode!=nullptr){
            // draw the links between between the pnode and the node
            // go through each child nodes input field and create a link if it's hooked to the parent node
            uint fc = feather::qml::command::get_field_count(node->uid());

            // if the pnode is the root, only connect the parent and child fields
            if(!pnode->uid()){
                m_links.push_back(new SceneGraphLink(pnode,2,node,1,this));
            } else {   
                for(uint i=1; i <= fc; i++){
                    // get the fid's fieldBase
                    feather::field::FieldBase* f;
                    feather::qml::command::get_node_field_base(uid,i,f);
                    if(f!=nullptr){
                        if(f->puid==pnode->uid() && f->conn_type==feather::field::connection::In)
                            m_links.push_back(new SceneGraphLink(pnode,f->pf,node,i,this));
                    }
                }
            }            
        }

        // since this is a new node we need to also draw it's children and links

        // get the connected nodes
        std::vector<int> cuids;
        feather::qml::command::get_node_connected_uids(uid,cuids);

        // add a link for each connection between the two nodes
        int ystep=0;
        for(auto c : cuids) {
            // add the child node to draw list and get it's links
            updateLeaf(node, c, xpos+200, ypos+ystep);
            ystep+=40;
        } 

    }

}


void SceneGraphEditor::mousePressEvent(QMouseEvent* event){ std::cout << "mouse press\n"; };
void SceneGraphEditor::mouseReleaseEvent(QMouseEvent* event){ std::cout << "mouse release\n"; };
void SceneGraphEditor::hoverEnterEvent(QHoverEvent* event){ std::cout << "hover enter\n"; };
void SceneGraphEditor::hoverLeaveEvent(QHoverEvent* event){ std::cout << "hover leave\n"; };
void SceneGraphEditor::hoverMoveEvent(QHoverEvent* event){ std::cout << "hover move\n"; };
void SceneGraphEditor::mouseMoveEvent(QMouseEvent* event){ std::cout << "mouse move\n"; };

