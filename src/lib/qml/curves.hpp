/***********************************************************************
 *
 * Filename: curves.hpp
 *
 * Description: Various curve types that can be drawn in the UI.
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

#ifndef CURVES_HPP
#define CURVES_HPP

#include "deps.hpp"
#include "qml_deps.hpp"

// BEZIER CURVE
class BezierCurve : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QPointF p1 READ p1 WRITE setP1 NOTIFY p1Changed)
    Q_PROPERTY(QPointF p2 READ p2 WRITE setP2 NOTIFY p2Changed)
    Q_PROPERTY(QPointF p3 READ p3 WRITE setP3 NOTIFY p3Changed)
    Q_PROPERTY(QPointF p4 READ p4 WRITE setP4 NOTIFY p4Changed)
    Q_PROPERTY(int segmentCount READ segmentCount WRITE setSegmentCount NOTIFY segmentCountChanged)

    public:
        BezierCurve(QQuickItem *parent = 0);
        ~BezierCurve();

        QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);

        QPointF p1() const { return m_p1; }
        QPointF p2() const { return m_p2; }
        QPointF p3() const { return m_p3; }
        QPointF p4() const { return m_p4; }
        int segmentCount() const { return m_segmentCount; }

        void setP1(const QPointF &p) {
            if(m_p1 != p) {
                m_p1=p;
                emit p1Changed(p);
            }
        };

        void setP2(const QPointF &p) {
            if(m_p2 != p) {
                m_p2=p;
                emit p1Changed(p);
            }
        };

        void setP3(const QPointF &p) {
            if(m_p3 != p) {
                m_p3=p;
                emit p1Changed(p);
            }
        };

        void setP4(const QPointF &p) {
            if(m_p4 != p) {
                m_p4=p;
                emit p1Changed(p);
            }
        };

        void setSegmentCount(int count) {
            if(m_segmentCount != count) {
                m_segmentCount=count;
                emit segmentCountChanged(count);
            }
        };


    signals:
        void p1Changed(const QPointF &p);
        void p2Changed(const QPointF &p);
        void p3Changed(const QPointF &p);
        void p4Changed(const QPointF &p);
        void segmentCountChanged(int count);

    private:
        QPointF m_p1;
        QPointF m_p2;
        QPointF m_p3;
        QPointF m_p4;
        int m_segmentCount;
};

#endif
