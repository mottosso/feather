PROJECT(feather_vert_shaders)
FILE(GLOB GLSL_FILES "*.glsl")
FILE(GLOB VERT_FILES "*.vert")
INSTALL(FILES ${GLSL_FILES} ${VERT_FILES} DESTINATION /usr/local/feather/shaders/vert)
