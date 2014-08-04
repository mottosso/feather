project(feather_nodes)

SET(feather_nodes_SRCS
    polygon_mesh.cpp
)

SET_SOURCE_FILES_PROPERTIES(${feather_nodes_SRCS}
 PROPERTIES
 COMPILE_FLAGS ${CMAKE_CXX_FLAGS} )

INCLUDE_DIRECTORIES(${feather_core_SOURCE_DIR})

ADD_LIBRARY(feather_nodes SHARED ${feather_nodes_SRCS})

SET_TARGET_PROPERTIES(feather_nodes
    PROPERTIES
    VERSION 0.01
    SOVERSION 1)

INSTALL(TARGETS feather_nodes
    LIBRARY DESTINATION /usr/lib64/feather)
