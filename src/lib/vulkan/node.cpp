/***********************************************************************
 *
 * Filename: node.cpp
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

#include "node.hpp"

using namespace feather::vulkan;

Node::Node()
{

}

Node::~Node()
{

}

void Node::prepareVertices(VkDevice device, VkPhysicalDeviceMemoryProperties deviceMemoryProperties, MeshBuffer* meshBuffer)
{
    struct Vertex {
        float pos[3];
        float norm[3];
        float uv[2];
        float col[3];
    };

    //std::vector<float> vertexBuffer;
    //loadMesh(vertexBuffer);

    std::vector<Vertex> vertexBuffer = {
        { {1.0f,1.0f,0.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f},{1.0f,0.0f,0.0f} },
        { {-1.0f,1.0f,0.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f},{1.0f,1.0f,0.0f} },
        { {0.0f,-1.0f,0.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f},{0.0f,0.0f,1.0f} },
        { {2.0f,-1.0f,0.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f},{0.0f,0.0f,1.0f} }
    };
    
    /*
    // Setup vertices
    std::vector<Vertex> vertexBuffer = {
        { { 1.0f,  1.0f, 0.0f },{ 1.0f, 0.0f, 0.0f } },
        { { -1.0f,  1.0f, 0.0f },{ 0.0f, 1.0f, 0.0f } },
        { { 0.0f, -1.0f, 0.0f },{ 0.0f, 0.0f, 1.0f } },
        { { 2.0f, -1.0f, 0.0f },{ 0.0f, 0.0f, 1.0f } }
    };
    */

    int vertexBufferSize = vertexBuffer.size() * sizeof(Vertex);

    // Setup indices
    //std::vector<uint32_t> indexBuffer = { 0, 1, 2, 0, 2, 3 };
    std::vector<uint32_t> indexBuffer = { 0, 1, 2, 0, 2, 3 };
    int indexBufferSize = indexBuffer.size() * sizeof(uint32_t);

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
    err = vkCreateBuffer(device, &bufInfo, nullptr, &meshBuffer->vertices.buf);
    assert(!err);
    vkGetBufferMemoryRequirements(device, meshBuffer->vertices.buf, &memReqs);
    memAlloc.allocationSize = memReqs.size;
    getMemoryType(deviceMemoryProperties, memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, &memAlloc.memoryTypeIndex);
    err = vkAllocateMemory(device, &memAlloc, nullptr, &meshBuffer->vertices.mem);
    assert(!err);
    err = vkMapMemory(device, meshBuffer->vertices.mem, 0, memAlloc.allocationSize, 0, &data);
    assert(!err);
    memcpy(data, vertexBuffer.data(), vertexBufferSize);
    vkUnmapMemory(device, meshBuffer->vertices.mem);
    err = vkBindBufferMemory(device, meshBuffer->vertices.buf, meshBuffer->vertices.mem, 0);
    assert(!err);

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
    err = vkCreateBuffer(device, &indexbufferInfo, nullptr, &meshBuffer->indices.buf);
    assert(!err);
    vkGetBufferMemoryRequirements(device, meshBuffer->indices.buf, &memReqs);
    memAlloc.allocationSize = memReqs.size;
    getMemoryType(deviceMemoryProperties, memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, &memAlloc.memoryTypeIndex);
    err = vkAllocateMemory(device, &memAlloc, nullptr, &meshBuffer->indices.mem);
    assert(!err);
    err = vkMapMemory(device, meshBuffer->indices.mem, 0, indexBufferSize, 0, &data);
    assert(!err);
    memcpy(data, indexBuffer.data(), indexBufferSize);
    vkUnmapMemory(device, meshBuffer->indices.mem);
    err = vkBindBufferMemory(device, meshBuffer->indices.buf, meshBuffer->indices.mem, 0);
    assert(!err);
    meshBuffer->indexCount = indexBuffer.size();
}


VkBool32 Node::getMemoryType(VkPhysicalDeviceMemoryProperties deviceMemoryProperties, uint32_t typeBits, VkFlags properties, uint32_t *typeIndex)
{
    for (uint32_t i = 0; i < 32; i++)
    {
        if ((typeBits & 1) == 1)
        {
            if ((deviceMemoryProperties.memoryTypes[i].propertyFlags & properties) == properties)
            {
                *typeIndex = i;
                return true;
            }
        }
        typeBits >>= 1;
    }
    return false;
}


