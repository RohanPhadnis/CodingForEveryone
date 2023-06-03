/*
 * C is a pass by value language. Call by reference can be simulated using pointers.
 * Need to dereference data for swapping.
 * 2 functions need to have different names.
 * We need to create 2 separate swapping functions for ints and doubles
 * */

#include <stdio.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swap_double(double* a, double* b) {
    double temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int a = 0;
    int b = 1;
    double c = 3.14;
    double d = 0.5;

    printf("original a: %d\toriginal b: %d\n", a, b);
    swap(&a, &b);
    printf("new a: %d\tnew b: %d\n", a, b);

    printf("original c: %lf\toriginal d: %lf\n", c, d);
    swap_double(&c, &d);
    printf("new c: %lf\tnew d: %lf\n", c, d);

    return 0;
}