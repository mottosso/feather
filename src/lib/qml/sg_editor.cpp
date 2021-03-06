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
#include "state.hpp"

#define BACKGROUND_COLOR "#444444"
#define NODE_TEXT_COLOR "#000000"
#define SELECTED_NODE_COLOR "#FF007F"
#define DESELECTED_NODE_COLOR "#666666"
#define NODE_TITLE_BLOCK_COLOR "#888888"
#define HOVER_NODE_COLOR "#FF8C00"
#define SELECTED_CONNECTOR_COLOR "#FFFF00" // TODO
#define DESELECTED_IN_CONNECTOR_COLOR "#50C878"
#define HOVER_CONNECTOR_COLOR "#FFBF00"
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
std::vector<SceneGraphConnection*> SGState::selectedConnections = std::vector<SceneGraphConnection*>();

// SCENEGRAPH

SceneGraphConnection::SceneGraphConnection(QString name, int fid, SceneGraphNode* node, SceneGraphConnection::Connection type, QQuickItem* parent) :
    QQuickPaintedItem(parent),
    m_name(name),
    m_selected(false),
    m_type(type),
    m_node(node),
    m_fid(fid)
{
    setWidth(CONNECTION_WIDTH+(NODE_WIDTH/2));
    setHeight(CONNECTION_HEIGHT);
    setAcceptedMouseButtons(Qt::AllButtons);
    setAcceptHoverEvents(true);

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
    
    if(!m_selected){
        if(m_type == In)
            m_connFillBrush = QBrush(QColor(DESELECTED_IN_CONNECTOR_COLOR));
        else
            m_connFillBrush = QBrush(QColor(DESELECTED_OUT_CONNECTOR_COLOR));
    } else {
        m_connFillBrush = QBrush(QColor(SELECTED_CONNECTOR_COLOR));
    }
   
    painter->setBrush(m_connFillBrush);

    // text block 
    if(m_type == In)
        painter->drawRect(CONNECTION_WIDTH+2,0,width(),height());
    else
        painter->drawRect(0,0,width()-CONNECTION_WIDTH,height());
 
    QPen textPen(QColor(NODE_TEXT_COLOR),2);
    QFont textFont("DejaVuSans",7);
    painter->setPen(textPen);
    painter->setFont(textFont);
    if(m_type == In) {
        painter->drawText(QRect(CONNECTION_WIDTH+2,0,NODE_WIDTH/2,height()),Qt::AlignLeft|Qt::AlignVCenter,m_name);
    } else {
        painter->drawText(QRect(0,0,(NODE_WIDTH/2)-2,height()),Qt::AlignRight|Qt::AlignVCenter,m_name);
    }


    if(m_type == In) {
        painter->drawRect(0,0,CONNECTION_WIDTH,CONNECTION_HEIGHT);
    } else {
        painter->drawRect(NODE_WIDTH/2,0,CONNECTION_WIDTH,CONNECTION_HEIGHT);
    }

}

