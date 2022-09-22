// option 1: read array from an input file and write array data and metadata to an output file


// importing dependencies
#include <stdio.h>


// average method to compute average of an array
double average(int array[], int size) {
    int total = 0;
    int i;
    for (i = 0; i < size; i++) {
        total += array[i];
    }
    return (double) total / size;
}


// max method to return the maximum value within an array
int max(int array[], int size) {
    int num = array[0];
    int i;
    for (i = 1; i < size; i++) {
        if (array[i] > num) {
            num = array[i];
        }
        i++;
    }
    return num;
}



// set_size method to read the first number from the file and set it to the size variable
void set_size(FILE* f, int* s) {
    rewind(f);
    fscanf(f, "%d", s);
}


// read_file method to read the remaining file data points into the array
void read_file(FILE* f, int array[], int s) {
    int i = 0;
    int c;
    while ((c = getc(f)) != EOF && i < s) {
        fscanf(f, "%d", &array[i]);
        i++;
    }
}


// print_array method to print out values of an array to the console
void print_array(int array[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%d\t", array[i]);
    }
    printf("\n");
}


// fprint_array method to print out values of an array to a file
void fprint_array(FILE* f, int array[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        fprintf(f, "%d\t", array[i]);
    }
    putc('\n', f);
}


// main method
int main() {
    // variable definition and instantiation
    FILE* file_input = fopen("input-hw3", "r");
    FILE* file_output = fopen("answer-hw3", "w");
    int size;
    set_size(file_input, &size);
    int data[size];
    read_file(file_input, data, size);

    // printing data to console
    printf("size: %d\n", size);
    printf("array values: ");
    print_array(data, size);
    printf("average: %lf\n", average(data, size));
    printf("maximum: %d\n", max(data, size));

    // printing data to file
    rewind(file_output);
    fprintf(file_output, "size: %d\n", size);
    fprintf(file_output, "array values: ");
    fprint_array(file_output, data, size);
    fprintf(file_output, "average: %lf\n", average(data, size));
    fprintf(file_output, "maximum: %d\n", max(data, size));

    // closing and return
    fclose(file_input);
    fclose(file_output);
    return 0;
}
