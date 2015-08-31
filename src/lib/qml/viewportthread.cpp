/***********************************************************************
 *
 * Filename: viewportthread.cpp
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

#include "viewportthread.hpp"

QList<QThread *> ViewportThread::threads;


ViewportThread::ViewportThread()
: m_renderThread(new RenderViewportThread(QSize(0, 0))), m_rx(0), m_ry(0)
{
    setFlag(ItemHasContents, true);
    //m_renderThread = new RenderViewportThread(QSize(0, 0));
}

ViewportThread::~ViewportThread()
{
    m_renderThread->quit();
    m_renderThread->wait();
    // fixed seq fault
    //delete m_renderThread;
    //m_renderThread=0;
}

void ViewportThread::ready()
{
    m_renderThread->surface = new QOffscreenSurface();
    m_renderThread->surface->setFormat(m_renderThread->context->format());
    m_renderThread->surface->create();

    m_renderThread->moveToThread(m_renderThread);

    connect(window(), SIGNAL(sceneGraphInvalidated()), m_renderThread, SLOT(shutDown()), Qt::DirectConnection);
    //connect(this, SIGNAL(updateGLWindow()), this, SLOT(updateWindow()), Qt::DirectConnection);
    m_renderThread->start();
    update();
}

void ViewportThread::updateWindow()
{
    //update();
    std::cout << "updating window\n";
    //window()->blockSignals(true);
    m_renderThread->eventDispatcher()->processEvents(QEventLoop::AllEvents);
    //processEvents();
    std::cout << "past blocking\n";
    //window()->update();
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
 
        connect(m_renderThread, SIGNAL(textureReady(int,QSize)), node, SLOT(newTexture(int,QSize)), Qt::QueuedConnection);
        connect(m_renderThread, SIGNAL(glFinished()), this, SLOT(updateWindow()), Qt::QueuedConnection);
        //connect(node, SIGNAL(pendingNewTexture()), window(), SLOT(update()), Qt::DirectConnection);
        connect(window(), SIGNAL(beforeRendering()), node, SLOT(prepareNode()), Qt::DirectConnection);
        connect(node, SIGNAL(textureInUse()), m_renderThread, SLOT(renderNext()), Qt::QueuedConnection);

        QMetaObject::invokeMethod(m_renderThread, "renderNext", Qt::QueuedConnection);
 
        /*
        connect(m_renderThread, SIGNAL(textureReady(int,QSize)), node, SLOT(newTexture(int,QSize)), Qt::DirectConnection);
        //connect(node, SIGNAL(pendingNewTexture()), window(), SLOT(update()), Qt::QueuedConnection);
        connect(window(), SIGNAL(beforeRendering()), node, SLOT(prepareNode()), Qt::DirectConnection);
        connect(node, SIGNAL(textureInUse()), m_renderThread, SLOT(renderNext()), Qt::DirectConnection);

        QMetaObject::invokeMethod(m_renderThread, "renderNext", Qt::DirectConnection);
        */

        /*
        connect(m_renderThread, SIGNAL(textureReady(int,QSize)), node, SLOT(newTexture(int,QSize)), Qt::QueuedConnection);
        //connect(node, SIGNAL(pendingNewTexture()), window(), SLOT(update()), Qt::QueuedConnection);
        connect(window(), SIGNAL(beforeRendering()), node, SLOT(prepareNode()), Qt::QueuedConnection);
        connect(node, SIGNAL(textureInUse()), m_renderThread, SLOT(renderNext()), Qt::QueuedConnection);

        QMetaObject::invokeMethod(m_renderThread, "renderNext", Qt::QueuedConnection);
        */
    }

    node->setRect(boundingRect());

    //std::cout << "thread x=" << node->rect().width() << ", y= " << node->rect().height() << std::endl;

    m_renderThread->setSize(QSize(node->rect().width(), node->rect().height()));
    //std::cout << "renderThread->setSize w=" << node->rect().width() << " h=" << node->rect().height() << std::endl;

    return node;
}


void ViewportThread::mousePressed(int x, int y)
{
    m_rx=x;
    m_ry=y;
}

void ViewportThread::moveCamera(double x, double y, double z)
{
    m_renderThread->moveCamera(x,y,z);
    update();
    //emit updateGLWindow();
}

void ViewportThread::rotateCamera(int x, int y)
{
    m_renderThread->rotateCamera(x-m_rx, y-m_ry);
    m_rx=x;
    m_ry=y;
    update();
    //emit updateGLWindow();
}

void ViewportThread::zoomCamera(int z)
{
    m_renderThread->zoomCamera(z);
    update();
    //emit updateGLWindow();
}

void ViewportThread::initialize()
{
    m_renderThread->init();
}

void ViewportThread::nodeInitialize(int uid)
{
    m_renderThread->nodeInit(uid);
}

void ViewportThread::updateGL()
{
    update();
}

