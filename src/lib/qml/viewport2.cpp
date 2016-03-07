/***********************************************************************
 *
 * Filename: viewport2.cpp
 *
 * Description: Qt3D version of the viewport that displays the scenegraph.
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

#include "viewport2.hpp"
#include "commands.hpp"
#include "state.hpp"
#include "draw.hpp"

// MAIN VIEWPORT

DrawItem::DrawItem(feather::draw::Item* _item, Type _type, QNode *parent)
    : QEntity(parent),
    m_item(_item),
    m_type(_type)
{
}

DrawItem::~DrawItem()
{
    QNode::cleanup();
}


// PERSPECTIVE CAMERA 
PerspCamera::PerspCamera(feather::draw::Item* _item, QNode *parent)
    : DrawItem(_item,DrawItem::PerspCamera,parent)
{

}

PerspCamera::~PerspCamera()
{
    QNode::cleanup();
}

void PerspCamera::updateItem()
{

}

// CAN NOT GET SHADERS TO WORK IN QT3D
// YET BUT I'M LEAVING THIS HERE FOR
// WHEN I CAN
/*
WireEffect::WireEffect(QNode* parent)
    : QEffect(parent),
    m_pPassCriterion(new Qt3D::QAnnotation()),
    m_pRenderPass(new Qt3D::QRenderPass()),
    m_pTechnique(new Qt3D::QTechnique())
{
    addParameter(new Qt3D::QParameter("ambient",QVector3D(0.1,0.1,0.1)));
    addParameter(new Qt3D::QParameter("diffuse",QVector3D(0.7,0.7,0.7)));
    addParameter(new Qt3D::QParameter("specular",QVector3D(0.95,0.95,0.95)));
    addParameter(new Qt3D::QParameter("shininess",150.0));
 

    m_pTechnique->openGLFilter()->setProfile(Qt3D::QOpenGLFilter::Core);
    m_pTechnique->openGLFilter()->setApi(Qt3D::QOpenGLFilter::Desktop);
    m_pTechnique->openGLFilter()->setMajorVersion(3);               
    m_pTechnique->openGLFilter()->setMinorVersion(1);

    m_pTechnique->addParameter(new Qt3D::QParameter("light.position",QVector4D(0,0,0,1)));
    m_pTechnique->addParameter(new Qt3D::QParameter("light.intensity",QVector3D(1,1,1)));
    m_pTechnique->addParameter(new Qt3D::QParameter("line.width",1.0));
    m_pTechnique->addParameter(new Qt3D::QParameter("line.color",QVector4D(1,1,1,1)));

    m_pRenderPass->addBinding(new Qt3D::QParameterMapping("ambient","ka",Qt3D::QParameterMapping::Uniform)); 
    m_pRenderPass->addBinding(new Qt3D::QParameterMapping("diffuse","kd",Qt3D::QParameterMapping::Uniform)); 
    m_pRenderPass->addBinding(new Qt3D::QParameterMapping("specular","ks",Qt3D::QParameterMapping::Uniform)); 
 
    m_pPassCriterion->setName(QStringLiteral("renderingStyle"));
    m_pPassCriterion->setValue(QStringLiteral("forward"));
     
    Qt3D::QShaderProgram *gl3Shader = new Qt3D::QShaderProgram();
    // Vert Shader
    QFile* gl3VertFile = new QFile("/usr/local/feather/shaders/vert/robustwireframe.vert");
    gl3VertFile->open(QIODevice::ReadOnly);
    gl3Shader->setVertexShaderCode(gl3VertFile->readAll());
    gl3VertFile->flush();
    gl3VertFile->close();
    // Frag Shader
    QFile* gl3FragFile = new QFile("/usr/local/feather/shaders/frag/robustwireframe.frag");
    gl3FragFile->open(QIODevice::ReadOnly);
    gl3Shader->setFragmentShaderCode(gl3FragFile->readAll());
    gl3FragFile->flush();
    gl3FragFile->close();
    // Geom Shader
    QFile* gl3GeomFile = new QFile("/usr/local/feather/shaders/geom/robustwireframe.geom");
    gl3GeomFile->open(QIODevice::ReadOnly);
    gl3Shader->setGeometryShaderCode(gl3GeomFile->readAll());
    gl3GeomFile->flush();
    gl3GeomFile->close();
    
    m_pRenderPass->addAnnotation(m_pPassCriterion);
    m_pRenderPass->setShaderProgram(gl3Shader);
    m_pTechnique->addPass(m_pRenderPass);

    addTechnique(m_pTechnique);

}

WireEffect::~WireEffect()
{

}
*/

 
MeshGeometry::MeshGeometry(int _uid, int _nid, int _fid, QNode *parent)
    : Qt3D::QGeometry(parent),
    m_pVAttribute(new Qt3D::QAttribute(this)),
    m_pVertexBuffer(new Qt3D::QBuffer(Qt3D::QBuffer::VertexBuffer, this)),
    m_pVnAttribute(new Qt3D::QAttribute(this)),
    m_pNormalBuffer(new Qt3D::QBuffer(Qt3D::QBuffer::VertexBuffer, this))
{
    uid=_uid;
    nid=_nid;
    fid=_fid;

    build();

    // V
    const int vsize = m_aMeshVData.size() * sizeof(feather::FVertex3D);
    QByteArray meshVBytes;
    meshVBytes.resize(vsize);
    memcpy(meshVBytes.data(), m_aMeshVData.data(), vsize);

    m_pVertexBuffer->setData(meshVBytes);

    m_pVAttribute->setName(Qt3D::QAttribute::defaultPositionAttributeName());
    m_pVAttribute->setDataType(Qt3D::QAttribute::Double);
    m_pVAttribute->setDataSize(3);
    m_pVAttribute->setCount(m_aMeshVData.size());
    m_pVAttribute->setByteStride(sizeof(feather::FVertex3D));
    m_pVAttribute->setBuffer(m_pVertexBuffer);

    // VN
    const int vnsize = m_aMeshVnData.size() * sizeof(feather::FVertex3D);
    QByteArray meshVnBytes;
    meshVnBytes.resize(vnsize);
    memcpy(meshVnBytes.data(), m_aMeshVnData.data(), vsize);

    m_pNormalBuffer->setData(meshVnBytes);

    m_pVnAttribute->setName(Qt3D::QAttribute::defaultNormalAttributeName());
    m_pVnAttribute->setDataType(Qt3D::QAttribute::Double);
    m_pVnAttribute->setDataSize(3);
    m_pVnAttribute->setCount(m_aMeshVnData.size());
    m_pVnAttribute->setByteStride(sizeof(feather::FVertex3D));
    m_pVnAttribute->setBuffer(m_pNormalBuffer);

    addAttribute(m_pVAttribute);
    addAttribute(m_pVnAttribute);
}

