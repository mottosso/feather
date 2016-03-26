/***********************************************************************
 *
 * Filename: mesh.hpp
 *
 * Description: vulkan mesh node.
 *
 * Copyright (C) 2016 Richard Layman, rlayman2000@yahoo.com 
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

#ifndef MESH_HPP
#define MESH_HPP

#include "deps.hpp"
#include "vulkan_deps.hpp"
#include "node.hpp"

namespace feather
{

    namespace vulkan
    {

        class Mesh : public Node
        {
            public:
                Mesh();
                ~Mesh();
                void prepareVertices(VkDevice device, VkPhysicalDeviceMemoryProperties deviceMemoryProperties);
                void updateVertices(VkDevice device, VkPhysicalDeviceMemoryProperties deviceMemoryProperties, float step=1.0);
                void build();

            private:
                /*
                struct Vertex {
                    float pos[3];
                    float norm[3];
                    float uv[2];
                    float col[3];
                    uint32_t selected;
                };
                */

                /*
                 * The Face struct is for each triangle and layouts out
                 * describs it's layout.
                 * The id is tied to the FMesh's face id so that it makes
                 * it possible to tell when what face this is actually tied
                 * to.
                 * The options member is a bit field that tells the following:
                 * bit:
                 * 0 - face selected
                 * 1 - is boundary 0->1 a viewable edge
                 * 2 - is boundary 1->2 a viewable edge
                 * 3 - is boundary 2->3 a viewable edge
                 * 4 - is boundary 0->1 selected 
                 * 5 - is boundary 1->2 selected 
                 * 6 - is boundary 2->3 selected
                 * 7
                 * | unassigned
                 * 31
                 *
                 * The face is created the same time the index buffer is
                 * created.
                 */
                /*
                struct Face {
                    uint32_t id;
                    uint32_t options;
                };
                */

                //void buildVertex(VkDevice device, VkPhysicalDeviceMemoryProperties deviceMemoryProperties);
                //void buildIndex(VkDevice device, VkPhysicalDeviceMemoryProperties deviceMemoryProperties);
                //void buildFace(VkDevice device, VkPhysicalDeviceMemoryProperties deviceMemoryProperties);

                //std::vector<Vertex> m_vertexBuffer;
                //std::vector<uint32_t> m_indexBuffer;
                //std::vector<Face> m_faceBuffer;
        };

    } // namespace vulkan

} // namespace feather

#endif
