project(feather_core)

set(feather_core_SRCS
    core.cpp
)

add_library(feather_core SHARED ${feather_core_SRCS})

set(feather_core_LIBS
 ${BOOST_LIBRARIES}
 ${OPENGL_LIBRARIES}
)

target_link_libraries(feather_core ${feather_core_LIBS})

set(CMAKE_CXX_FLAGS "-I/usr/include/boost")

set_target_properties(feather_core
    PROPERTIES
    VERSION 0.01
    SOVERSION 1)

install(TARGETS feather_core
    LIBRARY DESTINATION /usr/lib64/feather)