void SceneGraphConnection::mousePressEvent(QMouseEvent* event)
{
    std::cout << "connector mouse press event\n";
    MouseInfo::clickX = event->windowPos().x();
    MouseInfo::clickY = event->windowPos().y();

    // add to selected connections
    if(!m_selected) {
        m_selected=true;
        SGState::selectedConnections.push_back(this);
    } else {
        m_selected=false;
        SGState::remove(this);
    }

    connClicked(event->button(),m_type);
    update();
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
SceneGraphNode::SceneGraphNode(int uid, int nid, QQuickItem* parent) : 
    QQuickPaintedItem(parent),
    m_uid(uid),
    m_nid(nid),
    m_x(0),
    m_y(0),
    m_imgDir("ui/icons/"),
    m_nodeFillBrush(QBrush(QColor(DESELECTED_NODE_COLOR))),
    m_layerFillBrush(QBrush(QColor("#DDDDDD"))),
    m_nodeTitleBrush(QBrush(QColor(NODE_TITLE_BLOCK_COLOR)))
    //m_pFieldNames(model)
{
    feather::status e;

    if(feather::smg::Instance()->selected(m_uid))
        m_nodeFillBrush.setColor(QColor(SELECTED_NODE_COLOR));
    else
        m_nodeFillBrush.setColor(QColor(DESELECTED_NODE_COLOR));

    setAcceptedMouseButtons(Qt::AllButtons);
    setAcceptHoverEvents(true);

    m_inConnCount = feather::qml::command::get_in_field_count(m_uid);
    m_outConnCount = feather::qml::command::get_out_field_count(m_uid);
    m_connCount = feather::qml::command::get_field_count(m_uid);

    std::vector<feather::field::FieldBase*> inFields;
    std::vector<feather::field::FieldBase*> outFields;
  
    feather::qml::command::get_fid_list(m_uid,m_nid,feather::field::connection::In,inFields);
    feather::qml::command::get_fid_list(m_uid,m_nid,feather::field::connection::Out,outFields);

    int i=1; 
    for(auto field : inFields) { 
        // add the input fields here
        int fid = field->id;
        std::cout << "nid:" << m_nid << ", fid:" << fid << std::endl;
        SceneGraphConnection* conn = new SceneGraphConnection(FieldModel::getFieldName(m_nid,fid),fid,this,SceneGraphConnection::In,this);
        m_pInConns.push_back(conn);
        conn->setX(0);
        conn->setY(((CONNECTION_HEIGHT+2)*i)+12);
        connect(conn,SIGNAL(connClicked(Qt::MouseButton,SceneGraphConnection::Connection)),this,SLOT(ConnPressed(Qt::MouseButton,SceneGraphConnection::Connection)));
        i++;
    }

    i=1;
    for(auto field : outFields) { 
        // add the input fields here
        int fid = field->id;
        std::cout << "nid:" << m_nid << ", fid:" << fid << std::endl;
        SceneGraphConnection* conn = new SceneGraphConnection(FieldModel::getFieldName(m_nid,fid),fid,this,SceneGraphConnection::Out,this);
        m_pOutConns.push_back(conn);
        conn->setX((NODE_WIDTH/2)+CONNECTION_WIDTH);
        conn->setY(((CONNECTION_HEIGHT+2)*i)+12);
        connect(conn,SIGNAL(connClicked(Qt::MouseButton,SceneGraphConnection::Connection)),this,SLOT(ConnPressed(Qt::MouseButton,SceneGraphConnection::Connection)));
        i++;
    }

    feather::qml::command::get_node_icon(m_nid,m_imgFile,e);
    m_imgPath << m_imgDir << m_imgFile;

    // set the node's height based on side with the most connections
    int max = 0;
    if(inFields.size() > outFields.size())
        max = inFields.size();
    else
        max = outFields.size();

    setWidth(NODE_WIDTH+(CONNECTION_WIDTH*2));
    //setHeight(NODE_HEIGHT+4);
    setHeight(((CONNECTION_HEIGHT + 2) * max) + 24 + 24);
}

SceneGraphNode::~SceneGraphNode()
{
    for(auto c : m_pInConns)
        delete c;
    m_pInConns.clear();

    for(auto c : m_pInConns)
        delete c;
    m_pInConns.clear();

    //delete m_pInConn;
    //delete m_pOutConn;
}

void SceneGraphNode::ConnPressed(Qt::MouseButton button, SceneGraphConnection::Connection conn)
{
    std::cout << "node got connector event\n";
    ConnClicked(button,conn,m_uid,m_nid); 
}

void SceneGraphNode::paint(QPainter* painter)
{
    feather::status e;
    painter->setRenderHints(QPainter::Antialiasing, true);
 
    QPen trimPen = QPen(QColor(0,0,0),1);
    //trimPen.setStyle(Qt::NoPen);
    QPen textPen = QPen(QColor(NODE_TEXT_COLOR),2);
    QFont textFont("DejaVuSans",10);

    if(feather::smg::Instance()->selected(m_uid))
        m_nodeFillBrush.setColor(QColor(SELECTED_NODE_COLOR));
    else
        m_nodeFillBrush.setColor(QColor(DESELECTED_NODE_COLOR));

    textFont.setBold((feather::smg::Instance()->selected(m_uid)) ? true : false);

    QBrush connInFillBrush = QBrush(QColor("#FF4500"));
    QBrush connOutFillBrush = QBrush(QColor("#DA70D6"));

    // set the node's height based on side with the most connections
    int max = 0;
    if(m_pInConns.size() > m_pOutConns.size())
        max = m_pInConns.size();
    else
        max = m_pOutConns.size();

    //setWidth(NODE_WIDTH+4);
    //int height = (CONNECTION_HEIGHT * max) + NODE_HEIGHT;
    //setHeight(height+10);
    //setHeight(NODE_HEIGHT+44);

    // node trim 
    painter->setPen(trimPen);

    // draw layer bar
    painter->setBrush(m_layerFillBrush);

    // draw title block
    painter->setBrush(m_nodeTitleBrush);
    painter->drawRect(CONNECTION_WIDTH+5,2,NODE_WIDTH-10,18);

    // draw the node block
    painter->setBrush(m_nodeFillBrush);
    painter->drawRect(CONNECTION_WIDTH,18,NODE_WIDTH,height()-20);

    // node icon
    QRectF tgt(CONNECTION_WIDTH + (NODE_WIDTH/2)-12,height()-24,24,24);
    QImage img(m_imgPath.str().c_str());
    painter->drawImage(tgt,img);

    // node label 
    painter->setPen(textPen);
    painter->setFont(textFont);
    std::string name;
    feather::qml::command::get_node_name(m_uid,name,e);
    painter->drawText(QRect(CONNECTION_WIDTH+5,2,NODE_WIDTH-10,18),Qt::AlignHCenter|Qt::AlignVCenter,name.c_str());

}

void SceneGraphNode::mousePressEvent(QMouseEvent* event)
{
    m_x = event->screenPos().x();
    m_y = event->screenPos().y();
}

void SceneGraphNode::mouseDoubleClickEvent(QMouseEvent* event)
{
    emit nodePressed(event->button(),m_uid,m_nid);
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
    for(auto c : m_pInConns) {
        if(c->fid() == fid)
            point = mapToItem(parentItem(),QPoint(c->x(),c->y()+(CONNECTION_WIDTH/2)));
    }
}

void SceneGraphNode::outConnectionPoint(unsigned int fid, QPointF& point)
{
    for(auto c : m_pOutConns) {
        if(c->fid() == fid)
            point = mapToItem(parentItem(),QPoint(c->x()+(NODE_WIDTH/2)+CONNECTION_WIDTH,c->y()+(CONNECTION_WIDTH/2)));
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

SceneGraphConnection* SceneGraphNode::inConnection(unsigned int fid)
{
    for(auto c : m_pInConns){
        if(c->fid()==fid)
            return c;
    }
    return nullptr;
}

SceneGraphConnection* SceneGraphNode::outConnection(unsigned int fid)
{
    for(auto c : m_pOutConns){
        if(c->fid()==fid)
            return c;
    }
    return nullptr;
}

std::vector<SceneGraphConnection*>& SceneGraphNode::inConnections()
{
    return m_pInConns;
}

std::vector<SceneGraphConnection*>& SceneGraphNode::outConnections()
{
    return m_pOutConns;
}


// Link

SceneGraphLink::SceneGraphLink(SceneGraphConnection* sconn, SceneGraphConnection* tconn, QQuickItem* parent) :
QQuickPaintedItem(parent),
m_sconnection(sconn),
m_tconnection(tconn)
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
    m_sconnection->node()->outConnectionPoint(m_sconnection->fid(),sp);
    m_tconnection->node()->inConnectionPoint(m_tconnection->fid(),tp);

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
}

SceneGraphEditor::~SceneGraphEditor()
{
    clearGraph();
}

void SceneGraphEditor::ConnOption(Qt::MouseButton button, SceneGraphConnection::Connection conn, int uid, int nid)
{
    std::cout << "sg editor got node connector event\n";

    feather::field::FieldBase* pfield;
    int i=1;
    feather::qml::command::get_field_base(uid,i,pfield);

    /*
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
    */
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

bool SceneGraphEditor::connectNodes()
{
    if(SGState::selectedConnections.size() > 1){
        // for now we'll just connect the inputs to the first in connection we see
        SceneGraphConnection* in = nullptr;

        // find the first in connection
        for(auto c : SGState::selectedConnections) {
            if(c->type() == SceneGraphConnection::In) {
                in = c;
                break;
            }
        }

        if(in != nullptr) {
            for(auto c : SGState::selectedConnections) {
                if(c->type() == SceneGraphConnection::Out) {
                    // are they are two connections already connected?
                    feather::qml::command::connect_nodes(c->node()->uid(),c->fid(),in->node()->uid(),in->fid()); 
                    m_links.push_back(new SceneGraphLink(in,c,this));
                 }
            }
        }
    }

    // unselect all the currently selected connections
    for(auto c : SGState::selectedConnections)
        c->setSelected(false);

    SGState::selectedConnections.erase(SGState::selectedConnections.begin(),SGState::selectedConnections.end());

   feather::qml::command::scenegraph_update();

    update();
    return true;
}

bool SceneGraphEditor::disconnectNodes()
{

    return false;
}

void SceneGraphEditor::paint(QPainter* painter)
{
    setFillColor(QColor(BACKGROUND_COLOR));
    painter->setRenderHints(QPainter::Antialiasing, true);

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

    updateNode(nullptr,0,xpos,ypos);
    for(auto n : m_nodes) 
        updateLinks(n->uid());
}


void SceneGraphEditor::updateNode(SceneGraphNode* pnode, int uid, int xpos, int ypos)
{
    feather::status e;
    unsigned int nid = feather::qml::command::get_node_id(uid,e);

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

        // get the connected nodes
        std::vector<int> cuids;
        feather::qml::command::get_node_connected_uids(uid,cuids);

        // add a link for each connection between the two nodes
        int ystep=0;
        for(auto c : cuids) {
            // add the child node to draw list and get it's links
            updateNode(node, c, xpos+200, ypos+ystep);
            ystep+=node->height()+40;
        } 

    }

}

void SceneGraphEditor::updateLinks(int uid)
{
    // draw all links between the uid and it's children nodes
    
    // get the node
    SceneGraphNode* pnode = nullptr;
    for(auto n : m_nodes){
        if(n->uid() == uid)
            pnode=n;
    }

    // no point in going any further if no node was found
    if(!pnode)
        return;

    // get all the node's output connections
    std::vector<int> uids;
    feather::qml::command::get_node_connected_uids(uid,uids); 

    // if there is no connected nodes, no need to go any further
    if(!uids.size())
        return;

    // some of the connected uids are not shown in sg editor, so remove them from the list
    std::vector<int> shownuids;

    for(auto tuid : uids){
        for(auto n : m_nodes){
            if(n->uid()==tuid)
                shownuids.push_back(tuid);
        } 
    }

    // if none of the uids are displayed, no need to go any further
    if(!shownuids.size())
        return;

    // for each node create a link for each connection
    for(auto tuid : shownuids){
        // go through each in field of the target uid
        for(auto tconn : getNode(tuid)->inConnections()){

            // go through each out field of the parent uid
            for(auto sconn : pnode->outConnections()){
                // is the field connected
                bool connected=false;
                feather::qml::command::get_field_connection_status(uid, sconn->fid(), tuid, tconn->fid(), connected);
                if(connected){
                    // add the link
                    m_links.push_back(new SceneGraphLink(sconn,tconn,this));
                }
            }
        }
    }
}

void SceneGraphEditor::mousePressEvent(QMouseEvent* event){ std::cout << "mouse press\n"; };
void SceneGraphEditor::mouseReleaseEvent(QMouseEvent* event){ std::cout << "mouse release\n"; };
void SceneGraphEditor::hoverEnterEvent(QHoverEvent* event){ std::cout << "hover enter\n"; };
void SceneGraphEditor::hoverLeaveEvent(QHoverEvent* event){ std::cout << "hover leave\n"; };
void SceneGraphEditor::hoverMoveEvent(QHoverEvent* event){ std::cout << "hover move\n"; };
void SceneGraphEditor::mouseMoveEvent(QMouseEvent* event){ std::cout << "mouse move\n"; };
