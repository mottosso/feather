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

TreeModel::TreeModel(QObject* parent) : QAbstractListModel(parent)
{
    addLeaf(LeafInfo(1,2));
    addLeaf(LeafInfo(2,3));
}

TreeModel::~TreeModel()
{
}                                                                        

QHash<int, QByteArray> TreeModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[UidRole] = "uid";
    roles[NidRole] = "nid";
    return roles;
}

int TreeModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return m_tree.count();
}

QVariant TreeModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant(); // Return Null variant if index is invalid
    if (index.row() > (m_tree.size()-1) )
        return QVariant();
    const LeafInfo &leaf = m_tree[index.row()];
    if(role==UidRole) {
        return leaf.uid;
    }
    else if(role==NidRole) {
        return leaf.nid;
    }
    return QVariant();
}

void TreeModel::clear()
{
    m_tree.clear();
}

void TreeModel::addLeaf(const LeafInfo &leaf)
{
    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    m_tree << leaf;
    endInsertRows();
}

