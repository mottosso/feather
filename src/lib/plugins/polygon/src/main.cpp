// =====================================================================================
// 
//       Filename:  main.cpp
// 
//    Description:  This plugin holds the POLYGON_PLANE, POLYGON_CUBE scenegraph nodes.
// 
//        Version:  1.0
//        Created:  11/03/2014 04:44:11 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#include "deps.hpp"
#include "pluginmanager.hpp"
#include "field.hpp"
#include "node.hpp"
#include "parameter.hpp"
#include "command.hpp"

#ifdef __cplusplus
extern "C" {
#endif
    C_PLUGIN_WRAPPER()
#ifdef __cplusplus
}
#endif

using namespace feather;

#define POLYGON_SHAPE 320
#define POLYGON_PLANE 321
#define POLYGON_CUBE 322


PLUGIN_INIT(POLYGON_SHAPE,POLYGON_CUBE)


/*
 ***************************************
 *            POLYGON SHAPE            *
 ***************************************
*/

// meshIn
ADD_FIELD_TO_NODE(POLYGON_SHAPE,FMesh,field::Mesh,field::connection::In,FMesh(),1)
// testIn
ADD_FIELD_TO_NODE(POLYGON_SHAPE,int,field::Int,field::connection::In,10,2)


namespace feather
{

    DO_IT(POLYGON_SHAPE)
    { 
        //PolygonShapeFields* shape = static_cast<PolygonShapeFields*>(fields);
        typedef field::Field<int,field::connection::In>* fielddata;
    fielddata f = static_cast<fielddata>(fields.at(0));
  
        std::cout << "value from polycube field:" << f->value << std::endl;

        return status();
    };

    GL_INIT(POLYGON_SHAPE)
    {
       //info.fragShader->compileSourceFile("shaders/frag/lambert.glsl");
        //info.vertShader->compileSourceFile("shaders/vert/mesh.glsl");
        QOpenGLShader* frag = new QOpenGLShader(QOpenGLShader::Fragment);
        frag->compileSourceFile("shaders/frag/lambert.glsl");
        QOpenGLShader* vert = new QOpenGLShader(QOpenGLShader::Vertex);
        vert->compileSourceFile("shaders/vert/mesh.glsl");


        //info.program->addShader(info.fragShader);
        //info.program->addShader(info.vertShader);
        
        info.program->addShader(frag);
        info.program->addShader(vert);

        info.program->link();

        info.vertex = info.program->attributeLocation("vertex");
        info.matrix = info.program->uniformLocation("matrix");
        info.normal = info.program->attributeLocation("normal");
        info.lightPosition = info.program->attributeLocation("lightposition");
        info.shaderDiffuse = info.program->attributeLocation("shader_diffuse");
        typedef field::Field<FMesh,field::connection::In>* fielddata;
        fielddata f = static_cast<fielddata>(node.fields.at(1));

        // test Cube Vertex
        // Front 
        f->value.v.push_back(FVertex3D(1.0,1.0,1.0));
        f->value.v.push_back(FVertex3D(1.0,-1.0,1.0));
        f->value.v.push_back(FVertex3D(-1.0,-1.0,1.0));
        f->value.v.push_back(FVertex3D(-1.0,1.0,1.0));

        /*
        // R Side
        m_apV.push_back(FVertex3D(1.0,1.0,1.0));
        m_apV.push_back(FVertex3D(1.0,1.0,-1.0));
        m_apV.push_back(FVertex3D(1.0,-1.0,-1.0));
        m_apV.push_back(FVertex3D(1.0,-1.0,1.0));
        // L Side
        m_apV.push_back(FVertex3D(-1.0,1.0,1.0));
        m_apV.push_back(FVertex3D(-1.0,-1.0,1.0));
        m_apV.push_back(FVertex3D(-1.0,-1.0,-1.0));
        m_apV.push_back(FVertex3D(-1.0,1.0,-1.0));
        // Back 
        m_apV.push_back(FVertex3D(1.0,1.0,-1.0));
        m_apV.push_back(FVertex3D(-1.0,1.0,-1.0));
        m_apV.push_back(FVertex3D(-1.0,-1.0,-1.0));
        m_apV.push_back(FVertex3D(1.0,-1.0,-1.0));
        // Top
        m_apV.push_back(FVertex3D(1.0,1.0,1.0));
        m_apV.push_back(FVertex3D(-1.0,1.0,1.0));
        m_apV.push_back(FVertex3D(-1.0,1.0,-1.0));
        m_apV.push_back(FVertex3D(1.0,1.0,-1.0));
        // Bottom 
        m_apV.push_back(FVertex3D(1.0,-1.0,1.0));
        m_apV.push_back(FVertex3D(1.0,-1.0,-1.0));
        m_apV.push_back(FVertex3D(-1.0,-1.0,-1.0));
        m_apV.push_back(FVertex3D(-1.0,-1.0,1.0));

        // test Cube Normals
        // Front
        m_apVn.push_back(FVertex3D(0.0,0.0,1.0));
        m_apVn.push_back(FVertex3D(0.0,0.0,1.0));
        m_apVn.push_back(FVertex3D(0.0,0.0,1.0));
        m_apVn.push_back(FVertex3D(0.0,0.0,1.0));
        // Left
        m_apVn.push_back(FVertex3D(-1.0,0.0,0.0));
        m_apVn.push_back(FVertex3D(-1.0,0.0,0.0));
        m_apVn.push_back(FVertex3D(-1.0,0.0,0.0));
        m_apVn.push_back(FVertex3D(-1.0,0.0,0.0));
        // Right 
        m_apVn.push_back(FVertex3D(1.0,0.0,0.0));
        m_apVn.push_back(FVertex3D(1.0,0.0,0.0));
        m_apVn.push_back(FVertex3D(1.0,0.0,0.0));
        m_apVn.push_back(FVertex3D(1.0,0.0,0.0));
        // Back 
        m_apVn.push_back(FVertex3D(0.0,0.0,-1.0));
        m_apVn.push_back(FVertex3D(0.0,0.0,-1.0));
        m_apVn.push_back(FVertex3D(0.0,0.0,-1.0));
        m_apVn.push_back(FVertex3D(0.0,0.0,-1.0));
        // Top 
        m_apVn.push_back(FVertex3D(0.0,1.0,0.0));
        m_apVn.push_back(FVertex3D(0.0,1.0,0.0));
        m_apVn.push_back(FVertex3D(0.0,1.0,0.0));
        m_apVn.push_back(FVertex3D(0.0,1.0,0.0));
        // Bottom 
        m_apVn.push_back(FVertex3D(0.0,-1.0,0.0));
        m_apVn.push_back(FVertex3D(0.0,-1.0,0.0));
        m_apVn.push_back(FVertex3D(0.0,-1.0,0.0));
        m_apVn.push_back(FVertex3D(0.0,-1.0,0.0));
        */
        std::cout << "polygonshape gl init\n";
    }; 

