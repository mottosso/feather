/***********************************************************************
 *
 * Filename: qml_deps.hpp
 *
 * Description: Dependencies for the qml wrapper.
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

#ifndef QML_DEPS_HPP
#define QML_DEPS_HPP

// QT5
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickPaintedItem>
#include <QtQuick/QQuickItem>
#include <QtQuick/qquickwindow.h>
#include <QtQuick/QQuickWindow>
#include <QtQuick/QSGFlatColorMaterial>
#include <QQuickItem>
#include <QtCore/QMutex>
#include <QtCore/QThread>
#include <QtGui/QGuiApplication>
#include <QtGui/QOffscreenSurface>
#include <QTime>
#include <QTimer>

#include <qmath.h>

// QtOpenGL
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLFramebufferObject>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/qvector3d.h>
#include <QtGui/qmatrix4x4.h>
#include <QtGui/qopenglshaderprogram.h>
#include <qsgsimpletexturenode.h>
#include <QVector>
#include <QPainter>
#include <QPaintEngine>
#include <QtOpenGL/QtOpenGL>
#include <QtOpenGL/QGLFunctions>

// Qt3D
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QNode>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DCore/QTranslateTransform>
#include <Qt3DCore/QScaleTransform>
#include <Qt3DRenderer/QCuboidMesh>
#include <Qt3DRenderer/QPhongMaterial>
#include <Qt3DRenderer/QShaderProgram>
#include <Qt3DRenderer/QEffect>
#include <Qt3DRenderer/QTechnique>
#include <Qt3DRenderer/QRenderPass>
#include <Qt3DRenderer/QOpenGLFilter>
#include <Qt3DRenderer/QParameter>
#include <Qt3DRenderer/QParameterMapping>
#include <Qt3DRenderer/qattribute.h>
#include <Qt3DRenderer/qbuffer.h>
#include <Qt3DRenderer/qgeometry.h>
#include <Qt3DInput/QMouseInput>
#include <Qt3DInput/QMouseController>
#include <Qt3DInput/Q3DMouseEvent>

#endif