MeshGeometry::~MeshGeometry()
{
    QNode::cleanup();
    delete m_pVAttribute;
    m_pVAttribute=0;
    delete m_pVertexBuffer;
    m_pVertexBuffer=0;
    delete m_pVnAttribute;
    m_pVnAttribute=0;
    delete m_pNormalBuffer;
    m_pNormalBuffer=0;
}

void MeshGeometry::build()
{
    feather::FMesh mesh;
    feather::qml::command::get_field_val(uid,nid,fid,mesh);

    // build gl mesh from mesh
    feather::FIntArray glei;
    feather::FIntArray gli;
    feather::FColorRGBAArray glc;
    //feather::FVertex3DArray glv;
    uint id=0;
    int fcount=0; // this is a temp value to test selection
    std::for_each(mesh.f.begin(), mesh.f.end(), [this,&mesh,&id,&fcount,&glei,&gli,&glc](feather::FFace _face){

            for_each(_face.begin(),_face.end(),[&mesh,&glei](feather::FFacePoint _fp){ glei.push_back(_fp.v); });
            /*
               std::cout << "build glei\n";
               for_each(glei.begin(),glei.end(),[this](int _v){ std::cout << _v << " "; });
               std::cout << std::endl;
               */

            while(id+2 <= _face.size()) {
            if(fcount==3) {
            glc.push_back(feather::FColorRGBA(1.0,0.0,0.0,1.0));
            glc.push_back(feather::FColorRGBA(1.0,0.0,0.0,1.0));
            glc.push_back(feather::FColorRGBA(1.0,0.0,0.0,1.0));
            } else {
            glc.push_back(feather::FColorRGBA());
            glc.push_back(feather::FColorRGBA());
            glc.push_back(feather::FColorRGBA());
            }

            //std::cout << "v" << id << ":" << _face.at(id).v << ",";
            std::cout << "v.y" << id << ":" << mesh.v.at(_face.at(id).v).y << ",";
            m_aMeshVData.push_back(mesh.v.at(_face.at(id).v));
            m_aMeshVnData.push_back(mesh.vn.at(_face.at(id).vn));
            //glvn.push_back(vn.at(_face.at(id).vn));
            gli.push_back(_face.at(id).v);

            //std::cout << "v" << id+1 << ":" << _face.at(id+1).v << ",";
            m_aMeshVData.push_back(mesh.v.at(_face.at(id+1).v));
            m_aMeshVnData.push_back(mesh.vn.at(_face.at(id+1).vn));
            //glvn.push_back(vn.at(_face.at(id+1).vn));
            gli.push_back(_face.at(id+1).v);

            if(id+2 < _face.size()) {
                //std::cout << "v" << id+2 << ":" << _face.at(id+2).v << ",";
                m_aMeshVData.push_back(mesh.v.at(_face.at(id+2).v));
                m_aMeshVnData.push_back(mesh.vn.at(_face.at(id+2).vn));
                //glvn.push_back(vn.at(_face.at(id+2).vn));
                gli.push_back(_face.at(id+2).v);
            } else {
                //std::cout << "v" << 0 << ":" << _face.at(0).v << ",";
                m_aMeshVData.push_back(mesh.v.at(_face.at(0).v));
                m_aMeshVnData.push_back(mesh.vn.at(_face.at(0).vn));
                //glvn.push_back(vn.at(_face.at(0).vn));
                gli.push_back(_face.at(0).v);
            }

            id=id+2;
            }
            //std::cout << "\n";
            fcount++;
            id=0;
    });


}


