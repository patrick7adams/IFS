#ifndef L_SYSTEM_H
#define L_SYSTEM_H

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

#include "turtle.h"
#include "stack.h"

struct L_System {
    int num_iter;

    struct Turtle* t;
    struct Turtle* start_t;

    int num_variables;
    char* variables; // maps to variable_conversions
    int* variable_conversion_lengths;
    char** variable_conversions;
    void (**variable_actions) (struct L_System*);

    int state_len;
    char* state;

    float move_dist;
    double angle;
    float div_factor;

    int len_line_points;
    int cur_line_point;
    float* line_points;
};

typedef void (*move_ptr)(struct L_System*);

void do_nothing(struct L_System* sys);
void move_forward(struct L_System* sys);
void step_forward(struct L_System* sys);
void turn_left(struct L_System* sys);
void turn_right(struct L_System* sys);
void save_state(struct L_System* sys);
void load_state(struct L_System* sys);
void turn_left_and_save(struct L_System* sys);
void turn_right_and_load(struct L_System* sys);

float move_dist_div_factor(float move_dist, float div_factor);

struct Turtle* copy_turtle(struct Turtle* t);

struct L_System* lsystem_init(
    float start_x, float start_y, float start_direction,
    int max_stack, int num_variables, char* variables, 
    int* variable_conversion_lengths, char** variable_conversions,
    void (**variable_actions) (struct L_System*), int initial_state_len, 
    char* initial_state, float move_dist, double angle, float div_factor
);

void step(struct L_System* sys);
int str_eq(char* str_1, char* str_2, int len);
void step_back(struct L_System* sys);
void act(struct L_System* sys);
void iterate(struct L_System* sys, int num_iter);

#endif