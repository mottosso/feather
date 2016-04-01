/***********************************************************************
 *
 * Filename: pointlight.hpp
 *
 * Description: vulkan point light node.
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

#ifndef POINTLIGHT_HPP
#define POINTLIGHT_HPP

#include "deps.hpp"
#include "vulkan_deps.hpp"
#include "node.hpp"

namespace feather
{

    namespace vulkan
    {

        class PointLight: public Node
        {
            public:
                PointLight();
                ~PointLight();
                void prepareVertices(VkDevice device, VkPhysicalDeviceMemoryProperties deviceMemoryProperties);
                void updateVertices(VkDevice device, VkPhysicalDeviceMemoryProperties deviceMemoryProperties, float step=1.0);
                void build();
                void loadShaders();

            private:
                std::string m_vertexEdgeShader;
                std::string m_geometryEdgeShader;
                std::string m_fragmentEdgeShader;
                std::string m_vertexPointShader;
                std::string m_geometryPointShader;
                std::string m_fragmentPointShader;
                std::string m_vertexSolidShader;
                std::string m_fragmentSolidShader;
        };

    } // namespace vulkan

} // namespace feather

#endif
