#include <stdio.h>
#include <stdlib.h>


void print_file(FILE* f) {
    int c;
    rewind(f);
    while ((c = getc(f)) != EOF) {
        putc(c, stdout);
    }
}


void double_space(FILE* f_in, FILE* f_out) {
    int c;
    rewind(f_in);
    while ((c = getc(f_in)) != EOF) {
        putc(c, f_out);
        if (c == '\n') {
            putc('\n', f_out);
        }
    }
}


int main(int argc, char* argv[]) {
    FILE *file_input, *file_output;

    if (argc != 3) {
        printf("Need executable input file and output file\n");
        exit(1);
    }

    file_input = fopen(argv[1], "r+");
    file_output = fopen(argv[2], "w+");
    printf("my %s file as read is\n\n", argv[1]);
    print_file(file_input);
    printf("\n\n");
    double_space(file_input, file_output);
    printf("my %s file double spaced is\n\n", argv[2]);
    print_file(file_output);
    printf("\n\n");
    fclose(file_input);
    fclose(file_output);
    return 0;
}
