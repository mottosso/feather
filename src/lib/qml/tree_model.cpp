/***********************************************************************
 *
 * Filename: tree_model.cpp
 *
 * Description: qml list model used by the outliner.
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

#include "tree_model.hpp"

// LEAF

Leaf::Leaf(const QList<QVariant> &data, Leaf *parent)
{
    m_parentItem = parent;
    m_itemData = data;
}

Leaf::~Leaf()
{
    qDeleteAll(m_childItems);
}

void Leaf::appendChild(Leaf *item)
{
    std::cout << "APPENDING CHILD\n";
    m_childItems.append(item);
}

Leaf *Leaf::child(int row)
{
    return m_childItems.value(row);
}

int Leaf::childCount() const
{
    return m_childItems.count();
}

int Leaf::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<Leaf*>(this));

    return 0;
}

int Leaf::columnCount() const
{
    return m_itemData.count();
}

QVariant Leaf::data(int column) const
{
    return m_itemData.value(column);
}

Leaf *Leaf::parentItem()
{
    return m_parentItem;
}

void Leaf::clear()
{
    std::for_each(m_childItems.begin(), m_childItems.end(), [](Leaf* leaf){
        delete leaf;
        leaf=0;
    });

    m_childItems.clear();
    std::cout << "childItems cleared and are now " << m_childItems.count() << std::endl;
 
}

bool Leaf::removeChildren(int position, int count)
{
    if (position < 0 || position + count > m_childItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete m_childItems.takeAt(position);

    return true;
}

bool Leaf::removeColumns(int position, int columns)
{
    if (position < 0 || position + columns > m_itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        m_itemData.removeAt(position);

    std::for_each (m_childItems.begin(), m_childItems.end(), [position,columns](Leaf* child){
        child->removeColumns(position, columns);
    });

    return true;
}

bool Leaf::removeNode(int uid)
{
    std::for_each(m_childItems.begin(), m_childItems.end(), [](Leaf* leaf){
            std::cout << "leaf data = "
            << leaf->data(0).toInt() << " "
            << leaf->data(1).toInt() << " "
            << leaf->data(2).toInt() << " "
            << leaf->data(3).toInt() << "\n"
            ;
            });
    return false;
}

// TREE MODEL
    TreeModel::TreeModel(QObject *parent)
: QAbstractItemModel(parent)
{
    QList<QVariant> rootData;
    rootData << "name" << "visible" << "icon" << "uid" << "nid";

    /*
    QModelIndex root = index(0,0);
 
    Leaf* rootItem;    
    if(root.isValid())
        rootItem=static_cast<Leaf*>(root.internalPointer());
    else
        rootItem=new Leaf(rootData);
    */

    rootItem = new Leaf(rootData);
    updateTree();
}

TreeModel::~TreeModel()
{
    std::cout << "delete tree model\n";
    delete rootItem;
    rootItem=0;
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    Leaf *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<Leaf*>(parent.internalPointer());

    Leaf *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}


QHash<int, QByteArray> TreeModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[VisibleRole] = "visible";
    roles[IconRole] = "icon";
    roles[UidRole] = "uid";
    roles[NidRole] = "nid";
    return roles;
}



QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    Leaf *childItem = static_cast<Leaf*>(index.internalPointer());
    Leaf *parentItem = childItem->parentItem();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    Leaf *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<Leaf*>(parent.internalPointer());

    return parentItem->childCount();
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<Leaf*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();

}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    //std::cout << "tree data update\n";

    if (!index.isValid())
        return QVariant();

    Leaf *item = static_cast<Leaf*>(index.internalPointer());

    switch (role) {
        case NameRole:
            std::cout << "Name role enum value:" << NameRole << std::endl;
            return item->data(0);
        case VisibleRole:
            return item->data(1);
        case IconRole:
            return item->data(2);
        case UidRole:
            return item->data(3);
         case NidRole:
            return item->data(4);
        default:
            return QVariant();
    }

}


Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsUserCheckable | Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

void TreeModel::updateTree(QModelIndex parent)
{
    std::cout << "**** UPDATE OUTLINER TREE ****\n";
    Leaf* root;    
    if(parent.isValid())
        root=static_cast<Leaf*>(parent.internalPointer());
    else
        root=rootItem;

    /*
    QModelIndex parent = index(0,0);
    if(parent.isValid())
        static_cast<Leaf*>(parent.internalPointer())->clear();
    */
 
    //QList<QVariant> rootData;
    //rootData << "name" << "visible" << "icon" << "uid" << "nid";

    emit layoutAboutToBeChanged();
    root->clear();
    //delete rootItem;
    //rootItem = new Leaf(rootData);
    loadChildren(0,root);
    emit layoutChanged();

    // model will not update without this 
    //int childCount = columnCount(parent);    
    //removeColumns(0,childCount,parent);
    //std::cout << "updateTree child count " << childCount  << std::endl;
    // changePersistentIndex(index(0,0),index(4,0));
}

void TreeModel::test()
{
    //removeRows(0,1); // this deletes everything
    //removeRows(0,4,index(0,0)); // this only deletes the first four nodes under root
    //removeNode(2,index(0,0));
    clearTree();
}

