#include <iostream>
#include <random>

using namespace std;

inline int char_to_int(char x) {return static_cast<int>(x) - 65;}
inline char int_to_char(int x) {return static_cast<char>(x + 65);}
inline int randint(int min, int max) {return rand() % (max - min) + min;}
inline double rand_dub() {return static_cast<double>(rand()) / RAND_MAX;}
template<class T> inline T get_min(T a, T b) {
    return (a < b) ? a : b;
}

template <class T> void print_array(T* array, int size) {
    for (int i = 0; i < size; i++) {
        cout << array[i] << "\t";
    }
    cout << endl;
}

typedef struct edge{
    char start;
    char end;
    int cost;
} edge;


edge* build_edge(char start, char end, int cost) {
    edge* output = new edge;
    output->start = start;
    output->end = end;
    output->cost = cost;
    return output;
}


inline ostream& operator<<(ostream& out, edge* e) {
    if (e != nullptr) {
        out << "(" << e->start << ", " << e->end << ", " << e->cost << ")";
    } else {
        out << "()";
    }
    return out;
}

inline int hashCode(edge* e) {
    return char_to_int(e->end);// int_to_char(e->start) + int_to_char(e->end) + e->cost;
}


typedef struct list_node{
    edge* edge;
    list_node* next;
} list_node;


inline ostream& operator<<(ostream& out, list_node* current) {
    while (current != nullptr) {
        out << " -> " << current->edge;
        current = current->next;
    }
    return out;
}


class HashSet {
private:
    list_node** backing_array;
    int size;
    int capacity;
    double max_load_factor;

    list_node* cursor;
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
            if (cursor->next != nullptr) {
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
        list_node** temp = backing_array;
        backing_array = new list_node*[capacity * 2 + 1];
        list_node* current;
        list_node* build;
        for (int i = 0; i < capacity; i++) {
            current = temp[i];
            while (current != nullptr) {
                build = new list_node;
                build->edge = current->edge;
                build->next = backing_array[hashCode(current->edge) % (capacity * 2 + 1)];
                backing_array[hashCode(current->edge) % (capacity * 2 + 1)] = build;
                current = current->next;
            }
        }
        capacity = capacity * 2 + 1;
    }

public:
    HashSet(): size(0), capacity(11), max_load_factor(0.75), cursor(nullptr), cursor_index(0) {
        backing_array = new list_node*[capacity];
        for (int i = 0; i < capacity; i++) {
            backing_array[i] = nullptr;
        }
    }

    bool contains(edge* e) {
        list_node* current = backing_array[hashCode(e) % capacity];
        while (current != nullptr) {
            if (current->edge->end == e->end) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void add(edge* e) {
        if (!contains(e)) {
            if (static_cast<double>(size) / capacity > max_load_factor) {
                resize();
            }
            list_node* build = new list_node;
            build->edge = e;
            build->next = backing_array[hashCode(e) % capacity];
            backing_array[hashCode(e) % capacity] = build;
            size++;
            reset_cursor();
        }
    }

    edge* get_current_item() {
        edge* output = (cursor == nullptr) ? nullptr : cursor->edge;
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
    edge** backing_array;
    int size;
    int current_length;

    void swap(int index1, int index2) {
        edge* temp = backing_array[index1];
        backing_array[index1] = backing_array[index2];
        backing_array[index2] = temp;
    }

    void up_heap(int index) {
        edge* temp;
        int parent = index / 2;
        if (backing_array[parent] != nullptr && backing_array[parent]->cost > backing_array[index]->cost) {
            swap(index, parent);
            up_heap(parent);
        }
    }

    void down_heap(int index) {
        int child1 = index * 2;
        int child2 = index * 2 + 1;
        if (child1 <= size) {
            if (child2 <= size) {
                if (backing_array[child1]->cost < backing_array[index]->cost || backing_array[child2]->cost < backing_array[index]->cost) {
                    if (backing_array[child1]->cost < backing_array[child2]->cost) {
                        swap(index, child1);
                    } else {
                        swap(index, child2);
                    }
                }
            } else {
                if (backing_array[child1]->cost < backing_array[index]->cost) {
                    swap(index, child1);
                    down_heap(child1);
                }
            }
        }
    }

    void resize() {
        edge** temp = backing_array;
        backing_array = new edge*[current_length * 2];
        for (int i = 0; i < current_length; i++) {
            backing_array[i] = (i == 0) ? nullptr : temp[i];
        }
        current_length *= 2;
    }

public:

    MinHeap(): size(0), current_length(10) {
        backing_array = new edge*[current_length];
    }

    edge* dequeue() {
        edge* output = backing_array[1];
        backing_array[1] = backing_array[size];
        backing_array[size--] = nullptr;
        down_heap(1);
        return output;
    }

    void enqueue(edge* e) {
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
    HashSet* array;
    int n;

public:
    explicit Graph(int n): n(n) {
        array = new HashSet[n];
    }

    void add_edge(char val1, char val2, int cost) {
        array[char_to_int(val1)].add(build_edge(val1, val2, cost));
        array[char_to_int(val2)].add(build_edge(val2, val1, cost));
    }

    int get_n() const {return n;}

    HashSet get_set(char val) {
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
    HashSet visited_set;
    MinHeap reachable_pq;

    reachable_pq.enqueue(build_edge(start, start, 0));
    edge* current;
    edge* build;
    HashSet new_reach;

    while (!reachable_pq.is_empty()) {
        current = reachable_pq.dequeue();
        if (!visited_set.contains(current)) {
            new_reach = graph.get_set(current->end);
            build = new_reach.get_current_item();
            while (build != nullptr) {
                if (!visited_set.contains(build)) {
                    reachable_pq.enqueue(build_edge(build->start, build->end, build->cost + current->cost));
                }
                // cout << build << endl;
                build = new_reach.get_current_item();
            }
            visited_set.add(current);
            output[char_to_int(current->end)] = get_min(output[char_to_int(current->end)], current->cost);
        }
    }
    return output;
}


edge** prims(Graph graph, char start) {
    edge** output = new edge*[graph.get_n() - 1];
    int i = 0;
    HashSet visited_set;
    MinHeap reachable_pq;

    reachable_pq.enqueue(build_edge(start, start, 0));
    edge* current;
    HashSet new_reach;
    edge* build;

    while (!reachable_pq.is_empty()) {
        current = reachable_pq.dequeue();
        if (!visited_set.contains(current)) {
            if (current->cost != 0) {
                output[i++] = current;
            }
            new_reach = graph.get_set(current->end);
            build = new_reach.get_current_item();
            while (build != nullptr) {
                reachable_pq.enqueue(build);
                build = new_reach.get_current_item();
            }
            visited_set.add(current);
        }
    }

    return output;
}


int main() {
    srand(clock());
    /**
        * matrix representation of desired graph
        *      A   B   C   D   E
        * A    0   2   3   -   -
        * B    2   0   -   8   4
        * C    3   -   0   1   -
        * D    -   8   1   0   2
        * E    -   4   -   2   0
    */
    Graph graph = build_graph(26, 0.2);
    graph.print();
    print_array(dijkstra(graph, 'A'), graph.get_n());
    print_array(prims(graph, 'A'), graph.get_n() - 1);

    return 0;
}
