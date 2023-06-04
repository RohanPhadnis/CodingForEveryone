//
// Created by Rohan on 6/4/23.
//
#include <stdlib.h>
#include <stdio.h>

typedef struct point{
    double x;
    double y;
} point;

point* sum(point* p1, point* p2) {
    point* output = malloc(sizeof(point));
    output -> x = p1 -> x + p2 -> x;
    output -> y = p1 -> y + p2 -> y;
    return output;
}

void print_point(point* p) {
    printf("(%lf, %lf)\n", p->x, p->y);
}

int main() {
    point* p1 = malloc(sizeof(point));
    p1 -> x = 0;
    p1 -> y = 2;

    point* p2 = malloc(sizeof(point));
    p2 -> x = 3;
    p2 -> y = 4;

    print_point(p1);
    print_point(p2);
    print_point(sum(p1, p2));

    return 0;
}
