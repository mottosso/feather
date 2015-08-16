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
    addLayer(0,"Base",QColor("grey"),true,false);
    addLayer(1,"A",QColor("grey"),true,false);
    addLayer(2,"B",QColor("grey"),true,false);

    //updateLayers();
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
    roles.insert(SelectedRole, QByteArray("layerSelected"));
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
        case SelectedRole:
            return QVariant::fromValue(dobj->selected);
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
    // this will create a new layer with not uids
    feather::FLayer l(name.toStdString(),feather::FColorRGB( static_cast<float>(color.red())/255.0, static_cast<float>(color.green())/255.0, static_cast<float>(color.blue())/255.0 ), visible, locked);
    feather::qml::command::add_layer(l);
    updateLayers();
}

void LayerModel::moveLayerUp()
{
    for(uint i=0; i < m_layers.size()-1; i++){
        if(m_layers.at(1)->selected){
            moveLayer(i,i+1);
            break;
        }
    }       
}

void LayerModel::moveLayerDown()
{

}

void LayerModel::moveLayer(int sid, int tid)
{
    //clear(); 
    feather::qml::command::move_layer(sid,tid);
    std::cout << "LayerModel\n";
    for(int i=0; i < m_layers.size(); i++){
        std::cout << "layer " << i << " name: " << m_layers[i]->name.toStdString().c_str() << std::endl;
    }
    updateLayers();
}

void LayerModel::updateLayers()
{
    // THIS IS FOR TESTING
    uint size = feather::qml::command::layer_count();

    m_layers.clear();

    for(uint i=0; i < size; i++){
        feather::FLayer l;
        feather::qml::command::get_layer(i,l);
        m_layers.append(new LayerInfo(i,QString(l.name.c_str()),QColor(l.color.int_red(),l.color.int_green(),l.color.int_blue())));
    }
    layoutChanged();
}

