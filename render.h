#ifndef RENDER_C
#define RENDER_C

#include "glad.h"
#include "glfw3.h"

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

const float pi = 3.14159265f;

void error_callback(int error, const char* description);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void checkError();
void draw(unsigned int program, unsigned int VAO, int num_lines);
GLFWwindow* init();
unsigned int programInit();
void dataInit(unsigned int* VAO, float* line_points, int num_lines);
int render(GLFWwindow* window, unsigned int* VAO, unsigned int program, int num_lines);
#endif