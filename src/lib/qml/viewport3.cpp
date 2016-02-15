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
    : QEntity(parent),
    m_pMouseController(new Qt3D::QMouseController(this)),
    m_pMouseInput(new Qt3D::QMouseInput())
{
    m_pMouseInput->setController(m_pMouseController);
 
    addComponent(m_pMouseInput);

    connect(m_pMouseInput,SIGNAL(clicked(Qt3D::Q3DMouseEvent*)),this,SLOT(mouseClicked(Qt3D::Q3DMouseEvent*)));
}

Root::~Root()
{

}

void Root::mouseClicked(Qt3D::Q3DMouseEvent* event)
{
    std::cout << "mouse clicked\n";
}

// GBUFFER
GBuffer::GBuffer(Qt3D::QNode *parent)
    : Qt3D::QRenderTarget(parent)
{
    const Qt3D::QAbstractTextureProvider::TextureFormat formats[AttachmentsCount] = {
        Qt3D::QAbstractTextureProvider::RGBA32F,
        Qt3D::QAbstractTextureProvider::RGB32F,
        Qt3D::QAbstractTextureProvider::RGB16F,
        Qt3D::QAbstractTextureProvider::D32F
    };

    const Qt3D::QRenderAttachment::RenderAttachmentType attachmentTypes[AttachmentsCount] = {
        Qt3D::QRenderAttachment::ColorAttachment0,
        Qt3D::QRenderAttachment::ColorAttachment1,
        Qt3D::QRenderAttachment::ColorAttachment2,
        Qt3D::QRenderAttachment::DepthAttachment
    };

    const QString attachmentNames[AttachmentsCount] = {
        QString::fromLatin1("color"),
        QString::fromLatin1("position"),
        QString::fromLatin1("normal"),
        QString::fromLatin1("depth")
    };

    for (int i = 0; i < AttachmentsCount; i++) {
        Qt3D::QRenderAttachment *attachment = new Qt3D::QRenderAttachment(this);

        m_textures[i] = new Qt3D::QTexture2D();
        m_textures[i]->setFormat(formats[i]);
        m_textures[i]->setWidth(1024);
        m_textures[i]->setHeight(1024);
        m_textures[i]->setGenerateMipMaps(false);
        m_textures[i]->setWrapMode(Qt3D::QTextureWrapMode(Qt3D::QTextureWrapMode::ClampToEdge));
        m_textures[i]->setMinificationFilter(Qt3D::QAbstractTextureProvider::Linear);
        m_textures[i]->setMagnificationFilter(Qt3D::QAbstractTextureProvider::Linear);

        attachment->setTexture(m_textures[i]);
        attachment->setType(attachmentTypes[i]);
        attachment->setName(attachmentNames[i]);

        addAttachment(attachment);
    }
}

Qt3D::QAbstractTextureProvider* GBuffer::colorTexture() const
{
    return m_textures[Color];
}

Qt3D::QAbstractTextureProvider* GBuffer::positionTexture() const
{
    return m_textures[Position];
}

Qt3D::QAbstractTextureProvider* GBuffer::normalTexture() const
{
    return m_textures[Normal];
}

Qt3D::QAbstractTextureProvider* GBuffer::depthTexture() const
{
    return m_textures[Depth];
}


// FINAL EFFECT

