#include <iostream>
using namespace std;

// call by reference
inline void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// call by reference
inline void swap(double& a, double& b) {
    double temp = a;
    a = b;
    b = temp;
}


int main() {
    int m = 0;
    int n = 1;
    cout << "Initial: m = " << m << "; n = " << n << endl;
    swap(m, n);
    cout << "Final: m = " << m << "; n = " << n << endl << endl;


    double a = 0.5;
    double b = 1.5;
    cout << "Initial: a = " << a << "; b = " << b << endl;
    swap(a, b);
    cout << "Final: a = " << a << "; b = " << b << endl << endl;
    return 0;
}

