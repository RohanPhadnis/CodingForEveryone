#include <stdio.h>


#define MAX_HW 20


void read_data(FILE* f, int array[], int* size) {
    *size = 0;
    while (fscanf(f, "%d", &array[*size]) == 1) {
        (*size)++;
    }
}


void print_data(int array[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%d\t", array[i]);
        if (i % 10 == 0 && i != 0) {
            printf("\n");
        }
    }
}


double average(int array[], int size) {
    int sum = 0;
    int i;
    for (i = 0; i < size; i++) {
        sum += array[i];
    }
    return (double) sum / size;
}


int main() {
    int i, size = MAX_HW;
    FILE* file;
    int data[MAX_HW] = {100, 0};

    file = fopen("homework_data.txt", "r");
    read_data(file, data, &size);
    printf("number of scores: %d\n", size);
    printf("scores: ");
    print_data(data, size);
    printf("\naverage score: %f\n", average(data, size));
    fclose(file);
    return 0;
}
