project(feather_core)

FIND_PACKAGE(Boost COMPONENTS filesystem system REQUIRED)

SET(feather_core_SRCS
    pluginmanager.cpp
)

SET_SOURCE_FILES_PROPERTIES(${feather_core_SRCS}
 PROPERTIES
 COMPILE_FLAGS ${CMAKE_CXX_FLAGS} )

INCLUDE_DIRECTORIES(${BOOST_INCLUDE_DIRS})

SET(feather_core_LIBS
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
)

ADD_LIBRARY(feather_core SHARED ${feather_core_SRCS})

TARGET_LINK_LIBRARIES(feather_core ${feather_core_LIBS})

#SET(CMAKE_CXX_FLAGS "-I/usr/include/boost")

SET_TARGET_PROPERTIES(feather_core
    PROPERTIES
    VERSION 0.01
    SOVERSION 1)

INSTALL(TARGETS feather_core
    LIBRARY DESTINATION /usr/lib64/feather)
