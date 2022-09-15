#include <stdio.h>

int main(void) {
    const int SIZE = 5;
    int grades[SIZE] = {78, 67, 82, 83, 88};
    double sum = 0.0;
    int i;
    printf("\n my grades are: \n");
    for (i = 0; i < SIZE; i++) {
        printf("%d\t", grades[i]);
        sum += grades[i];
    }
    printf("\n my average grade is: %lf \n", sum / SIZE);
    return 0;
}