    GL_DRAW(POLYGON_SHAPE)
    {
        info.program->bind();
        //info.program->setAttributeValue(info.lightPosition, m_pLight->position());

        typedef field::Field<FMesh,field::connection::In>* fielddata;
        fielddata f = static_cast<fielddata>(node.fields.at(1));

        info.program->setUniformValue(info.matrix, *info.view);
        info.program->enableAttributeArray(info.vertex);
        //info.program->enableAttributeArray(info.normal);
        info.program->setAttributeArray(info.vertex, GL_FLOAT, &f->value.v[0], 3);
        //info.program->setAttributeArray(node.normal, GL_FLOAT, &f->value.vn[0],3);

        //m_ShaderDiffuse.setRgb(100,100,100);
        //info.program->setAttributeValue(m_ShaderDiffuseId, m_ShaderDiffuse);
        glPolygonMode(GL_FRONT, GL_FILL);
        glPolygonMode(GL_BACK, GL_LINE);
        glDrawArrays(GL_QUADS, 0, f->value.v.size());

        //m_ShaderDiffuse.setRgb(0,0,0);
        //info.program.setAttributeValue(m_ShaderDiffuseId, m_ShaderDiffuse);
        /*
        glLineWidth(4.5);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_QUADS, 0, f->value.v.size());
        */

        info.program->disableAttributeArray(info.vertex);
        //info.program->disableAttributeArray(info.normal);
        info.program->release();

        std::cout << "polygonshape gl draw\n";
    }; 

} // namespace feather

NODE_INIT(POLYGON_SHAPE,node::Polygon)


/*
 ***************************************
 *            POLYGON PLANE            *
 ***************************************
*/

ADD_FIELD_TO_NODE(POLYGON_PLANE,int,field::Int,field::connection::In,2,1)
ADD_FIELD_TO_NODE(POLYGON_PLANE,int,field::Int,field::connection::In,2,2)



namespace feather
{

    DO_IT(POLYGON_PLANE)
    { 
        //PolygonPlaneFields* plane = static_cast<PolygonPlaneFields*>(fields);
        //std::cout << "plane: subX:" << plane->subX << std::endl;

        return status();
    };

} // namespace feather

NODE_INIT(POLYGON_PLANE,node::Polygon)


/*
 ***************************************
 *            POLYGON CUBE             *
 ***************************************
*/

ADD_FIELD_TO_NODE(POLYGON_CUBE,int,field::Int,field::connection::In,0,1)
ADD_FIELD_TO_NODE(POLYGON_CUBE,int,field::Int,field::connection::In,0,2)
ADD_FIELD_TO_NODE(POLYGON_CUBE,int,field::Int,field::connection::In,0,3)
ADD_FIELD_TO_NODE(POLYGON_CUBE,int,field::Int,field::connection::Out,5,4)

namespace feather
{

    DO_IT(POLYGON_CUBE) 
    {
        //PolygonCubeFields* cube = static_cast<PolygonCubeFields*>(fields);
        //std::cout << "cube: subX:" << cube->subX << std::endl;
        return status();
    };

} // namespace feather

NODE_INIT(POLYGON_CUBE,node::Polygon)


/*
 ***************************************
 *              COMMANDS               *
 ***************************************
*/

namespace feather
{
    namespace command
    {
        enum Command { N=0 };
    } // namespace command

} // namespace feather

INIT_COMMAND_CALLS(N)
