//
// Created by Rohan on 6/4/23.
// An implementation of Dijkstra's algorithm without using any stdlib optimizations.
// Efficiency is not max and can be improved by using hashing for sets and min heap implementation of priority queue.
//
#include <iostream>
#include <random>


using namespace std;


typedef struct nodeDistPair{char val; int cost;} nodeDistPair;
typedef struct listNode{nodeDistPair* data; listNode* next;} listNode;


inline nodeDistPair* buildPair(char val, int cost) {
    nodeDistPair* output = new nodeDistPair();
    output->val = val;
    output->cost = cost;
    return output;
}


inline char intToChar(int x) {
    return static_cast<char>(x + 65);
}


inline int charToInt(char x) {
    return static_cast<int>(x) - 65;
}


void printOutputArray(int* array, int size) {
    for (int i = 0; i < size; i++) {
        cout << intToChar(i) << ": " << array[i] << endl;
    }
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
    int n;
public:
    Graph(int n): n(n) {
        array = new Set[n];
        for (int i = 0; i < n; i++) {
            array[i] = Set();
        }
    }

    void addPair(char val1, char val2, int dist) {
        int index1 = charToInt(val1);
        int index2 = charToInt(val2);
        nodeDistPair* data1 = buildPair(val2, dist);
        nodeDistPair* data2 = buildPair(val1, dist);
        array[index1].add(data1);
        array[index2].add(data2);
    }

    Set getSet(char val) {
        return array[charToInt(val)];
    }

    int getN() {
        return n;
    }
};


int* dijkstra(Graph graph, char start) {
    Set visitedSet;
    PriorityQueue pq;
    pq.enqueue(buildPair(start, 0));
    nodeDistPair* current;
    nodeDistPair* currentChild;
    Set graphSet;
    int* output = new int[graph.getN()];
    for (int i = 0; i < graph.getN(); i++) {
        output[i] = 10000;
    }
    while (!pq.isEmpty()) {
        current = pq.dequeue();
        if (!visitedSet.contains(current)) {
            output[charToInt(current->val)] = current->cost;
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
    }
    return output;
}


Graph generateGraph(double density, int minNodes = 2, int maxNodes = 10) {
    srand(time(0));
    int size = rand() % (maxNodes - minNodes) + minNodes;
    Graph output(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            double num = static_cast<double>(rand()) / RAND_MAX;
            if (num <= density) {
                output.addPair(
                        intToChar(i),
                        intToChar(j),
                        static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 100)
                );
            }
        }
    }
    return output;
}


int main() {
    /**
        * matrix representation of desired graph
        *      A   B   C   D   E
        * A    0   2   3   -   -
        * B    2   0   -   8   4
        * C    3   -   0   1   -
        * D    -   8   1   0   2
        * E    -   4   -   2   0
    */
    Graph graph = generateGraph(0.2);
    int* dist = dijkstra(graph, 'A');
    printOutputArray(dist, graph.getN());
    return 0;
}
