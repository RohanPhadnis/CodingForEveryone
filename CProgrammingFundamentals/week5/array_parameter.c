#include <stdio.h>

double average_grades(int size, int grades[]) {
    int i;
    double sum = 0;
    for (i = 0; i < size; i++) {
        sum += grades[i];
    }
    return sum / size;
}

void print_grades(int size, int grades[]) {
    int i;
    printf("I have %d grades:\n", size);
    for (i = 0; i < size; i++) {
        printf("%d \t", grades[i]);
    }
}

int main(void) {
    const int SIZE = 5;
    int grades[SIZE] = {78, 67, 92, 83, 88};
    print_grades(SIZE, grades);
    printf("\n");
    printf("grade average: %lf \n", average_grades(SIZE, grades));
    return 0;
}
