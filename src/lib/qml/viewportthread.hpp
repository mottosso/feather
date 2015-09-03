/***********************************************************************
 *
 * Filename: viewportthread.hpp
 *
 * Description: Threaded viewport.
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

#ifndef VIEWPORTTHREAD_HPP
#define VIEWPORTTHREAD_HPP

#include "deps.hpp"
#include "qml_deps.hpp"
#include "viewport.hpp"
#include "gl_scene.hpp"

class RenderViewportThread;

class ViewportThread : public QQuickItem
{
    Q_OBJECT
    Q_ENUMS(ShadingMode);
    Q_ENUMS(SelectionMode);
    Q_PROPERTY(bool axis READ axis WRITE setAxis NOTIFY axisChanged)
    Q_PROPERTY(bool grid READ grid WRITE setGrid NOTIFY gridChanged)
    Q_PROPERTY(ShadingMode shadingMode READ shadingMode WRITE setShadingMode NOTIFY shadingModeChanged)
    Q_PROPERTY(SelectionMode selectionMode READ selectionMode WRITE setSelectionMode NOTIFY selectionModeChanged)
 
    public:
        ViewportThread();
        ~ViewportThread();

        enum ShadingMode {
            FLAT = feather::gl::glScene::FLAT,
            SHADED = feather::gl::glScene::SHADED
        };

        enum SelectionMode {
            OBJECT = feather::gl::glScene::OBJECT,
            FACE = feather::gl::glScene::FACE,
            EDGE = feather::gl::glScene::EDGE,
            VERTEX = feather::gl::glScene::VERTEX
        };

        static QList<QThread *> threads;
        Q_INVOKABLE void mousePressed(int x, int y);
        Q_INVOKABLE void moveCamera(double x, double y, double z);
        Q_INVOKABLE void rotateCamera(int x, int y);
        Q_INVOKABLE void zoomCamera(int z);
        Q_INVOKABLE void initialize();
        Q_INVOKABLE void nodeInitialize(int uid);
        Q_INVOKABLE void nodesAdded();
        Q_INVOKABLE void updateGL();


        // axis 
        void setAxis(bool& s);
        bool axis() { return m_axis; };

        // grid
        void setGrid(bool& s);
        bool grid() { return m_grid; };

        // shadingMode
        void setShadingMode(ShadingMode& m);
        ShadingMode shadingMode() { return m_shadingMode; };

        // selectionMode 
        void setSelectionMode(SelectionMode& m);
        SelectionMode selectionMode() { return m_selectionMode; };

    signals:
        void axisChanged();
        void gridChanged();
        void shadingModeChanged(ShadingMode m);
        void selectionModeChanged(SelectionMode m);
        //void updateGL();
        void updateGLWindow();

        public Q_SLOTS:
            void ready();
            void updateWindow();
            void setGlToUpdate();

    protected:
        QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);
        //void mousePressEvent(QMouseEvent* event);

    private:
        bool m_update;
        int m_ucount;
        RenderViewportThread *m_renderThread;
        //double m_x;
        //double m_y;
        int m_rx;
        int m_ry;
        // states
        bool m_axis;
        bool m_grid;
        ShadingMode m_shadingMode;
        SelectionMode m_selectionMode;
};


/*
 * The render thread shares a context with the scene graph and will
 * render into two separate FBOs, one to use for display and one
 * to use for rendering
 */
class RenderViewportThread : public QThread
//class RenderViewportThread : public QObject
{
    Q_OBJECT
    public:
        RenderViewportThread(const QSize &size);
        ~RenderViewportThread();
        void setSize(const QSize& size) { m_size=size; };
        QOffscreenSurface *surface;
        QOpenGLContext *context;
        void moveCamera(double x, double y, double z);
        void rotateCamera(int x, int y);
        void zoomCamera(int z);
        void init() { m_viewport->initialize(m_width,m_height); };
        void nodeInit(int uid) { m_viewport->nodeInitialize(uid); };
        void nodesAdded() { m_viewport->nodesAdded(); };
        void showAxis(bool s) { m_viewport->showAxis(s); };
        void showGrid(bool s) { m_viewport->showGrid(s); };
        void setShadingState(feather::gl::glScene::ShadingMode m) { m_viewport->setShadingMode(m); };
        void setSelectionState(feather::gl::glScene::SelectionMode m) { m_viewport->setSelectionMode(m); };
        void updateGL() { emit textureReady(m_displayFbo->texture(), m_size); };

        public slots:
            void renderNext();
        void shutDown();

signals:
        void textureReady(int id, const QSize &size);
        void glFinished();

    private:
        QOpenGLFramebufferObject *m_renderFbo;
        QOpenGLFramebufferObject *m_displayFbo;
        int m_width;
        int m_height;
        Viewport *m_viewport;
        QSize m_size;
        //bool m_update;
        //bool m_textureReady;
};


class TextureNode : public QObject, public QSGSimpleTextureNode 
{
    Q_OBJECT

    public:
        TextureNode(QQuickWindow *window);
        ~TextureNode();

signals:
        void textureInUse();
        void pendingNewTexture();

        public slots:
            void newTexture(int id, const QSize &size); 
        void prepareNode();

    private:
        int m_id;
        QSize m_size;
        QMutex m_mutex;
        QSGTexture *m_texture;
        QQuickWindow *m_window;
};

#endif
