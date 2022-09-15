#include <stdio.h>

int main(void) {
    double fahrenheit=0, celsius=0;
    printf("Enter fahrenheit temperature: ");
    scanf("%lf", &fahrenheit);
    celsius = (fahrenheit - 32) / 1.8;
    printf("The temperature is %lf degrees celsius.\n", celsius);
    return 0;
}
