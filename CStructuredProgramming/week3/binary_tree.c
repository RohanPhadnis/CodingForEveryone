#include <stdio.h>
#include <stdlib.h>


typedef char DATA;
struct node {
    DATA d;
    struct node* left;
    struct node* right;
};
typedef struct node NODE;
typedef NODE *BTREE;    // binary tree is a pointer to node; binary tree will be pointer to its root


void in_order_print(BTREE root) {
    if (root != NULL) {
        in_order_print(root -> left);
        printf("%c ", root -> d);
        in_order_print(root -> right);
    }
}


BTREE new_node(void) {
    return malloc(sizeof(NODE));
}


BTREE init_node(DATA d1, BTREE p1, BTREE p2) {
    BTREE t;
    t = new_node();
    t -> d = d1;
    t -> left = p1;
    t -> right = p2;
    return t;
}


BTREE create_tree(DATA a[], int i, int size) {
    if (i >= size) {
        return NULL;
    } else {
        return init_node(a[i], create_tree(a, 2 * i + 1, size), create_tree(a, 2 * i + 2, size));
    }
}


int main() {
    char d[] = {'a', 'b', 'c', 'd', 'e'};
    BTREE b;
    b = create_tree(d, 0, 5);
    in_order_print(b);
    printf("\n");
    return 0;
}

/*
Result:
            a
    b                c
d       e
*/
