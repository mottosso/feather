set(CMAKE_CXX_COMPILER "g++")

project(Feather)

cmake_minimum_required(VERSION 3.1.0)

find_package(OpenGL REQUIRED)
find_package(Boost REQUIRED)

set(QT_USE_OPENGL TRUE)

add_definitions("-D GL_GLEXT_PROTOTYPES")

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

# RELEASE VERSION
set(CMAKE_BUILD_TYPE=Release)
set(CMAKE_CXX_FLAGS "-g -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# DEBUG VERSION
#set(CMAKE_BUILD_TYPE=Debug)
#set(CMAKE_CXX_FLAGS "-ggdb -Wall")
#set(CMAKE_CXX_FLAGS_RELEASE "-O0")

#set(CMAKE_BUILD_TYPE=Profile)

#set(CMAKE_CXX_LIBRARY "libc++")
#set(CMAKE_CXX_FLAGS "-g")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
# for seg fault debugging
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v -da -Q -std=c++11")

#set(CMAKE_CXX_FLAGS_PROFILE "-pg")
#set(CMAKE_CXX_LINK_FLAGS "-Wl")
set(CMAKE_CXX_LINK_FLAGS "-ldl")

add_subdirectory(src)
add_subdirectory(assets)