// MESHES

Mesh::Mesh(feather::draw::Item* _item, QNode *parent)
    : DrawItem(_item,DrawItem::Mesh,parent),
    m_pTransform(new Qt3D::QTransform()),
    m_pMaterial(new Qt3D::QPhongMaterial()),
    m_pMesh(new Qt3D::QGeometryRenderer()),
    m_pLight(new Qt3D::QPointLight())
{
    m_pMesh->setPrimitiveType(Qt3D::QGeometryRenderer::Triangles);
    m_pMesh->setGeometry(new MeshGeometry(_item->uid,_item->nid,static_cast<feather::draw::Mesh*>(item())->fid,this));

    // Shaded Material 
    //m_pMaterial->addParameter(new Qt3D::QParameter(QStringLiteral("meshColor"),QColor(Qt::blue)));  
    m_pMaterial->setDiffuse(QColor(Qt::red));
    m_pMaterial->setAmbient(Qt::black);
    m_pMaterial->setSpecular(Qt::white);
    m_pMaterial->setShininess(0.4f);


    // THIS WAS FROM SHADER TESTING
    /*
    m_pMaterial->addParameter(new Qt3D::QParameter(QStringLiteral("ambient"),QColor(Qt::blue)));
    m_pMaterial->addParameter(new Qt3D::QParameter(QStringLiteral("diffuse"),QColor(Qt::red)));
    m_pMaterial->addParameter(new Qt3D::QParameter(QStringLiteral("specular"),QColor(Qt::white)));
    m_pMaterial->addParameter(new Qt3D::QParameter(QStringLiteral("shininess"),150.0));
    m_pMaterial->addParameter(new Qt3D::QParameter(QStringLiteral("line.width"),0.8));
    m_pMaterial->addParameter(new Qt3D::QParameter(QStringLiteral("line.color"),QColor(Qt::black)));
    */

    // Light testing
    m_pLight->setColor(Qt::blue);
    m_pLight->setIntensity(10.5f);
    m_pLight->setPosition(QVector3D(4,4,4)); 

    addComponent(static_cast<Viewport2*>(parent)->frameGraph());
    //addComponent(m_pTransform);
    addComponent(m_pMaterial);
    addComponent(m_pMesh);
    //addComponent(m_pLight);

    //m_pMaterial->setEffect(m_pMaterialEffect);
}

Mesh::~Mesh()
{
    QNode::cleanup();
    
}


void Mesh::updateItem()
{
}

void Mesh::test()
{
    //m_pTransform->matrix().translate(1,0,0); 
    //removeComponent(m_pMesh);
    //setParent(Q_NULLPTR);
    //removeAllComponents();
}



// LINE
Line::Line(feather::draw::Item* _item, QNode *parent)
    : DrawItem(_item,DrawItem::Line,parent),
    m_pTransform(new Qt3D::QTransform()),
    m_pMaterial(new Qt3D::QPhongMaterial()),
    m_pMesh(new Qt3D::QGeometryRenderer()),
    //m_pMouseInput(new Qt3D::QMouseInput(this)),
    m_meshAttribute(new Qt3D::QAttribute(this)),
    m_vertexBuffer(new Qt3D::QBuffer(Qt3D::QBuffer::VertexBuffer, this))
{
    m_aVertex.push_back(feather::FVertex3D(0,0,0));
    m_aVertex.push_back(feather::FVertex3D(2,2,2));
    //const int nVerts = 2;
    const int size = m_aVertex.size() * sizeof(feather::FVertex3D);
    QByteArray meshBytes;
    meshBytes.resize(size);
    memcpy(meshBytes.data(), m_aVertex.data(), size);

    m_vertexBuffer->setData(meshBytes);

    m_meshAttribute->setName(Qt3D::QAttribute::defaultPositionAttributeName());
    m_meshAttribute->setDataType(Qt3D::QAttribute::Double);
    m_meshAttribute->setDataSize(3);
    m_meshAttribute->setCount(m_aVertex.size());
    m_meshAttribute->setByteStride(sizeof(feather::FVertex3D));
    m_meshAttribute->setBuffer(m_vertexBuffer);

    //setVerticesPerPatch(4);
    m_pMesh->setGeometry(new Qt3D::QGeometry(this));
    m_pMesh->geometry()->addAttribute(m_meshAttribute);

    m_pMesh->setPrimitiveType(Qt3D::QGeometryRenderer::Lines);
    //m_pMesh->setPrimitiveType(Qt3D::QGeometryRenderer::Triangles);
    //m_pMesh->setGeometry(new QGeometry(this));
    
    m_pMaterial->setDiffuse(QColor(Qt::red));
    m_pMaterial->setAmbient(Qt::red);
    //m_pMaterial->setSpecular(Qt::black);
    //m_pMaterial->setShininess(0.0f);

    
    addComponent(m_pTransform);
    addComponent(m_pMesh);
    addComponent(m_pMaterial);

    //connect(m_pMouseInput,SIGNAL(entered()),this,SLOT(mouseClicked()));
}

