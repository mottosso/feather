// =====================================================================================
// 
//       Filename:  viewportthread.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/14/2014 03:57:02 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#include "viewportthread.hpp"

QList<QThread *> ViewportThread::threads;


ViewportThread::ViewportThread()
: m_renderThread(0)
{
    setFlag(ItemHasContents, true);
    m_renderThread = new RenderViewportThread(QSize(800, 600));
}

void ViewportThread::ready()
{
    m_renderThread->surface = new QOffscreenSurface();
    m_renderThread->surface->setFormat(m_renderThread->context->format());
    m_renderThread->surface->create();

    m_renderThread->moveToThread(m_renderThread);

    connect(window(), SIGNAL(sceneGraphInvalidated()), m_renderThread, SLOT(shutDown()), Qt::QueuedConnection);

    m_renderThread->start();
    update();
}

QSGNode *ViewportThread::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    TextureNode *node = static_cast<TextureNode *>(oldNode);

    if (!m_renderThread->context) {
        QOpenGLContext *current = window()->openglContext();
        current->doneCurrent();

        m_renderThread->context = new QOpenGLContext();
        m_renderThread->context->setFormat(current->format());
        m_renderThread->context->setShareContext(current);
        m_renderThread->context->create();
        m_renderThread->context->moveToThread(m_renderThread);

        current->makeCurrent(window());

        QMetaObject::invokeMethod(this, "ready");
        return 0;
    }

    if (!node) {
        node = new TextureNode(window());

        connect(m_renderThread, SIGNAL(textureReady(int,QSize)), node, SLOT(newTexture(int,QSize)), Qt::DirectConnection);
        connect(node, SIGNAL(pendingNewTexture()), window(), SLOT(update()), Qt::QueuedConnection);
        connect(window(), SIGNAL(beforeRendering()), node, SLOT(prepareNode()), Qt::DirectConnection);
        connect(node, SIGNAL(textureInUse()), m_renderThread, SLOT(renderNext()), Qt::QueuedConnection);

        QMetaObject::invokeMethod(m_renderThread, "renderNext", Qt::QueuedConnection);
    }

    node->setRect(boundingRect());

    return node;
}


    RenderViewportThread::RenderViewportThread(const QSize &size)
    : surface(0)
    , context(0)
    , m_renderFbo(0)
    , m_displayFbo(0)
    , m_viewport(0)
      , m_size(size)
{
    ViewportThread::threads << this;
}

void RenderViewportThread::renderNext()
{
    context->makeCurrent(surface);

    if (!m_renderFbo) {
        // Initialize the buffers and renderer
        QOpenGLFramebufferObjectFormat format;
        format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        m_renderFbo = new QOpenGLFramebufferObject(m_size, format);
        m_displayFbo = new QOpenGLFramebufferObject(m_size, format);
        m_viewport= new Viewport();
        m_viewport->initialize();
    }

    m_renderFbo->bind();
    glViewport(0, 0, m_size.width(), m_size.height());

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float ar = (float)m_size.height()/(float)m_size.width();
    // glFrustum(left,right,bottom,top,near,far)
    glFrustum(-1.0,1.0,-1.0*ar,1.0*ar,0.01,20.0);
    // glOrtho(left,right,bottom,top,near,far)
    //glOrtho(-1,1,-1*ar,1*ar,0,20);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    std::cout << "renderNext " << ar << " " << m_size.width() << " " << m_size.height() << std::endl;
    m_viewport->render();

    glFlush();

    m_renderFbo->bindDefault();
    qSwap(m_renderFbo, m_displayFbo);

    emit textureReady(m_displayFbo->texture(), m_size);
}

void RenderViewportThread::shutDown()
{
    context->makeCurrent(surface);
    delete m_renderFbo;
    delete m_displayFbo;
    delete m_viewport;
    context->doneCurrent();
    delete context;
    surface->deleteLater();
    exit();
    moveToThread(QGuiApplication::instance()->thread());
}

    TextureNode::TextureNode(QQuickWindow *window)
    : m_id(0)
    , m_size(0, 0)
    , m_texture(0)
      , m_window(window)
{
    m_texture = m_window->createTextureFromId(0, QSize(1, 1));
    setTexture(m_texture);
    setFiltering(QSGTexture::Linear);
}

TextureNode::~TextureNode()
{
    delete m_texture;
}


void TextureNode::newTexture(int id, const QSize &size) {
    m_mutex.lock();
    m_id = id;
    m_size = size;
    m_mutex.unlock();
    emit pendingNewTexture();
}

void TextureNode::prepareNode() {
    m_mutex.lock();
    int newId = m_id;
    QSize size = m_size;
    m_id = 0;
    m_mutex.unlock();
    if (newId) {
        delete m_texture;
        m_texture = m_window->createTextureFromId(newId, size);
        setTexture(m_texture);
        emit textureInUse();
    }
}
