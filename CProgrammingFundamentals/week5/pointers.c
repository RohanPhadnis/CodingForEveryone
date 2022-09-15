#include <stdio.h>

int main(void) {
    const int SIZE = 5;
    int grades[SIZE] = {78, 67, 92, 83, 88};
    double sum = 0.0;
    double *ptr_to_sum = &sum;
    int i;
    printf("\n my grades are: \n");
    for (i = 0; i < SIZE; i++) {
        printf("%d\t", grades[i]);
        sum += grades[i];
    }
    printf("\n my average grade is: %lf \n", sum / SIZE);
    printf("The sum's memory address is: %p or %lu \n It stores: %lf \n", ptr_to_sum, ptr_to_sum, *ptr_to_sum);
    printf("grades are at: %lu \n", grades);
    printf("address of the 5th element (offset by 20): %lu", grades + 5);
    return 0;
}