Line::~Line()
{
    QNode::cleanup();
    delete m_meshAttribute;
    m_meshAttribute=0;
    delete m_vertexBuffer;
    m_vertexBuffer=0;
}

void Line::updateItem()
{

}

/*
void Line::mouseClicked()
{
    std::cout << "Line Pressed\n";
}
*/


// AXIS GEOMETRY

AxisGeometry::AxisGeometry(QNode *parent)
    : Qt3D::QGeometry(parent),
    m_meshAttribute(new Qt3D::QAttribute(this)),
    m_vertexBuffer(new Qt3D::QBuffer(Qt3D::QBuffer::VertexBuffer, this))
{
    build();

    //const int nVerts = 6;
    const int size = m_axis.size() * sizeof(feather::FVertex3D);
    QByteArray meshBytes;
    meshBytes.resize(size);
    memcpy(meshBytes.data(), m_axis.data(), size);

    m_vertexBuffer->setData(meshBytes);

    m_meshAttribute->setName(Qt3D::QAttribute::defaultPositionAttributeName());
    m_meshAttribute->setDataType(Qt3D::QAttribute::Double);
    m_meshAttribute->setDataSize(3);
    m_meshAttribute->setCount(m_axis.size());
    m_meshAttribute->setByteStride(sizeof(feather::FVertex3D));
    m_meshAttribute->setBuffer(m_vertexBuffer);

    //setVerticesPerPatch(4);
    addAttribute(m_meshAttribute);
}

void AxisGeometry::build()
{
    // X axis 
    m_axis.push_back(feather::FVertex3D(0,0,0));
    m_axis.push_back(feather::FVertex3D(10,0,0));
 
    // Y axis 
    m_axis.push_back(feather::FVertex3D(0,0,0));
    m_axis.push_back(feather::FVertex3D(0,10,0));
 
    // Z axis 
    m_axis.push_back(feather::FVertex3D(0,0,0));
    m_axis.push_back(feather::FVertex3D(0,0,10));
}

// AXIS 