QModelIndex TreeModel::setCurrentNode(int uid)
{
    std::cout << "SETTING CURRENT NODE TO:" << uid << std::endl;
    QModelIndex rindex = getNodeIndex(uid,index(0,0));
    if(!rindex.isValid())
        return QModelIndex();
    else
        return rindex;
 
    //Leaf *parentItem = static_cast<Leaf*>(rindex.internalPointer())->parentItem();

    //int row = static_cast<Leaf*>(rindex.internalPointer())->row();
    //Leaf *parentItem = childItem->parentItem();

    //if (!hasIndex(row, 0, parentItem))
    //    return QModelIndex();
    //else
    //return createIndex(row, 0, parentItem);


    /*
    QModelIndex parent = index(0,0);
    int childCount=0;
    if(parent.isValid()) {
        childCount = static_cast<Leaf*>(parent.internalPointer())->childCount();
        std::cout << "parent for uid: " << uid << " is valid.\n";
    }
    //Leaf* leaf = static_cast<Leaf*>(parent.internalPointer());
 
    //int childCount = columnCount(parent);    
    //int childCount = leaf->childCount();    
    std::cout << "uid " << uid << " child count " << childCount  << std::endl;
 
    for(int i=0; i<childCount; i++){
        //Leaf* leaf = static_cast<Leaf*>(index(1,i).internalPointer());
        std::cout << "Leaf " << i << " values are " 
            << data(index(i,0,parent),257).toInt() << " "
            << data(index(i,0,parent),258).toInt() << " "
            << data(index(i,0,parent),259).toInt() << " "
            << data(index(i,0,parent),260).toInt() << " "
            << data(index(i,0,parent),261).toInt() << " "
            << std::endl;  
        if(uid==data(index(i,0,parent),260).toInt()) {
            std::cout << "returning row " << i << std::endl;
            return index(i,0,parent);
        }
    }
    return index(uid,0);
    */
}

QModelIndex TreeModel::getNodeIndex(int uid, QModelIndex parent)
{
    if(!parent.isValid())
        return QModelIndex();

    int childCount=0;
    childCount = static_cast<Leaf*>(parent.internalPointer())->childCount();
    int row = static_cast<Leaf*>(parent.internalPointer())->row();
    std::cout << "searching " << row << " uid=" << data(parent,260).toInt() << std::endl;
    if(data(parent,260).toInt() == uid)
        return parent;

    QModelIndex rindex;

    for(int i=0; i<childCount; i++){
        rindex=getNodeIndex(uid,index(i,0,parent));
        //std::cout << "i=" << i << " uid=" << data(index(i,0,parent),260).toInt();
        if(rindex.isValid()) {
            std::cout << "uid:" << data(rindex,260).toInt() << " VALID\n";
            if(data(rindex,260).toInt()==uid)
                return rindex;
        }
    }

    return QModelIndex();    
}

bool TreeModel::removeColumns(int position, int columns, const QModelIndex &parent) 
{
    bool success;

    beginRemoveColumns(parent, position, position + columns - 1);
    success = rootItem->removeColumns(position, columns);
    endRemoveColumns();

    /*
    if (rootItem->columnCount() == 0)
        removeRows(0, rowCount());
    */

    return success;
}

bool TreeModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    Leaf* parentItem = getLeaf(parent);
    bool success = true;

    beginRemoveRows(parent, position, position + rows - 1);
    //success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}

Leaf* TreeModel::getLeaf(const QModelIndex& index) const
{
    if (index.isValid()) {
        Leaf* item = static_cast<Leaf*>(index.internalPointer());
        if (item)
            return item;
    }
    return rootItem;
}

void TreeModel::removeNode(int uid, const QModelIndex& parent)
{

    std::cout << "looking at parent " << data(parent,260).toInt() << " children\n";
    QList<Leaf*> children = getLeaf(parent)->childItems();

    std::for_each(children.begin(), children.end(), [this,&parent,uid](Leaf* leaf){
        std::cout << "looking at child " << leaf->data(3).toInt() << std::endl;
        // TODO for now I have to remove all the children of a parent
        // because when just one item is deleted all the other child
        // nodes get moved out of root and new nodes take their place
        if(uid == leaf->data(3).toInt()){
            std::cout << "REMOVING NODE " << uid << " child" << std::endl;
            removeRows(leaf->row(),1,parent);
        } else {
            std::cout << "Looking into child node of uid " << uid << std::endl;
            removeNode(uid,index(leaf->row(),0,parent));
        }
    });
}

void TreeModel::clearTree()
{
    QModelIndex parent = index(0,0);
    QList<Leaf*> children = getLeaf(parent)->childItems();

    std::for_each(children.begin(), children.end(), [this,&parent](Leaf* leaf){
        std::cout << "removing child " << leaf->data(3).toInt() << " at " << leaf->row() << std::endl;
        removeRows(leaf->row(),1,parent);
    });
}

void TreeModel::loadChildren(const int uid, Leaf* parent)
{
    QList<QVariant> data;
    // create data
    data.append(feather::qml::command::get_node_name(uid).c_str()); // name
    data.append(true); // visible
    int nid;
    std::string icon;
    feather::qml::command::get_node_id(uid,nid); 
    feather::qml::command::get_node_icon(nid,icon); 
    data.append(icon.c_str()); // icon 
    data.append(uid); // uid
    data.append(0); // nid

    //std::cout << "load child for " << uid << std::endl;

    std::cout << "CHILD APPENDED to " << uid << std::endl;
    parent->appendChild(new Leaf(data,parent)); 

    // recursive loop through each child node
    std::vector<int> children;

    feather::qml::command::get_node_connected_uids(uid,children);
    std::cout << "tree model loadChildren uid " << uid << " has " << children.size() << " children " << std::endl;
   
    if(!children.size())
        return;

    for_each(children.begin(), children.end(), [this,&parent](int uid){
        loadChildren(uid,parent->lastChild());
    });
}

