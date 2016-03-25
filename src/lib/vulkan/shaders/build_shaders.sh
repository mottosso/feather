# Wireframe Shaders
glslangValidator -V wire.vert -o wire.vert.spv
glslangValidator -V wire.geom -o wire.geom.spv
glslangValidator -V wire.frag -o wire.frag.spv
# Point Shaders
glslangValidator -V point.vert -o point.vert.spv
glslangValidator -V point.geom -o point.geom.spv
glslangValidator -V point.frag -o point.frag.spv
# Base Shaders
glslangValidator -V base.vert -o base.vert.spv
glslangValidator -V base.frag -o base.frag.spv