Axis::Axis(QNode *parent)
    : Qt3D::QEntity(parent),
    m_pTransform(new Qt3D::QTransform()),
    m_pMaterial(new Qt3D::QMaterial()),
    m_pMesh(new Qt3D::QGeometryRenderer())
    //m_pMouseInput(new Qt3D::QMouseInput(this))
{
    //m_pMesh->setPrimitiveType(Qt3D::QGeometryRenderer::Lines);
    m_pMesh->setPrimitiveType(Qt3D::QGeometryRenderer::Triangles);
    m_pMesh->setGeometry(new AxisGeometry(this));
    
    //m_pMaterial->setDiffuse(QColor(Qt::red));
    //m_pMaterial->setAmbient(Qt::red);
    //m_pMaterial->setSpecular(Qt::black);
    //m_pMaterial->setShininess(0.0f);

    
    Qt3D::QEffect* effect = new Qt3D::QEffect();
    Qt3D::QShaderProgram* shader = new Qt3D::QShaderProgram();
    Qt3D::QTechnique* technique = new Qt3D::QTechnique(); 
    Qt3D::QRenderPass* pass = new Qt3D::QRenderPass();

    //technique->openGLFilter()->setApi(Qt3D::QOpenGLFilter::Desktop);
    //technique->openGLFilter()->setApi(Qt3D::QOpenGLFilter::ES);
    //technique->openGLFilter()->setProfile(Qt3D::QOpenGLFilter::Core);
    technique->openGLFilter()->setMajorVersion(3);
    technique->openGLFilter()->setMinorVersion(3);

    technique->addParameter(new Qt3D::QParameter("line.width",QVariant(2.0)));

    pass->addBinding(new Qt3D::QParameterMapping("ambient","ka",Qt3D::QParameterMapping::Uniform));
    pass->addBinding(new Qt3D::QParameterMapping("diffuse","kd",Qt3D::QParameterMapping::Uniform));
    pass->addBinding(new Qt3D::QParameterMapping("specular","ks",Qt3D::QParameterMapping::Uniform));

    /*
    shader->setVertexShaderCode("#version 130\\
            in vec3 vertexPosition;\\
            in vec3 vertexNormal;\\
            out vec3 position;\\
            out vec3 normal;\\
            uniform mat4 modelView;\\
            uniform mat3 modelViewNormal;\\
            uniform mat4 mvp;\\
            void main()\\
            {\\
            normal = normalize(modelViewNormal * vertexNormal);\\
            position = vec3(modelView * vec4(vertexPosition, 1.0));\\
            gl_Position = mvp * vec4(vertexPosition, 1.0);\\
            }");

            shader->setFragmentShaderCode("#version 130\\
                    in vec3 normal;\\
                    in vec3 position;\\
                    uniform vec3 finalColor;\\
                    out vec4 fragColor;\\
                    void main()\\
                    {\\
                    vec3 n = normalize(normal);\\
                    vec3 s = normalize(vec3(1.0, 0.0, 1.0) - position);\\
                    vec3 v = normalize(-position);\\
                    float diffuse = max(dot(s, n), 0.0);\\
                    //fragColor = vec4(diffuse * finalColor, 1.0);\\
                    gl_FragColor = 1.0;\\
                    }");

                    pass->setShaderProgram(shader);
                    technique->addPass(pass); 
                    effect->addTechnique(technique);
                    m_pMaterial->setEffect(effect);

    */

    QFile vert("shaders/vert/mesh2.glsl");
    QFile frag("shaders/frag/test.glsl");
    QFile geom("shaders/geom/geom.glsl");

    if (!vert.open(QIODevice::ReadOnly | QIODevice::Text) ||
            !frag.open(QIODevice::ReadOnly | QIODevice::Text) ||
            !geom.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cout << "Shaders failed to open!\n";
        return;
    } else {
        while (!vert.atEnd()) {
            shader->setVertexShaderCode(vert.readLine());
        }

        while (!frag.atEnd()) {
            shader->setFragmentShaderCode(frag.readLine());
        }

        while (!geom.atEnd()) {
            shader->setGeometryShaderCode(geom.readLine());
        }

        pass->setShaderProgram(shader);
        technique->addPass(pass); 
        effect->addTechnique(technique);
        m_pMaterial->setEffect(effect);
    }

    addComponent(m_pTransform);
    addComponent(m_pMesh);
    addComponent(m_pMaterial);

    //connect(m_pMouseInput,SIGNAL(entered()),this,SLOT(mouseClicked()));
    /*
    connect(m_pTransform,SIGNAL(entered()),this,SLOT(mouseClicked()));
    connect(m_pMesh,SIGNAL(entered()),this,SLOT(mouseClicked()));
    connect(m_pMaterial,SIGNAL(entered()),this,SLOT(mouseClicked()));
    */
}

Axis::~Axis()
{

}

/*
void Axis::mouseClicked()
{
    std::cout << "Axis Pressed\n";
}
*/

// GRID GEOMETRY

GridGeometry::GridGeometry(QNode *parent)
    : Qt3D::QGeometry(parent),
    m_majorLevel(10),
    m_minorLevel(10),
    m_meshAttribute(new Qt3D::QAttribute(this)),
    m_vertexBuffer(new Qt3D::QBuffer(Qt3D::QBuffer::VertexBuffer, this))
{
    build();

    //const int nVerts = 6;
    const int size = m_grid.size() * sizeof(feather::FVertex3D);
    QByteArray meshBytes;
    meshBytes.resize(size);
    memcpy(meshBytes.data(), m_grid.data(), size);

    m_vertexBuffer->setData(meshBytes);

    m_meshAttribute->setName(Qt3D::QAttribute::defaultPositionAttributeName());
    m_meshAttribute->setDataType(Qt3D::QAttribute::Double);
    m_meshAttribute->setDataSize(3);
    m_meshAttribute->setCount(m_grid.size());
    m_meshAttribute->setByteStride(sizeof(feather::FVertex3D));
    m_meshAttribute->setBuffer(m_vertexBuffer);

    //setVerticesPerPatch(4);
    addAttribute(m_meshAttribute);
}

int GridGeometry::majorSubDividLevel()
{
    return m_majorLevel;
}

int GridGeometry::minorSubDividLevel()
{
    return m_minorLevel;
}

void GridGeometry::setMajorSubDividLevel(const int &level)
{
    m_majorLevel = level;
}

void GridGeometry::setMinorSubDividLevel(const int &level)
{
    m_minorLevel = level;
}

