// ================
// Vertex shader:
// ================
#version 330 core
layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texCoords;

out VS_OUT {
    vec2 texCoords;
} vs_out;
