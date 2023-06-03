//
// Created by Rohan on 6/1/23.
//
#include <complex>
#include <iostream>
using namespace std;

template <class T>
inline void swap_function(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

int main() {

    int i = 0;
    int j = 1;
    cout << "Initial: i = " << i << "; j = " << j << endl;
    swap_function(i, j);
    cout << "Final: i = " << i << "; j = " << j << endl << endl;

    double m = 1.5;
    double n = 3.5;
    cout << "Initial: m = " << m << "; n = " << n << endl;
    swap_function(m, n);
    cout << "Final: m = " << m << "; n = " << n << endl << endl;

    complex<double> a(3.14, 2.71);
    complex<double> b(9.7, 6.8);
    cout << "Initial: a = " << a << "; b = " << b << endl;
    swap_function(a, b);
    cout << "Final: a = " << a << "; b = " << b << endl << endl;

    return 0;
}