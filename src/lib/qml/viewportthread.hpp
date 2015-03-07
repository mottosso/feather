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

class RenderViewportThread;

class ViewportThread : public QQuickItem
{
    Q_OBJECT

    public:
        ViewportThread();
        ~ViewportThread();

        static QList<QThread *> threads;
       Q_INVOKABLE void mousePressed(int x, int y);
       Q_INVOKABLE void moveCamera(int x, int y);
       Q_INVOKABLE void zoomCamera(int z);

        public Q_SLOTS:
            void ready();


    protected:
        QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);
        //void mousePressEvent(QMouseEvent* event);

    private:
        RenderViewportThread *m_renderThread;
        int m_x;
        int m_y;
};


/*
 * The render thread shares a context with the scene graph and will
 * render into two separate FBOs, one to use for display and one
 * to use for rendering
 */
class RenderViewportThread : public QThread
{
    Q_OBJECT
    public:
        RenderViewportThread(const QSize &size);
        void setSize(const QSize& size) { m_size=size; };
        QOffscreenSurface *surface;
        QOpenGLContext *context;
        void moveCamera(int x, int y);
        void zoomCamera(int z);

        public slots:
            void renderNext();
        void shutDown();

signals:
        void textureReady(int id, const QSize &size);

    private:
        QOpenGLFramebufferObject *m_renderFbo;
        QOpenGLFramebufferObject *m_displayFbo;
        int m_width;
        int m_height;
        Viewport *m_viewport;
        QSize m_size;
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
