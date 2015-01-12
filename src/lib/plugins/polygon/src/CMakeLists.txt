PROJECT(feather_polygon)

SET(feather_polygon_SRCS
    main.cpp
)

SET_SOURCE_FILES_PROPERTIES(${feather_qml_SRCS}
 PROPERTIES
 COMPILE_FLAGS ${CMAKE_CXX_FLAGS} )

INCLUDE_DIRECTORIES(${feather_core_SOURCE_DIR})

LINK_DIRECTORIES(${feather_core_BINARY_DIR})

LINK_LIBRARIES(feather_core)

ADD_LIBRARY(feather_polygon SHARED ${feather_polygon_SRCS})

SET_TARGET_PROPERTIES(feather_polygon
    PROPERTIES
    VERSION 0.01
    SOVERSION 1)

INSTALL(TARGETS feather_polygon 
    LIBRARY DESTINATION /usr/local/feather/plugins)
