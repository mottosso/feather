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
    m_vertexBuffer.push_back({{1.0f,1.0f,0.0f},{0.0f,0.0f,1.0f},{0.0f,0.0f},{1.0f,0.0f,0.0f},1});
    m_vertexBuffer.push_back({{-1.0f,1.0f,0.0f},{0.0f,0.0f,1.0f},{0.0f,0.0f},{1.0f,1.0f,0.0f},1});
    m_vertexBuffer.push_back({{0.0f,-1.0f,0.0f},{0.0f,0.0f,1.0f},{0.0f,0.0f},{0.0f,0.0f,1.0f},1});
    m_vertexBuffer.push_back({{2.0f,-1.0f,0.0f},{0.0f,0.0f,1.0f},{0.0f,0.0f},{0.0f,0.0f,1.0f},0});
    m_indexBuffer = {{0},{1},{2},{0},{2},{3}};
    m_edgeBuffer = {{0},{1},{1},{2},{2},{3},{3},{0}};
}

void Mesh::prepareVertices(VkDevice device, VkPhysicalDeviceMemoryProperties deviceMemoryProperties)
{
    build();

    buildVertex(device, deviceMemoryProperties);
    buildIndex(device, deviceMemoryProperties);
    buildEdge(device, deviceMemoryProperties);
}

void Mesh::updateVertices(VkDevice device, VkPhysicalDeviceMemoryProperties deviceMemoryProperties, float step)
{
    // free the vertex buffer
    vkDestroyBuffer(device, m_pMeshBuffer->vertices.buf, nullptr);
    vkFreeMemory(device, m_pMeshBuffer->vertices.mem, nullptr);

    //build();

    m_vertexBuffer.at(0)={{1.0f*step,1.0f*step,0.0f},{0.0f,0.0f,1.0f},{0.0f,0.0f},{1.0f,0.0f,0.0f},1};
    buildVertex(device, deviceMemoryProperties);
}

void Mesh::loadShaders()
{

}
