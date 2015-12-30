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

// MAIN VIEWPORT


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
    m_pMesh(new Qt3D::QGeometryRenderer()),
    m_pMouseInput(new Qt3D::QMouseInput(this))
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

    connect(m_pMouseInput,SIGNAL(entered()),this,SLOT(mouseClicked()));
    /*
    connect(m_pTransform,SIGNAL(entered()),this,SLOT(mouseClicked()));
    connect(m_pMesh,SIGNAL(entered()),this,SLOT(mouseClicked()));
    connect(m_pMaterial,SIGNAL(entered()),this,SLOT(mouseClicked()));
    */
}

Axis::~Axis()
{

}

void Axis::mouseClicked()
{
    std::cout << "Axis Pressed\n";
}

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


// MESHES

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


// VIEWPORT
Viewport2::Viewport2(QNode *parent)
    : Qt3D::QEntity(parent),
    m_showGrid(true),
    m_showAxis(true),
    m_pMouseInput(new Qt3D::QMouseInput(this))
{
    m_pGrid = new Grid(this);
    m_pAxis = new Axis(this);

    // update the draw items
    feather::qml::command::scenegraph_update(feather::state::DrawIt);

    buildScene();
    updateScene();
    addComponent(m_pMouseInput);
    connect(m_pMouseInput,SIGNAL(entered()),this,SLOT(onEntered()));
}

Viewport2::~Viewport2()
{
    qDeleteAll(m_entities);
    delete m_pGrid;
    m_pGrid=0;
    delete m_pAxis;
    m_pAxis=0;
}

void Viewport2::updateScene()
{
    if (m_entities.isEmpty()) {
        buildScene();
    } else {
        Q_FOREACH (Object *entity, m_entities) {
            entity->setParent(this);
        }
    }
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

void Viewport2::buildScene()
{
    m_entities.append(new Object()); 
}

void Viewport2::onEntered()
{
    std::cout << "VP Entered\n";
}