FinalEffect::FinalEffect(Qt3D::QNode* parent)
    : Qt3D::QEffect(parent),
    m_pGl2Technique(new Qt3D::QTechnique()),
    m_pGl3Technique(new Qt3D::QTechnique()),
    m_pGl2Pass(new Qt3D::QRenderPass()),
    m_pGl3Pass(new Qt3D::QRenderPass()),
    m_pPassCriterion(new Qt3D::QAnnotation(this))
{
    m_pGl3Technique->openGLFilter()->setProfile(Qt3D::QOpenGLFilter::Core);
    m_pGl3Technique->openGLFilter()->setApi(Qt3D::QOpenGLFilter::Desktop);
    m_pGl3Technique->openGLFilter()->setMajorVersion(3);               
    m_pGl3Technique->openGLFilter()->setMinorVersion(3);
    
    m_pGl2Technique->openGLFilter()->setApi(Qt3D::QOpenGLFilter::Desktop);
    m_pGl2Technique->openGLFilter()->setMajorVersion(2);               
    m_pGl2Technique->openGLFilter()->setMinorVersion(0);
    m_pGl2Technique->openGLFilter()->setProfile(Qt3D::QOpenGLFilter::Core);
    
    m_pPassCriterion->setName(QStringLiteral("pass"));
    m_pPassCriterion->setValue(QStringLiteral("geometry"));
    
    Qt3D::QShaderProgram *gl3Shader = new Qt3D::QShaderProgram();
    QFile* gl3VertFile = new QFile("/usr/local/feather/shaders/vert/final_gl3.vert");
    gl3VertFile->open(QIODevice::ReadOnly);
    gl3Shader->setVertexShaderCode(gl3VertFile->readAll());
    gl3VertFile->flush();
    gl3VertFile->close();
    QFile* gl3FragFile = new QFile("/usr/local/feather/shaders/frag/final_gl3.frag");
    gl3FragFile->open(QIODevice::ReadOnly);
    gl3Shader->setFragmentShaderCode(gl3FragFile->readAll());
    gl3FragFile->flush();
    gl3FragFile->close();
    
    m_pGl3Pass->addAnnotation(m_pPassCriterion);
    m_pGl3Pass->setShaderProgram(gl3Shader);
    m_pGl3Technique->addPass(m_pGl3Pass);

    Qt3D::QShaderProgram *gl2Shader = new Qt3D::QShaderProgram();
    QFile* gl2VertFile = new QFile("/usr/local/feather/shaders/vert/final_gl2.vert");
    gl2VertFile->open(QIODevice::ReadOnly);
    gl2Shader->setVertexShaderCode(gl2VertFile->readAll());
    gl2VertFile->flush();
    gl2VertFile->close();
    QFile* gl2FragFile = new QFile("/usr/local/feather/shaders/frag/final_gl2.frag");
    gl2FragFile->open(QIODevice::ReadOnly);
    gl2Shader->setFragmentShaderCode(gl2FragFile->readAll());
    gl2FragFile->flush();
    gl2FragFile->close();
   
    m_pGl2Pass->addAnnotation(m_pPassCriterion);
    m_pGl2Pass->setShaderProgram(gl2Shader);
    m_pGl2Technique->addPass(m_pGl2Pass);
    
    addTechnique(m_pGl3Technique);
    addTechnique(m_pGl2Technique);                              
}

FinalEffect::~FinalEffect()
{

}

QList<Qt3D::QAnnotation*> FinalEffect::passCriteria() const
{
    return QList<Qt3D::QAnnotation*>() << m_pPassCriterion; 
}



// SCENE EFFECT

