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
    uid = 10;
}

Leaf::~Leaf()
{
    qDeleteAll(m_childItems);
}

void Leaf::appendChild(Leaf *item)
{
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


// TREE MODEL
    TreeModel::TreeModel(QObject *parent)
: QAbstractItemModel(parent)
{
    QList<QVariant> rootData;
    rootData << "uid" << "nid";
    rootItem = new Leaf(rootData);
    updateTree();
}

TreeModel::~TreeModel()
{
    delete rootItem;
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
    if (!index.isValid())
        return QVariant();

    /* 
    if (role != Qt::DisplayRole)
        return QVariant();
    */

    Leaf *item = static_cast<Leaf*>(index.internalPointer());

    switch (role) {
        case UidRole:
            return item->data(0);
        case NidRole:
            return item->data(1);
        default:
            return QVariant();
    }

}


Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return QAbstractItemModel::flags(index);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

void TreeModel::updateTree()
{
    // Get the scenegraph tree that is stored in the core and updated whenever a node is added or removed.
    // Go through the tree and translate each node to a Leaf to be added to the scenegraph.
    rootItem->clear();

    // Start with the root node
    loadChildren(0,rootItem);
}

void TreeModel::loadChildren(const int uid, Leaf* parent)
{
    QList<QVariant> data;
    QStringList cStrings;
    cStrings << feather::qml::command::get_node_name(uid).c_str() << "0";
    data << cStrings[0];
    parent->appendChild(new Leaf(data,parent)); 

    // recursive loop through each child node
    std::vector<int> children;

    feather::qml::command::get_node_connected_uids(uid,children);
    feather::qml::command::get_children(uid,children);

    if(!children.size())
        return;

    QList<Leaf*> parents;

    for_each(children.begin(), children.end(), [this,&parent](int uid){
        loadChildren(uid,parent->lastChild());
    });
}

