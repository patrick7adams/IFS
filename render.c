#include "render.h"
#include "obj/shader_constants.h"

const int resX = 1000;
const int resY = 1000;

void error_callback(int error, const char* description) {
    fprintf(stderr, "Error %d: %s\n", error, description);
}
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void checkError() {
    int error = glGetError();
    if(error != 0) {
        fprintf(stderr, "Error found! Code: %d\n", error);
        exit(1);
    }
}

void draw(unsigned int program, unsigned int VAO, int num_lines) {
    float time = glfwGetTime();
    glClearColor(0.0, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    int resolutionLocation = glGetUniformLocation(program, "resolution");
    int timeLocation = glGetUniformLocation(program, "time");

    glUseProgram(program);

    glUniform1f(timeLocation, time);
    glUniform2i(resolutionLocation, resX, resY);

    // glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, num_lines*2);

    // glFlush();
}

GLFWwindow* init() {
    if(!glfwInit()) {
        fprintf(stderr, "GLFW failed to initialize!\n");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(resX, resY, "fractals are awesome!", NULL, NULL);
    if(!window) {
        fprintf(stderr, "Window failed to create!\n");
    }

    glfwSetErrorCallback(error_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);

    glfwSetTime(0.0);
    return window;
}

unsigned int programInit() {
    const char *vertex = (char*) shaders_vertex_glsl;
    const char *fragment = (char*) shaders_fragment_glsl;

    // vertex shader

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex, NULL);
    glCompileShader(vertexShader);

    int success;
	char log[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    glGetProgramInfoLog(vertexShader, 512, NULL, log);
    printf("Vertex shader info log: %s\n", log);
	if (!success) {
		fprintf(stderr, "Vertex shader failed to compile!\n");
		glDeleteShader(vertexShader);
	}

    // Fragment shader

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment, NULL);
    glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    glGetProgramInfoLog(fragmentShader, 512, NULL, log);
    printf("Fragment shader info log: %s\n", log);
	if (!success) {
		fprintf(stderr, "Fragment shader failed to compile.\n");
		glDeleteShader(fragmentShader);
	}

    // Shader program

    unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindAttribLocation(shaderProgram, 0, "vertices");
	glBindAttribLocation(shaderProgram, 0, "colors");
	glLinkProgram(shaderProgram);

    glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
    glGetProgramInfoLog(shaderProgram, 512, NULL, log);
    printf("Program info log: %s\n", log);
	if (!success) {
		fprintf(stderr, "Shader program failed to link.\n");
		glDeleteShader(shaderProgram);
	}

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

void dataInit(unsigned int* VAO, float* line_points, int num_lines) {
    int line_size = num_lines * 4 * sizeof(float);

    unsigned int VBO;

    glGenVertexArrays(1, VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(*VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, line_size, line_points, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
}

int render(GLFWwindow* window, unsigned int* VAO, unsigned int program, int num_lines) {
    draw(program, *VAO, num_lines);
    glfwSwapBuffers(window);
    glfwPollEvents();
    return 0;
}