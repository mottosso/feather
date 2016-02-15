project(feather_geom_shaders)
FILE(GLOB GLSL_FILES "*.glsl")
FILE(GLOB GEOM_FILES "*.geom")
INSTALL(FILES ${GLSL_FILES} ${GEOM_FILES} DESTINATION /usr/local/feather/shaders/geom)
