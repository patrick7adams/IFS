#include "main.h"

void change_num_lines(int* num_lines, float** line_points, struct L_System** systems, int num_systems, int num) {
    (*num_lines) = get_num_lines(systems, num_systems, num);
    (*line_points) = get_line_points(systems, num_systems, num, (*num_lines));
}

void inputs(GLFWwindow *window, unsigned int* VAO, float** line_points, int* num_lines, struct L_System** systems, int num_systems) {
    float zoom_factor = 1.0f;
    float x_offset = 0.0f;
    float y_offset = 0.0f;
    int key_pressed = 0;
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        zoom_factor = 1.0f/zoom_speed;
        key_pressed = 1;
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        zoom_factor = zoom_speed;
        key_pressed = 1;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        x_offset = -move_speed;
        key_pressed = 1;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        x_offset = move_speed;
        key_pressed = 1;
    }
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        y_offset = -move_speed;
        key_pressed = 1;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        y_offset = move_speed;
        key_pressed = 1;
    }
    if(glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
        change_num_lines(num_lines, line_points, systems, num_systems, 0-(*systems)[0].num_iter);
    }
    if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        change_num_lines(num_lines, line_points, systems, num_systems, 1-(*systems)[0].num_iter);
    }
    if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        change_num_lines(num_lines, line_points, systems, num_systems, 2-(*systems)[0].num_iter);
    }
    if(glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
        change_num_lines(num_lines, line_points, systems, num_systems, 3-(*systems)[0].num_iter);
    }
    if(glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
        change_num_lines(num_lines, line_points, systems, num_systems, 4-(*systems)[0].num_iter);
    }
    if(glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
        change_num_lines(num_lines, line_points, systems, num_systems, 5-(*systems)[0].num_iter);
    }
    if(glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) {
        change_num_lines(num_lines, line_points, systems, num_systems, 6-(*systems)[0].num_iter);
    }
    if(glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS) {
        change_num_lines(num_lines, line_points, systems, num_systems, 7-(*systems)[0].num_iter);
    }
    if(glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS) {
        change_num_lines(num_lines, line_points, systems, num_systems, 8-(*systems)[0].num_iter);
    }
    if(glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS) {
        change_num_lines(num_lines, line_points, systems, num_systems, 9-(*systems)[0].num_iter);
    }

    if (key_pressed) {
        for(int i = 0; i < (*num_lines)*2; i++) {
            (*line_points)[2*i] *= zoom_factor;
            (*line_points)[2*i+1] *= zoom_factor;
            (*line_points)[2*i] += x_offset;
            (*line_points)[2*i+1] += y_offset;
        }
    }
}

struct L_System* sierpinski() {
    float start_x = -0.5f;
    float start_y = -0.27f;
    float start_direction = double_pi/3.0f;
    int max_stack = 256;
    int num_variables = 4;

    char variables[4] = {'F', 'G', '+', '-'};
    int variable_conversion_lengths[4] = {9, 2, 1, 1};
    char* variable_conversions[4] = {"F-G+F+G-F", "GG", "+", "-"};
    move_ptr variable_actions[4] = {move_forward, step_forward, turn_left, turn_right};

    int initial_state_len = 5;
    char* state = "F-F-F";

    float move_dist = 1.0f;
    double angle = 2*double_pi/3;
    float div_factor = 2.0f;

    return lsystem_init(
        start_x, start_y, start_direction, max_stack, 
        num_variables, variables, variable_conversion_lengths,
        variable_conversions, variable_actions, initial_state_len, 
        state, move_dist, angle, div_factor
    );
}

struct L_System* sierpinski_arrowhead() {
    float start_x = -0.5f;
    float start_y = -0.27f;
    float start_direction = 0.0f;
    int max_stack = 256;
    int num_variables = 4;

    char variables[4] = {'A', 'B', '+', '-'};
    int variable_conversion_lengths[4] = {5, 5, 1, 1};
    char* variable_conversions[4] = {"B-A-B", "A+B+A", "+", "-"};
    move_ptr variable_actions[4] = {move_forward, move_forward, turn_left, turn_right};

    int initial_state_len = 1;
    char* state = "A";

    float move_dist = 1.0f;
    double angle = double_pi/3;
    float div_factor = 2.0f;

    return lsystem_init(
        start_x, start_y, start_direction, max_stack, 
        num_variables, variables, variable_conversion_lengths,
        variable_conversions, variable_actions, initial_state_len, 
        state, move_dist, angle, div_factor
    );
}

