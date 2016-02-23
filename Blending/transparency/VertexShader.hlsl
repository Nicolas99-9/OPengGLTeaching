#version 330 core

// input data
layout(location = 0) in vec3 position;


// just return the positions
void main()
{
	gl_Position = vec4(position.x, position.y, position.z, 1.0);
}