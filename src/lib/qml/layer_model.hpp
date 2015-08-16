/***********************************************************************
 *
 * Filename: layer_model.hpp
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

#ifndef LAYER_MODEL_HPP
#define LAYER_MODEL_HPP

#include "deps.hpp"
#include "qml_deps.hpp"
#include "commands.hpp"

class LayerInfo { 
    public:
        LayerInfo(const int _id,
                const QString _name,
                const QColor _color=QColor(0,0,0),
                const bool _visible=true,
                const bool _locked=false,
                const bool _selected=false ):
            id(_id),
            name(_name),
            color(_color),
            visible(_visible),
            locked(_locked),
            selected(_selected) {}
        int id;
        QString name;
        QColor color;
        bool visible;
        bool locked;
        bool selected;
};

class LayerModel : public QAbstractListModel
{
    Q_OBJECT
        Q_PROPERTY(QList<LayerInfo*> layers READ layers WRITE setLayers NOTIFY layersChanged)
 
    public:
        LayerModel(QObject* parent=0);
        ~LayerModel();

        enum ERoles
        {
            IdRole = Qt::UserRole + 1,
            NameRole,
            ColorRole,
            VisibleRole,
            LockedRole,
            SelectedRole
        };

        Q_INVOKABLE int rowCount(const QModelIndex& parent = QModelIndex()) const;
        QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
        void clear();
 
        // layers 
        void setLayers(QList<LayerInfo*>& f) {
            if(m_layers != f) {
                m_layers=f;
            }
        };

        QList<LayerInfo*> layers() { return m_layers; };
        Q_INVOKABLE void addLayer(int id, QString name, QColor color, bool visible, bool locked);
        Q_INVOKABLE void moveLayerUp();
        Q_INVOKABLE void moveLayerDown();
        Q_INVOKABLE void moveLayer(int sid, int tid);
        Q_INVOKABLE void updateLayers();
        Q_INVOKABLE void test() { std::cout << "this is a test\n"; };

    signals:
        void layersChanged();

    protected:
        QHash<int,QByteArray> roleNames() const;

    private:
        Q_DISABLE_COPY(LayerModel);
        QList<LayerInfo*> m_layers;
};

#endif
