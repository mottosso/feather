/* **********************************************************************
 *
 * Filename: viewport3.cpp
 *
 * Description: Qt3D version of the viewport that uses deferred rendering.
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

#include "viewport3.hpp"


Root::Root(Qt3D::QNode* parent)
    : QEntity(parent)
{

}

Root::~Root()
{

}


DeferredRenderer::DeferredRenderer(Qt3D::QNode* parent)
    : Qt3D::QViewport(parent),
    m_pSceneFilter(new Qt3D::QLayerFilter(this)),
    m_pScreenQuadFilter(new Qt3D::QLayerFilter(this)),
    m_pClearScreenQuad(new Qt3D::QClearBuffer(m_pScreenQuadFilter)),
    m_pBufferTargetSelector(new Qt3D::QRenderTargetSelector(m_pSceneFilter)),
    m_pClearGBuffer(new Qt3D::QClearBuffer(m_pBufferTargetSelector)),
    m_pGeometryPassFilter(new Qt3D::QRenderPassFilter(m_pClearGBuffer)),
    m_pFinalPassFilter(new Qt3D::QRenderPassFilter(m_pClearScreenQuad)),
    m_pSceneCameraSelector(new Qt3D::QCameraSelector(m_pGeometryPassFilter))
{
    m_pClearGBuffer->setBuffers(Qt3D::QClearBuffer::ColorDepthBuffer);
    m_pClearScreenQuad->setBuffers(Qt3D::QClearBuffer::ColorDepthBuffer);
}

DeferredRenderer::~DeferredRenderer()
{

}

void DeferredRenderer::setSceneCamera(Qt3D::QEntity* camera)
{
    m_pSceneCameraSelector->setCamera(camera);
}

void DeferredRenderer::setGBuffer(Qt3D::QRenderTarget* gBuffer)
{
    m_pBufferTargetSelector->setTarget(gBuffer);
}

void DeferredRenderer::setGeometryPassCriteria(QList<Qt3D::QAnnotation*> criteria)
{
    Q_FOREACH (Qt3D::QAnnotation* c, criteria)
        m_pGeometryPassFilter->addInclude(c);
}

void DeferredRenderer::setFinalPassCriteria(QList<Qt3D::QAnnotation*> criteria)
{
    Q_FOREACH (Qt3D::QAnnotation* c, criteria)
        c->setParent(m_pFinalPassFilter);
}

void DeferredRenderer::setGBufferLayers(const QStringList &layerNames)
{
    m_pSceneFilter->setLayers(layerNames);
}

void DeferredRenderer::setScreenQuadLayers(const QStringList &layerNames)
{
    m_pScreenQuadFilter->setLayers(layerNames);
}


Viewport3::Viewport3(Qt3D::QWindow* parent)
    : Qt3D::QWindow(parent),
    m_pFrameGraph(new Qt3D::QFrameGraph()),
    m_pSceneLayer(new Qt3D::QLayer()),
    m_pQuadLayer(new Qt3D::QLayer()),
    m_pDeferredRenderer(new DeferredRenderer()),
    m_pRoot(new Root())
{
    // Sphere
    Qt3D::QEntity* sphere = new Qt3D::QEntity(m_pRoot);
    // mesh
    Qt3D::QSphereMesh* sphereMesh = new Qt3D::QSphereMesh();
    sphereMesh->setRings(50);
    sphereMesh->setSlices(100);
    // material
    Qt3D::QMaterial* sphereMaterial = new Qt3D::QMaterial();
    //sphereMaterial->setEffect(effect);
    sphereMaterial->addParameter(new Qt3D::QParameter(QStringLiteral("meshColor"),QColor(Qt::blue)));


    // Light
    Qt3D::QPointLight* light = new Qt3D::QPointLight();
    light->setColor(Qt::white);
    light->setIntensity(1.5f);


    // build
    sphere->addComponent(sphereMaterial);
    sphere->addComponent(sphereMesh);
    sphere->addComponent(light);



    m_pSceneLayer->setNames(QStringList("scene"));
    m_pQuadLayer->setNames(QStringList("quad"));
    m_pRoot->setObjectName(QStringLiteral("root"));
    
    m_pCamera = defaultCamera();

    m_pCamera->setFieldOfView(45.0f);
    m_pCamera->setNearPlane(0.01f);
    m_pCamera->setFarPlane(1000.0f);
    m_pCamera->setProjectionType(Qt3D::QCameraLens::PerspectiveProjection);

    m_pCamera->setPosition(QVector3D(10.0f, 10.0f, -25.0f));
    m_pCamera->setUpVector(QVector3D(0.0f, 1.0f, 0.0f));
    m_pCamera->setViewCenter(QVector3D(0.0f, 0.0f, 10.0f));

    // Deferred Renderer
    m_pDeferredRenderer->setClearColor(Qt::black);
    m_pDeferredRenderer->setRect(QRectF(0.0f,0.0f,1.0f,1.0f));
    //m_pDeferredRenderer->setFinalPassCriteria(m_pFinalEffect->names());
    //m_pDeferredRenderer->setGeometryPassCriteria(m_pSceneEffect->names());
    m_pFrameGraph->setActiveFrameGraph(m_pDeferredRenderer);
    setFrameGraph(m_pFrameGraph); 

    setRootEntity(m_pRoot);

    show();
}

Viewport3::~Viewport3()
{
    delete m_pFrameGraph;
    m_pFrameGraph=0;    
}


