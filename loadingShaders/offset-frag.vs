// In your CPP file:
// ======================
GLfloat offset = 0.5f;

glUniform1f(glGetUniformLocation(ourShader.Program, "xOffset"), offset);

// In your vertex shader:
// ======================
#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 ourColor;

uniform float xOffset;

void main()
{
    gl_Position = vec4(position.x + xOffset, position.y, position.z, 1.0f); // Add the xOffset to the x position of the vertex position
    ourColor = color;
}
