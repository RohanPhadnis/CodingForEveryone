//
// Created by Rohan on 6/4/23.
// An implementation of Dijkstra's algorithm without using any stdlib optimizations.
// Efficiency is not max and can be improved by using hashing for sets and min heap implementation of priority queue.
//
#include <iostream>

using namespace std;


typedef struct nodeDistPair{char val; int cost;} nodeDistPair;
typedef struct listNode{nodeDistPair* data; listNode* next;} listNode;


nodeDistPair* buildPair(char val, int cost) {
    nodeDistPair* output = new nodeDistPair();
    output->val = val;
    output->cost = cost;
    return output;
}


class PriorityQueue {
private:
    listNode* head;
    int size;
public:
    PriorityQueue() {
        head = NULL;
        size = 0;
    }

    void enqueue(nodeDistPair* data) {
        listNode* d = new listNode();
        d->data = data;
        d->next = NULL;
        if (head == NULL) {
            head = d;
        }
        else if (data->cost < head->data->cost) {
            d->next = head;
            head = d;
        } else {
            listNode* current = head;
            while (current->next != NULL && data->cost > current->next->data->cost) {
                current = current -> next;
            }
            d -> next = current -> next;
            current -> next = d;
        }
        size++;
    }

    nodeDistPair* dequeue() {
        if (head != NULL) {
            nodeDistPair* output = head -> data;
            head = head -> next;
            size--;
            return output;
        }
        return NULL;
    }

    nodeDistPair* peek() {
        if (head != NULL) {
            return head -> data;
        }
        return NULL;
    }

    bool isEmpty() {
        return size == 0;
    }
};


class Set {
private:
    listNode* head;
    listNode* currentNode;
    int size;
public:
    bool contains(nodeDistPair* data) {
        listNode* current = head;
        while (current != NULL) {
            if (current->data->val == data->val) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void add(nodeDistPair* data) {
        if (!contains(data)) {
            size++;
            listNode* d = new listNode();
            d->data = data;
            d->next = head;
            head = d;
            currentNode = head;
        }
    }

    nodeDistPair* getNext() {
        listNode* output = currentNode;
        if (currentNode != NULL) {
            currentNode = currentNode->next;
            return output->data;
        }
        return NULL;
    }

    nodeDistPair* remove() {
        if (head != NULL) {
            nodeDistPair* output = head->data;
            head = head->next;
            currentNode = head;
            size--;
            return output;
        }
        return NULL;
    }

    bool isEmpty() {
        return size == 0;
    }

    Set() {
        head = NULL;
        size = 0;
    }

    Set(nodeDistPair* head) {
        add(head);
    }
};


class Graph {
private:
    Set* array;
public:
    Graph(int n) {
        array = new Set[n];
        for (int i = 0; i < n; i++) {
            array[i] = Set();
        }
    }

    void addPair(char val1, char val2, int dist) {
        int index1 = static_cast<int>(val1) - 65;
        int index2 = static_cast<int>(val2) - 65;
        nodeDistPair* data1 = buildPair(val2, dist);
        nodeDistPair* data2 = buildPair(val1, dist);
        array[index1].add(data1);
        array[index2].add(data2);
    }

    Set getSet(char val) {
        return array[static_cast<int>(val) - 65];
    }
};


int dijkstra(Graph graph, char start, char end) {
    Set visitedSet;
    PriorityQueue pq;
    pq.enqueue(buildPair(start, 0));
    nodeDistPair* current;
    nodeDistPair* currentChild;
    Set graphSet;

    while (!pq.isEmpty()) {
        current = pq.dequeue();
        if (current->val == end) {
            return current->cost;
        }
        graphSet = graph.getSet(current->val);
        currentChild = graphSet.getNext();
        while (currentChild != NULL) {
            if (!visitedSet.contains(currentChild)) {
                pq.enqueue(buildPair(currentChild->val, currentChild->cost + current->cost));
            }
            currentChild = graphSet.getNext();
        }
        visitedSet.add(current);
    }

    return 0;
}


int main() {
    /**
        * matrix representation of desired graph
        *      A   B   C   D   E
        * A    0   2   3   -   -
        * B    2   0   -   3   5
        * C    3   -   0   1   -
        * D    -   3   1   0   2
        * E    -   5   -   2   0
    */
    Graph graph(5);
    graph.addPair('A', 'B', 2);
    graph.addPair('A', 'C', 3);
    graph.addPair('B', 'D', 3);
    graph.addPair('B', 'E', 5);
    graph.addPair('C', 'D', 1);
    graph.addPair('D', 'E', 2);
    int dist = dijkstra(graph, 'A', 'E');
    cout << dist << endl;
    return 0;
}
