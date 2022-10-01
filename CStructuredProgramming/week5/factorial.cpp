#include <iostream>
using namespace :: std;

long long fact(int n) {
    long long f = 1;
    for (int i=1; i <= n; i++) {
        f *= i;
    }
    return f;
}

int main(void) {
    cout << "This program uses new features not in C89\n";

    for (auto i=0; i<16; i++) {
        cout << i << "! = " << fact(i) << endl;
    }
    cout << "The end!" << endl;
}
