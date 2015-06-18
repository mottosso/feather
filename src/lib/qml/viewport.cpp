/***********************************************************************
 *
 * Filename: viewport.cpp
 *
 * Description: Holds the scenegraph.
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

#include "viewport.hpp"

// MAIN VIEWPORT

Viewport::Viewport()
: m_pRender(0), m_x(0), m_y(0)
{
    //setFlag(ItemHasContents, true);
    //m_pRender = new RenderViewport(QSize(0, 0));
    connect(this, SIGNAL(windowChanged(QQuickWindow*)), this, SLOT(handleWindowChanged(QQuickWindow*)));    
}

Viewport::~Viewport()
{
    //m_pRender->quit();
}

/*
void Viewport::ready()
{
    m_pRender->surface = new QOffscreenSurface();
    m_pRender->surface->setFormat(m_pRender->context->format());
    m_pRender->surface->create();

    m_pRender->moveToThread(m_pRender);

    connect(window(), SIGNAL(sceneGraphInvalidated()), m_pRender, SLOT(shutDown()), Qt::QueuedConnection);

    m_pRender->start();
    update();
}
*/

/*
QSGNode *Viewport::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    TextureNode *node = static_cast<TextureNode *>(oldNode);

    if (!m_pRender->context) {
        QOpenGLContext *current = window()->openglContext();
        current->doneCurrent();

        m_pRender->context = new QOpenGLContext();
        m_pRender->context->setFormat(current->format());
        m_pRender->context->setShareContext(current);
        m_pRender->context->create();
        m_pRender->context->moveToThread(m_pRender);

        current->makeCurrent(window());

        QMetaObject::invokeMethod(this, "ready");
        return 0;
    }

    if (!node) {
        node = new TextureNode(window());

        connect(m_pRender, SIGNAL(textureReady(int,QSize)), node, SLOT(newTexture(int,QSize)), Qt::DirectConnection);
        connect(node, SIGNAL(pendingNewTexture()), window(), SLOT(update()), Qt::QueuedConnection);
        connect(window(), SIGNAL(beforeRendering()), node, SLOT(prepareNode()), Qt::DirectConnection);
        connect(node, SIGNAL(textureInUse()), m_pRender, SLOT(renderNext()), Qt::QueuedConnection);

        QMetaObject::invokeMethod(m_pRender, "renderNext", Qt::QueuedConnection);
    }

    node->setRect(boundingRect());

    //std::cout << "thread x=" << node->rect().width() << ", y= " << node->rect().height() << std::endl;

    m_pRender->setSize(QSize(node->rect().width(), node->rect().height()));

    return node;
}
*/

void Viewport::mousePressed(int x, int y)
{
    m_x=x;
    m_y=y;
}

void Viewport::moveCamera(int x, int y)
{
    m_pRender->rotateCamera(x-m_x, y-m_y);
    m_x=x;
    m_y=y;
}

void Viewport::zoomCamera(int z)
{
    m_pRender->zoomCamera(z);
}

void Viewport::handleWindowChanged(QQuickWindow *win)
{
    if(win) {
        connect(win, SIGNAL(beforeSynchronizing()), this, SLOT(sync()), Qt::DirectConnection);
        connect(win, SIGNAL(sceneGraphInvalidated()), this, SLOT(cleanup()), Qt::DirectConnection);
        win->setClearBeforeRendering(false);
    }
}

void Viewport::sync()
{
    if(!m_pRender) {
        m_pRender = new ViewportRender();
        m_pRender->setViewportSize(window()->size() * window()->devicePixelRatio());
        m_pRender->initialize();
        connect(window(), SIGNAL(beforeRendering()), m_pRender, SLOT(paint()), Qt::DirectConnection);
    } else {
        m_pRender->setViewportSize(window()->size() * window()->devicePixelRatio());
    }
    window()->update();
}

void Viewport::cleanup()
{
    delete m_pRender;
}


// VIEWPORT RENDERER

ViewportRender::ViewportRender()
{
    m_pScene = new feather::gl::glScene();
    m_CurrentCamera = 0;
}

ViewportRender::~ViewportRender()
{
    delete m_pScene;
}

void ViewportRender::initialize()
{
    initializeOpenGLFunctions();
    m_pScene->init();
}

void ViewportRender::render(int width, int height)
{
    m_pScene->draw(width,height);
}

void ViewportRender::rotateCamera(int x, int y)
{
    m_pScene->camera(m_CurrentCamera)->rotate(x,y);
}

void ViewportRender::zoomCamera(int z)
{
    m_pScene->camera(m_CurrentCamera)->zoom(z);
}

void ViewportRender::paint()
{
    render(m_viewportSize.width(),m_viewportSize.height());
}
