project(polyplaneshape)

SET(polyplaneshape_SRCS
    main.cpp
)

INCLUDE_DIRECTORIES(${feather_core_SOURCE_DIR})

LINK_DIRECTORIES(${feather_core_BINARY_DIR})

LINK_LIBRARIES(feather_core)

ADD_LIBRARY(polyplaneshape SHARED ${polyplaneshape_SRCS})

SET_TARGET_PROPERTIES(polyplaneshape
    PROPERTIES
    VERSION 0.01
    SOVERSION 1)

INSTALL(TARGETS polyplaneshape 
    LIBRARY DESTINATION /usr/local/feather/plugins/nodes)
