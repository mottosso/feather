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

#define UPDATE_COUNT 3 // this is a hack that will update the gl viewport a couple of times or else the viewport will be a few frames behind the gl

QList<QThread *> ViewportThread::threads;


ViewportThread::ViewportThread():
    m_update(true),
    m_ucount(UPDATE_COUNT),
    m_renderThread(new RenderViewportThread(QSize(0,0))),
    m_rx(0),
    m_ry(0)
{
    setFlag(ItemHasContents, true);
    //m_renderThread = new RenderViewportThread(QSize(0, 0));
}

ViewportThread::~ViewportThread()
{
    //m_renderThread->quit();
    //m_renderThread->wait();
    // fixed seq fault
    //delete m_renderThread;
    //m_renderThread=0;
}

void ViewportThread::ready()
{
    //std::cout << "ViewportThread::ready()\n";
    m_renderThread->surface = new QOffscreenSurface();
    m_renderThread->surface->setFormat(m_renderThread->context->format());
    m_renderThread->surface->create();

    m_renderThread->moveToThread(m_renderThread);

    connect(window(), SIGNAL(sceneGraphInvalidated()), m_renderThread, SLOT(shutDown()), Qt::QueuedConnection);
    //connect(this, SIGNAL(updateGLWindow()), this, SLOT(updateWindow()), Qt::DirectConnection);
    m_renderThread->start();
    update();
}

void ViewportThread::setGlToUpdate()
{
    //std::cout << "ViewportThread::setGlToUpdate\n";
    m_update=true;
    m_ucount=UPDATE_COUNT;
}

void ViewportThread::updateWindow()
{
    //std::cout << "ViewportThread::updateWindow\n";
    if(m_update || m_ucount > 0){
        //window()->beforeRendering();
        window()->update();
        //update();
        m_ucount--;
        m_update=false;
    }

    //window()->blockSignals(true);
    //m_renderThread->eventDispatcher()->processEvents(QEventLoop::AllEvents);
   // processEvents();
    //std::cout << "past blocking\n";
    //window()->update();
    //qApp->processEvents();
}

QSGNode *ViewportThread::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    //std::cout << "ViewportThread::updatePaintNode\n";

    TextureNode *node = static_cast<TextureNode *>(oldNode);

    if (!m_renderThread->context) {
        //std::cout << "ViewportThread::updatePaintNode - create context\n";
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
        //std::cout << "ViewportThread::updatePaintNode - create texture node\n";
        node = new TextureNode(window());
 
        connect(m_renderThread, SIGNAL(textureReady(int,QSize)), node, SLOT(newTexture(int,QSize)), Qt::QueuedConnection);
        connect(m_renderThread, SIGNAL(glFinished()), this, SLOT(setGlToUpdate()), Qt::QueuedConnection);
        connect(m_renderThread, SIGNAL(glFinished()), this, SLOT(updateWindow()), Qt::QueuedConnection);
        connect(node, SIGNAL(pendingNewTexture()), this, SLOT(updateWindow()), Qt::DirectConnection);
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

    //window()->beforeRendering();

    return node;
}


void ViewportThread::mousePressed(int x, int y)
{
    m_rx=x;
    m_ry=y;
}

void ViewportThread::moveCamera(double x, double y, double z)
{
    //emit window()->beforeRendering();
    //std::cout << "ViewportThread::moveCamera()\n";
    m_renderThread->moveCamera(x,y,z);
    //emit window()->beforeRendering();
    //update();
    //emit updateGLWindow();
}

void ViewportThread::rotateCamera(int x, int y)
{
    //std::cout << "ViewportThread::rotateCamera()\n";
    m_renderThread->rotateCamera(x-m_rx, y-m_ry);
    m_rx=x;
    m_ry=y;
    //update();
    //emit updateGLWindow();
}

void ViewportThread::zoomCamera(int z)
{
    //std::cout << "ViewportThread::zoomCamera()\n";
    m_renderThread->zoomCamera(z);
    //update();
    //emit updateGLWindow();
}

void ViewportThread::initialize()
{
    //std::cout << "ViewportThread::initialize()\n";
    m_renderThread->init();
}

void ViewportThread::nodeInitialize(int uid)
{
    //std::cout << "ViewportThread::nodeInitialize()\n";
     m_renderThread->nodeInit(uid);
}

void ViewportThread::updateGL()
{
    //qApp->processEvents();
     //emit window()->beforeRendering();
     //qApp->processEvents();
     //std::cout << "ViewportThread::updateGL()\n";
    //emit window()->afterRendering();
    //update();
    //emit window()->beforeRendering();
    //qApp->processEvents();
    setGlToUpdate();
    updateWindow();
}

// axis
void ViewportThread::setAxis(bool& s) {
    //std::cout << "ViewportThread::setAxis()\n";
     if(m_axis!= s) {
        m_axis=s;
        m_renderThread->showAxis(s);                
        emit axisChanged();
    }
}

// grid
void ViewportThread::setGrid(bool& s) {
    //std::cout << "ViewportThread::setGrid()\n";
     if(m_grid!= s) {
        m_grid=s;
        m_renderThread->showGrid(s);
        emit gridChanged();
    }
}