struct L_System* koch_curve() {
    float start_x = -0.5f;
    float start_y = 0.0f;
    float start_direction = 0.0f;
    int max_stack = 256;
    int num_variables = 3;

    char variables[3] = {'F', '+', '-'};
    int variable_conversion_lengths[3] = {8, 1, 1};
    char* variable_conversions[3] = {"F-F++F-F", "+", "-"};
    move_ptr variable_actions[3] = {move_forward, turn_right, turn_left};

    int initial_state_len = 1;
    char* state = "F";

    float move_dist = 1.0f;
    double angle = double_pi/3;
    float div_factor = 3.0f;

    return lsystem_init(
        start_x, start_y, start_direction, max_stack, 
        num_variables, variables, variable_conversion_lengths,
        variable_conversions, variable_actions, initial_state_len, 
        state, move_dist, angle, div_factor
    );
}

struct L_System* koch_snowflake() {
    float start_x = -0.5f;
    float start_y = 0.5f;
    float start_direction = 0.0f;
    int max_stack = 256;
    int num_variables = 3;

    char variables[3] = {'F', '+', '-'};
    int variable_conversion_lengths[3] = {8, 1, 1};
    char* variable_conversions[3] = {"F-F++F-F", "+", "-"};
    move_ptr variable_actions[3] = {move_forward, turn_right, turn_left};

    int initial_state_len = 7;
    char* state = "F++F++F";

    float move_dist = 1.0f;
    double angle = double_pi/3;
    float div_factor = 3.0f;

    return lsystem_init(
        start_x, start_y, start_direction, max_stack, 
        num_variables, variables, variable_conversion_lengths,
        variable_conversions, variable_actions, initial_state_len, 
        state, move_dist, angle, div_factor
    );
}

struct L_System* binary_tree() {
    float start_x = 0.0f;
    float start_y = -0.5f;
    float start_direction = double_pi/2.0f;
    int max_stack = 256;
    int num_variables = 4;

    char variables[] = {'0', '1', '[', ']'};
    int variable_conversion_lengths[] = {5, 2, 1, 1};
    char* variable_conversions[] = {"1[0]0", "11", "[", "]"};
    move_ptr variable_actions[] = {move_forward, move_forward, turn_left_and_save, turn_right_and_load};

    int initial_state_len = 1;
    char* state = "0";

    float move_dist = 1.0f;
    double angle = double_pi/4;
    float div_factor = 2.0f;

    return lsystem_init(
        start_x, start_y, start_direction, max_stack, 
        num_variables, variables, variable_conversion_lengths,
        variable_conversions, variable_actions, initial_state_len, 
        state, move_dist, angle, div_factor
    );
}

struct L_System* dragon_curve() {
    float start_x = 0.0f;
    float start_y = -0.5f;
    float start_direction = double_pi/2.0f;
    int max_stack = 256;
    int num_variables = 4;

    char variables[] = {'F', 'G', '+', '-'};
    int variable_conversion_lengths[] = {3, 3, 1, 1};
    char* variable_conversions[] = {"F+G", "F-G", "+", "-"};
    move_ptr variable_actions[] = {move_forward, move_forward, turn_right, turn_left};

    int initial_state_len = 1;
    char* state = "F";

    float move_dist = 1.0f;
    double angle = double_pi/2;
    float div_factor = 1.5f;

    return lsystem_init(
        start_x, start_y, start_direction, max_stack, 
        num_variables, variables, variable_conversion_lengths,
        variable_conversions, variable_actions, initial_state_len, 
        state, move_dist, angle, div_factor
    );
}

struct L_System* fractal_plant() {
    float start_x = 0.0f;
    float start_y = -0.5f;
    float start_direction = double_pi/2.0f;
    int max_stack = 256;
    int num_variables = 6;

    char variables[] = {'X', 'F', '+', '-', '[', ']'};
    int variable_conversion_lengths[] = {18, 2, 1, 1, 1, 1};
    char* variable_conversions[] = {"F+[[X]-X]-F[-FX]+X", "FF", "+", "-", "[", "]"};
    move_ptr variable_actions[] = {do_nothing, move_forward, turn_left, turn_right, save_state, load_state};

    int initial_state_len = 1;
    char* state = "X";

    float move_dist = 1.0f;
    double angle = 5.0*double_pi/36.0;
    float div_factor = 2.0f;

    return lsystem_init(
        start_x, start_y, start_direction, max_stack, 
        num_variables, variables, variable_conversion_lengths,
        variable_conversions, variable_actions, initial_state_len, 
        state, move_dist, angle, div_factor
    );
}

