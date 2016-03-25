/***********************************************************************
 *
 * Filename: mesh.cpp
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

#include "mesh.hpp"

using namespace feather::vulkan;

Mesh::Mesh() : Node(Node::Mesh)
{

}


Mesh::~Mesh()
{

}

void Mesh::build()
{
    m_vertexBuffer.clear();
    m_indexBuffer.clear();
    m_vertexBuffer.push_back({{1.0f,1.0f,0.0f},{0.0f,0.0f,1.0f},{0.0f,0.0f},{1.0f,0.0f,0.0f}});
    m_vertexBuffer.push_back({{-1.0f,1.0f,0.0f},{0.0f,0.0f,1.0f},{0.0f,0.0f},{1.0f,1.0f,0.0f}});
    m_vertexBuffer.push_back({{0.0f,-1.0f,0.0f},{0.0f,0.0f,1.0f},{0.0f,0.0f},{0.0f,0.0f,1.0f}});
    m_vertexBuffer.push_back({{2.0f,-1.0f,0.0f},{0.0f,0.0f,1.0f},{0.0f,0.0f},{0.0f,0.0f,1.0f}});
    m_indexBuffer = {{0},{1},{2},{0},{2},{3}};
    m_edgeBuffer = {{1},{1},{0},{0},{1},{1}};
}

void Mesh::buildVertex(VkDevice device, VkPhysicalDeviceMemoryProperties deviceMemoryProperties)
{
    int vertexBufferSize = m_vertexBuffer.size() * sizeof(Vertex);

    VkMemoryAllocateInfo memAlloc = {};
    memAlloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    memAlloc.pNext = NULL;
    memAlloc.allocationSize = 0;
    memAlloc.memoryTypeIndex = 0;
    VkMemoryRequirements memReqs;

    VkResult err;
    void *data;

    // Generate vertex buffer
    //	Setup
    VkBufferCreateInfo bufInfo = {};
    bufInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufInfo.pNext = NULL;
    bufInfo.size = vertexBufferSize;
    bufInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    bufInfo.flags = 0;
    //	Copy vertex data to VRAM
    //memset(&m_vertices, 0, sizeof(m_vertices));
    err = vkCreateBuffer(device, &bufInfo, nullptr, &m_pMeshBuffer->vertices.buf);
    assert(!err);
    vkGetBufferMemoryRequirements(device, m_pMeshBuffer->vertices.buf, &memReqs);
    memAlloc.allocationSize = memReqs.size;
    getMemoryType(deviceMemoryProperties, memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, &memAlloc.memoryTypeIndex);
    err = vkAllocateMemory(device, &memAlloc, nullptr, &m_pMeshBuffer->vertices.mem);
    assert(!err);
    err = vkMapMemory(device, m_pMeshBuffer->vertices.mem, 0, memAlloc.allocationSize, 0, &data);
    assert(!err);
    memcpy(data, m_vertexBuffer.data(), vertexBufferSize);
    vkUnmapMemory(device, m_pMeshBuffer->vertices.mem);
    err = vkBindBufferMemory(device, m_pMeshBuffer->vertices.buf, m_pMeshBuffer->vertices.mem, 0);
    assert(!err);
}

void Mesh::buildIndex(VkDevice device, VkPhysicalDeviceMemoryProperties deviceMemoryProperties)
{
    // Setup indices
    int indexBufferSize = m_indexBuffer.size() * sizeof(uint32_t);

    VkMemoryAllocateInfo memAlloc = {};
    memAlloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    memAlloc.pNext = NULL;
    memAlloc.allocationSize = 0;
    memAlloc.memoryTypeIndex = 0;
    VkMemoryRequirements memReqs;

    VkResult err;
    void *data;

    // Generate index buffer
    //	Setup
    VkBufferCreateInfo indexbufferInfo = {};
    indexbufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    indexbufferInfo.pNext = NULL;
    indexbufferInfo.size = indexBufferSize;
    indexbufferInfo.usage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
    indexbufferInfo.flags = 0;
    // Copy index data to VRAM
    //memset(&m_indices, 0, sizeof(m_indices));
    err = vkCreateBuffer(device, &indexbufferInfo, nullptr, &m_pMeshBuffer->indices.buf);
    assert(!err);
    vkGetBufferMemoryRequirements(device, m_pMeshBuffer->indices.buf, &memReqs);
    memAlloc.allocationSize = memReqs.size;
    getMemoryType(deviceMemoryProperties, memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, &memAlloc.memoryTypeIndex);
    err = vkAllocateMemory(device, &memAlloc, nullptr, &m_pMeshBuffer->indices.mem);
    assert(!err);
    err = vkMapMemory(device, m_pMeshBuffer->indices.mem, 0, indexBufferSize, 0, &data);
    assert(!err);
    memcpy(data, m_indexBuffer.data(), indexBufferSize);
    vkUnmapMemory(device, m_pMeshBuffer->indices.mem);
    err = vkBindBufferMemory(device, m_pMeshBuffer->indices.buf, m_pMeshBuffer->indices.mem, 0);
    assert(!err);
    m_pMeshBuffer->indexCount = m_indexBuffer.size();
}

void Mesh::buildEdge(VkDevice devic, VkPhysicalDeviceMemoryProperties deviceMemoryProperties)
{

}

void Mesh::prepareVertices(VkDevice device, VkPhysicalDeviceMemoryProperties deviceMemoryProperties)
{
    build();

    buildVertex(device, deviceMemoryProperties);
    buildIndex(device, deviceMemoryProperties);
}


void Mesh::updateVertices(VkDevice device, VkPhysicalDeviceMemoryProperties deviceMemoryProperties, float step)
{
    // free the vertex buffer
    vkDestroyBuffer(device, m_pMeshBuffer->vertices.buf, nullptr);
    vkFreeMemory(device, m_pMeshBuffer->vertices.mem, nullptr);

    //build();

    m_vertexBuffer.at(0)={{1.0f*step,1.0f*step,0.0f},{0.0f,0.0f,1.0f},{0.0f,0.0f},{1.0f,0.0f,0.0f}};
    buildVertex(device, deviceMemoryProperties);
}