void GridGeometry::build()
{
    float major_spacing = 10.0/m_majorLevel;
    //float minor_spacing = major_spacing/m_minorLevel;

    // Z corners
    m_grid.push_back(feather::FVertex3D(-10,0,10));
    m_grid.push_back(feather::FVertex3D(-10,0,-10));
    m_grid.push_back(feather::FVertex3D(10,0,10));
    m_grid.push_back(feather::FVertex3D(10,0,-10));
 
    // X corners
    m_grid.push_back(feather::FVertex3D(10,0,-10));
    m_grid.push_back(feather::FVertex3D(-10,0,-10));
    m_grid.push_back(feather::FVertex3D(10,0,10));
    m_grid.push_back(feather::FVertex3D(-10,0,10));

    double cpos = 10.0; 
    for(unsigned int i=0; i < 10; i++){
        cpos -= major_spacing;
        // Z corners
        m_grid.push_back(feather::FVertex3D(-cpos,0,10));
        m_grid.push_back(feather::FVertex3D(-cpos,0,-10));
        m_grid.push_back(feather::FVertex3D(cpos,0,10));
        m_grid.push_back(feather::FVertex3D(cpos,0,-10));

        // X corners
        m_grid.push_back(feather::FVertex3D(10,0,-cpos));
        m_grid.push_back(feather::FVertex3D(-10,0,-cpos));
        m_grid.push_back(feather::FVertex3D(10,0,cpos));
        m_grid.push_back(feather::FVertex3D(-10,0,cpos));
    } 
}

// GRID

Grid::Grid(QNode *parent)
    : Qt3D::QEntity(parent),
    m_pTransform(new Qt3D::QTransform()),
    m_pMaterial(new Qt3D::QPhongMaterial()),
    m_pMesh(new Qt3D::QGeometryRenderer())
{
    connect(m_pMaterial, SIGNAL(diffuseChanged()), this, SIGNAL(diffuseColorChanged()));
    m_pMesh->setPrimitiveType(Qt3D::QGeometryRenderer::Lines);
    m_pMesh->setGeometry(new GridGeometry(this));
    
    m_pMaterial->setDiffuse(QColor(Qt::black));
    m_pMaterial->setAmbient(Qt::black);
    m_pMaterial->setSpecular(Qt::black);
    m_pMaterial->setShininess(0.0f);

    addComponent(m_pTransform);
    addComponent(m_pMesh);
    addComponent(m_pMaterial);
}

Grid::~Grid()
{

}

void Grid::setDiffuseColor(const QColor &diffuseColor)
{
    m_pMaterial->setDiffuse(diffuseColor);
}

QColor Grid::diffuseColor()
{
    return m_pMaterial->diffuse();
}


TessellatedGeometry::TessellatedGeometry(QNode *parent)
    : Qt3D::QGeometry(parent),
    m_positionAttribute(new Qt3D::QAttribute(this)),
    m_vertexBuffer(new Qt3D::QBuffer(Qt3D::QBuffer::VertexBuffer, this))
{
    const float positionData[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        1.0f,  1.0f, 0.0f,
        1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f
    };

    const int nVerts = 6;
    const int size = nVerts * 3 * sizeof(float);
    QByteArray positionBytes;
    positionBytes.resize(size);
    memcpy(positionBytes.data(), positionData, size);

    m_vertexBuffer->setData(positionBytes);

    m_positionAttribute->setName(Qt3D::QAttribute::defaultPositionAttributeName());
    m_positionAttribute->setDataType(Qt3D::QAttribute::Float);
    m_positionAttribute->setDataSize(3);
    m_positionAttribute->setCount(nVerts);
    m_positionAttribute->setByteStride(3 * sizeof(float));
    m_positionAttribute->setBuffer(m_vertexBuffer);

    setVerticesPerPatch(4);
    addAttribute(m_positionAttribute);

}


Object::Object(QNode *parent)
    : Qt3D::QEntity(parent),
    m_transform(new Qt3D::QTransform()),
    m_translate(new Qt3D::QTranslateTransform()),
    m_mesh(new Qt3D::QGeometryRenderer()),
    m_material(new Qt3D::QPhongMaterial())
{
    m_transform->addTransform(m_translate);

    connect(m_material, SIGNAL(diffuseChanged()), this, SIGNAL(diffuseColorChanged()));
    m_material->setAmbient(Qt::red);
    m_material->setSpecular(Qt::white);
    m_material->setShininess(0.0f);

    //m_pMouseController = new Qt3D::QMouseController(this);
    //m_pMouseInput = new Qt3D::QMouseInput(this);
    //m_pMouseInput->setController(m_pMouseController);
    //connect(m_pMouseInput,SIGNAL(clicked(Qt3D::Q3DMouseEvent*)),this,SLOT(onClicked(Qt3D::Q3DMouseEvent*)));
    //connect(m_pMouseInput,SIGNAL(event(Qt3D::Q3DMouseEvent*)),this,SLOT(onEvent(Qt3D::Q3DMouseEvent*)));

    /*
    Points
    Lines
    LineLoop
    LineStrip
    Triangles
    TriangleStrip
    TriangleFan
    LinesAdjacency
    TrianglesAdjacency
    LineStripAdjacency
    TriangleStripAdjacency
    Patches
    */
    // Faces
    m_mesh->setPrimitiveType(Qt3D::QGeometryRenderer::Triangles);
    // Edges
    //m_mesh->setPrimitiveType(Qt3D::QGeometryRenderer::LineLoop);
    // Points
    //m_mesh->setPrimitiveType(Qt3D::QGeometryRenderer::Points);
    m_mesh->setGeometry(new TessellatedGeometry(this));

    addComponent(m_transform);
    addComponent(m_mesh);
    addComponent(m_material);
    //addComponent(m_pMouseInput);
}

