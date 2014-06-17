project(feather_core)

FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5Quick REQUIRED)


SET(CMAKE_AUTOMOC ON)
SET(QT_USE_QTOPENGL TRUE)

set(feather_core_SRCS
    core.cpp
    #test.cpp
    viewport.cpp
    #viewportthread.cpp
)

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

add_library(feather_core SHARED ${feather_core_SRCS})

QT5_USE_MODULES(feather_core Widgets Quick OpenGL)

set(feather_core_LIBS
 ${BOOST_LIBRARIES}
 ${OPENGL_LIBRARIES}
 ${QT5Widgets_LIBRARIES}
 ${QT5Quick_LIBRARIES}
 ${QT5OpenGL_LIBRARIES}
)

target_link_libraries(feather_core ${feather_core_LIBS})

set(CMAKE_CXX_FLAGS "-I/usr/include/boost")

set_target_properties(feather_core
    PROPERTIES
    VERSION 0.01
    SOVERSION 1)

install(TARGETS feather_core
    LIBRARY DESTINATION /usr/lib64/feather)

FILE(GLOB GLSL_FILES "*.vert" "*.frag")

INSTALL(FILES ${GLSL_FILES} DESTINATION /usr/local/feather)
