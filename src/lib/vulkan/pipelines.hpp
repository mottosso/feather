/***********************************************************************
 *
 * Filename: pipelines.hpp
 *
 * Description: holds all the pipelines for shaders.
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

#ifndef PIPELINES_HPP
#define PIPELINES_HPP

#include "deps.hpp"
#include "vulkan_deps.hpp"
#include "node.hpp"

#include "mesh.hpp"
#include "pointlight.hpp"


#define VERTEX_BUFFER_BIND_ID 0

namespace feather
{

    namespace vulkan
    {

        class Pipeline
        {
            public:
                enum Type { Point, Wire, Shade };

                Pipeline(
                        std::string shadeVertShader,
                        std::string shadeFragShader,
                        std::string wireVertShader,
                        std::string wireGeomShader,
                        std::string wireFragShader,
                        std::string pointVertShader,
                        std::string pointGeomShader,
                        std::string pointFragShader
                        );
                ~Pipeline();

                void cleanup(VkDevice device);
                void prepare(VkDevice device, VkPipelineCache cache, VkPipelineLayout layout, VkRenderPass renderPass, VkPipelineVertexInputStateCreateInfo* vi);
                VkPipelineShaderStageCreateInfo loadShader(VkDevice device, const char * fileName, VkShaderStageFlagBits stage);
                VkPipeline shade() { return m_shade; };
                VkPipeline wire() { return m_wire; };
                VkPipeline point() { return m_point; };

            private:
                // shade
                std::string m_shadeVertShader;
                std::string m_shadeFragShader;
                // wire
                std::string m_wireVertShader;
                std::string m_wireFragShader;
                std::string m_wireGeomShader;
                // point
                std::string m_pointVertShader;
                std::string m_pointFragShader;
                std::string m_pointGeomShader;

                std::vector<VkShaderModule> m_shaderModules;

                // pipelines
                VkPipeline m_shade;
                VkPipeline m_point;
                VkPipeline m_wire;
        };

        class Pipelines
        {
            public:
                Pipelines();
                ~Pipelines();
                void cleanup(VkDevice device);
                void bind(VkDevice device, VkCommandBuffer buffer, Node* node, VkDeviceSize offset[1]);
                void prepare(VkDevice device, VkRenderPass renderPass, VkPipelineVertexInputStateCreateInfo* vi);
                //VkPipeline pipeline(Node::Type node);
                void createCache(VkDevice device);
                void createLayout(VkDevice device, VkPipelineLayoutCreateInfo info);
                VkPipelineLayout layout() { return m_pipelineLayout; };

            private:
                VkPipelineCache m_pipelineCache;
                VkPipelineLayout m_pipelineLayout;

                void bindMesh(VkDevice device, VkCommandBuffer buffer, Node* node, VkDeviceSize offsets[1]);
                void bindLight(VkDevice device, VkCommandBuffer buffer, Node* node, VkDeviceSize offsets[1]);
                VkPipelineShaderStageCreateInfo loadShader(VkDevice device, const char * fileName, VkShaderStageFlagBits stage);
                //void bindPipeline(VkCommandBuffer buffer, Node* node, Pipeline::Type type);

                //std::vector<VkShaderModule> m_shaderModules;
                /* 
                struct {
                    VkPipeline wire;
                    VkPipeline point;
                    VkPipeline solid;
                } m_meshPipelines;

                struct {
                    VkPipeline wire;
                    VkPipeline point;
                    VkPipeline solid;
                } m_lightPipelines;
                */
                Pipeline m_meshPipeline = Pipeline(
                        "shaders/spv/shade.mesh.vert.spv",
                        "shaders/spv/shade.mesh.frag.spv",
                        "shaders/spv/wire.mesh.vert.spv",
                        "shaders/spv/wire.mesh.frag.spv",
                        "shaders/spv/wire.mesh.geom.spv",
                        "shaders/spv/point.mesh.vert.spv",
                        "shaders/spv/point.mesh.frag.spv",
                        "shaders/spv/point.mesh.geom.spv"
                        );
                Pipeline m_lightPipeline = Pipeline(
                        "shaders/spv/shade.light.vert.spv",
                        "shaders/spv/shade.light.frag.spv",
                        "shaders/spv/wire.light.vert.spv",
                        "shaders/spv/wire.light.frag.spv",
                        "shaders/spv/wire.light.geom.spv",
                        "shaders/spv/point.light.vert.spv",
                        "shaders/spv/point.light.frag.spv",
                        "shaders/spv/point.light.geom.spv"
                        );
 
        };

    } // namespace vulkan

} // namespace feather

#endif
