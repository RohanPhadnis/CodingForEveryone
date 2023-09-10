//
// Created by Rohan on 9/9/23.
//
#include <iostream>

using namespace std;

const int INITIAL_ARRAY_CAPACITY = 10;
inline int hashCode(int x) {return x;}
inline bool equals(int x, int y) {return x==y;}
inline int hashCode(char x) {return static_cast<int>(x) - 97;}
inline bool equals(char x, char y) {return x==y;}


class Vertex {
private:
    char data;
public:
    Vertex(char data): data(data) {}
    char getData() {return data;}
    void setData(char data) {this->data = data;}
};
inline int hashCode(Vertex x) {return hashCode(x.getData());}
inline bool equals(Vertex x, Vertex y) {return x.getData() == y.getData();}
inline ostream& operator<<(ostream& out, Vertex x) {return out << x.getData();}


class Edge {
private:
    Vertex start;
    Vertex end;
    int cost;
public:
    Edge(char start, char end, int cost): start(start), end(end), cost(cost) {}
    char getStart() {return start.getData();}
    char getEnd() {return end.getData();}
    int getCost() {return cost;}
};
inline int hashCode(Edge x) {return hashCode(x.getStart()) + hashCode(x.getEnd()) + hashCode(x.getCost());}
inline bool equals(Edge x, Edge y) {return x.getStart() == y.getStart() && x.getEnd() == y.getEnd() && x.getCost() == y.getCost();}
inline bool operator==(Edge x, Edge y) {return x.getCost() == y.getCost();}
inline bool operator>(Edge x, Edge y) {return x.getCost() > y.getCost();}
inline bool operator<(Edge x, Edge y) {return x.getCost() < y.getCost();}
inline bool operator>=(Edge x, Edge y) {return x > y || x == y;}
inline bool operator<=(Edge x, Edge y) {return x < y || x == y;}
inline ostream& operator<<(ostream& out, Edge x) {return out << '(' << x.getStart() << ", " << x.getEnd() << ", " << x.getCost() << ')' ;}


template <class T>
class Node {
private:
    T data;
    Node<T>* next;
public:
    Node<T>(T data): data(data), next(nullptr) {}
    T getData() {return data;}
    Node<T>* getNext() {return next;}
    void setData(T data) {this->data = data;}
    void setNext(Node<T>* next) {this->next = next;}
};
template <class T>
inline ostream& operator<<(ostream& out, Node<T>* x) {
    if (x != nullptr) {
        return out << x->getData() << " -> ";
    }
    return out << "None";
}


template <class T>
class LinkedList{
private:
    int size;
    Node<T>* head;
public:
    LinkedList(): head(nullptr), size(0) {}
    Node<T>* getHead() {return head;}
    void add(T data) {
        if (head != nullptr) {
            Node<T>* node = new Node<T>(data);
            node->setNext(head);
            head = node;
            size++;
        } else {
            size++;
            head = new Node<T>(data);
        }
    }
};
template <class T>
inline ostream& operator<<(ostream& out, LinkedList<T> x) {
    Node<T>* node = x.getHead();
    while (node != nullptr) {
        out << node;
        node = node->getNext();
    }
    return out;
}


template <class T>
class HashSet {
private:
    int size;
    int capacity;
    LinkedList<T>* backingArray;
    void resize() {
        if (static_cast<double>(size) / capacity >= 0.75) {
            LinkedList<T>* temp = backingArray;
            backingArray = new LinkedList<T>[capacity * 2 + 1];
            for (int i = 0; i < capacity; i++) {
                Node<T>* node = temp[i].getHead();
                while (node != nullptr) {
                    int hc = hashCode(node->getData());
                    backingArray[hc % capacity].add(node->getData());
                    node = node->getNext();
                }
            }
            capacity = capacity * 2 + 1;
        }
    }
public:
    HashSet(): size(0), capacity(INITIAL_ARRAY_CAPACITY) {
        backingArray = new LinkedList<T>[capacity];
    }
    bool contains(T data) {
        Node<T>* node = backingArray[hashCode(data) % capacity].getHead();
        while (node != nullptr) {
            if (equals(node->getData(), data)) {
                return true;
            }
            node = node->getNext();
        }
        return false;
    }
    void add(T data) {
        backingArray[hashCode(data) % capacity].add(data);
        size++;
        resize();
    }
    void display() {
        for (int i = 0; i < capacity; i++) {
            cout << i << ": " << backingArray[i] << endl;
        }
        cout << endl;
    }
};


template <class T>
class PriorityQueue {
private:
    int capacity;
    T* backingArray;
    int size;
    void swap(int index1, int index2) {
        T temp = backingArray[index1];
        backingArray[index1] = backingArray[index2];
        backingArray[index2] = temp;
    }
    void upHeap(int index) {
        int parent = index / 2;
        if (parent > 0 && backingArray[parent] > backingArray[index]) {
            swap(parent, index);
            upHeap(parent);
        }
    }
    void downHeap(int index) {
        int child1 = index * 2;
        int child2 = index * 2 + 1;
        if (child1 < capacity) {
            if (child2 < capacity) {
                if ((backingArray[index] > backingArray[child1]) || (backingArray[index] > backingArray[child2])) {
                    int child = (backingArray[child1] <= backingArray[child2]) ? child1: child2;
                    swap(child, index);
                    downHeap(child);
                }
            }
            if (backingArray[index] > backingArray[child1]) {
                swap(index, child1);
                downHeap(child1);
            }
        }
    };
    void resize() {
        T* temp = backingArray;
        backingArray = new T[capacity * 2 + 1];
        for (int i = 1; i < capacity; i++) {
            backingArray[i] = temp[i];
        }
        capacity = capacity * 2 + 1;
    }
public:
    PriorityQueue(): size(0), capacity(INITIAL_ARRAY_CAPACITY) {
        backingArray = new T[capacity];
        backingArray[0] = nullptr;
    }
    // todo implement this method
    void buildHeap(T array[]);
    void add(T data) {
        if (size == capacity - 1) {
            resize();
        }
        backingArray[++size] = data;
        upHeap(size);
    }
    T remove() {
        T output = backingArray[1];
        backingArray[1] = backingArray[size--];
        downHeap(1);
        return output;
    }
    void display() {
        for (int i = 0; i < capacity; i++) {
            cout << backingArray[i] << ", ";
        }
        cout << endl;
    }
};


class Graph {
private:
    HashSet<Edge>* backingArray;
    int n;
public:
    Graph(int n): n(n) {
        backingArray = new HashSet<Edge>[n];
    }

    void addEdge(char a, char b, int cost) {
        backingArray[hashCode(a)].add(*new Edge(a, b, cost));
        backingArray[hashCode(b)].add(*new Edge(b, a, cost));
    }

    void display() {
        for (int i = 0; i < n; i++) {
            cout << static_cast<char>(i+97) << ": " << endl;
            backingArray[i].display();
        }
        cout << endl;
    }
};


int main() {
    Graph g(5);
    g.addEdge('a', 'b', 3);
    g.addEdge('a', 'c', 5);
    g.addEdge('b', 'c', 1);
    g.display();
    return 0;
}
