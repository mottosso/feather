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

Node::Node(VkDevice* device, VkQueue* queue, VkInstance* m_instance) :
m_device(device),
m_queue(queue),
m_instance(instance)
{

}

Node::~Node()
{

}

bool Node::prepare()
{
    // don't prepare if we are missing vulkan components
    if(!m_device || !m_queue|| !m_instance)
        return false;

    prepareSemaphore();
    prepareVertices();
    prepareUniformBuffers();
    setupDescriptorSetLayout();
    preparePipelines();
    setupDescriptorPool();
    setupDescriptorSet();
    buildCommandBuffers();
    return true;
}

void Node::render()
{
    vkDeviceWaitIdle(m_device);
    draw();
    vkDeviceWaitIdle(m_device);
}

void Node::viewChanged()
{
    updateUniformBuffers();
}

void Node::prepareSemaphore()
{
    VkSemaphoreCreateInfo semaphoreCreateInfo = {};
    semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    semaphoreCreateInfo.pNext = NULL;

    // This semaphore ensures that the image is complete
    // before starting to submit again
    VkResult err = vkCreateSemaphore(m_device, &semaphoreCreateInfo, nullptr, &m_semaphores.presentComplete);
    assert(!err);

    // This semaphore ensures that all commands submitted
    // have been finished before submitting the image to the queue
    err = vkCreateSemaphore(m_device, &semaphoreCreateInfo, nullptr, &m_semaphores.renderComplete);
    assert(!err);
}

void Node::prepareVertices()
{
    // TODO replace this with the mesh vertex
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
    err = vkCreateBuffer(m_device, &bufInfo, nullptr, &m_vertices.buf);
    assert(!err);
    vkGetBufferMemoryRequirements(m_device, m_vertices.buf, &memReqs);
    memAlloc.allocationSize = memReqs.size;
    getMemoryType(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, &memAlloc.memoryTypeIndex);
    err = vkAllocateMemory(m_device, &memAlloc, nullptr, &m_vertices.mem);
    assert(!err);
    err = vkMapMemory(m_device, m_vertices.mem, 0, memAlloc.allocationSize, 0, &data);
    assert(!err);
    memcpy(data, vertexBuffer.data(), vertexBufferSize);
    vkUnmapMemory(m_device, m_vertices.mem);
    err = vkBindBufferMemory(m_device, m_vertices.buf, m_vertices.mem, 0);
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
    err = vkCreateBuffer(m_device, &indexbufferInfo, nullptr, &m_indices.buf);
    assert(!err);
    vkGetBufferMemoryRequirements(m_device, m_indices.buf, &memReqs);
    memAlloc.allocationSize = memReqs.size;
    getMemoryType(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, &memAlloc.memoryTypeIndex);
    err = vkAllocateMemory(m_device, &memAlloc, nullptr, &m_indices.mem);
    assert(!err);
    err = vkMapMemory(m_device, m_indices.mem, 0, indexBufferSize, 0, &data);
    assert(!err);
    memcpy(data, indexBuffer.data(), indexBufferSize);
    vkUnmapMemory(m_device, m_indices.mem);
    err = vkBindBufferMemory(m_device, m_indices.buf, m_indices.mem, 0);
    assert(!err);
    m_indices.count = indexBuffer.size();

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
}

