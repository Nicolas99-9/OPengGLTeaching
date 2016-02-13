#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdio>
#include "Shader.h"

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}


void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}


int main(void) {


	// initialise the windows
	GLFWwindow *window;
	glfwSetErrorCallback(error_callback);



	if (!glfwInit()) {

		return -1;
	}
	window = glfwCreateWindow(640, 480, "Test", NULL, NULL);

	if (window == nullptr) {
		std::cout << "Erreur lors du chargement de la fenetree ";
		glfwTerminate();
		return -1;

	}
	glfwMakeContextCurrent(window);

	printf("OpenGL Version:%s\n", glGetString(GL_VERSION));
	printf("GLSL Version  :%s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	// create  a windows


	if (!window) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		glfwTerminate();
		return -1;
	}


	// make the window's current context

	// loop until the window close


	glfwSetKeyCallback(window, key_callback);


	// triangle

	// must be normalized to be inside the screen 

	// GLEW INITIALISATION

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
	}

	Shader ourShader("shader.vs", "shader.frag"
		);


	GLfloat firstTriangle[] =  {
		//position          // color
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // Bottom Right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // Bottom Left
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // Top 
	};


	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//say to opengl how to interpret the data (say how to link the data with the fragment shader)
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);

	// position attribute

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);	// Vertex attributes stay the same
	glEnableVertexAttribArray(0);


	// say to the VBO that data are stored at the first index 
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// unbind the vao
	glBindVertexArray(0);


	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// swap back and front buffers

		// every object drawn after this will use those shaders

		ourShader.Use();

		// get the current time
		GLfloat timeValue = glfwGetTime();

		// modulate the green value
		GLfloat greenValue = (sin(timeValue) / 2) + 0.5;

		// get the uniform vector and then set the color
		GLint vertexColorLocation = glGetUniformLocation(ourShader.Program, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);


		// Draw the first triangle using the data from our first VAO
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);

		// poll the events

		glfwPollEvents();
	}

	std::cout << "finished ";
	// de allocate all ressources

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();

	return 0;
}
