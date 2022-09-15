#include <stdio.h>
#include <assert.h>

int main() {
    double x, y, result;
    while (1) {
        printf("Enter a number: ");
        scanf("%lf", &x);
        printf("Enter another number: ");
        scanf("%lf", &y);
        assert(y != 0);     // prevents integer division by 0
        result = x / y;
        printf("%lf / %lf = %lf\n\n", x, y, result);
    }
}
