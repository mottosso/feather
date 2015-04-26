/***********************************************************************
 *
 * Filename: field_model.hpp
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

#ifndef FIELD_MODEL_HPP
#define FIELD_MODEL_HPP

#include "deps.hpp"
#include "qml_deps.hpp"
#include "field.hpp"
#include "commands.hpp"

class FieldInfo { 
    public:
        FieldInfo(const int &_uid=0,
                const int &_nid=0,
                const int &_fid=0,
                const int &_type=0,
                const bool &_locked=false):
            uid(_uid),
            nid(_nid),
            fid(_fid),
            type(_type),
            locked(_locked) {}
        int uid;
        int nid;
        int fid;
        int type;
        bool locked;
};

class FieldModel : public QAbstractListModel
{
    Q_OBJECT
        Q_PROPERTY(QList<FieldInfo*> fields READ fields WRITE setFields NOTIFY fieldsChanged)
 
    public:
        FieldModel(QObject* parent=0);
        ~FieldModel();

        enum ERoles
        {
            UidRole = Qt::UserRole + 1,
            NidRole = Qt::UserRole + 2,
            FidRole = Qt::UserRole + 3,
            TypeRole = Qt::UserRole + 4,
            LockedRole = Qt::UserRole + 5
        };

        QHash<int, QByteArray> roleNames() const;
        Q_INVOKABLE int rowCount(const QModelIndex& parent = QModelIndex()) const;
        QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
        void clear();
 
        // fields 
        void setFields(QList<FieldInfo*>& f) {
            if(m_fields != f) {
                m_fields=f;
            }
        }

        QList<FieldInfo*> fields() { return m_fields; }

        Q_INVOKABLE void addField(int uid, int nid, int fid, int type, bool locked);
        Q_INVOKABLE void addFields(int uid, int nid);
 
    signals:
        void fieldsChanged();

    private:
        Q_DISABLE_COPY(FieldModel);
        QList<FieldInfo*> m_fields;
};

#endif
