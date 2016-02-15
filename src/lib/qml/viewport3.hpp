/* **********************************************************************
 *
 * Filename: viewport3.hpp
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
#ifndef VIEWPORT3_HPP
#define VIEWPORT3_HPP

#include "deps.hpp"
#include "qml_deps.hpp"
#include "types.hpp"

class Root : public Qt3D::QEntity
{
    Q_OBJECT

    public:
        Root(Qt3D::QNode* parent=0);
        ~Root();

    protected slots:
        void mouseClicked(Qt3D::Q3DMouseEvent* event);

    private:
        Qt3D::QMouseController* m_pMouseController;
        Qt3D::QMouseInput* m_pMouseInput;
};


// GBUFFER

class GBuffer : public Qt3D::QRenderTarget
{
    public:
        explicit GBuffer(Qt3D::QNode *parent = 0);

        enum Attachments {
            Color = 0,
            Position,
            Normal,
            Depth,
            AttachmentsCount
        };

        Qt3D::QAbstractTextureProvider *colorTexture() const;
        Qt3D::QAbstractTextureProvider *positionTexture() const;
        Qt3D::QAbstractTextureProvider *normalTexture() const;
        Qt3D::QAbstractTextureProvider *depthTexture() const;

    private:
        Qt3D::QAbstractTextureProvider *m_textures[AttachmentsCount];
        Qt3D::QRenderAttachment *m_attachments[AttachmentsCount];
};


// FINAL EFFECT

class FinalEffect : public Qt3D::QEffect
{
    //Q_OBJECT

    public:
        FinalEffect(Qt3D::QNode* parent=0);
        ~FinalEffect();

        QList<Qt3D::QAnnotation*> passCriteria() const;
        inline Qt3D::QTechnique *gl3Technique() const { return m_pGl3Technique; }
        inline Qt3D::QTechnique *gl2Technique() const { return m_pGl2Technique; }

    private:
        Qt3D::QTechnique* m_pGl2Technique;
        Qt3D::QTechnique* m_pGl3Technique;
        Qt3D::QRenderPass* m_pGl2Pass;
        Qt3D::QRenderPass* m_pGl3Pass;
        Qt3D::QAnnotation* m_pPassCriterion; 
};


// SCENE EFFECT

class SceneEffect : public Qt3D::QEffect
{
    //Q_OBJECT

    public:
        SceneEffect(Qt3D::QNode* parent=0);
        ~SceneEffect();

        QList<Qt3D::QAnnotation*> passCriteria() const;

    private:
        Qt3D::QTechnique* m_pGl2Technique;
        Qt3D::QTechnique* m_pGl3Technique;
        Qt3D::QRenderPass* m_pGl2Pass;
        Qt3D::QRenderPass* m_pGl3Pass;
        Qt3D::QAnnotation* m_pPassCriterion; 
};


// DEFERRED RENDERER

class DeferredRenderer : public Qt3D::QViewport
{
    Q_OBJECT

    public:
        DeferredRenderer(Qt3D::QNode* parent=0);
        ~DeferredRenderer();
        void setSceneCamera(Qt3D::QEntity* camera);
        void setGBuffer(Qt3D::QRenderTarget* gBuffer);
        void setGeometryPassCriteria(QList<Qt3D::QAnnotation*> criteria);
        void setFinalPassCriteria(QList<Qt3D::QAnnotation*> criteria);
        void setGBufferLayers(const QStringList &layerNames);
        void setScreenQuadLayers(const QStringList &layerNames);

    private:
        Qt3D::QLayerFilter* m_pSceneFilter;
        Qt3D::QLayerFilter* m_pScreenQuadFilter;
        Qt3D::QClearBuffer* m_pClearScreenQuad;
        Qt3D::QRenderTargetSelector* m_pBufferTargetSelector;
        Qt3D::QClearBuffer* m_pClearGBuffer;
        Qt3D::QRenderPassFilter* m_pGeometryPassFilter;
        Qt3D::QRenderPassFilter* m_pFinalPassFilter;
        Qt3D::QCameraSelector* m_pSceneCameraSelector;
};


// VIEWPORT

class Viewport3 : public Qt3D::QWindow
{
    Q_OBJECT
    
    public:
        Viewport3(Qt3D::QWindow* parent=0);
        ~Viewport3();
    //protected slots:
    //    void mouseClicked(Qt3D::Q3DMouseEvent* event);

    private:
        //Qt3D::QMouseController* m_pMouseController;
        //Qt3D::QMouseInput* m_pMouseInput;
        Qt3D::QInputAspect* m_pInput;
        Qt3D::QFrameGraph* m_pFrameGraph;
        Qt3D::QCamera* m_pCamera;
        //Qt3D::QLayer* m_pSceneLayer;
        //Qt3D::QLayer* m_pQuadLayer;
        //GBuffer* m_pGBuffer;
        DeferredRenderer* m_pDeferredRenderer;
        //FinalEffect* m_pFinalEffect;
        //SceneEffect* m_pSceneEffect;
        Root* m_pRoot;
        
};

#endif
