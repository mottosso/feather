/***********************************************************************
 *
 * Filename: node.hpp
 *
 * Description: vulkan base node.
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

#ifndef NODE_HPP
#define NODE_HPP

#include "deps.hpp"
#include "vulkan_deps.hpp"

namespace feather
{

    namespace vulkan
    {
        struct MeshBufferInfo {
            VkBuffer buf = VK_NULL_HANDLE;
            VkDeviceMemory mem = VK_NULL_HANDLE;
        };
    
        struct MeshBuffer {
            MeshBufferInfo vertices;
            MeshBufferInfo indices;
            MeshBufferInfo edges;
            uint32_t indexCount;
            uint32_t edgeCount;
        };

        struct Vertex {
            float pos[3];
            float norm[3];
            float uv[2];
            float col[3];
            uint32_t selected;
        };

        class Node
        {
            public:
                enum Type { Null, Camera, Light, Mesh };

                Node(Type type=Null);
                ~Node();
                virtual void prepareVertices(VkDevice device, VkPhysicalDeviceMemoryProperties deviceMemoryProperties)=0;
                virtual void updateVertices(VkDevice device, VkPhysicalDeviceMemoryProperties deviceMemoryProperties, float step=1.0)=0;
                Type type() { return m_type; }; 
                MeshBuffer* buffer() { return m_pMeshBuffer; };
                void freeBuffer(VkDevice device);
                virtual void build()=0;
                virtual void loadShaders()=0;
                // wire
                void setWireVertShader(std::string path) { m_wireVertShader = path; };
                void setWireGeomShader(std::string path) { m_wireGeomShader = path; };
                void setWireFragShader(std::string path) { m_wireFragShader = path; };
                // point
                void setPointVertShader(std::string path) { m_pointVertShader = path; };
                void setPointGeomShader(std::string path) { m_pointGeomShader = path; };
                void setPointFragShader(std::string path) { m_pointFragShader = path; };
                // shade
                void setShadeVertShader(std::string path) { m_shadeVertShader = path; };
                void setShadeFragShader(std::string path) { m_shadeFragShader = path; };

                // wire 
                std::string wireVertShader() { return m_wireVertShader; };
                std::string wireGeomShader() { return m_wireGeomShader; };
                std::string wireFragShader() { return m_wireFragShader; };
                // point
                std::string pointVertShader() { return m_pointVertShader; };
                std::string pointGeomShader() { return m_pointGeomShader; };
                std::string pointFragShader() { return m_pointFragShader; };
                // shaded
                std::string shadeVertShader() { return m_shadeVertShader; };
                std::string shadeFragShader() { return m_shadeFragShader; };

            protected:
                // node methods and members
                VkBool32 getMemoryType(VkPhysicalDeviceMemoryProperties deviceMemoryProperties, uint32_t typeBits, VkFlags properties, uint32_t *typeIndex);
                void buildVertex(VkDevice device, VkPhysicalDeviceMemoryProperties deviceMemoryProperties);
                void buildIndex(VkDevice device, VkPhysicalDeviceMemoryProperties deviceMemoryProperties);
                void buildEdge(VkDevice device, VkPhysicalDeviceMemoryProperties deviceMemoryProperties);

                Type m_type;
                MeshBuffer* m_pMeshBuffer;
                std::vector<Vertex> m_vertexBuffer;
                std::vector<uint32_t> m_indexBuffer;
                std::vector<uint32_t> m_edgeBuffer;

                // wire
                std::string m_wireVertShader;
                std::string m_wireGeomShader;
                std::string m_wireFragShader;

                // point
                std::string m_pointVertShader;
                std::string m_pointGeomShader;
                std::string m_pointFragShader;

                // shaded
                std::string m_shadeVertShader;
                std::string m_shadeFragShader;
         };

    } // namespace vulkan

} // namespace feather

#endif