// axis
void ViewportThread::setAxis(bool& s) {
    if(m_axis!= s) {
        m_axis=s;
        m_renderThread->showAxis(s);                
        emit axisChanged();
    }
}

// grid
void ViewportThread::setGrid(bool& s) {
    if(m_grid!= s) {
        m_grid=s;
        m_renderThread->showGrid(s);
        emit gridChanged();
    }
}

// shadingMode
void ViewportThread::setShadingMode(ShadingMode& m) {
    if(m_shadingMode!= m) {
        m_shadingMode=m;
        m_renderThread->setShadingState(static_cast<feather::gl::glScene::ShadingMode>(m));
        emit shadingModeChanged(m);
    }
}

// selectionMode 
void ViewportThread::setSelectionMode(SelectionMode& m) {
    if(m_selectionMode!= m) {
        m_selectionMode=m;
        m_renderThread->setSelectionState(static_cast<feather::gl::glScene::SelectionMode>(m));
        emit selectionModeChanged(m);
    }
}



RenderViewportThread::RenderViewportThread(const QSize &size):
    surface(0),
    context(0),
    m_renderFbo(0),
    m_displayFbo(0),
    m_viewport(0),
    m_size(size)
    //m_update(false),
    //m_textureReady(false)
{
    ViewportThread::threads << this;
    //updateLoop();
}

RenderViewportThread::~RenderViewportThread()
{
    //context->makeCurrent(surface);
    delete m_renderFbo;
    m_renderFbo=0;
    delete m_displayFbo;
    m_displayFbo=0;
    delete m_viewport;
    m_viewport=0;
    //context->doneCurrent();
    //delete context;
    surface->deleteLater();
    //exit();
    //moveToThread(QGuiApplication::instance()->thread());
    delete surface;
    surface=0;
    delete context;
    context=0;
}

void RenderViewportThread::moveCamera(double x, double y, double z)
{
    //emit textureReady(m_displayFbo->texture(), m_size);
    m_viewport->moveCamera(x,y,z);
    //m_update=true;
    //emit textureReady(m_displayFbo->texture(), m_size);
}

void RenderViewportThread::rotateCamera(int x, int y)
{
    //emit textureReady(m_displayFbo->texture(), m_size);
    m_viewport->rotateCamera(x,y);
    //m_update=true;
    //emit textureReady(m_displayFbo->texture(), m_size);
}

void RenderViewportThread::zoomCamera(int z)
{
    //emit textureReady(m_displayFbo->texture(), m_size);
    m_viewport->zoomCamera(z);
    //m_update=true;
    //emit textureReady(m_displayFbo->texture(), m_size);
}

/*
void RenderViewportThread::updateLoop()
{
    if(m_update && m_textureReady){
        //emit textureReady(m_displayFbo->texture(), m_size);
        m_update=false;
    }
    updateLoop();
}
*/

