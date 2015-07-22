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
};

class TreeModel : public QAbstractListModel
{
    Q_OBJECT
        Q_PROPERTY(QList<LeafInfo*> tree READ tree WRITE setTree NOTIFY treeChanged)
 
    public:
        TreeModel(QObject* parent=0);
        ~TreeModel();

        enum ERoles
        {
            UidRole = Qt::UserRole + 1,
            NidRole = Qt::UserRole + 2,
        };

        QHash<int, QByteArray> roleNames() const;
        Q_INVOKABLE int rowCount(const QModelIndex& parent = QModelIndex()) const;
        QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
        void clear();
 
        // fields 
        void setTree(QList<LeafInfo*>& t) {
            if(m_tree != t) {
                m_tree=t;
            }
        }

        QList<LeafInfo*> tree() { return m_tree; }

        Q_INVOKABLE void addLeaf(int uid, int nid);

    signals:
        void treeChanged();

    private:
        Q_DISABLE_COPY(TreeModel);
        QList<LeafInfo*> m_tree;
};

#endif