struct L_System* ice_square() {
    float start_x = 0.0f;
    float start_y = -0.5f;
    float start_direction = 0.0f;
    int max_stack = 256;
    int num_variables = 2;

    char variables[] = {'F', '+'};
    int variable_conversion_lengths[] = {9, 1};
    char* variable_conversions[] = {"FF+F++F+F", "+"};
    move_ptr variable_actions[] = {move_forward, turn_left};

    int initial_state_len = 7;
    char* state = "F+F+F+F";

    float move_dist = 1.0f;
    double angle = double_pi/2.0;
    float div_factor = 3.0f;

    return lsystem_init(
        start_x, start_y, start_direction, max_stack, 
        num_variables, variables, variable_conversion_lengths,
        variable_conversions, variable_actions, initial_state_len, 
        state, move_dist, angle, div_factor
    );
}

struct L_System* gosper_curve() {
    float start_x = 0.0f;
    float start_y = -0.5f;
    float start_direction = 0.0f;
    int max_stack = 256;
    int num_variables = 5;

    char variables[] = {'X', 'Y', 'F', '-', '+'};
    int variable_conversion_lengths[] = {21, 21, 1, 1, 1};
    char* variable_conversions[] = {"X+YF++YF-FX--FXFX-YF+", "-FX+YFYF++YF+FX--FX-Y", "F", "-", "+"};
    move_ptr variable_actions[] = {do_nothing, do_nothing, move_forward, turn_right, turn_left};

    int initial_state_len = 7;
    char* state = "XF";

    float move_dist = 1.0f;
    double angle = double_pi/3.0f;
    float div_factor = 3.0f;

    return lsystem_init(
        start_x, start_y, start_direction, max_stack, 
        num_variables, variables, variable_conversion_lengths,
        variable_conversions, variable_actions, initial_state_len, 
        state, move_dist, angle, div_factor
    );
}

struct L_System* sierpinski_curve() {
    float start_x = 0.0f;
    float start_y = -0.5f;
    double start_direction = 0.0f;
    int max_stack = 256;
    int num_variables = 4;

    char variables[] = {'X', 'F', '-', '+'};
    int variable_conversion_lengths[] = {20, 1, 1, 1};
    char* variable_conversions[] = {"XF-F+F-XF+F+XF-F+F-X", "F", "-", "+"};
    move_ptr variable_actions[] = {do_nothing, do_nothing, move_forward, turn_left, turn_right};

    int initial_state_len = 9;
    char* state = "F+XF+F+XF";

    float move_dist = 1.0f;
    double angle = double_pi/2.0f;
    float div_factor = 3.0f;

    return lsystem_init(
        start_x, start_y, start_direction, max_stack, 
        num_variables, variables, variable_conversion_lengths,
        variable_conversions, variable_actions, initial_state_len, 
        state, move_dist, angle, div_factor
    );
}

struct L_System* gilbert_curve() {
    float start_x = -0.5f;
    float start_y = -0.5f;
    double start_direction = 0.0f;
    int max_stack = 256;
    int num_variables = 5;

    char variables[] = {'X', 'Y', 'F', '-', '+'};
    int variable_conversion_lengths[] = {11, 11, 1, 1, 1};
    char* variable_conversions[] = {"-YF+XFX+FY-", "+XF-YFY-FX+", "F", "-", "+"};
    move_ptr variable_actions[] = {do_nothing, do_nothing, move_forward, turn_left, turn_right};

    int initial_state_len = 1;
    char* state = "X";

    float move_dist = 1.0f;
    double angle = double_pi/2.0f;
    float div_factor = 2.0f;

    return lsystem_init(
        start_x, start_y, start_direction, max_stack, 
        num_variables, variables, variable_conversion_lengths,
        variable_conversions, variable_actions, initial_state_len, 
        state, move_dist, angle, div_factor
    );
}

struct L_System* cool_square_curve() {
    float start_x = -0.5f;
    float start_y = 0.5f;
    double start_direction = 0.0f;
    int max_stack = 256;
    int num_variables = 2;

    char variables[] = {'F', '+'};
    int variable_conversion_lengths[] = {11, 1};
    char* variable_conversions[] = {"FF+F+F+F+FF", "+"};
    move_ptr variable_actions[] = {move_forward, turn_right};

    int initial_state_len = 7;
    char* state = "F+F+F+F";

    float move_dist = 1.0f;
    double angle = double_pi/2.0f;
    float div_factor = 3.0f;

