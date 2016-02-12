#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdio>


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}


void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";
const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";


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

	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f };

    // VBO is used to store çdata and passed it to the GPU
	// generate an unique id for the VBO
    
	GLuint VBO;
	glGenBuffers(1, &VBO);

	// possible to bind several several buffers if they have a different type

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// configure the current vbo
	// copy the data into the VBO bound to GL_ARRAY_BUFFER
	//GL_STATIC_DRAW => data will not change
	// GL_DYNAMIC_DRAW data will change a lot
	// GL_STREAM_DRAW : change every time is drawn
	// store the data into the GPU

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// say how to interpret the data
	// first argument the vertex attibute we want to configure
	// number of valuer per block
	//type of data
	//specifies if we want the data to be normalized
	//space between two consecutives data
	//offset of where the data begins
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// vertex shader creation
	// store the vertex shader as a GLuint
	// create the vertex shader
	glEnableVertexAttribArray(0);


	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// attach the shader to our file
	// compile the shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);


	// create the fragment shader and compile it

	GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

	// create a shaed program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);




	// attach the shader to the program

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// VAO CREATION
	// generate an unique id to the VAO
	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	// 2. Copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
		GL_STATIC_DRAW);
	// 3. Then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (
		GLvoid*)0);
	glEnableVertexAttribArray(0);
	//4. Unbind the VAO
	glBindVertexArray(0);



	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// swap back and front buffers

		// every object drawn after this will use those shaders

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		// draw a triangle using draws
        // using the currently active shader, the previously defined vertex attribute configuration
        // and with the VBO’s vertex data(indirectly bound via the VAO).
		// starting index into the VAO
		//3 => how many vertices we want to draw


		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);





		glfwSwapBuffers(window);


		// poll the events

		glfwPollEvents();
	}

	std::cout << "finished ";
	// de allocate all ressources

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	glfwTerminate();

	return 0;
}


