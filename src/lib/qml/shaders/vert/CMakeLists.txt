PROJECT(feather_vert_shaders)
FILE(GLOB GLSL_FILES "*.glsl")
INSTALL(FILES ${GLSL_FILES} DESTINATION /usr/local/feather/shaders/vert)
