project(feather_core)

SET(feather_core_SRCS
    pluginmanager.cpp
)

ADD_LIBRARY(feather_core SHARED ${feather_core_SRCS})

SET_TARGET_PROPERTIES(feather_core
    PROPERTIES
    VERSION 0.01
    SOVERSION 1)

INSTALL(TARGETS feather_core
    LIBRARY DESTINATION /usr/lib64/feather)