void RenderViewportThread::renderNext()
{
    std::cout << "renderNext\n";
    /*
    if(m_update){
    */

    /*
    std::cout << "start update rendering\n";

    if(!m_update){
        emit textureReady(m_displayFbo->texture(), m_size);
        return;
    }
    
    std::cout << "updating rendering\n";
    */

    context->makeCurrent(surface);
    
    if (!m_renderFbo || !m_displayFbo) {
        // Initialize the buffers and renderer
        QOpenGLFramebufferObjectFormat format;
        format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        m_renderFbo = new QOpenGLFramebufferObject(m_size, format);
        m_displayFbo = new QOpenGLFramebufferObject(m_size, format);
        m_viewport= new Viewport();
        //m_viewport->setContext(context);
        m_viewport->initialize(m_size.width(), m_size.height());
        //m_width = m_size.width();
        //m_height = m_size.height();
    }

    if(m_size.width() != m_width || m_size.height() != m_height) {
        std::cout << "delete renderFbo\n";
         delete m_renderFbo;
        QOpenGLFramebufferObjectFormat format;
        format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        m_renderFbo = new QOpenGLFramebufferObject(QSize(m_size.width(),m_size.height()), format);
    }

    m_renderFbo->bind();

    m_width = m_size.width();
    m_height = m_size.height();
 
    glViewport(0, 0, m_size.width(), m_size.height());
    m_viewport->render(m_size.width(),m_size.height());

    /*
    glViewport(0, 0, m_renderFbo->width(), m_renderFbo->height());
    m_viewport->render(m_renderFbo->width(),m_renderFbo->height());
    */

    if(m_renderFbo->width() != m_displayFbo->width() || m_renderFbo->height() != m_displayFbo->height()) {
    //if(m_size.width() != m_width || m_size.height() != m_height) {
        std::cout << "delete displayFbo\n";
        delete m_displayFbo;
        QOpenGLFramebufferObjectFormat format;
        format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        m_displayFbo = new QOpenGLFramebufferObject(QSize(m_renderFbo->width(),m_renderFbo->height()), format);
    }

    glFlush();
    m_renderFbo->bindDefault();
    qSwap(m_renderFbo, m_displayFbo);

    /*
    if(m_size.width() != m_width || m_size.height() != m_height) {
        delete m_renderFbo;
        QOpenGLFramebufferObjectFormat format;
        format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        m_renderFbo = new QOpenGLFramebufferObject(m_size, format);
    }
    */

    //glFlush();
 
    /*
    if(m_size.width() != m_width || m_size.height() != m_height) {
        delete m_renderFbo;
        delete m_displayFbo;
        QOpenGLFramebufferObjectFormat format;
        format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        //m_renderFbo = new QOpenGLFramebufferObject(m_size, format);
        m_renderFbo = new QOpenGLFramebufferObject(QSize(m_width,m_height), format);
        m_displayFbo = new QOpenGLFramebufferObject(m_size, format);
        m_renderFbo->bind();

        glViewport(0, 0, m_size.width(), m_size.height());
        m_viewport->render(m_size.width(),m_size.height());
        glFlush();
        qSwap(m_renderFbo, m_displayFbo);
        //glViewport(0, 0, m_size.width(), m_size.height());
        //m_viewport->render(m_size.width(),m_size.height());
    } else {
        m_renderFbo->bind();
        //glViewport(0, 0, m_size.width(), m_size.height());
        //m_viewport->render(m_size.width(),m_size.height());
        glViewport(0, 0, m_size.width(), m_size.height());
        m_viewport->render(m_size.width(),m_size.height());
        glFlush();
        qSwap(m_renderFbo, m_displayFbo);
     }
    */

    // START
    /*
    int width = m_size.width();
    int height = m_size.height();
    QSize size(width,height);

    //if(m_size.width() != m_width || m_size.height() != m_height) {
    if(width != m_width || height != m_height) {
        delete m_renderFbo;
        QOpenGLFramebufferObjectFormat format;
        format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        //m_renderFbo = new QOpenGLFramebufferObject(m_size, format);
        m_renderFbo = new QOpenGLFramebufferObject(size, format);
    }

    m_renderFbo->bind();

    //int side = qMin(m_size.width(),m_size.height());
    std::cout << "m_size w=" << m_size.width() << " h=" << m_size.height() << std::endl;
    std::cout << "m_width=" << m_width << " m_height=" << m_height << std::endl;

    glViewport(0, 0, m_size.width(), m_size.height());

    m_viewport->render(m_size.width(),m_size.height());

    glFlush();

    qSwap(m_renderFbo, m_displayFbo);
 
    //m_renderFbo->bindDefault();
    
    //if(m_size.width() != m_width || m_size.height() != m_height) {
    if(width != m_width || height != m_height) {
        delete m_displayFbo;
        QOpenGLFramebufferObjectFormat format;
        format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        //m_displayFbo = new QOpenGLFramebufferObject(m_size, format);
        m_displayFbo = new QOpenGLFramebufferObject(size, format);
    }
    */
    // END

    //std::cout << "m_renderFbo w=" << m_renderFbo->width() << " m_renderFbo h=" << m_renderFbo->height() << std::endl;
    //std::cout << "m_displayFbo w=" << m_displayFbo->width() << " m_displayFbo h=" << m_displayFbo->height() << std::endl;

    /*
    glViewport(0, 0, m_size.width(), m_size.height());

    m_viewport->render(m_size.width(),m_size.height());
    */

    //glFlush();
    //qSwap(m_renderFbo, m_displayFbo);

    m_width = m_size.width();
    m_height = m_size.height();

    
    //std::cout << "w=" << m_size.width() << " h=" << m_size.height() << std::endl;
    emit textureReady(m_displayFbo->texture(), m_size);
    //m_update=false;
    //m_textureReady=true;
    /*
    }
    emit textureReady(m_displayFbo->texture(), m_size);
    */

    emit glFinished();
   //updateLoop();
}

void RenderViewportThread::shutDown()
{
    // this never gets called
}

TextureNode::TextureNode(QQuickWindow *window) :
    m_id(0),
    m_size(0, 0),
    m_texture(0),
    m_window(window)
{
    m_texture = m_window->createTextureFromId(0, QSize(1, 1));
    setTexture(m_texture);
    setFiltering(QSGTexture::Linear);
}

TextureNode::~TextureNode()
{
    delete m_texture;
    m_texture=0;
}


void TextureNode::newTexture(int id, const QSize &size)
{
    m_mutex.lock();
    m_id = id;
    m_size = size;
    m_mutex.unlock();
    emit pendingNewTexture();
}

void TextureNode::prepareNode()
{
    m_mutex.lock();
    int newId = m_id;
    QSize size = m_size;
    m_id = 0;
    m_mutex.unlock();
    std::cout << "newId=" << newId << std::endl;
    if (newId) {
        delete m_texture;
        m_texture = m_window->createTextureFromId(newId, size);
        setTexture(m_texture);
        //emit textureInUse();
    }
    emit textureInUse();
}
