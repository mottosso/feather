project(feather_frag_shaders)
FILE(GLOB GLSL_FILES "*.glsl")
INSTALL(FILES ${GLSL_FILES} DESTINATION /usr/local/feather/shaders/frag)
