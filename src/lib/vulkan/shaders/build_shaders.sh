# Wireframe Shaders
glslangValidator -V edge.vert -o edge.vert.spv
glslangValidator -V edge.geom -o edge.geom.spv
glslangValidator -V edge.frag -o edge.frag.spv
# Point Shaders
glslangValidator -V point.vert -o point.vert.spv
glslangValidator -V point.geom -o point.geom.spv
glslangValidator -V point.frag -o point.frag.spv
# Base Shaders
glslangValidator -V base.vert -o base.vert.spv
glslangValidator -V base.frag -o base.frag.spv

