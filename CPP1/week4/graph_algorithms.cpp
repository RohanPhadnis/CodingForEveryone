#include <iostream>
#include <random>
using namespace std;


inline int char_to_int(char x) {return static_cast<int>(x) - 65;}
inline char int_to_char(int x) {return static_cast<char>(x + 65);}
inline int randint(int min, int max) {return rand() % (max - min) + min;}
inline double rand_dub() {return static_cast<double>(rand()) / RAND_MAX;}
template<class T> inline T get_min(T a, T b) {return (a < b) ? a : b;}
template<class T> inline T get_max(T a, T b) {return (a > b) ? a : b;}


template <class T> void print_array(T* array, int size) {
    for (int i = 0; i < size; i++) {
        cout << array[i] << "\t";
    }
    cout << endl;
}


class Edge {
private:
    char start;
    char end;
    int cost;
public:
    Edge(): start(0), end(0), cost(0) {}
    Edge(char start, char end, int cost): start(start), end(end), cost(cost) {}

    char get_start() {return start;}
    char get_end() {return end;}
    int get_cost() {return cost;}
};


inline int hashCode(char c) {return char_to_int(c);}
inline int hashCode(Edge data) {return char_to_int(data.get_end());}
inline bool operator==(Edge e1, Edge e2) {return e1.get_end() == e2.get_end();}
inline bool operator>(Edge e1, Edge e2) {return e1.get_cost() > e2.get_cost();}
inline bool operator<(Edge e1, Edge e2) {return e1.get_cost() < e2.get_cost();}



inline ostream& operator<<(ostream& out, Edge e) {
    out << "(" << e.get_start() << ", " << e.get_end() << ", " << e.get_cost() << ")";
    return out;
}


template <class T>
class ListNode {
private:
    T data;
    ListNode<T> next;
public:
    ListNode(): data(nullptr), next(nullptr) {}

    ListNode(T data): data(data), next(nullptr) {}

    T get_data() {return data;}
    void set_data(T data) {this->data = data;}

    ListNode<T> get_next() {return next;}
    void set_next(ListNode<T> next) {this->next = next;}
    void set_next(T data) {
        ListNode<T> node(data);
        this->next = node;
    }
};


template <class T>
inline ostream& operator<<(ostream& out, ListNode<T> node) {
    if (node != nullptr) {
        out << node << " -> " << node.get_next();
    }
    return out;
}


template <class T>
class HashSet {
private:
    ListNode<T>* backing_array;
    int size;
    int capacity;
    double max_load_factor;

    ListNode<T> cursor;
    int cursor_index;

    void reset_cursor() {
        cursor = nullptr;
        for (int i = 0; i < capacity && cursor == nullptr; i++) {
            if (backing_array[i] != nullptr) {
                cursor = backing_array[i];
                cursor_index = i;
            }
        }
    }

    void advance() {
        if (cursor != nullptr) {
            if (cursor.get_next() != nullptr) {
                cursor = cursor->next;
            } else {
                cursor = nullptr;
                for (int i = cursor_index + 1; i < capacity && cursor == nullptr; i++) {
                    if (backing_array[i] != nullptr) {
                        cursor = backing_array[i];
                        cursor_index = i;
                    }
                }
            }
        }
    }

    void resize() {
        ListNode<T>* temp = backing_array;
        backing_array = new ListNode<T>[capacity * 2 + 1];
        for (int i = 0; i < capacity * 2 + 1; i++) {
            backing_array[i] = nullptr;
        }
        ListNode<T> current;
        ListNode<T> build;
        for (int i = 0; i < capacity; i++) {
            current = temp[i];
            while (current != nullptr) {
                build = new ListNode<T>;
                build.set_data(current.get_data());
                build.set_next(backing_array[hashCode(current->edge) % (capacity * 2 + 1)]);
                backing_array[hashCode(current->edge) % (capacity * 2 + 1)] = build;
                current = current.get_next();
            }
        }
        capacity = capacity * 2 + 1;
    }

public:
    HashSet(): size(0), capacity(11), max_load_factor(0.75), cursor_index(0) {
        backing_array = new ListNode<T>[capacity];
        for (int i = 0; i < capacity; i++) {
            backing_array[i] = nullptr;
        }
        cursor = nullptr;
    }

