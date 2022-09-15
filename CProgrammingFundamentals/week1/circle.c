#include <stdio.h>

// define is a directive that defines macro values that are standardized throughout the program
#define PI 3.14159

int main() {
    double radius = 0.0, perimeter = 0.0, area = 0.0;   // variables
    printf("Enter radius: ");
    scanf("%lf", &radius);  // scanf is the input function
    /* String formatting
        * %d --> integer
        * %f --> float
        * %s --> string
        * %lf --> "long float" (double)
    */
    // &varname --> & is the pointer operator
    perimeter = 2 * PI * radius;
    area = PI * radius * radius;
    printf("The perimeter is %lf meters.\n", perimeter);
    printf("The area is %lf meters squared.\n", area);
    return 0;
}
