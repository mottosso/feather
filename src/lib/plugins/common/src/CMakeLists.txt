PROJECT(feather_common)

SET(feather_common_SRCS
    main.cpp
)

SET_SOURCE_FILES_PROPERTIES(${feather_qml_SRCS}
 PROPERTIES
 COMPILE_FLAGS ${CMAKE_CXX_FLAGS} )

INCLUDE_DIRECTORIES(${feather_core_SOURCE_DIR})

LINK_DIRECTORIES(${feather_core_BINARY_DIR})

LINK_LIBRARIES(feather_core)

ADD_LIBRARY(feather_common SHARED ${feather_common_SRCS})

SET_TARGET_PROPERTIES(feather_common
    PROPERTIES
    VERSION 0.01
    SOVERSION 1)

INSTALL(TARGETS feather_common
    LIBRARY DESTINATION /usr/local/feather/plugins)
