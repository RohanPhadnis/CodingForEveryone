/*
option 1 (general): bubble sort for structured list
*/

// importing dependencies
#include <stdio.h>
#include <stdlib.h>


// abstract data type definition
typedef struct list {
    int data;
    struct list* next;
} list;


// create_element method to make an element from native data
list* create_element(int num) {
    list* output = malloc(sizeof(list));
    output -> data = num;
    output -> next = NULL;
    return output;
}


// print_list method to print a list in rows of 5 (with title)
void print_list(list* l, char title[]) {
    list* current = l;
    int i = 0;
    printf("%s:\n", title);
    while (current != NULL) {
        printf("%d\t", current -> data);
        current = current -> next;
        if (++i % 5 == 0) {
            printf("\n");
        }
    }
}


// list_from_array method to create a linked list from native type array
list* list_from_array(int array[], int size) {
    int i;
    list* head = create_element(array[0]);
    list* current = head;
    for (i = 1; i < size; i++) {
        current -> next = create_element(array[i]);
        current = current -> next;
    }
    return head;
}


// count method to return size of linked list
int count(list* l) {
    int i = 0;
    list* current = l;
    while (current != NULL) {
        current = current -> next;
        i++;
    }
    return i;
}


// bubble_sort method to sort list using bubble sorting algorithm
void bubble_sort(list* l) {
    int i;
    int j;
    int size = count(l);
    list* head = l;
    list* current;
    int temp;
    for (i = 0; i < size; i++) {
        current = head;
        for (j = 0; j < size - 1; j++) {
            if (current->next != NULL && current->data > current->next->data) {
                temp = current -> data;
                current -> data = current -> next -> data;
                current -> next -> data = temp;
            }
            current = current -> next;
        }
    }
}


// main method
int main() {

    // random array generation
    int size = 100;
    int array[size];
    int i;
    for (i = 0; i < size; i++) {
        array[i] = rand() % 1000;
    }

    // list creation
    list* head = list_from_array(array, size);
    printf("list size: %d\n", count(head));
    print_list(head, "raw list");
    printf("\n");

    // list sorting
    bubble_sort(head);
    print_list(head, "sorted list");
    printf("\n");

    return 0;
}
