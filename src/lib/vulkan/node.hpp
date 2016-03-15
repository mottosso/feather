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

#ifndef MESH_HPP
#define MESH_HPP

#include "deps.hpp"
#include "vulkan_deps.hpp"

namespace feather
{

    namespace vulkan
    {

        class Node
        {
            public:
                Node(VkDevice* device=0, VkQueue* queue=0, VkInstance* m_instance=0);
                ~Node();
                bool prepare();
                void render();
                void viewChanged();

            protected:
                // vulkan system
                VkDevice* m_device;
                VkQueue m_queue;
                VkInstance m_instance;
 
                // node methods and members
                void prepareSemaphore();
                void prepareVertices();
                void prepareUniformBuffers();
                void setupDescriptorSetLayout();
                void preparePipelines();
                void setupDescriptorPool();
                void setupDescriptorSet();
                void buildCommandBuffers();

                void updateUniformBuffers();
                VkPipelineShaderStageCreateInfo loadShader(const char * fileName, VkShaderStageFlagBits stage);

                void draw();

                struct {
                    VkBuffer buf;
                    VkDeviceMemory mem;
                    VkPipelineVertexInputStateCreateInfo vi;
                    std::vector<VkVertexInputBindingDescription> bindingDescriptions;
                    std::vector<VkVertexInputAttributeDescription> attributeDescriptions;
                } m_vertices;

                struct {
                    int count;
                    VkBuffer buf;
                    VkDeviceMemory mem;
                } m_indices;

                struct {
                    VkBuffer buffer;
                    VkDeviceMemory memory;
                    VkDescriptorBufferInfo descriptor;
                }  m_uniformDataVS;

                struct {
                    glm::mat4 projectionMatrix;
                    glm::mat4 modelMatrix;
                    glm::mat4 viewMatrix;
                } m_uboVS;

                struct {
                    VkPipeline solid;
                } m_pipelines;


        };

    } // namespace vulkan

} // namespace feather

#endif
