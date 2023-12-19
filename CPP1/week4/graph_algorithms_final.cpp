//
// Created by Rohan on 9/9/23.
//
#include <iostream>
#include <random>

using namespace std;

const int INITIAL_ARRAY_CAPACITY = 10;
const int INFINITY_VALUE = 100000;
inline int hashCode(int x) {return x;}
inline bool equals(int x, int y) {return x==y;}
inline int hashCode(char x) {return static_cast<int>(x) - 97;}
inline bool equals(char x, char y) {return x==y;}
inline double randDouble() {return static_cast<double>(rand()) / RAND_MAX;}
inline int randInt(int min, int max) {return rand() % (max-min) + min;}


class Vertex {
private:
    char data;
public:
    Vertex(): data('0') {}
    Vertex(char data): data(data) {}
    char getData() {return data;}
    void setData(char data) {this->data = data;}
};
inline int hashCode(Vertex x) {return hashCode(x.getData());}
inline bool equals(Vertex x, Vertex y) {return x.getData() == y.getData();}
inline ostream& operator<<(ostream& out, Vertex x) {return out << x.getData();}
inline bool isNull(Vertex v) {
    return v.getData() == '0';
}


class Edge {
private:
    Vertex start;
    Vertex end;
    int cost;
public:
    Edge(): start('0'), end('0'), cost(0) {}
    Edge(char start, char end, int cost): start(start), end(end), cost(cost) {}
    Vertex getStart() {return start;}
    Vertex getEnd() {return end;}
    int getCost() {return cost;}
    bool isNull() {return start.getData() == '0' && end.getData() == '0' && cost == 0;}
};
inline int hashCode(Edge x) {return hashCode(x.getStart()) + hashCode(x.getEnd()) + hashCode(x.getCost());}
inline bool equals(Edge x, Edge y) {return equals(x.getStart(), y.getStart()) && equals(x.getEnd(), y.getEnd()) && x.getCost() == y.getCost();}
inline bool operator==(Edge x, Edge y) {return x.getCost() == y.getCost();}
inline bool operator>(Edge x, Edge y) {return x.getCost() > y.getCost();}
inline bool operator<(Edge x, Edge y) {return x.getCost() < y.getCost();}
inline bool operator>=(Edge x, Edge y) {return x > y || x == y;}
inline bool operator<=(Edge x, Edge y) {return x < y || x == y;}
inline ostream& operator<<(ostream& out, Edge x) {return out << '(' << x.getStart() << ", " << x.getEnd() << ", " << x.getCost() << ')' ;}
inline bool isNull(Edge e) {return e.getStart().getData() == '0' && e.getEnd().getData() == '0' && e.getCost() == 0;}


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
    int index;
    bool resetPerformed;
    Node<T>* iterator;
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
    HashSet(): size(0), capacity(INITIAL_ARRAY_CAPACITY), index(0), iterator(nullptr), resetPerformed(false) {
        backingArray = new LinkedList<T>[capacity];
    }
    int getSize() {
        return size;
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
        reset();
    }
    void reset() {
        index = 0;
        iterator = nullptr;
        resetPerformed = true;
    }
    T getNext() {
        if (size == 0) {
            return T();
        }
        if (resetPerformed) {
            while (iterator == nullptr) {
                iterator = backingArray[index].getHead();
                index++;
            }
        } else {
            if (iterator -> getNext() == nullptr) {
                iterator = nullptr;
                while (iterator == nullptr && index < capacity) {
                    iterator = backingArray[index].getHead();
                    index++;
                }
            } else {
                iterator = iterator -> getNext();
            }
        }
        resetPerformed = false;
        if (iterator == nullptr) {
            return T();
        } else {
            return iterator->getData();
        }
    }
    void unify(HashSet<T> other) {
        T data = other.getNext();
        while (!isNull(data)) {
            this->add(data);
            data = other.getNext();
        }
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
                    if (!isNull(backingArray[child])) {
                        swap(child, index);
                        downHeap(child);
                    }
                }
            }
            if (backingArray[index] > backingArray[child1] && !isNull(backingArray[child1])) {
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
        backingArray[size+1] = T();
        downHeap(1);
        return output;
    }
    void display() {
        for (int i = 0; i < capacity; i++) {
            cout << backingArray[i] << ", ";
        }
        cout << endl;
    }
    int getSize() {return size;}
};


class Graph {
private:
    HashSet<Edge>* backingArray;
    int n;
public:
    Graph(int n): n(n) {
        backingArray = new HashSet<Edge>[n];
    }

    int getN() {return n;}

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

    HashSet<Edge> getSet(char x) {
        cout << hashCode(x) << endl;
        HashSet<Edge> output = backingArray[hashCode(x)];
        return backingArray[hashCode(x)];
    }

    HashSet<Edge> getSet(Vertex v) {
        return backingArray[hashCode(v.getData())];
    }
};