// shadingMode
void ViewportThread::setShadingMode(ShadingMode& m) {
    //std::cout << "ViewportThread::setShadingMode()\n";
     if(m_shadingMode!= m) {
        m_shadingMode=m;
        m_renderThread->setShadingState(static_cast<feather::gl::glScene::ShadingMode>(m));
        emit shadingModeChanged(m);
    }
}

// selectionMode 
void ViewportThread::setSelectionMode(SelectionMode& m) {
    //std::cout << "ViewportThread::setSelectionMode()\n";
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
    //std::cout << "RenderViewportThread::RenderViewportThread()\n";
     //ViewportThread::threads << this;
    //updateLoop();
}

RenderViewportThread::~RenderViewportThread()
{
    //std::cout << "RenderViewportThread::~RenderViewportThread()\n";
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
     //std::cout << "RenderViewportThread::moveCamera()\n";
     //emit textureReady(m_displayFbo->texture(), m_size);
    m_viewport->moveCamera(x,y,z);
    //renderNext();
    //m_update=true;
    //emit textureReady(m_displayFbo->texture(), m_size);
    emit glFinished();
}

void RenderViewportThread::rotateCamera(int x, int y)
{
    //std::cout << "RenderViewportThread::rotateCamera()\n";
     //emit textureReady(m_displayFbo->texture(), m_size);
    m_viewport->rotateCamera(x,y);
    //m_update=true;
    //emit textureReady(m_displayFbo->texture(), m_size);
    emit glFinished();
}

void RenderViewportThread::zoomCamera(int z)
{
    //std::cout << "RenderViewportThread::zoomCamera()\n";
     //emit textureReady(m_displayFbo->texture(), m_size);
    m_viewport->zoomCamera(z);
    //m_update=true;
    //emit textureReady(m_displayFbo->texture(), m_size);
    emit glFinished();
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
    //std::cout << "RenderViewportThread::renderNext()\n";
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
        //std::cout << "delete renderFbo\n";
         delete m_renderFbo;
        QOpenGLFramebufferObjectFormat format;
        format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        m_renderFbo = new QOpenGLFramebufferObject(QSize(m_size.width(),m_size.height()), format);
    }

    m_renderFbo->bind();
    context->functions()->glViewport(0, 0, m_renderFbo->width(), m_renderFbo->height());
    m_viewport->render(m_renderFbo->width(),m_renderFbo->height());
    context->functions()->glFlush();

    m_width = m_size.width();
    m_height = m_size.height();
 
    //glFinish();

    /*
    glViewport(0, 0, m_renderFbo->width(), m_renderFbo->height());
    m_viewport->render(m_renderFbo->width(),m_renderFbo->height());
    */

    if(m_renderFbo->width() != m_displayFbo->width() || m_renderFbo->height() != m_displayFbo->height()) {
    //if(m_size.width() != m_width || m_size.height() != m_height) {
        //std::cout << "delete displayFbo\n";
        delete m_displayFbo;
        QOpenGLFramebufferObjectFormat format;
        format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        m_displayFbo = new QOpenGLFramebufferObject(QSize(m_renderFbo->width(),m_renderFbo->height()), format);
    }

    m_renderFbo->bindDefault();

    qSwap(m_renderFbo, m_displayFbo);

    emit textureReady(m_displayFbo->texture(), m_size);


    //qSwap(m_displayFbo, m_renderFbo);


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
    //emit textureReady(m_displayFbo->texture(), m_size);
    //m_update=false;
    //m_textureReady=true;
    /*
    }
    emit textureReady(m_displayFbo->texture(), m_size);
    */
 
   //updateLoop();
}

void RenderViewportThread::shutDown()
{
    // TODO - why is this not being called?
    context->makeCurrent(surface);
    delete m_renderFbo;
    delete m_displayFbo;
    delete m_viewport;
    context->doneCurrent();
    delete context;

    // schedule this to be deleted only after we're done cleaning up
    surface->deleteLater();

    // Stop event processing, move the thread to GUI and make sure it is deleted.
    exit();
    moveToThread(QGuiApplication::instance()->thread());
    //std::cout << "RenderViewportThread::shutDown()\n";
    // this never gets called
}

TextureNode::TextureNode(QQuickWindow *window) :
    m_id(0),
    m_size(0, 0),
    m_texture(0),
    m_window(window)
{
    //std::cout << "TextureNode::TextureNode()\n";
     m_texture = m_window->createTextureFromId(0, QSize(1, 1));
    setTexture(m_texture);
    setFiltering(QSGTexture::Linear);
}

TextureNode::~TextureNode()
{
    //std::cout << "TextureNode::~TextureNode()\n";
     delete m_texture;
    m_texture=0;
}


void TextureNode::newTexture(int id, const QSize &size)
{
    //std::cout << "TextureNode::newTexture()\n";
     m_mutex.lock();
    m_id = id;
    m_size = size;
    m_mutex.unlock();
    emit pendingNewTexture();
}

void TextureNode::prepareNode()
{
    //std::cout << "TextureNode::prepareNode()\n";
     m_mutex.lock();
    int newId = m_id;
    QSize size = m_size;
    m_id = 0;
    m_mutex.unlock();
    //std::cout << "newId=" << newId << std::endl;
    if (newId) {
        //std::cout << "TextureNode::prepareNode() - create new texture from id\n";
         delete m_texture;
        m_texture = m_window->createTextureFromId(newId, size);
        setTexture(m_texture);
        emit textureInUse();
    } 
    //emit textureInUse();
}
