#include <GL/glew.h> //must be before other gl stuff
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>

#define BUFFER_SIZE 2048

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
        char* shader_error = (char*)alloca(BUFFER_SIZE * sizeof(char));
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

static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader) {
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
    char* program_error = (char*)alloca(BUFFER_SIZE * sizeof(char));
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
    window = glfwCreateWindow(800, 450, "Hello World", NULL, NULL);


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

    std::cout << glGetString(GL_VERSION) << std::endl;

    float pos[6] = { 
        -0.5f, -0.5f, 
        -0.5f,  0.5f, 
         0.5f,  0.5f
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), pos, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader_id);
    glfwTerminate();
    return 0;
}