#include "l_system.h"

void do_nothing(struct L_System* sys) {
    // why are we here just to suffer
}

void move_forward(struct L_System* sys) {
    (*sys).line_points[(*sys).cur_line_point*4] = (*(*sys).t).x;
    (*sys).line_points[(*sys).cur_line_point*4+1] = (*(*sys).t).y;
    (*(*sys).t).x += cos((*(*sys).t).direction) * (*sys).move_dist;
    (*(*sys).t).y += sin((*(*sys).t).direction) * (*sys).move_dist;
    (*sys).line_points[(*sys).cur_line_point*4+2] = (*(*sys).t).x;
    (*sys).line_points[(*sys).cur_line_point*4+3] = (*(*sys).t).y;
    (*sys).cur_line_point++;
}

void step_forward(struct L_System* sys) {
    (*(*sys).t).x += cos((*(*sys).t).direction) * (*sys).move_dist;
    (*(*sys).t).y += sin((*(*sys).t).direction) * (*sys).move_dist;
}

void turn_left(struct L_System* sys) {
    (*(*sys).t).direction += (*sys).angle;
}

void turn_right(struct L_System* sys) {
    (*(*sys).t).direction -= (*sys).angle;
}

void save_state(struct L_System* sys) {
    push((*(*sys).t).states, (*(*sys).t).x);
    push((*(*sys).t).states, (*(*sys).t).y);
    push((*(*sys).t).states, (*(*sys).t).direction);
}

void load_state(struct L_System* sys) {
    (*(*sys).t).direction = pop((*(*sys).t).states);
    (*(*sys).t).y = pop((*(*sys).t).states);
    (*(*sys).t).x = pop((*(*sys).t).states);
}

void turn_left_and_save(struct L_System* sys) {
    save_state(sys);
    turn_left(sys);
}

void turn_right_and_load(struct L_System* sys) {
    load_state(sys);
    turn_right(sys);
}

float move_dist_div_factor(float move_dist, float div_factor) {
    return move_dist / div_factor;
}

struct Turtle* copy_turtle(struct Turtle* t) {
    struct Turtle* new_t = (struct Turtle*) malloc(sizeof(struct Turtle));
    (*new_t).x = (*t).x;
    (*new_t).y = (*t).y;
    (*new_t).direction = (*t).direction;
    struct Stack* states = stack_init((*(*t).states).max_stack_size);
    (*new_t).states = (*t).states;
    return new_t;
}

struct L_System* lsystem_init(
    float start_x, float start_y, float start_direction,
    int max_stack, int num_variables, char* variables, 
    int* variable_conversion_lengths, char** variable_conversions,
    move_ptr* variable_actions, int initial_state_len, 
    char* initial_state, float move_dist, double angle, float div_factor
    ){

    struct L_System* sys = (struct L_System*) malloc(sizeof(struct L_System));
    (*sys).num_iter = 0;

    struct Stack* states = stack_init(max_stack);
    struct Turtle* t = (struct Turtle*) malloc(sizeof(struct Turtle));

    (*t).x = start_x;
    (*t).y = start_y;
    (*t).direction = start_direction;
    (*t).states = states;
    (*sys).t = t;
    (*sys).start_t = copy_turtle(t);

    char* real_variables = (char*) malloc(num_variables*sizeof(char));
    char** real_variable_conversions = (char**) malloc(num_variables * sizeof(char*));
    int* real_variable_conversion_lengths = (int*) malloc(num_variables * sizeof(int));

    int func_pointer_total_size = 0;
    for (int var = 0; var < num_variables; var++) {
        func_pointer_total_size += sizeof(variable_actions[var]);
    }
    
    move_ptr* real_variable_actions = (move_ptr*) malloc(sizeof(move_ptr)*num_variables);

    memcpy(real_variables, variables, num_variables*sizeof(char));
    memcpy(real_variable_conversion_lengths, variable_conversion_lengths, num_variables * sizeof(int));
    memcpy(real_variable_actions, variable_actions, num_variables * sizeof(move_ptr));
    for(int var = 0; var < num_variables; var++) {
        char* real_var_convert_str = (char*) malloc(sizeof(char) * variable_conversion_lengths[var]);
        strncpy(real_var_convert_str, variable_conversions[var], variable_conversion_lengths[var]);
        real_variable_conversions[var] = real_var_convert_str;
    }

    (*sys).num_variables = num_variables;
    (*sys).variables = real_variables;
    (*sys).variable_conversion_lengths = real_variable_conversion_lengths;
    (*sys).variable_conversions = real_variable_conversions;
    (*sys).variable_actions = real_variable_actions;


    char* state = (char*) malloc(initial_state_len * sizeof(char));
    strncpy(state, initial_state, initial_state_len);
    (*sys).state_len = initial_state_len;
    (*sys).state = state;

    (*sys).move_dist = move_dist;
    (*sys).angle = angle;
    (*sys).div_factor = div_factor;

    return sys;
}

