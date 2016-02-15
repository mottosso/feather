project(feather_frag_shaders)
FILE(GLOB GLSL_FILES "*.glsl")
FILE(GLOB FRAG_FILES "*.frag")
INSTALL(FILES ${GLSL_FILES} ${FRAG_FILES} DESTINATION /usr/local/feather/shaders/frag)