    bool contains(T data) {
        ListNode<T> current = backing_array[hashCode(data) % capacity];
        while (current != nullptr) {
            if (current.get_data() == data) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void add(T e) {
        if (!contains(e)) {
            if (static_cast<double>(size) / capacity > max_load_factor) {
                resize();
            }
            ListNode<T> build(e);
            build.set_next(backing_array[hashCode(e) % capacity]);
            backing_array[hashCode(e) % capacity] = build;
            size++;
            reset_cursor();
        }
    }

    T get_current_item() {
        T output = (cursor == nullptr) ? nullptr : cursor->edge;
        advance();
        return output;
    }

    void print() {
        for (int i = 0; i < capacity; i++) {
            cout << i << ": " << backing_array[i] << endl;
        }
    }
};


class MinHeap {
private:
    Edge* backing_array;
    int size;
    int current_length;

    void swap(int index1, int index2) {
        Edge temp = backing_array[index1];
        backing_array[index1] = backing_array[index2];
        backing_array[index2] = temp;
    }

    void up_heap(int index) {
        int parent = index / 2;
        if (backing_array[parent] != nullptr && backing_array[parent].get_cost() > backing_array[index].get_cost()) {
            swap(index, parent);
            up_heap(parent);
        }
    }

    void down_heap(int index) {
        int child1 = index * 2;
        int child2 = index * 2 + 1;
        if (child1 <= size) {
            if (child2 <= size) {
                if (backing_array[child1].get_cost() < backing_array[index].get_cost() || backing_array[child2].get_cost() < backing_array[index].get_cost()) {
                    if (backing_array[child1].get_cost() < backing_array[child2].get_cost()) {
                        swap(index, child1);
                    } else {
                        swap(index, child2);
                    }
                }
            } else {
                if (backing_array[child1].get_cost() < backing_array[index].get_cost()) {
                    swap(index, child1);
                    down_heap(child1);
                }
            }
        }
    }

    void resize() {
        Edge* temp = backing_array;
        backing_array = new Edge[current_length * 2];
        for (int i = 0; i < current_length; i++) {
            backing_array[i] = (i == 0) ? nullptr : temp[i];
        }
        current_length *= 2;
    }

public:

    MinHeap(): size(0), current_length(10) {
        backing_array = new Edge[current_length];
    }

    Edge dequeue() {
        Edge output = backing_array[1];
        backing_array[1] = backing_array[size];
        backing_array[size--] = nullptr;
        down_heap(1);
        return output;
    }

    void enqueue(Edge e) {
        if (size == current_length - 1) {
            resize();
        }
        backing_array[++size] = e;
        up_heap(size);
    }

    bool is_empty() {return size == 0;}

    int get_size() {return size;}
};


class Graph {
private:
    HashSet<Edge>* array;
    int n;

public:
    explicit Graph(int n): n(n) {
        array = new HashSet<Edge>[n];
    }

    void add_edge(char val1, char val2, int cost) {
        array[char_to_int(val1)].add(Edge(val1, val2, cost));
        array[char_to_int(val2)].add(Edge(val2, val1, cost));
    }

    int get_n() const {return n;}

    HashSet<Edge> get_set(char val) {
        return array[char_to_int(val)];
    }

    void print() {
        for (int i = 0; i < n; i++) {
            cout << int_to_char(i) << ':' << endl;
            array[i].print();
            cout << endl;
        }
    }
};


Graph build_graph(int n, double density) {
    Graph output(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (rand_dub() < density) {
                output.add_edge(int_to_char(i), int_to_char(j), randint(2, 50));
            }
        }
    }
    return output;
}


int* dijkstra(Graph graph, char start) {
    int* output = new int[graph.get_n()];
    for (int i = 0; i < graph.get_n(); i++) {
        output[i] = 10000;
    }
    HashSet<Edge> visited_set;
    MinHeap reachable_pq;

    reachable_pq.enqueue(Edge(start, start, 0));
    Edge current;
    Edge build;
    HashSet<Edge> new_reach;

    while (!reachable_pq.is_empty()) {
        current = reachable_pq.dequeue();
        if (!visited_set.contains(current)) {
            new_reach = graph.get_set(current.get_end());
            build = new_reach.get_current_item();
            while (build != nullptr) {
                if (!visited_set.contains(build)) {
                    reachable_pq.enqueue(Edge(build.get_start(), build.get_end(), build.get_cost() + current.get_cost()));
                }
                // cout << build << endl;
                build = new_reach.get_current_item();
            }
            visited_set.add(current);
            output[char_to_int(current.get_end())] = get_min(output[char_to_int(current.get_end())], current.get_cost());
        }
    }
    return output;
}


int main() {

    Graph graph = build_graph(26, 0.2);
    graph.print();
    print_array(dijkstra(graph, 'A'), graph.get_n());
    return 0;
}