SceneEffect::SceneEffect(Qt3D::QNode* parent)
    : Qt3D::QEffect(parent),
    m_pGl2Technique(new Qt3D::QTechnique()),
    m_pGl3Technique(new Qt3D::QTechnique()),
    m_pGl2Pass(new Qt3D::QRenderPass()),
    m_pGl3Pass(new Qt3D::QRenderPass()),
    m_pPassCriterion(new Qt3D::QAnnotation(this))
{
    m_pGl3Technique->openGLFilter()->setProfile(Qt3D::QOpenGLFilter::Core);
    m_pGl3Technique->openGLFilter()->setApi(Qt3D::QOpenGLFilter::Desktop);
    m_pGl3Technique->openGLFilter()->setMajorVersion(3);               
    m_pGl3Technique->openGLFilter()->setMinorVersion(3);
    
    m_pGl2Technique->openGLFilter()->setApi(Qt3D::QOpenGLFilter::Desktop);
    m_pGl2Technique->openGLFilter()->setMajorVersion(2);               
    m_pGl2Technique->openGLFilter()->setMinorVersion(0);
    m_pGl2Technique->openGLFilter()->setProfile(Qt3D::QOpenGLFilter::Core);
                                                                           
    
    m_pPassCriterion->setName(QStringLiteral("pass"));
    m_pPassCriterion->setValue(QStringLiteral("geometry"));
    
    Qt3D::QShaderProgram *gl3Shader = new Qt3D::QShaderProgram();
    QFile* gl3VertFile = new QFile("/usr/local/feather/shaders/vert/geometry_gl3.vert");
    gl3VertFile->open(QIODevice::ReadOnly);
    gl3Shader->setVertexShaderCode(gl3VertFile->readAll());
    gl3VertFile->flush();
    gl3VertFile->close();
    QFile* gl3FragFile = new QFile("/usr/local/feather/shaders/frag/geometry_gl3.frag");
    gl3FragFile->open(QIODevice::ReadOnly);
    gl3Shader->setFragmentShaderCode(gl3FragFile->readAll());
    gl3FragFile->flush();
    gl3FragFile->close();
    
    m_pGl3Pass->addAnnotation(m_pPassCriterion);
    m_pGl3Pass->setShaderProgram(gl3Shader);
    m_pGl3Technique->addPass(m_pGl3Pass);                                    
    Qt3D::QShaderProgram *gl2Shader = new Qt3D::QShaderProgram();
    QFile* gl2VertFile = new QFile("/usr/local/feather/shaders/vert/geometry_gl2.vert");
    gl2VertFile->open(QIODevice::ReadOnly);
    gl2Shader->setVertexShaderCode(gl2VertFile->readAll());
    gl2VertFile->flush();
    gl2VertFile->close();
    QFile* gl2FragFile = new QFile("/usr/local/feather/shaders/frag/geometry_gl2.frag");
    gl2FragFile->open(QIODevice::ReadOnly);
    gl2Shader->setFragmentShaderCode(gl2FragFile->readAll());
    gl2FragFile->flush();
    gl2FragFile->close();
   
    m_pGl2Pass->addAnnotation(m_pPassCriterion);                             
    m_pGl2Pass->setShaderProgram(gl2Shader);
    m_pGl2Technique->addPass(m_pGl2Pass);
    
    addTechnique(m_pGl3Technique);
    addTechnique(m_pGl2Technique);                              
}

SceneEffect::~SceneEffect()
{

}

QList<Qt3D::QAnnotation*> SceneEffect::passCriteria() const
{
    return QList<Qt3D::QAnnotation*>() << m_pPassCriterion; 
}


