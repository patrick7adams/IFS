#ifndef MAIN_H
#define MAIN_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "render.h"
#include "stack.h"
#include "turtle.h"
#include "l_system.h"

const double double_pi = 3.14159265358979;
const float zoom_speed = 0.99;
const float move_speed=  0.01;
int changed_iter_flag = 0;

void inputs(GLFWwindow *window, unsigned int* VAO, float** line_points, int* num_lines, struct L_System** systems, int num_systems);
struct L_System* sierpinski();
struct L_System* sierpinski_arrowhead();
struct L_System* koch_curve();
struct L_System* koch_snowflake();
struct L_System* binary_tree();
struct L_System* dragon_curve();
struct L_System* fractal_plant();
struct L_System* ice_square();
struct L_System* gosper_curve();
struct L_System* sierpinski_curve();
struct L_System* gilbert_curve();
struct L_System* cool_square_curve();
struct L_System* sierpinski_carpet();
struct L_System* levy_curve();

int get_num_lines(struct L_System** systems, int num_systems, int num_iter);
float* get_line_points(struct L_System** systems, int num_systems, int num_iter, int num_lines);
int main();

#endif