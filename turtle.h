#ifndef TURTLE_H
#define TURTLE_H

struct Turtle{
    float x;
    float y;
    double direction;
    struct Stack* states;
};
#endif