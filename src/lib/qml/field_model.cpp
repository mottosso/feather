/***********************************************************************
 *
 * Filename: field_model.cpp
 *
 * Description: qml list model for node fields.
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

#include "field_model.hpp"

FieldModel::FieldModel(QObject* parent) : QAbstractListModel(parent)
{
}

FieldModel::~FieldModel()
{
}                                                                        

QHash<int, QByteArray> FieldModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles.insert(UidRole, QByteArray("uid"));
    roles.insert(NidRole, QByteArray("nid"));
    roles.insert(FidRole, QByteArray("fid"));
    roles.insert(TypeRole, QByteArray("type"));
    roles.insert(LockedRole, QByteArray("locked"));
    return roles;
}

int FieldModel::rowCount(const QModelIndex& parent) const
{
    return m_fields.size();
}

QVariant FieldModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant(); // Return Null variant if index is invalid
    if (index.row() > (m_fields.size()-1) )
        return QVariant();
    FieldInfo *dobj = m_fields.at(index.row());
    switch (role) {
        case Qt::DisplayRole: // The default display role now displays the first name as well
        case UidRole:
            return QVariant::fromValue(dobj->uid);
        case NidRole:
            return QVariant::fromValue(dobj->nid);
        case FidRole:
            return QVariant::fromValue(dobj->fid);
        case TypeRole:
            return QVariant::fromValue(dobj->type);
        case LockedRole:
            return QVariant::fromValue(dobj->locked);
        default:
            return QVariant();
    }
}

void FieldModel::clear()
{
    m_fields.clear();
}

void FieldModel::addField(int uid, int nid, int fid, int type, bool locked)
{
    m_fields.append(new FieldInfo(uid,nid,fid,type,locked));
}

void FieldModel::addFields(int uid, int nid)
{
    std::vector<feather::field::FieldBase*> fids;
    std::cout << "addFields " << nid << std::endl;
    feather::qml::command::get_fid_list(uid,nid,feather::field::connection::In,fids);
    m_fields.clear();
    for(uint i=0; i < fids.size(); i++) {
        m_fields.append(new FieldInfo(uid,nid,fids.at(i)->id,fids.at(i)->type,0));
    }
    layoutChanged();
}

