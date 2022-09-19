#include <stdio.h>
#include <stdlib.h>

typedef struct list {int data; struct list *next;} list;

int is_empty(const list *l) {return l == NULL;}

void print_list(list *h, char *title) {
    printf("%s: ", title);
    while (h != NULL) {
        printf(" %d ", h -> data);
        h = h -> next;
    }
}

list* create_list(int num) {
    list* l = malloc(sizeof(list));
    l -> data = num;
    l -> next = NULL;
    return l;
}

list* add_to_front(list* h, int num) {
    list* head = create_list(num);
    head -> next = h;
    return head;
}

list* array_to_list(int array[], int size) {
    list* head = NULL;
    int i;
    for (i = 0; i < size; i++) {
        head = add_to_front(head, array[i]);
    }
    return head;
}

int count(list* h) {
    int i = 0;
    list* current = h;
    while (!is_empty(current)) {
        current = current -> next;
        i++;
    }
    return i;
}

void concat(list* first, list* second) {
    list* current = first;
    while (!is_empty(current -> next)) {
        current = current -> next;
    }
    current -> next = second;
}

void insert(list* h, int index, int value) {
    int i = 0;
    list* current = h;
    list* next;
    list* target = create_list(value);
    while (i < index - 1 && !is_empty(current -> next)) {
        current = current -> next;
        i++;
    }
    next = current -> next;
    current -> next = target;
    target -> next = next;
}

void delete(list* h, int index) {
    int i = 0;
    list* before;
    list* current = h;
    list* after;
    while (i < index - 1 && !(is_empty(current -> next))) {
        current = current -> next;
        i++;
    }
    before = current;
    current = before -> next;
    after = current -> next;
    before -> next = after;
}


int main() {
    list list_of_int;
    int array[] = {2, 3, 5, 7, 8, 9};

    // arrray to list conversion
    list* head = array_to_list(array, 6);
    print_list(head, "data list");
    printf("\n");

    // count function
    printf("length: %d\n", count(head));

    // concatenation
    int array2[] = {10, 11, 12};
    list* head2 = array_to_list(array2, 3);
    concat(head, head2);
    print_list(head, "concatenated array");
    printf("\n");

    // insert
    insert(head, 1, 6);
    print_list(head, "inserted array");
    printf("\n");

    // delete
    delete(head, 1);
    print_list(head, "deleted array");
    printf("\n");
}
