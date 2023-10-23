#include "stack.h"

struct Stack* stack_init(int max_stack_size) {
    struct Stack* s = (struct Stack*) malloc(sizeof(struct Stack));
    (*s).max_stack_size = max_stack_size;
    (*s).stack_pos = 0.0f;
    (*s).stack = (float*) malloc(sizeof(float) * max_stack_size);
    return s;
}

float pop(struct Stack* s) {
    (*s).stack_pos--;
    return (*s).stack[(*s).stack_pos];
}

void push(struct Stack* s, float item) {
    (*s).stack[(*s).stack_pos] = item;
    (*s).stack_pos++;
}