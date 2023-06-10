//
// Created by Rohan on 6/5/23.
// A basic implementation of a singly linked list.
//
#include <iostream>


using namespace std;


typedef struct list_node{int data; list_node* next;} list_node;


class List {
public:
    // constructor
    List(): head(nullptr), cursor(nullptr){}

    // conversion constructor: array -> list
    List(int* array, int size) {
        if (size > 0) {
            head = new list_node();
            head->data = array[0];
            list_node* current = head;
            list_node* build;
            for (int i = 1; i < size; i++) {
                build = new list_node();
                build->data = array[i];
                current->next = build;
                current = build;
            }
            cursor = head;
        }
    }

    // deep copy constructor
    List(List const &list) {
        head = new list_node();
        head->data = list.get_element();
        list_node* build;
        list_node* current = head;
        while (list.has_next()) {
            build = new list_node;
            build->data = list.get_element();
            current->next = build;
        }
        cursor = head;
    }

    // destructor
    ~List() {
        for (cursor = head; cursor != nullptr;) {
            cursor = head->next;
            delete head;
            head = cursor;
        }
    }

    // prepend to add to front
    void prepend(int data) {
        list_node* h = new list_node;
        h->data = data;
        h->next = head;
        cursor = head = h;
    }

    // get current element
    int get_element() const {
        return cursor->data;
    };

    // has next method
    bool has_next() const {
        return cursor->next != NULL;
    };

    // advance iterator
    void advance() {
        cursor = cursor->next;
    }

    // print
    void print() {
        list_node* current = head;
        while (current != nullptr) {
            cout << current->data << "\t";
            current = current->next;
        }
        cout << endl;
    }
private:
    list_node* head; // head of the SLL
    list_node* cursor;   // current iterator value of SLL
};


int main() {
    List l;
    for (int i = 0; i < 50; i = (i + 1) * 2) {
        l.prepend(i);
    }
    l.print();
    return 0;
}
