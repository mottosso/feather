set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Boost REQUIRED)

set(feather_SRCS
 main.cpp
)

set(QT_USE_QTOPENGL TRUE)

include_directories(${feather_core_SOURCE_DIR}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5Quick_INCLUDE_DIRS}
    "/usr/include/qt/QtGui/5.3.0"
    "/usr/include/qt/QtGui/5.3.0/QtGui"
    "/usr/include/qt/QtCore/5.3.0"
    "/usr/include/qt/QtCore/5.3.0/QtCore"
)

link_directories(${feather_core_BINARY_DIR}
)

link_libraries( feather_core
)

add_definitions( ${Qt5Widgets_DEFINITIONS}
    ${Qt5Quick_DEFINITIONS}
)

set(feather_LIBS
 ${Qt5Widgets_LIBRARIES}
 ${Qt5Quick_LIBRARIES}
 ${QTOPENGL_LIBRARIES}
 ${OPENGL_LIBRARIES}
 ${BOOST_LIBRARIES})

set(CMAKE_CXX_FLAGS "-I/usr/include/boost")

set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${Qt5Quick_EXECUTABLE_COMPILE_FLAGS}")

add_executable(feather ${feather_SRCS} ${feather_MOC_SRCS})

target_link_libraries(feather ${feather_LIBS})

# INSTALL
install( TARGETS feather
    RUNTIME DESTINATION /usr/local/feather)