// DEFERRED RENDERER

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
    //m_pMouseController(new Qt3D::QMouseController()),
    //m_pMouseInput(new Qt3D::QMouseInput()),
    m_pInput(new Qt3D::QInputAspect()),
    m_pFrameGraph(new Qt3D::QFrameGraph()),
    //m_pSceneLayer(new Qt3D::QLayer()),
    //m_pQuadLayer(new Qt3D::QLayer()),
    //m_pGBuffer(new GBuffer()),
    m_pDeferredRenderer(new DeferredRenderer()),
    //m_pFinalEffect(new FinalEffect()),
    //m_pSceneEffect(new SceneEffect()),
    m_pRoot(new Root())
{
    //m_pMouseController->setParent(m_pRoot);
    //m_pMouseInput->setController(m_pMouseController);
    //m_pSceneLayer->setNames(QStringList("scene"));
    //m_pQuadLayer->setNames(QStringList("screenQuad"));
    m_pRoot->setObjectName(QStringLiteral("root"));
 
    m_pCamera = defaultCamera();

    m_pCamera->setFieldOfView(45.0f);
    m_pCamera->setNearPlane(0.01f);
    m_pCamera->setFarPlane(1000.0f);
    m_pCamera->setProjectionType(Qt3D::QCameraLens::PerspectiveProjection);

    m_pCamera->setPosition(QVector3D(10.0f, 10.0f, -25.0f));
    m_pCamera->setUpVector(QVector3D(0.0f, 1.0f, 0.0f));
    m_pCamera->setViewCenter(QVector3D(0.0f, 0.0f, 10.0f));

    m_pInput->setCamera(m_pCamera);

    // Deferred Renderer
    m_pDeferredRenderer->setClearColor(Qt::black);
    m_pDeferredRenderer->setRect(QRectF(0.0f,0.0f,1.0f,1.0f));
    /*
    m_pDeferredRenderer->setFinalPassCriteria(m_pFinalEffect->passCriteria());
    m_pDeferredRenderer->setGeometryPassCriteria(m_pSceneEffect->passCriteria());
    m_pDeferredRenderer->setGBuffer(m_pGBuffer);
    m_pDeferredRenderer->setSceneCamera(m_pCamera);
    m_pDeferredRenderer->setGBufferLayers(m_pSceneLayer->names());
    m_pDeferredRenderer->setScreenQuadLayers(m_pQuadLayer->names());

    m_pFrameGraph->setActiveFrameGraph(m_pDeferredRenderer);
    setFrameGraph(m_pFrameGraph);
    m_pDeferredRenderer->setGBufferLayers(m_pSceneLayer->names());
    m_pDeferredRenderer->setScreenQuadLayers(m_pQuadLayer->names());
    */

    m_pFrameGraph->setActiveFrameGraph(m_pDeferredRenderer);
    setFrameGraph(m_pFrameGraph);
 
    // Sphere
    Qt3D::QEntity* sphere = new Qt3D::QEntity(m_pRoot);
    // mesh
    Qt3D::QSphereMesh* sphereMesh = new Qt3D::QSphereMesh();
    sphereMesh->setRings(50);
    sphereMesh->setSlices(100);
    // material
    Qt3D::QMaterial* sphereMaterial = new Qt3D::QMaterial();
    //sphereMaterial->setEffect(m_pSceneEffect);
    sphereMaterial->addParameter(new Qt3D::QParameter(QStringLiteral("meshColor"),QColor(Qt::blue)));

    // Light
    Qt3D::QPointLight* light = new Qt3D::QPointLight();
    light->setColor(Qt::white);
    light->setIntensity(1.5f);

    // build
    sphere->addComponent(sphereMaterial);
    sphere->addComponent(sphereMesh);
    sphere->addComponent(light);



    /*

    // Screen Quad
    Qt3D::QEntity *screenQuad = new Qt3D::QEntity(m_pRoot);
    Qt3D::QMaterial *screenQuadMaterial = new Qt3D::QMaterial();
    screenQuadMaterial->addParameter(new Qt3D::QParameter(QStringLiteral("position"), m_pGBuffer->positionTexture()));
    screenQuadMaterial->addParameter(new Qt3D::QParameter(QStringLiteral("normal"), m_pGBuffer->normalTexture()));
    screenQuadMaterial->addParameter(new Qt3D::QParameter(QStringLiteral("color"), m_pGBuffer->colorTexture()));
    screenQuadMaterial->addParameter(new Qt3D::QParameter(QStringLiteral("winSize"), QSize(1024, 1024)));
    //PointLightBlock *lightsData = new PointLightBlock(screenQuadMaterial);
    //lightsData->addLight(light);
    //lightsData->addLight(light2);
    //lightsData->addLight(light3);

    //m_pFinalEffect->gl3Technique()->addParameter(new Qt3DRender::QParameter(QStringLiteral("PointLightBlock"), QVariant::fromValue(lightsData)));
    //m_pFinalEffect->gl2Technique()->addParameter(new Qt3DRender::QParameter(QStringLiteral("pointLights"), QVariant::fromValue(lightsData)));
    screenQuadMaterial->setEffect(m_pFinalEffect);

    Qt3D::QTransform *screenPlaneTransform = new Qt3D::QTransform;
    //screenPlaneTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), 90.0f));

    screenQuad->addComponent(m_pQuadLayer);
    screenQuad->addComponent(screenPlaneTransform);
    screenQuad->addComponent(screenQuadMaterial);
    screenQuad->addComponent(sphereMesh);
    */

    setRootEntity(m_pRoot);

    show();
}

Viewport3::~Viewport3()
{
    delete m_pFrameGraph;
    m_pFrameGraph=0;    
}

