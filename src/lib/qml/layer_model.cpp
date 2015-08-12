/***********************************************************************
 *
 * Filename: layer_model.cpp
 *
 * Description: qml list model for layers.
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

#include "layer_model.hpp"

LayerModel::LayerModel(QObject* parent) : QAbstractListModel(parent)
{
    // TESTING
    addLayers();
}

LayerModel::~LayerModel()
{
}                                                                        

QHash<int, QByteArray> LayerModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles.insert(IdRole, QByteArray("layerId"));
    roles.insert(NameRole, QByteArray("layerName"));
    roles.insert(ColorRole, QByteArray("layerColor"));
    roles.insert(VisibleRole, QByteArray("layerVisible"));
    roles.insert(LockedRole, QByteArray("layerLocked"));
    return roles;
}

int LayerModel::rowCount(const QModelIndex& parent) const
{
    return m_layers.size();
}

QVariant LayerModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant(); // Return Null variant if index is invalid
    if (index.row() > (m_layers.size()-1) )
        return QVariant();
    LayerInfo *dobj = m_layers.at(index.row());
    switch (role) {
        case Qt::DisplayRole: // The default display role now displays the first name as well
        case IdRole:
            return QVariant::fromValue(dobj->id);
        case NameRole:
            return QVariant::fromValue(dobj->name);
        case ColorRole:
            return QVariant::fromValue(dobj->color);
        case VisibleRole:
            return QVariant::fromValue(dobj->visible);
        case LockedRole:
            return QVariant::fromValue(dobj->locked);
        default:
            return QVariant();
    }
}

void LayerModel::clear()
{
    m_layers.clear();
}

void LayerModel::addLayer(int id, QString name, QColor color, bool visible, bool locked)
{
    m_layers.append(new LayerInfo(id,name,color,visible,locked));
}

void LayerModel::addLayers()
{
    // THIS IS FOR TESTING
    m_layers.append(new LayerInfo(0,"base","hotpink"));
    m_layers.append(new LayerInfo(1,"A","limegreen"));
    m_layers.append(new LayerInfo(2,"B","skyblue"));
    layoutChanged();
 
    /*
    feather::qml::command::get_fid_list(uid,nid,feather::field::connection::In,fids);
    m_layers.clear();
    for(uint i=0; i < fids.size(); i++) {
        m_layers.append(new LayerInfo(uid,nid,fids.at(i)->id,fids.at(i)->type,0));
    }
    layoutChanged();
    */
}

