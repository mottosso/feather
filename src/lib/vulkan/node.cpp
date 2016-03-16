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

Node::Node(VkDevice* device) :
m_device(device)
{

}

Node::~Node()
{

}

void Node::prepareVertices()
{
    struct Vertex {
        float pos[3];
        float col[3];
    };

    // Setup vertices
    std::vector<Vertex> vertexBuffer = {
        { { 1.0f,  1.0f, 0.0f },{ 1.0f, 0.0f, 0.0f } },
        { { -1.0f,  1.0f, 0.0f },{ 0.0f, 1.0f, 0.0f } },
        { { 0.0f, -1.0f, 0.0f },{ 0.0f, 0.0f, 1.0f } }
    };
    int vertexBufferSize = vertexBuffer.size() * sizeof(Vertex);

    // Setup indices
    std::vector<uint32_t> indexBuffer = { 0, 1, 2 };
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
    memset(&m_vertices, 0, sizeof(m_vertices));
    err = vkCreateBuffer(*m_device, &bufInfo, nullptr, &m_vertices.buf);
    assert(!err);
    vkGetBufferMemoryRequirements(*m_device, m_vertices.buf, &memReqs);
    memAlloc.allocationSize = memReqs.size;
    getMemoryType(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, &memAlloc.memoryTypeIndex);
    err = vkAllocateMemory(*m_device, &memAlloc, nullptr, &m_vertices.mem);
    assert(!err);
    err = vkMapMemory(*m_device, m_vertices.mem, 0, memAlloc.allocationSize, 0, &data);
    assert(!err);
    memcpy(data, vertexBuffer.data(), vertexBufferSize);
    vkUnmapMemory(*m_device, m_vertices.mem);
    err = vkBindBufferMemory(*m_device, m_vertices.buf, m_vertices.mem, 0);
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
    memset(&m_indices, 0, sizeof(m_indices));
    err = vkCreateBuffer(*m_device, &indexbufferInfo, nullptr, &m_indices.buf);
    assert(!err);
    vkGetBufferMemoryRequirements(*m_device, m_indices.buf, &memReqs);
    memAlloc.allocationSize = memReqs.size;
    getMemoryType(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, &memAlloc.memoryTypeIndex);
    err = vkAllocateMemory(*m_device, &memAlloc, nullptr, &m_indices.mem);
    assert(!err);
    err = vkMapMemory(*m_device, m_indices.mem, 0, indexBufferSize, 0, &data);
    assert(!err);
    memcpy(data, indexBuffer.data(), indexBufferSize);
    vkUnmapMemory(*m_device, m_indices.mem);
    err = vkBindBufferMemory(*m_device, m_indices.buf, m_indices.mem, 0);
    assert(!err);
    m_indices.count = indexBuffer.size();

    // Putting this back into the Window for now
    /*
    // Binding description
    m_vertices.bindingDescriptions.resize(1);
    m_vertices.bindingDescriptions[0].binding = VERTEX_BUFFER_BIND_ID;
    m_vertices.bindingDescriptions[0].stride = sizeof(Vertex);
    m_vertices.bindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    // Attribute descriptions
    // Describes memory layout and shader attribute locations
    m_vertices.attributeDescriptions.resize(2);
    // Location 0 : Position
    m_vertices.attributeDescriptions[0].binding = VERTEX_BUFFER_BIND_ID;
    m_vertices.attributeDescriptions[0].location = 0;
    m_vertices.attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
    m_vertices.attributeDescriptions[0].offset = 0;
    m_vertices.attributeDescriptions[0].binding = 0;
    // Location 1 : Color
    m_vertices.attributeDescriptions[1].binding = VERTEX_BUFFER_BIND_ID;
    m_vertices.attributeDescriptions[1].location = 1;
    m_vertices.attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
    m_vertices.attributeDescriptions[1].offset = sizeof(float) * 3;
    m_vertices.attributeDescriptions[1].binding = 0;

    // Assign to vertex buffer
    m_vertices.vi.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    m_vertices.vi.pNext = NULL;
    m_vertices.vi.vertexBindingDescriptionCount = m_vertices.bindingDescriptions.size();
    m_vertices.vi.pVertexBindingDescriptions = m_vertices.bindingDescriptions.data();
    m_vertices.vi.vertexAttributeDescriptionCount = m_vertices.attributeDescriptions.size();
    m_vertices.vi.pVertexAttributeDescriptions = m_vertices.attributeDescriptions.data();
    */

}
