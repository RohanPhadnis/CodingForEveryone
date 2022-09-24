// binary tree exercise

// importing dependencies
#include <stdio.h>
#include <stdlib.h>

// abstract data type for binary tree node
typedef struct node {int data; struct node* left; struct node* right;} node;

// get_size method for extracting array size from file
int get_size(FILE* f) {
    rewind(f);
    int i;
    fscanf(f, "%d", &i);
    return i;
}

// read_file method to read file into array
void read_file(FILE*f, int arr[], int s) {
    int i;
    int num;
    for (i = 0; i < s; i++) {
        fscanf(f, "%d", &num);
        arr[i] = num;
    }
}

// create_node to create a node in a binary tree
node* create_node(int d) {
    node* output = malloc(sizeof(node));
    output -> data = d;
    output -> left = NULL;
    output -> right = NULL;
    return output;
}

// place method to place values in order
void place(node* r, int d) {
    if (r -> data > d) {
        if (r -> left == NULL) {
            r -> left = create_node(d);
        } else {
            place(r -> left, d);
        }
    } else {
        if (r -> right == NULL) {
            r -> right = create_node(d);
        } else {
            place(r -> right, d);
        }
    }
}

// array_to_tree method to convert array into binary tree
node* array_to_tree(int arr[], int s) {
    node* r = create_node(arr[0]);
    int i;
    for (i = 1; i < s; i++) {
        place(r, arr[i]);
    }
    return r;
}

// in_order_print method to print binary tree values in order
void in_order_print(node* r) {
    if (r != NULL) {
        in_order_print(r -> left);
        printf("%d\t", r -> data);
        in_order_print(r -> right);
    }
}

// print_array method to print array values
void print_array(int arr[], int s) {
    int i;
    for (i = 0; i < s; i++) {
        printf("%d\t", arr[i]);
    }
    printf("\n");
}

// main method. needs input file argument
int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("please enter input file name \n");
    } else {
        // file reading
        FILE* file = fopen(argv[1], "r");
        int size = get_size(file);
        int array[size];
        read_file(file, array, size);
        printf("array: ");
        print_array(array, size);

        // binary tree creation
        node* root;
        root = array_to_tree(array, size);
        printf("binary tree: ");
        in_order_print(root);
        printf("\n");
        fclose(file);
    }
    return 0;
}
