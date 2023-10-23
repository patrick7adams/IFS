#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

struct Stack {
    int max_stack_size;
    float* stack;
    int stack_pos;
};

struct Stack* stack_init(int max_stack_size);
float pop(struct Stack* s);
void push(struct Stack* s, float item);
#endif