void Node::prepareUniformBuffers()
{
    // Prepare and initialize uniform buffer containing shader uniforms
    VkMemoryRequirements memReqs;

    // Vertex shader uniform buffer block
    VkBufferCreateInfo bufferInfo = {};
    VkMemoryAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.pNext = NULL;
    allocInfo.allocationSize = 0;
    allocInfo.memoryTypeIndex = 0;
    VkResult err;

    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = sizeof(m_uboVS);
    bufferInfo.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;

    // Create a new buffer
    err = vkCreateBuffer(m_device, &bufferInfo, nullptr, &m_uniformDataVS.buffer);
    assert(!err);
    // Get memory requirements including size, alignment and memory type 
    vkGetBufferMemoryRequirements(m_device, m_uniformDataVS.buffer, &memReqs);
    allocInfo.allocationSize = memReqs.size;
    // Gets the appropriate memory type for this type of buffer allocation
    // Only memory types that are visible to the host
    getMemoryType(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, &allocInfo.memoryTypeIndex);
    // Allocate memory for the uniform buffer
    err = vkAllocateMemory(m_device, &allocInfo, nullptr, &(m_uniformDataVS.memory));
    assert(!err);
    // Bind memory to buffer
    err = vkBindBufferMemory(m_device, m_uniformDataVS.buffer, m_uniformDataVS.memory, 0);
    assert(!err);

    // Store information in the uniform's descriptor
    m_uniformDataVS.descriptor.buffer = m_uniformDataVS.buffer;
    m_uniformDataVS.descriptor.offset = 0;
    m_uniformDataVS.descriptor.range = sizeof(m_uboVS);

    updateUniformBuffers();
}

