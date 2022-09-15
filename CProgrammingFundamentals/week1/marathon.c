#include <stdio.h>

int main(void) {
    int miles=26, yards=385;
    double kilometers;
    kilometers = 1.609 * (miles + yards / 1760.0);
    // casting: conversion of one datatype to another
    // yards / 1760 = 0, because it uses integer division
    // the more extensive datatype (double) is preserved in the operation
    printf("A marathon is %lf kilometers.\n", kilometers);
    return 0;
}