void step(struct L_System* sys) {
    int new_state_len = 0;
    for (int i = 0; i < (*sys).state_len; i++) {
        for(int var = 0; var < (*sys).num_variables; var++) {
            if((*sys).state[i] == (*sys).variables[var]) {
                new_state_len += (*sys).variable_conversion_lengths[var];
            }
        }
    }
    char* new_state = (char*) malloc(sizeof(char) * new_state_len);
    int new_state_pos = 0;

    for (int i = 0; i < (*sys).state_len; i++) {
        for(int var = 0; var < (*sys).num_variables; var++) {
            if((*sys).state[i] == (*sys).variables[var]) {
                strncpy(&new_state[new_state_pos], (*sys).variable_conversions[var], (*sys).variable_conversion_lengths[var]);
                new_state_pos += (*sys).variable_conversion_lengths[var];
            }
        }
    }

    (*sys).move_dist = move_dist_div_factor((*sys).move_dist, (*sys).div_factor);
    (*sys).num_iter++;

    free((*sys).state);
    (*sys).state = new_state;
    (*sys).state_len = new_state_len;
}

int str_eq(char* str_1, char* str_2, int len) {
    // printf("Comparing ");
    // for (int i = 0; i < len; i++) {
    //     printf("%c", str_1[i]);
    // }
    // printf(" to ");
    // for (int i = 0; i < len; i++) {
    //     printf("%c", str_2[i]);
    // }
    // printf(".\n");
    for(int c = 0; c < len; c++) {
        if(str_1[c] != str_2[c]) {
            return 0;
        }
    }
    // printf(" They are similar!\n");
    return 1;
}   

void step_back(struct L_System* sys) {
    int counter = 0;
    int back_step_len = 0;
    while(counter < (*sys).state_len) {
        for (int var = 0; var < (*sys).num_variables; var++) {
            int var_len = (*sys).variable_conversion_lengths[var];
            int added_already = 0;
            if (!added_already && counter+var_len <= (*sys).state_len && str_eq((*sys).variable_conversions[var], &(*sys).state[counter], var_len)) {
                counter += var_len;
                back_step_len++;
                added_already = 1;
            }
        }
    }

    char* new_state = (char*) malloc(sizeof(char) * back_step_len);
    int new_state_pos = 0;
    counter = 0;
    
    while(counter < (*sys).state_len) {
        for (int var = 0; var < (*sys).num_variables; var++) {
            int var_len = (*sys).variable_conversion_lengths[var];
            int added_already = 0;
            if (!added_already && counter+var_len <= (*sys).state_len && str_eq((*sys).variable_conversions[var], &(*sys).state[counter], var_len)) {
                new_state[new_state_pos] = (*sys).variables[var];
                counter += var_len;
                new_state_pos++;
                added_already = 1;
            }
        }
    }

    (*sys).move_dist = move_dist_div_factor((*sys).move_dist, 1.0f/(*sys).div_factor);
    (*sys).num_iter--;

    free((*sys).state);
    (*sys).state = new_state;
    (*sys).state_len = back_step_len;
}

void act(struct L_System* sys) {
    for (int i = 0; i < (*sys).state_len; i++) {
        // printf("At string [%c], iteration %d, direction is %f, position is (%f, %f)\n", l_str[i], i, t.direction, t.x, t.y);
        for (int var = 0; var < (*sys).num_variables; var++) {
            if ((*sys).state[i] == (*sys).variables[var]) {
                (*sys).variable_actions[var] (sys);
            }
        }
    }
}

void iterate(struct L_System* sys, int num_iter) {
    printf("Current iter is %d, changing by %d\n", (*sys).num_iter, num_iter);
    if(num_iter < 0) {
        for (int i = 0; i < num_iter*-1; i++) {
            if ((*sys).num_iter > 0) {
                step_back(sys);
            }
        }
    } else {
        for (int i = 0; i < num_iter; i++) {
            step(sys);
        }
    }

    int num_lines = 0;
    for (int i = 0; i < (*sys).state_len; i++) {
        for (int var = 0; var < (*sys).num_variables; var++) {
            if ((*sys).state[i] == (*sys).variables[var] && (*sys).variable_actions[var] == move_forward) {
                num_lines++;
            }
        }
    }

    float* line_points = (float*) malloc(num_lines*4*sizeof(float));
    (*sys).len_line_points = num_lines;
    (*sys).cur_line_point = 0;
    (*sys).line_points = line_points;

    (*sys).t = copy_turtle((*sys).start_t);

    act(sys);
}