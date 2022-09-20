// Duplicate Removal for Doubly Linked List

// importing dependencies
#include <stdio.h>
#include <stdlib.h>


// abstract data type definition
typedef struct list {
    int data;
    struct list* before;
    struct list* after;
} list;


// create_element method to create list element from primitive
list* create_element(int num) {
    list* output = malloc(sizeof(list));
    output -> data = num;
    output -> before = NULL;
    output -> after = NULL;
    return output;
}


// add_to_front method to insert primitive element into list head
list* add_to_front(list* h, int num) {
    list* head = create_element(num);
    head -> after = h;
    h -> before = head;
    return head;
}


// list_from_array method to create list object from primitive type array
list* list_from_array(int array[], int size) {
    int i;
    list* head;
    for (i = 0; i < size; i++) {
        if (i == 0) {
            head = create_element(array[i]);
        } else {
            head = add_to_front(head, array[i]);
        }
    }
    return head;
}


// count method to return array size
int count(list* h) {
    list* current = h;
    int i = 0;
    while(current != NULL) {
        current = current -> after;
        i++;
    }
    return i;
}


// bubble_sort function to sort list using bubble sort algorithm
void bubble_sort(list* h) {
    int i, j, temp;
    int size = count(h);
    list* current;
    for (i = 0; i < size; i++) {
        current = h;
        for (j = 0; j < size - i; j++) {
            if (current->after != NULL && current->data > current->after->data) {
                temp = current->data;
                current -> data = current -> after -> data;
                current -> after -> data = temp;
            }
            current = current -> after;
        }
    }
}


// remove_duplicates method to truncate all list duplicates
void remove_duplicates(list* h) {
    list* current = h;
    while (current != NULL) {
        if (current->before != NULL && current->data == current->before->data) {
            current->before->after = current->after;
            if (current -> after != NULL) {
                current->after->before = current->before;
            }
        }
        current = current -> after;
    }
}


// print_list method to print list elements to console (with title)
void print_list(list* h, char title[]) {
    int i = 0;
    list* current = h;
    printf("%s:\n", title);
    while (current != NULL) {
        printf("%d\t", current->data);
        current = current -> after;
        if (++i % 5 == 0) {
            printf("\n");
        }
    }
}


// main method
int main() {

    // random array generation
    int size = 200;
    int array[size];
    int i;
    for (i = 0; i < size; i++) {
        array[i] = rand() % 50;
    }

    // list creation
    list* head = list_from_array(array, size);
    print_list(head, "initial list");
    printf("list size: %d\n", count(head));
    printf("\n");

    // sorting
    bubble_sort(head);
    print_list(head, "sorted list");
    printf("list size: %d\n", count(head));
    printf("\n");

    // duplicate removal
    remove_duplicates(head);
    print_list(head, "truncated list");
    printf("list size: %d\n", count(head));
    printf("\n");

    return 0;
}