void Object::setAmbientColor(const QColor &ambientColor)
{
    m_material->setAmbient(ambientColor);
}


void Object::setSpecularColor(const QColor &specularColor)
{
    m_material->setSpecular(specularColor);
}

void Object::setDiffuseColor(const QColor &diffuseColor)
{
    m_material->setDiffuse(diffuseColor);
}

QColor Object::ambientColor()
{
    return m_material->ambient();
}

QColor Object::specularColor()
{
    return m_material->specular();
}

QColor Object::diffuseColor()
{
    return m_material->diffuse();
}

/*
void Object::onClicked(Qt3D::Q3DMouseEvent* event)
{
    std::cout << "Object Clicked\n";
}

void Object::onEvent(Qt3D::Q3DMouseEvent* event)
{
    std::cout << "Object Event\n";
}
*/


// FRAMEGRAPH
FrameGraph::FrameGraph(QNode* parent)
    : QFrameGraph(parent),
    m_pViewport(new Qt3D::QViewport()),
    m_pClearBuffer(new Qt3D::QClearBuffer(this)),
    m_pCameraSelector(new Qt3D::QCameraSelector())
{
    m_pViewport->setRect(QRect(0,0,1,1));
    m_pViewport->setClearColor(QColor("grey"));

    m_pClearBuffer->setBuffers(Qt3D::QClearBuffer::AllBuffers);
    m_pCameraSelector->setParent(m_pClearBuffer);

    setActiveFrameGraph(m_pViewport);
}

FrameGraph::~FrameGraph()
{
    QNode::cleanup();
}

void FrameGraph::setCamera(Qt3D::QCamera* camera)
{
    m_pCameraSelector->setCamera(camera); 
}


// VIEWPORT
Viewport2::Viewport2(QNode* parent)
    : Qt3D::QEntity(parent),
    m_showGrid(true),
    m_showAxis(true),
    m_pMouseController(new Qt3D::QMouseController()),
    m_pLight(new Qt3D::QPointLight()),
    m_pCamera(new Qt3D::QCamera(this)),
    m_pConfiguration(new Qt3D::Quick::Quick3DConfiguration(this)),
    m_pFrameGraph(new FrameGraph(this))
{

    m_pCamera->setProjectionType(Qt3D::QCameraLens::PerspectiveProjection);
    m_pCamera->setFieldOfView(45);
    m_pCamera->setNearPlane(0.1);
    m_pCamera->setFarPlane(100.0);
    m_pCamera->setAspectRatio(1.3);
    m_pCamera->setPosition(QVector3D(0,0,20));
    m_pCamera->setUpVector(QVector3D(0,1,0));
    m_pCamera->setViewCenter(QVector3D(0,0,0));

    m_pConfiguration->setControlledCamera(m_pCamera);
    
    m_pFrameGraph->setCamera(m_pCamera);

    m_clearBuffer.setBuffers(Qt3D::QClearBuffer::ColorBuffer);
    m_pMouseInput = new Qt3D::QMouseInput(this);
    m_pMouseInput->setController(m_pMouseController);
 
    m_pGrid = new Grid(this);
    m_pAxis = new Axis(this);
    m_pTorus = new Qt3D::QTorusMesh();

    // update the draw items
    feather::draw::DrawItems items;
    feather::qml::command::get_node_draw_items(1,items);

    std::cout << "There are " << items.size() << " draw items\n";

    buildScene(items);
    updateScene();
    //addComponent(m_pMouseInput);
    //connect(m_pMouseInput,SIGNAL(entered()),this,SLOT(onEntered()));
    //connect(m_pMouseInput,SIGNAL(clicked(Qt3D::Q3DMouseEvent*)),this,SLOT(onClicked(Qt3D::Q3DMouseEvent*)));

    // Light testing
    //m_pLight->setColor(Qt::blue);
    //m_pLight->setIntensity(1.5f);
   
    //m_pLight->setPosition(QVector3D(0,4,0)); 
    //Qt3D::QClearBuffer clearBuffer(this);
    //addComponent(m_pCamera);
    //addComponent(m_pFrameGraph);

}

Viewport2::~Viewport2()
{
    delete m_pGrid;
    m_pGrid=0;
    delete m_pAxis;
    m_pAxis=0;
    qDeleteAll(m_apDrawItems);
}

