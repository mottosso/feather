// =====================================================================================
// 
//       Filename:  viewportthread.hpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/14/2014 03:51:57 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#ifndef VIEWPORTTHREAD_HPP
#define VIEWPORTTHREAD_HPP

#include "deps.hpp"
#include "viewport.hpp"

class RenderViewportThread;

class ViewportThread : public QQuickItem
{
    Q_OBJECT

    public:
        ViewportThread();

        static QList<QThread *> threads;

        public Q_SLOTS:
            void ready();

    protected:
        QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);

    private:
        RenderViewportThread *m_renderThread;
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