    return lsystem_init(
        start_x, start_y, start_direction, max_stack, 
        num_variables, variables, variable_conversion_lengths,
        variable_conversions, variable_actions, initial_state_len, 
        state, move_dist, angle, div_factor
    );
}

struct L_System* sierpinski_carpet() {
    float start_x = -0.5f;
    float start_y = 0.5f;
    double start_direction = 0.0f;
    int max_stack = 256;
    int num_variables = 4;

    char variables[] = {'F', '+', '[', ']'};
    int variable_conversion_lengths[] = {17, 1, 1, 1};
    char* variable_conversions[] = {"FFF[+FFF+FFF+FFF]", "+", "[", "]"};
    move_ptr variable_actions[] = {move_forward, turn_right, save_state, load_state};

    int initial_state_len = 1;
    char* state = "F";

    float move_dist = 1.0f;
    double angle = double_pi/2.0f;
    float div_factor = 3.0f;

    return lsystem_init(
        start_x, start_y, start_direction, max_stack, 
        num_variables, variables, variable_conversion_lengths,
        variable_conversions, variable_actions, initial_state_len, 
        state, move_dist, angle, div_factor
    );
}

struct L_System* levy_curve() {
    float start_x = 0.0f;
    float start_y = 0.0f;
    double start_direction = 0.0f;
    int max_stack = 256;
    int num_variables = 3;

    char variables[] = {'F', '-', '+'};
    int variable_conversion_lengths[] = {6, 1, 1};
    char* variable_conversions[] = {"-F++F-", "-", "+"};
    move_ptr variable_actions[] = {move_forward, turn_left, turn_right};

    int initial_state_len = 10;
    char* state = "F++F++F++F";

    float move_dist = 1.0f;
    double angle = double_pi/4.0;
    float div_factor = 1.5f;

    return lsystem_init(
        start_x, start_y, start_direction, max_stack, 
        num_variables, variables, variable_conversion_lengths,
        variable_conversions, variable_actions, initial_state_len, 
        state, move_dist, angle, div_factor
    );
}


int get_num_lines(struct L_System** systems, int num_systems, int num_iter) {
    int num_lines = 0;
    for (int i = 0; i < num_systems; i++) {
        iterate(systems[i], num_iter);
        num_lines += (*systems[i]).len_line_points;
    }
    return num_lines;
}

float* get_line_points(struct L_System** systems, int num_systems, int num_iter, int num_lines) {
    float* line_points = (float*) malloc(sizeof(float) * 4*num_lines);
    int line_pos = 0;
    for (int i = 0; i < num_systems; i++) {
        for (int k = 0; k < (*systems[i]).len_line_points*4; k++) {
            line_points[line_pos] = (*systems[i]).line_points[k];
            if (k%2 == 0) {
                line_points[line_pos] += 2*i;
            }
            line_pos++;
        }
    }
    return line_points;
}

int main() {
    int num_iter = 2;

    int num_systems = 14;
    struct L_System* systems[] = {
        sierpinski(),
        sierpinski_arrowhead(),
        koch_curve(),
        koch_snowflake(),
        binary_tree(),
        dragon_curve(), // iter = 20
        fractal_plant(),
        ice_square(), // iter = 4
        gosper_curve(), // iter = 6
        sierpinski_curve(),
        gilbert_curve(),
        cool_square_curve(),
        sierpinski_carpet(), // iter = 5
        levy_curve(),
    };

    int num_lines = get_num_lines(systems, num_systems, num_iter);
    float* line_points = get_line_points(systems, num_systems, num_iter, num_lines);

    for(int i = 0; i < num_lines; i++) {
        printf("Line %d: (%f, %f) to (%f, %f)\n", i, line_points[4*i], line_points[4*i+1], line_points[4*i+2], line_points[4*i+3]);
    }
    printf("-----------------------\n");


    


    
    
    printf("Done initializing L_System!\n");

    GLFWwindow* window = init();
    int program = programInit();
    unsigned int VAO;
    float x_offset, y_offset, zoom_factor;
    dataInit(&VAO, line_points, num_lines);

    while(!glfwWindowShouldClose(window)) {
        // for(int i = 0; i < num_lines; i++) {
        //     printf("Line %d: (%f, %f) to (%f, %f)\n", i, line_points[4*i], line_points[4*i+1], line_points[4*i+2], line_points[4*i+3]);
        // }
        // printf("-----------------------\n");
        inputs(window, &VAO, &line_points, &num_lines, systems, num_systems);
        dataInit(&VAO, line_points, num_lines);
        render(window, &VAO, program, num_lines);
    }
}