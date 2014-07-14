project(feather_core)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5Quick REQUIRED)
FIND_PACKAGE(Qt5Quick REQUIRED)

SET(CMAKE_AUTOMOC ON)
SET(QT_USE_QTOPENGL TRUE)

SET(feather_core_SRCS
    core.cpp
    scenegraph.cpp
    #test.cpp
    viewport.cpp
    viewportthread.cpp
    qml.cpp
)

SET_SOURCE_FILES_PROPERTIES(${feather_core_SRCS}
 PROPERTIES
 COMPILE_FLAGS ${CMAKE_CXX_FLAGS} )


INCLUDE_DIRECTORIES(${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5Quick_INCLUDE_DIRS}
    ${QtOpenGL_INCLUDE_DIRS}
    "/usr/include/qt/QtGui/5.3.0"
    "/usr/include/qt/QtGui/5.3.0/QtGui"
    "/usr/include/qt/QtCore/5.3.0"
    "/usr/include/qt/QtCore/5.3.0/QtCore"
)

ADD_DEFINITIONS(${Qt5Widgets_DEFINITIONS}
    ${Qt5Quick_DEFINITIONS}
    ${Qt5OpenGL_DEFINITIONS}
)

SET(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
SET(CMAKE_CXX_FLAGS "${Qt5Quick_EXECUTABLE_COMPILE_FLAGS}")
SET(CMAKE_CXX_FLAGS "${Qt5OpenGL_EXECUTABLE_COMPILE_FLAGS}")

ADD_LIBRARY(feather_core SHARED ${feather_core_SRCS})

QT5_USE_MODULES(feather_core Widgets Quick OpenGL)

SET(feather_core_LIBS
 ${BOOST_LIBRARIES}
 ${OPENGL_LIBRARIES}
 ${QT5Widgets_LIBRARIES}
 ${QT5Quick_LIBRARIES}
 ${QT5OpenGL_LIBRARIES}
)

TARGET_LINK_LIBRARIES(feather_core ${feather_core_LIBS})

SET(CMAKE_CXX_FLAGS "-I/usr/include/boost")

SET_TARGET_PROPERTIES(feather_core
    PROPERTIES
    VERSION 0.01
    SOVERSION 1)

INSTALL(TARGETS feather_core
    LIBRARY DESTINATION /usr/lib64/feather)

FILE(GLOB GLSL_FILES "*.vert" "*.frag" "*.glsl")

INSTALL(FILES ${GLSL_FILES} DESTINATION /usr/local/feather)
