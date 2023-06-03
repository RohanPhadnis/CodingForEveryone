//
// Created by Rohan on 6/1/23.
//
#include <iostream>
using namespace std;

template <class T>
T sum(T* array, int size, T output = 0) {
    for (int i = 0; i < size; i++) {
        output += array[i];
    }
    return output;
}

int main() {
    int array1[] = {1, 2, 3, 4, 5, 6, 7};
    cout << "array 1: " << array1 << "; total: " << sum(array1, 7) << endl;

    double array2[] = {1, 2, 3, 4, 5, 6, 7};
    cout << "array 2: " << array2 << "; total: " << sum(array2, 7) << endl;

    return 0;
}