void Viewport2::updateScene()
{
    std::cout << "updating vp scene\n";
    /* 
    feather::draw::DrawItems items;
    feather::qml::command::get_node_draw_items(1,items);
    */
    std::cout << "There are " << m_apDrawItems.size() << " draw items\n";

    /* 
    if(m_apDrawItems.isEmpty()) {
        buildScene(items);
        //buildScene();
    } else {
    
    */
    /* 
        Q_FOREACH (DrawItem* item, m_apDrawItems) {
            item->setParent(this);
        }
    */
    //}
    for(auto item : m_apDrawItems) {
        switch(item->item()->type){
            case feather::draw::Item::Mesh:
                std::cout << "updating Mesh draw item\n";
                static_cast<Mesh*>(item)->test();
                removeAllComponents();
                //delete item;
                break;
            case feather::draw::Item::Line:
                std::cout << "updating Line draw item\n";
                static_cast<Line*>(item)->updateItem();
                break;
            case feather::draw::Item::PerspCamera:
                std::cout << "updating Perspective Camear draw item\n";
                static_cast<PerspCamera*>(item)->updateItem();
                break;
            default:
                std::cout << "nothing built\n";
        }
    }
    std::cout << "THERE ARE " << components().count() << std::endl;

    /*
    Q_FOREACH(DrawItem* item, m_apDrawItems){
        //item->updateItem();
        
        delete item;
    }
    */
}

bool Viewport2::buildItems(feather::draw::DrawItems& items)
{
    return false;
}

int Viewport2::majorSubDividLevel()
{
    return m_pGrid->grid()->majorSubDividLevel();
}

int Viewport2::minorSubDividLevel()
{
    return m_pGrid->grid()->minorSubDividLevel();
}

bool Viewport2::showGrid()
{
    return m_showGrid;
}

bool Viewport2::showAxis()
{
    return m_showAxis;
}

void Viewport2::setMajorSubDividLevel(const int &level)
{
    m_pGrid->grid()->setMajorSubDividLevel(level);
    majorSubDividLevelChanged();
}

void Viewport2::setMinorSubDividLevel(const int &level)
{
    m_pGrid->grid()->setMinorSubDividLevel(level);
    minorSubDividLevelChanged();
}

void Viewport2::setShowGrid(const bool &show)
{
    m_showGrid = show;
    showGridChanged();
}

void Viewport2::setShowAxis(const bool &show)
{
    m_showAxis = show;
    showAxisChanged();
}

void Viewport2::buildScene(feather::draw::DrawItems& items)
{
    for(auto item : items) {
        switch(item->type){
            case feather::draw::Item::Mesh:
                std::cout << "build Mesh\n";
                m_apDrawItems.append(new Mesh(item,this));
                break;
            case feather::draw::Item::Line:
                std::cout << "build Line\n";
                m_apDrawItems.append(new Line(item,this));
                break;
            case feather::draw::Item::PerspCamera:
                std::cout << "build Line\n";
                m_apDrawItems.append(new PerspCamera(item,this));
                break;
            default:
                std::cout << "nothing built\n";
        }
    }
}

void Viewport2::onEntered()
{
    std::cout << "VP Entered\n";
}

void Viewport2::onClicked(Qt3D::Q3DMouseEvent* event)
{
    std::cout << "VP Clicked\n";
}

void Viewport2::addItems(unsigned int uid)
{
    feather::status pass;
    unsigned int nid = feather::qml::command::get_node_id(uid,pass);
    feather::draw::DrawItems items;
    feather::qml::command::get_node_draw_items(nid,items);
    std::cout << "add draw item " << uid << std::endl;

    m_apDrawItems.clear();

    for(auto item : items) {
        item->uid=uid;
        item->nid=nid;
        switch(item->type){
            case feather::draw::Item::Mesh:
                std::cout << "add Mesh\n";
                m_apDrawItems.append(new Mesh(item,this));
                break;
            case feather::draw::Item::Line:
                std::cout << "add Line\n";
                m_apDrawItems.append(new Line(item,this));
                break;
            case feather::draw::Item::PerspCamera:
                std::cout << "updating Perspective Camear draw item\n";
                m_apDrawItems.append(new PerspCamera(item,this));
                break;
            default:
                std::cout << "nothing built\n";
        }
        m_apDrawItems.at(m_apDrawItems.size()-1)->updateItem();
    }


}

void Viewport2::updateItems(unsigned int uid)
{
    for(auto item : m_apDrawItems) {
        if(item->item()->uid == uid){
            switch(item->item()->type){
                case feather::draw::Item::Mesh:
                    std::cout << "updating Mesh draw item\n";
                    static_cast<Mesh*>(item)->updateItem();
                    break;
                case feather::draw::Item::Line:
                    std::cout << "updating Line draw item\n";
                    static_cast<Line*>(item)->updateItem();
                    break;
                case feather::draw::Item::PerspCamera:
                    std::cout << "updating Perspective Camear draw item\n";
                    static_cast<PerspCamera*>(item)->updateItem();
                    break;
                 default:
                    std::cout << "nothing built\n";
            }
        }
    }
}
