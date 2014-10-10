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
