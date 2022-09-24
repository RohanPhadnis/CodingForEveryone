#include <stdio.h>
#include <stdlib.h>


typedef struct list {int data; struct list* next;} list;

int is_empty(const list* l) {return l == NULL;}

list* create_list(int d) {
    list* head = malloc(sizeof(list));
    head -> data = d;
    head -> next = NULL;
    return head;
}

list* add_to_front(list* h, int d) {
    list* head = create_list(d);
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

void print_list(list* l, char title[]) {
    list* current = l;
    printf("%s: ", title);
    while (!is_empty(current)) {
        printf("%d\t", current -> data);
        current = current -> next;
    }
    printf("\n");
}

int count(list* l) {
    list* current = l;
    int i = 0;
    while (!is_empty(current)) {
        current = current -> next;
        i++;
    }
    return i;
}

// deletion of an element
// head and prev are pointers to pointers because the value in the pointer is to be modified
void delete(list* elem, list **prev, list** hd) {
    if (*hd == *prev) {
        *hd = elem -> next;
    } else {
        (*prev) -> next = elem -> next;
    }
    free(elem);
}

// deletion of the entire list
void delete_list(list *h) {
    list* temp;
    if (h != NULL) {
        delete_list(h = h -> next); // deletes recursively
        free(temp);
    }
}

void concat(list* h1, list* h2) {
    if (h1 == NULL) {
        h1 = h2;
    } else if (h1 -> next == NULL) {
        h1 -> next = h2;
    } else {
        concat(h1 -> next, h2);
    }
}


int main() {
    list list_of_int;
    list *head1 = NULL, *head2 = NULL;
    int data[6] = {2, 3, 5, 7, 8, 9};
    int data2[] = {17, 6, 99};
    head1 = array_to_list(data, 6);
    head2 = array_to_list(data2, 3);
    print_list(head1, "head 1");
    print_list(head2, "head 2");
    concat(head1, head2);
    print_list(head1, "concatenated list");
    printf("size of concatenated list: %d\n", count(head1));
    delete(head1, &head1, &head1);
    print_list(head1, "delete from list");
    delete(head1->next->next, &head1->next, &head1);
    print_list(head1, "delete from body");
    printf("\n");
    return 0;
}
