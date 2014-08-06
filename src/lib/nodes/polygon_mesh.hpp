// =====================================================================================
// 
//       Filename:  polygon_mesh.hpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/13/2014 05:40:25 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#ifndef POLYGON_MESH_HPP
#define POLYGON_MESH_HPP

#include "deps.hpp"
#include "types.hpp"
#include "status.hpp"
#include "field.hpp"
#include "node.hpp"

namespace feather
{

    namespace node
    {

        struct PolygonMeshFields : public Fields 
        {
        };

        typedef Node<node::PolygonMesh> polymesh;

        // INIT
        template <> status polymesh::init(NodeAttributes* nattr, Fields* fields)
        {
            std::cout << "polycube init\n";
            // Test
            nattr->vshader = new QOpenGLShader(QOpenGLShader::Vertex, &nattr->program);
            nattr->vshader->compileSourceFile("mesh.glsl");

            nattr->fshader = new QOpenGLShader(QOpenGLShader::Fragment, &nattr->program);
            nattr->fshader->compileSourceFile("texture.glsl");

            nattr->program.addShader(nattr->vshader);
            nattr->program.addShader(nattr->fshader);
            nattr->program.link();


            nattr->v.push_back(FVertex3D(-1,0,-1));
            nattr->v.push_back(FVertex3D(1,0,-1));
            nattr->v.push_back(FVertex3D(-1,0,1));
            nattr->v.push_back(FVertex3D(1,0,1));

            return status();
        }


        // DO IT
        template <> status polymesh::do_it(Fields* node)
        {
            //std::cout << "polycube do_it\n";
            return status();
        };

        // DRAW GL
        template <> status polymesh::draw_gl(NodeAttributes* nattr, Fields* node)
        {
           // std::cout << "polycube draw_gl\n";
            nattr->program.bind();
            nattr->program.setUniformValue(nattr->mAttr, nattr->view);
            //m_program.setUniformValue(texture,0);
            nattr->program.enableAttributeArray(nattr->vAttr);
            nattr->program.setAttributeArray(nattr->vAttr, GL_FLOAT, &nattr->v[0], 3);
            //program1.setAttributeArray(normalAttr1, normals.constData());
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            //program1.disableAttributeArray(normalAttr1);
            nattr->program.disableAttributeArray(nattr->vAttr);
            nattr->program.release();

            return status();
        }
    } // namespace node

} // namespace feather

#endif