void Node::updateVertices(VkDevice device, VkPhysicalDeviceMemoryProperties deviceMemoryProperties, MeshBuffer* meshBuffer, float step)
{
    // free the vertex buffer
    vkDestroyBuffer(device, meshBuffer->vertices.buf, nullptr);
    vkFreeMemory(device, meshBuffer->vertices.mem, nullptr);
    /*
    if (meshBuffer->indices.buf != VK_NULL_HANDLE)
    {
        vkDestroyBuffer(device, meshBuffer->indices.buf, nullptr);
        vkFreeMemory(device, meshBuffer->indices.mem, nullptr);
    }
    */

    /*
    struct Vertex {
        float pos[3];
        float col[3];
    };

    // Setup vertices
    std::vector<Vertex> vertexBuffer = {
        { { 1.0f * step,  1.0f * step, 0.0f },{ 1.0f, 0.0f, 0.0f } },
        { { -1.0f,  1.0f, 0.0f },{ 0.0f, 1.0f, 0.0f } },
        { { 0.0f, -1.0f, 0.0f },{ 0.0f, 0.0f, 1.0f } },
        { { 2.0f, -1.0f, 0.0f },{ 0.0f, 0.0f, 1.0f } }
    };
    */

    struct Vertex {
        float pos[3];
        float norm[3];
        float uv[2];
        float col[3];
    };

    std::vector<Vertex> vertexBuffer = {
        { {1.0f * step,1.0f * step,0.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f},{1.0f,0.0f,0.0f} },
        { {-1.0f,1.0f,0.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f},{1.0f,1.0f,0.0f} },
        { {0.0f,-1.0f,0.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f},{0.0f,0.0f,1.0f} },
        { {2.0f,-1.0f,0.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f},{0.0f,0.0f,1.0f} }
    };
 
    //std::vector<float> vertexBuffer;
    //loadMesh(vertexBuffer);

    int vertexBufferSize = vertexBuffer.size() * sizeof(Vertex);

    // Setup indices
    //std::vector<uint32_t> indexBuffer = { 0, 1, 2, 0, 2, 3 };
    std::vector<uint32_t> indexBuffer = { 0, 1, 2, 0, 2, 3 };
    int indexBufferSize = indexBuffer.size() * sizeof(uint32_t);

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
    err = vkCreateBuffer(device, &bufInfo, nullptr, &meshBuffer->vertices.buf);
    assert(!err);
    vkGetBufferMemoryRequirements(device, meshBuffer->vertices.buf, &memReqs);
    memAlloc.allocationSize = memReqs.size;
    getMemoryType(deviceMemoryProperties, memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, &memAlloc.memoryTypeIndex);
    err = vkAllocateMemory(device, &memAlloc, nullptr, &meshBuffer->vertices.mem);
    assert(!err);
    err = vkMapMemory(device, meshBuffer->vertices.mem, 0, memAlloc.allocationSize, 0, &data);
    assert(!err);
    memcpy(data, vertexBuffer.data(), vertexBufferSize);
    vkUnmapMemory(device, meshBuffer->vertices.mem);
    err = vkBindBufferMemory(device, meshBuffer->vertices.buf, meshBuffer->vertices.mem, 0);
    assert(!err);
}

void Node::loadMesh(std::vector<float>& vertexBuffer)
{
    // TESTING

    // p1
    // position
    vertexBuffer.push_back(0.0); // x
    vertexBuffer.push_back(1.0); // y
    vertexBuffer.push_back(0.0); // z
    // normal 
    vertexBuffer.push_back(0.0); // x
    vertexBuffer.push_back(1.0); // y
    vertexBuffer.push_back(0.0); // z
    // uv 
    vertexBuffer.push_back(0.0); // s
    vertexBuffer.push_back(1.0); // t
    // color 
    vertexBuffer.push_back(1.0); // r
    vertexBuffer.push_back(0.0); // g
    vertexBuffer.push_back(0.0); // b

    // p2
    // position
    vertexBuffer.push_back(0.0); // x
    vertexBuffer.push_back(0.0); // y
    vertexBuffer.push_back(0.0); // z
    // normal 
    vertexBuffer.push_back(0.0); // x
    vertexBuffer.push_back(1.0); // y
    vertexBuffer.push_back(0.0); // z
    // uv 
    vertexBuffer.push_back(0.0); // s
    vertexBuffer.push_back(1.0); // t
    // color 
    vertexBuffer.push_back(0.0); // r
    vertexBuffer.push_back(1.0); // g
    vertexBuffer.push_back(0.0); // b
 
    // p3
    // position
    vertexBuffer.push_back(1.0); // x
    vertexBuffer.push_back(0.0); // y
    vertexBuffer.push_back(0.0); // z
    // normal 
    vertexBuffer.push_back(0.0); // x
    vertexBuffer.push_back(1.0); // y
    vertexBuffer.push_back(0.0); // z
    // uv 
    vertexBuffer.push_back(0.0); // s
    vertexBuffer.push_back(1.0); // t
    // color 
    vertexBuffer.push_back(0.0); // r
    vertexBuffer.push_back(0.0); // g
    vertexBuffer.push_back(1.0); // b
 
    // p3
    // position
    vertexBuffer.push_back(1.0); // x
    vertexBuffer.push_back(1.0); // y
    vertexBuffer.push_back(0.0); // z
    // normal 
    vertexBuffer.push_back(0.0); // x
    vertexBuffer.push_back(1.0); // y
    vertexBuffer.push_back(0.0); // z
    // uv 
    vertexBuffer.push_back(0.0); // s
    vertexBuffer.push_back(1.0); // t
    // color 
    vertexBuffer.push_back(1.0); // r
    vertexBuffer.push_back(0.0); // g
    vertexBuffer.push_back(1.0); // b
}
