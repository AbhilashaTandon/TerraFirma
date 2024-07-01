#include <GL/glew.h> //must be before other gl stuff
#include <GLFW/glfw3.h>
#include "Sphere.h"

#include <iostream>
#include <fstream>
#include <string>

#define BUFFER_SIZE 4096
#define DEBUG false

static unsigned int compileShader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str(); //gl wants c style string
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	//ERROR HANDLING
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		GLint length = BUFFER_SIZE;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* shader_error = (char*)_malloca(BUFFER_SIZE * sizeof(char));
		glGetShaderInfoLog(id, length, &length, shader_error);

		switch (type) {
		case GL_VERTEX_SHADER:
			std::cerr << "Error in vertex shader" << std::endl;
			break;
		case GL_FRAGMENT_SHADER:
			std::cerr << "Error in fragment shader" << std::endl;
			break;
		default:
			std::cerr << "Error in other shader" << std::endl;
			break;
		}
		std::cerr << shader_error << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

static unsigned int createShader(const std::string& vertexShader,
	const std::string& fragmentShader) {
	//these strings are the source code of the shaders

	unsigned int program = glCreateProgram();
	unsigned int vertId = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fragId = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vertId);
	glAttachShader(program, fragId);
	glLinkProgram(program);
	glValidateProgram(program);


	//ERROR HANDLING
	GLint length = BUFFER_SIZE;
	char* program_error = (char*)_malloca(BUFFER_SIZE * sizeof(char));
	GLsizei error_length;
	glGetProgramInfoLog(program, length, &error_length, program_error);
	if (error_length != 0) {
		std::cerr << "Error with program" << std::endl;
		std::cerr << program_error << std::endl;
	}

	glDeleteShader(vertId);
	glDeleteShader(fragId);

	return program;
}

std::string loadShader(const std::string file_path) {
	std::ifstream shaderFile;
	shaderFile.open(file_path);
	if (shaderFile.is_open()) {
		std::string out((std::istreambuf_iterator<char>(shaderFile)),
			(std::istreambuf_iterator<char>()));
		shaderFile.close();
		return out;
	}
	else {
		std::cerr << "Unable to open shader file " << file_path << std::endl;
		return "";
	}
}



int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit()) {
		return -1;
	}

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(800, 800, "Hello World", NULL, NULL);


	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	GLenum glew_err = glewInit();

	if (GLEW_OK != glew_err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_err));
		return -1;
	}


	const std::string vertShader = loadShader("res/shaders/shader.vert");
	const std::string fragShader = loadShader("res/shaders/shader.frag");

	unsigned int shader_id = createShader(vertShader, fragShader);
	glUseProgram(shader_id);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);

	

	Sphere x = Sphere(.5, glm::vec3(0,0,0), 16, 32);

	x.scale(1.5f);


	std::vector<float> vertices_vec = x.get_vertices(true);

	std::vector<unsigned> indices_vec = x.get_indices();


	if (DEBUG) {
		for (int i = 0; i < vertices_vec.size(); i++) {
			float rounded = float(long(vertices_vec[i] * 100000)) / 100000;
			std::cout << rounded << ' ';
			if (i % 3 == 2) {
				std::cout << '\n';
			}
		}

		std::cout << "\n\nindices\n\n";

		
		for (int i = 0; i < indices_vec.size(); i++) {
			std::cout << indices_vec[i] << ' ';
			if (i % 3 == 2) {
				std::cout << '\n';
			}
		}
	}

	float vertices[BUFFER_SIZE];

	unsigned int indices[BUFFER_SIZE];

	std::copy(vertices_vec.begin(), vertices_vec.end(), vertices);
	std::copy(indices_vec.begin(), indices_vec.end(), indices);

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	//3 is dimension
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	//3 is dimension


	unsigned int index_buffer;
	glGenBuffers(1, &index_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);




	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{



		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float time_val = glfwGetTime();
		int vertex_shader_time_loc = glGetUniformLocation(shader_id, "time");
		glUniform1f(vertex_shader_time_loc, time_val);


		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

	}

	glDeleteProgram(shader_id);
	glfwTerminate();
	return 0;
}