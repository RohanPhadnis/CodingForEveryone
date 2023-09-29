//
// Created by Rohan on 9/29/23.
//

#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v(100); // allocate space

    // C style iteration
    for (int i = 0; i < 100; i++) {
        v[i] = i;
    }

    // C++ style iteration
    // uses generalized pointer (AKA cursor)
    // end() gives us the sentinel
    for (vector<int>::iterator p = v.begin(); p != v.end(); p++) {
        cout << *p << endl;
    }

    // using auto
    for (auto p = v.begin(); p != v.end(); p++) {
        cout << *p << endl;
    }
    return 0;
}
