/***********************************************************************
 *
 * Filename: tree_model.hpp
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
#ifndef TREE_MODEL_HPP
#define TREE_MODEL_HPP

#include "deps.hpp"
#include "qml_deps.hpp"
#include "field.hpp"
#include "commands.hpp"

class LeafInfo {
    public:
        LeafInfo(const int &_uid=0, const int &_nid=0): uid(_uid),nid(_nid){}
        int uid;
        int nid;
        std::vector<LeafInfo> children;
};

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT
 
    public:
        TreeModel(QObject* parent=0);
        ~TreeModel();

        enum ERoles
        {
            UidRole = Qt::UserRole + 1,
            NidRole
        };

        QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
        void clear();
 
        void addLeaf(const LeafInfo &leaf);
        int rowCount(const QModelIndex& parent = QModelIndex()) const;
        int columnCount(const QModelIndex& parent = QModelIndex()) const;
        QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const;
        QModelIndex parent(const QModelIndex& index) const;
         
    signals:
        void treeChanged();

    protected:
        QHash<int,QByteArray> roleNames() const;

    private:
        QList<LeafInfo> m_tree;
        QModelIndex m_main;
        QModelIndex m_child;
};

#endif
