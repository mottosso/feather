/***********************************************************************
 *
 * Filename: main.cpp
 *
 * Description: Holds polygon nodes and commands.
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

#include "deps.hpp"
#include "pluginmanager.hpp"
#include "field.hpp"
#include "node.hpp"
#include "parameter.hpp"
#include "command.hpp"
#include "scenegraph.hpp"

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
        //typedef field::Field<int,field::connection::In>* fielddata;
        //fielddata f = static_cast<fielddata>(fields.at(0));

        //std::cout << "value from polycube field:" << f->value << std::endl;
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

        node.glvertex = info.program->attributeLocation("vertex");
        node.glmatrix = info.program->uniformLocation("matrix");
        node.glnormal = info.program->attributeLocation("normal");
        node.gllightPosition = info.program->attributeLocation("lightposition");
        node.glshaderDiffuse = info.program->attributeLocation("shader_diffuse");
    }; 

    GL_DRAW(POLYGON_SHAPE)
    {
        typedef field::Field<FMesh,field::connection::In>* fielddata;
        fielddata f = static_cast<fielddata>(node.fields.at(1));

        typedef field::Field<FMesh,field::connection::Out>* targetdata;
        targetdata tf;

        if(f->connected) {
            tf = static_cast<targetdata>(scenegraph::get_fieldBase(f->puid,f->pn,f->pf));
        }

        if(tf!=NULL)
        { 
            if(tf->value.v.size() >= 4)
            {
                std::cout << "drawing CUBE\n";

                info.program->bind();
                //info.program->setAttributeValue(info.lightPosition, m_pLight->position());

                info.program->setUniformValue(node.glmatrix, *info.view);
                info.program->enableAttributeArray(node.glvertex);
                info.program->enableAttributeArray(node.glnormal);
                info.program->setAttributeArray(node.glvertex, GL_FLOAT, &tf->value.v[0], 3);
                info.program->setAttributeArray(node.glnormal, GL_FLOAT, &tf->value.vn[0],3);

                //m_ShaderDiffuse.setRgb(100,100,100);
                //info.program->setAttributeValue(m_ShaderDiffuseId, m_ShaderDiffuse);
                glPolygonMode(GL_FRONT, GL_FILL);
                glPolygonMode(GL_BACK, GL_LINE);
                glDrawArrays(GL_QUADS, 0, tf->value.v.size());

                //m_ShaderDiffuse.setRgb(0,0,0);
                //info.program.setAttributeValue(m_ShaderDiffuseId, m_ShaderDiffuse);
                glLineWidth(4.5);
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                glDrawArrays(GL_QUADS, 0, tf->value.vn.size());

                info.program->disableAttributeArray(node.glvertex);
                info.program->disableAttributeArray(node.glnormal);
                info.program->release();
            }
        }

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
ADD_FIELD_TO_NODE(POLYGON_CUBE,FMesh,field::Mesh,field::connection::Out,FMesh(),4)

namespace feather
{

    DO_IT(POLYGON_CUBE) 
    {
        //PolygonCubeFields* cube = static_cast<PolygonCubeFields*>(fields);
        //std::cout << "cube: subX:" << cube->subX << std::endl;

        typedef field::Field<FMesh,field::connection::Out>* fielddata;
        fielddata f = static_cast<fielddata>(fields.at(4));

        /*
        if(!f->value.v.size())
        {
            // Front 
            f->value.v.push_back(FVertex3D(1.0,1.0,1.0));
            f->value.v.push_back(FVertex3D(1.0,-1.0,1.0));
            f->value.v.push_back(FVertex3D(-1.0,-1.0,1.0));
            f->value.v.push_back(FVertex3D(-1.0,1.0,1.0));
            // R Side
            f->value.v.push_back(FVertex3D(1.0,1.0,1.0));
            f->value.v.push_back(FVertex3D(1.0,1.0,-1.0));
            f->value.v.push_back(FVertex3D(1.0,-1.0,-1.0));
            f->value.v.push_back(FVertex3D(1.0,-1.0,1.0));
            // L Side
            f->value.v.push_back(FVertex3D(-1.0,1.0,1.0));
            f->value.v.push_back(FVertex3D(-1.0,-1.0,1.0));
            f->value.v.push_back(FVertex3D(-1.0,-1.0,-1.0));
            f->value.v.push_back(FVertex3D(-1.0,1.0,-1.0));
            // Back 
            f->value.v.push_back(FVertex3D(1.0,1.0,-1.0));
            f->value.v.push_back(FVertex3D(-1.0,1.0,-1.0));
            f->value.v.push_back(FVertex3D(-1.0,-1.0,-1.0));
            f->value.v.push_back(FVertex3D(1.0,-1.0,-1.0));
            // Top
            f->value.v.push_back(FVertex3D(1.0,1.0,1.0));
            f->value.v.push_back(FVertex3D(-1.0,1.0,1.0));
            f->value.v.push_back(FVertex3D(-1.0,1.0,-1.0));
            f->value.v.push_back(FVertex3D(1.0,1.0,-1.0));
            // Bottom 
            f->value.v.push_back(FVertex3D(1.0,-1.0,1.0));
            f->value.v.push_back(FVertex3D(1.0,-1.0,-1.0));
            f->value.v.push_back(FVertex3D(-1.0,-1.0,-1.0));
            f->value.v.push_back(FVertex3D(-1.0,-1.0,1.0));

            // test Cube Normals
            // Front
            f->value.vn.push_back(FVertex3D(0.0,0.0,1.0));
            f->value.vn.push_back(FVertex3D(0.0,0.0,1.0));
            f->value.vn.push_back(FVertex3D(0.0,0.0,1.0));
            f->value.vn.push_back(FVertex3D(0.0,0.0,1.0));
            // Left
            f->value.vn.push_back(FVertex3D(-1.0,0.0,0.0));
            f->value.vn.push_back(FVertex3D(-1.0,0.0,0.0));
            f->value.vn.push_back(FVertex3D(-1.0,0.0,0.0));
            f->value.vn.push_back(FVertex3D(-1.0,0.0,0.0));
            // Right 
            f->value.vn.push_back(FVertex3D(1.0,0.0,0.0));
            f->value.vn.push_back(FVertex3D(1.0,0.0,0.0));
            f->value.vn.push_back(FVertex3D(1.0,0.0,0.0));
            f->value.vn.push_back(FVertex3D(1.0,0.0,0.0));
            // Back 
            f->value.vn.push_back(FVertex3D(0.0,0.0,-1.0));
            f->value.vn.push_back(FVertex3D(0.0,0.0,-1.0));
            f->value.vn.push_back(FVertex3D(0.0,0.0,-1.0));
            f->value.vn.push_back(FVertex3D(0.0,0.0,-1.0));
            // Top 
            f->value.vn.push_back(FVertex3D(0.0,1.0,0.0));
            f->value.vn.push_back(FVertex3D(0.0,1.0,0.0));
            f->value.vn.push_back(FVertex3D(0.0,1.0,0.0));
            f->value.vn.push_back(FVertex3D(0.0,1.0,0.0));
            // Bottom 
            f->value.vn.push_back(FVertex3D(0.0,-1.0,0.0));
            f->value.vn.push_back(FVertex3D(0.0,-1.0,0.0));
            f->value.vn.push_back(FVertex3D(0.0,-1.0,0.0));
            f->value.vn.push_back(FVertex3D(0.0,-1.0,0.0));
        }
        */

         std::cout << "polygon cube doit() - [" << f << "] type=\n";// << f->type << std::endl;

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