void Node::updateUniformBuffers()
{
    // Update matrices
    m_uboVS.projectionMatrix = glm::perspective(glm::radians(60.0f), (float)m_width / (float)m_height, 0.1f, 256.0f);

    m_uboVS.viewMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, m_zoom));

    m_uboVS.modelMatrix = glm::mat4();
    m_uboVS.modelMatrix = glm::rotate(m_uboVS.modelMatrix, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    m_uboVS.modelMatrix = glm::rotate(m_uboVS.modelMatrix, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    m_uboVS.modelMatrix = glm::rotate(m_uboVS.modelMatrix, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    // Map uniform buffer and update it
    uint8_t *pData;
    VkResult err = vkMapMemory(m_device, m_uniformDataVS.memory, 0, sizeof(m_uboVS), 0, (void **)&pData);
    assert(!err);
    memcpy(pData, &m_uboVS, sizeof(m_uboVS));
    vkUnmapMemory(m_device, m_uniformDataVS.memory);
    assert(!err);
}


void Node::setupDescriptorSetLayout()
{
    // Setup layout of descriptors used in this example
    // Basically connects the different shader stages to descriptors
    // for binding uniform buffers, image samplers, etc.
    // So every shader binding should map to one descriptor set layout
    // binding

    // Binding 0 : Uniform buffer (Vertex shader)
    VkDescriptorSetLayoutBinding layoutBinding = {};
    layoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    layoutBinding.descriptorCount = 1;
    layoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    layoutBinding.pImmutableSamplers = NULL;

    VkDescriptorSetLayoutCreateInfo descriptorLayout = {};
    descriptorLayout.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    descriptorLayout.pNext = NULL;
    descriptorLayout.bindingCount = 1;
    descriptorLayout.pBindings = &layoutBinding;

    VkResult err = vkCreateDescriptorSetLayout(m_device, &descriptorLayout, NULL, &m_descriptorSetLayout);
    assert(!err);

    // Create the pipeline layout that is used to generate the rendering pipelines that
    // are based on this descriptor set layout
    // In a more complex scenario you would have different pipeline layouts for different
    // descriptor set layouts that could be reused
    VkPipelineLayoutCreateInfo pPipelineLayoutCreateInfo = {};
    pPipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pPipelineLayoutCreateInfo.pNext = NULL;
    pPipelineLayoutCreateInfo.setLayoutCount = 1;
    pPipelineLayoutCreateInfo.pSetLayouts = &m_descriptorSetLayout;

    err = vkCreatePipelineLayout(m_device, &pPipelineLayoutCreateInfo, nullptr, &m_pipelineLayout);
    assert(!err);
}

void Node::preparePipelines()
{
    // Create our rendering pipeline used in this example
    // Vulkan uses the concept of rendering pipelines to encapsulate
    // fixed states
    // This replaces OpenGL's huge (and cumbersome) state machine
    // A pipeline is then stored and hashed on the GPU making
    // pipeline changes much faster than having to set dozens of 
    // states
    // In a real world application you'd have dozens of pipelines
    // for every shader set used in a scene
    // Note that there are a few states that are not stored with
    // the pipeline. These are called dynamic states and the 
    // pipeline only stores that they are used with this pipeline,
    // but not their states

    VkGraphicsPipelineCreateInfo pipelineCreateInfo = {};

    VkResult err;

    pipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    // The layout used for this pipeline
    pipelineCreateInfo.layout = m_pipelineLayout;
    // Renderpass this pipeline is attached to
    pipelineCreateInfo.renderPass = m_renderPass;

    // Vertex input state
    // Describes the topoloy used with this pipeline
    VkPipelineInputAssemblyStateCreateInfo inputAssemblyState = {};
    inputAssemblyState.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    // This pipeline renders vertex data as triangle lists
    inputAssemblyState.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

    // Rasterization state
    VkPipelineRasterizationStateCreateInfo rasterizationState = {};
    rasterizationState.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    // Solid polygon mode
    rasterizationState.polygonMode = VK_POLYGON_MODE_FILL;
    // No culling
    rasterizationState.cullMode = VK_CULL_MODE_NONE;
    rasterizationState.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    rasterizationState.depthClampEnable = VK_FALSE;
    rasterizationState.rasterizerDiscardEnable = VK_FALSE;
    rasterizationState.depthBiasEnable = VK_FALSE;

    // Color blend state
    // Describes blend modes and color masks
    VkPipelineColorBlendStateCreateInfo colorBlendState = {};
    colorBlendState.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    // One blend attachment state
    // Blending is not used in this example
    VkPipelineColorBlendAttachmentState blendAttachmentState[1] = {};
    blendAttachmentState[0].colorWriteMask = 0xf;
    blendAttachmentState[0].blendEnable = VK_FALSE;
    colorBlendState.attachmentCount = 1;
    colorBlendState.pAttachments = blendAttachmentState;

    // Viewport state
    VkPipelineViewportStateCreateInfo viewportState = {};
    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    // One viewport
    viewportState.viewportCount = 1;
    // One scissor rectangle
    viewportState.scissorCount = 1;

    // Enable dynamic states
    // Describes the dynamic states to be used with this pipeline
    // Dynamic states can be set even after the pipeline has been created
    // So there is no need to create new pipelines just for changing
    // a viewport's dimensions or a scissor box
    VkPipelineDynamicStateCreateInfo dynamicState = {};
    // The dynamic state properties themselves are stored in the command buffer
    std::vector<VkDynamicState> dynamicStateEnables;
    dynamicStateEnables.push_back(VK_DYNAMIC_STATE_VIEWPORT);
    dynamicStateEnables.push_back(VK_DYNAMIC_STATE_SCISSOR);
    dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicState.pDynamicStates = dynamicStateEnables.data();
    dynamicState.dynamicStateCount = dynamicStateEnables.size();

    // Depth and stencil state
    // Describes depth and stenctil test and compare ops
    VkPipelineDepthStencilStateCreateInfo depthStencilState = {};
    // Basic depth compare setup with depth writes and depth test enabled
    // No stencil used 
    depthStencilState.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    depthStencilState.depthTestEnable = VK_TRUE;
    depthStencilState.depthWriteEnable = VK_TRUE;
    depthStencilState.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
    depthStencilState.depthBoundsTestEnable = VK_FALSE;
    depthStencilState.back.failOp = VK_STENCIL_OP_KEEP;
    depthStencilState.back.passOp = VK_STENCIL_OP_KEEP;
    depthStencilState.back.compareOp = VK_COMPARE_OP_ALWAYS;
    depthStencilState.stencilTestEnable = VK_FALSE;
    depthStencilState.front = depthStencilState.back;

    // Multi sampling state
    VkPipelineMultisampleStateCreateInfo multisampleState = {};
    multisampleState.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampleState.pSampleMask = NULL;
    // No multi sampling used in this example
    multisampleState.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    // Load shaders
    // Shaders are loaded from the SPIR-V format, which can be generated from glsl
    VkPipelineShaderStageCreateInfo shaderStages[2] = { {},{} };
    shaderStages[0] = loadShader("shaders/spv/triangle.vert.spv", VK_SHADER_STAGE_VERTEX_BIT);
    shaderStages[1] = loadShader("shaders/spv/triangle.frag.spv", VK_SHADER_STAGE_FRAGMENT_BIT);

    // Assign states
    // Two shader stages
    pipelineCreateInfo.stageCount = 2;
    // Assign pipeline state create information
    pipelineCreateInfo.pVertexInputState = &m_vertices.vi;
    pipelineCreateInfo.pInputAssemblyState = &inputAssemblyState;
    pipelineCreateInfo.pRasterizationState = &rasterizationState;
    pipelineCreateInfo.pColorBlendState = &colorBlendState;
    pipelineCreateInfo.pMultisampleState = &multisampleState;
    pipelineCreateInfo.pViewportState = &viewportState;
    pipelineCreateInfo.pDepthStencilState = &depthStencilState;
    pipelineCreateInfo.pStages = shaderStages;
    pipelineCreateInfo.renderPass = m_renderPass;
    pipelineCreateInfo.pDynamicState = &dynamicState;

    // Create rendering pipeline
    err = vkCreateGraphicsPipelines(m_device, m_pipelineCache, 1, &pipelineCreateInfo, nullptr, &m_pipelines.solid);
    assert(!err);
}

VkPipelineShaderStageCreateInfo Node::loadShader(const char * fileName, VkShaderStageFlagBits stage)
{
    VkPipelineShaderStageCreateInfo shaderStage = {};
    shaderStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStage.stage = stage;
    shaderStage.module = feather::vulkan::tools::loadShader(fileName, m_device, stage);
    shaderStage.pName = "main"; // todo : make param
    assert(shaderStage.module != NULL);
    m_shaderModules.push_back(shaderStage.module);
    return shaderStage;
}

void Node::setupDescriptorPool()
{
    // We need to tell the API the number of max. requested descriptors per type
    VkDescriptorPoolSize typeCounts[1];
    // This example only uses one descriptor type (uniform buffer) and only
    // requests one descriptor of this type
    typeCounts[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    typeCounts[0].descriptorCount = 1;
    // For additional types you need to add new entries in the type count list
    // E.g. for two combined image samplers :
    // typeCounts[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    // typeCounts[1].descriptorCount = 2;

    // Create the global descriptor pool
    // All descriptors used in this example are allocated from this pool
    VkDescriptorPoolCreateInfo descriptorPoolInfo = {};
    descriptorPoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    descriptorPoolInfo.pNext = NULL;
    descriptorPoolInfo.poolSizeCount = 1;
    descriptorPoolInfo.pPoolSizes = typeCounts;
    // Set the max. number of sets that can be requested
    // Requesting descriptors beyond maxSets will result in an error
    descriptorPoolInfo.maxSets = 1;

    VkResult vkRes = vkCreateDescriptorPool(m_device, &descriptorPoolInfo, nullptr, &m_descriptorPool);
    assert(!vkRes);
}

void Node::setupDescriptorSet()
{
    // Update descriptor sets determining the shader binding points
    // For every binding point used in a shader there needs to be one
    // descriptor set matching that binding point
    VkWriteDescriptorSet writeDescriptorSet = {};

    VkDescriptorSetAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = m_descriptorPool;
    allocInfo.descriptorSetCount = 1;
    allocInfo.pSetLayouts = &m_descriptorSetLayout;

    VkResult vkRes = vkAllocateDescriptorSets(m_device, &allocInfo, &m_descriptorSet);
    assert(!vkRes);

    // Binding 0 : Uniform buffer
    writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writeDescriptorSet.dstSet = m_descriptorSet;
    writeDescriptorSet.descriptorCount = 1;
    writeDescriptorSet.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    writeDescriptorSet.pBufferInfo = &m_uniformDataVS.descriptor;
    // Binds this uniform buffer to binding point 0
    writeDescriptorSet.dstBinding = 0;

    vkUpdateDescriptorSets(m_device, 1, &writeDescriptorSet, 0, NULL);
}

void Node::buildCommandBuffers()
{
    VkCommandBufferBeginInfo cmdBufInfo = {};
    cmdBufInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    cmdBufInfo.pNext = NULL;

    VkClearValue clearValues[2];
    clearValues[0].color = m_defaultClearColor;
    clearValues[1].depthStencil = { 1.0f, 0 };

    VkRenderPassBeginInfo renderPassBeginInfo = {};
    renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassBeginInfo.pNext = NULL;
    renderPassBeginInfo.renderPass = m_renderPass;
    renderPassBeginInfo.renderArea.offset.x = 0;
    renderPassBeginInfo.renderArea.offset.y = 0;
    renderPassBeginInfo.renderArea.extent.width = m_width;
    renderPassBeginInfo.renderArea.extent.height = m_height;
    renderPassBeginInfo.clearValueCount = 2;
    renderPassBeginInfo.pClearValues = clearValues;

    VkResult err;

    for (int32_t i = 0; i < m_drawCommandBuffers.size(); ++i)
    {
        // Set target frame buffer
        renderPassBeginInfo.framebuffer = m_aFrameBuffers[i];

        err = vkBeginCommandBuffer(m_drawCommandBuffers[i], &cmdBufInfo);
        assert(!err);

        vkCmdBeginRenderPass(m_drawCommandBuffers[i], &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

        // Update dynamic viewport state
        VkViewport viewport = {};
        viewport.height = (float)m_height;
        viewport.width = (float)m_width;
        viewport.minDepth = (float) 0.0f;
        viewport.maxDepth = (float) 1.0f;
        vkCmdSetViewport(m_drawCommandBuffers[i], 0, 1, &viewport);

        // Update dynamic scissor state
        VkRect2D scissor = {};
        scissor.extent.width = m_width;
        scissor.extent.height = m_height;
        scissor.offset.x = 0;
        scissor.offset.y = 0;
        vkCmdSetScissor(m_drawCommandBuffers[i], 0, 1, &scissor);

        // Bind descriptor sets describing shader binding points
        vkCmdBindDescriptorSets(m_drawCommandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipelineLayout, 0, 1, &m_descriptorSet, 0, NULL);

        // Bind the rendering pipeline (including the shaders)
        vkCmdBindPipeline(m_drawCommandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipelines.solid);

        // Bind triangle vertices
        VkDeviceSize offsets[1] = { 0 };
        vkCmdBindVertexBuffers(m_drawCommandBuffers[i], VERTEX_BUFFER_BIND_ID, 1, &m_vertices.buf, offsets);

        // Bind triangle indices
        vkCmdBindIndexBuffer(m_drawCommandBuffers[i], m_indices.buf, 0, VK_INDEX_TYPE_UINT32);

        // Draw indexed triangle
        vkCmdDrawIndexed(m_drawCommandBuffers[i], m_indices.count, 1, 0, 0, 1);

        vkCmdEndRenderPass(m_drawCommandBuffers[i]);

        // Add a present memory barrier to the end of the command buffer
        // This will transform the frame buffer color attachment to a
        // new layout for presenting it to the windowing system integration 
        VkImageMemoryBarrier prePresentBarrier = {};
        prePresentBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        prePresentBarrier.pNext = NULL;
        prePresentBarrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        prePresentBarrier.dstAccessMask = 0;
        prePresentBarrier.oldLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        prePresentBarrier.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
        prePresentBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        prePresentBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        prePresentBarrier.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };			
        prePresentBarrier.image = m_swapChain.buffers[i].image;

        VkImageMemoryBarrier *pMemoryBarrier = &prePresentBarrier;
        vkCmdPipelineBarrier(
                m_drawCommandBuffers[i], 
                VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, 
                VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, 
                VK_FLAGS_NONE,
                0, nullptr,
                0, nullptr,
                1, &prePresentBarrier);

        err = vkEndCommandBuffer(m_drawCommandBuffers[i]);
        assert(!err);
    }
}


