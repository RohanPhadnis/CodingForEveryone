//
// Created by Rohan on 6/3/23.
//
#include <iostream>
using namespace std;

template <class T1, class T2>
void copy(T1* source, T2* destination, int size) {
    for (int i = 0; i < size; i++) {
        destination[i] = static_cast<T2>(source[i]);
    }
}

template <class T>
void printArray(const T* array, int size) {
    for (int i = 0; i < size; i++) {
        cout << array[i] << "\t";
    }
    cout << endl;
}

int main() {
    int size = 5;
    int source_array[] = {1, 2, 3, 4, 5};
    double destination_array[5];

    copy(source_array, destination_array, size);
    printArray(destination_array, size);

    return 0;
}
