#include <stdio.h>
#include <math.h>

extern int reps = 0;

void f(void) {
    static int called = 0;
    printf("Called %d times\n", called);
    called += 1;
    reps += called;
}


int main(void)
{
    double interval;
    int i;
    while (interval<1)
    {
        printf("sin( %lf ) = %lf \n", interval, sin(interval));
        printf("cos( %lf ) = %lf \n", interval, cos(interval));
        interval = interval + 0.1;
    }

    printf("\n++ +++++\n");
    return 0;
}
