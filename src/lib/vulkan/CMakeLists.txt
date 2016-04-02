PROJECT(feather_vulkan)

SET(CMAKE_CXX_LINK_FLAGS "-lvulkan")
SET(CMAKE_CXX_LINK_FLAGS "-lassimp")
SET(CMAKE_CXX_LINK_FLAGS "-lxcb")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVK_USE_PLATFORM_XCB_KHR")

MESSAGE(STATUS ${VULKAN_LIB})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNOMINMAX -DVK_PROTOTYPES -D_USE_MATH_DEFINES")

ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
#ADD_DEFINITIONS(-std=c++11)
#ADD_DEFINITIONS(-std=c++0x)

SET(feather_vulkan_SRCS
    tools.cpp
    debug.cpp
    node.cpp
    mesh.cpp
    pointlight.cpp
    pipelines.cpp
    window.cpp
)

SET_SOURCE_FILES_PROPERTIES(${feather_vulkan_SRCS}
 PROPERTIES
 COMPILE_FLAGS ${CMAKE_CXX_FLAGS}
)

INCLUDE_DIRECTORIES(${feather_core_SOURCE_DIR})
 
LINK_DIRECTORIES(${feather_core_BINARY_DIR})

ADD_LIBRARY(feather_vulkan SHARED ${feather_vulkan_SRCS})
TARGET_LINK_LIBRARIES(feather_vulkan "-lvulkan" ${PTHREAD})

SET_TARGET_PROPERTIES(feather_vulkan
    PROPERTIES
    CMAKE_CXX_STANDARD 14
    CMAKE_CXX_STANDARD_REQUIRED ON
)

SET_TARGET_PROPERTIES(feather_vulkan
    PROPERTIES
    VERSION 0.01
    SOVERSION 1
)

# INSTALL
INSTALL(TARGETS feather_vulkan
    LIBRARY DESTINATION /usr/lib64/feather)

# HEADERS
SET(feather_vulkan_HDRS
    window.hpp
)

INSTALL(FILES ${feather_vulkan_HDRS}
    DESTINATION /usr/include/feather/vulkan)

# SHADERS
add_subdirectory(shaders)
