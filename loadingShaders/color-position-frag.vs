// Vertex shader:
// ================
#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

// out vec3 ourColor;
out vec3 ourPosition;

void main()
{
    gl_Position = vec4(position, 1.0f); 
    // ourColor = color;
    ourPosition = position;
}

// Fragment shader:
// ================
#version 330 core
// in vec3 ourColor;
in vec3 ourPosition;

out vec4 color;

void main()
{
    color = vec4(ourPosition, 1.0f);    // Note how the position value is linearly interpolated to get all the different colors
}

/* 
Answer to the question: Do you know why the bottom-left side is black?
-- --------------------------------------------------------------------
Think about this for a second: the output of our fragment's color is equal to the (interpolated) coordinate of 
the triangle. What is the coordinate of the bottom-left point of our triangle? This is (-0.5f, -0.5f, 0.0f). Since the
xy values are negative they are clamped to a value of 0.0f. This happens all the way to the center sides of the 
triangle since from that point on the values will be interpolated positively again. Values of 0.0f are of course black
and that explains the black side of the triangle.
*/