int** dijkstra(Graph g) {
    int** output = new int*[g.getN()];
    int* distanceArray;
    for (int i = 0; i < g.getN(); i++) {
        distanceArray = new int[g.getN()];
        for (int j = 0; j < g.getN(); j++) {
            distanceArray[j] = INFINITY_VALUE;
        }
        // Vertex start(static_cast<char>(i+97));
        Edge current;
        Edge next;
        PriorityQueue<Edge> reachable;
        HashSet<Edge> hashSet;
        HashSet<Vertex> visited;
        reachable.add(Edge(static_cast<char>(i+97), static_cast<char>(i+97), 0));
        while (reachable.getSize() > 0) {
            current = reachable.remove();
            while (visited.contains(current.getEnd()) && reachable.getSize() > 0) {
                cout << current << endl;
                current = reachable.remove();
            }
            if (reachable.getSize() == 0 && visited.contains(current.getEnd())) {break;}
            visited.add(current.getEnd());
            distanceArray[hashCode(current.getEnd())] = current.getCost();
            hashSet = g.getSet(current.getEnd());
            next = hashSet.getNext();
            while (!isNull(next)) {
                // cout << next << endl;
                reachable.add(Edge(next.getStart().getData(), next.getEnd().getData(), current.getCost() + next.getCost()));
                next = hashSet.getNext();
            }
        }

        output[i] = distanceArray;
    }
    return output;
}

void printDijkstraOutput(Graph g, int** matrix) {
    if (matrix == nullptr) {return;}
    for (int i = 0; i < g.getN(); i++) {
        for (int j = 0; j < g.getN(); j++) {
            cout << static_cast<char>(i + 97) << " -> " << static_cast<char>(j + 97) << ": " << matrix[i][j] << "\t" << endl;
        }
    }
}

LinkedList<Edge>* prims(Graph g) {
    LinkedList<Edge>* output = new LinkedList<Edge>[g.getN()];
    for (int i = 0; i < g.getN(); i++) {
        LinkedList<Edge> mst;
        PriorityQueue<Edge> reachable;
        HashSet<Edge> hashSet;
        Edge current;
        Edge next;
        HashSet<Vertex> visited;
        reachable.add(Edge(static_cast<char>(i + 97), static_cast<char>(i + 97), 0));
        while (reachable.getSize() > 0) {
            current = reachable.remove();
            while (visited.contains(current.getEnd()) && reachable.getSize() > 0) {
                current = reachable.remove();
            }
            if (reachable.getSize() == 0 && visited.contains(current.getEnd())) {break;}
            mst.add(current);
            visited.add(current.getEnd());
            hashSet = g.getSet(current.getEnd());
            next = hashSet.getNext();
            while (!isNull(next)) {
                reachable.add(next);
                next = hashSet.getNext();
            }
        }
        output[i] = mst;
    }
    return output;
}


void printPrimsOutput(Graph g, LinkedList<Edge>* array) {
    for (int i = 0; i < g.getN(); i++) {
        cout << array[i] << endl << endl;
    }
}


LinkedList<Edge> kruskals(Graph g) {
    LinkedList<Edge> mst;
    PriorityQueue<Edge> pq;
    HashSet<Vertex>* trees = new HashSet<Vertex>[g.getN()];
    HashSet<Edge> hashSet;
    for (int i = 0; i < g.getN(); i++) {
        trees[i].add(Vertex(static_cast<char>(i+97)));
        hashSet = g.getSet(static_cast<char>(i+97));
        Edge next = hashSet.getNext();
        while (!isNull(next)) {
            pq.add(next);
            next = hashSet.getNext();
        }
    }
    while (pq.getSize() > 0) {
        Edge current = pq.remove();
        while (trees[static_cast<int>(current.getStart().getData()) - 97].contains(current.getEnd()) && pq.getSize() > 0) {
            current = pq.remove();
        }
        if (pq.getSize() == 0 && trees[static_cast<int>(current.getStart().getData()) - 97].contains(current.getEnd())) {break;}
        mst.add(current);
        trees[static_cast<int>(current.getStart().getData()) - 97].unify(trees[static_cast<int>(current.getEnd().getData()) - 97]);
        trees[static_cast<int>(current.getEnd().getData()) - 97] = trees[static_cast<int>(current.getStart().getData()) - 97];
        cout << pq.getSize() << endl;
    }
    return mst;
}


Graph buildGraph(double density, int n) {
    Graph g(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (randDouble() <= density) {
                g.addEdge(static_cast<char>(i+97), static_cast<char>(j+97), randInt(1, 10));
            }
        }
    }
    return g;
}



int main() {

    Graph g = buildGraph(0.8, 20);
    /*g.addEdge('a', 'b', 3);
    g.addEdge('a', 'c', 5);
    g.addEdge('b', 'c', 1);*/
    HashSet<Edge> hashSet = g.getSet(Vertex('c'));
//    Edge current = hashSet.getNext();
//    while (!isNull(current)) {
//        cout << current << endl;
//        current = hashSet.getNext();
//    }
    printDijkstraOutput(g, dijkstra(g));
    cout << endl << endl << endl << endl;
    printPrimsOutput(g, prims(g));
    cout << endl  << endl << endl;

    g.display();

    cout << kruskals(g) << endl;

    return 0;
}
