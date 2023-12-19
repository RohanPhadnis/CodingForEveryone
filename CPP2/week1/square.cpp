//
// Created by Rohan on 12/18/23.
//


#include <iostream>
#include <iterator>
#include <vector>
#include <ctime>

using namespace std;

template <class ForwardIterator>
void square(ForwardIterator first, ForwardIterator last) {
    for (; first != last; first++) {
        *first *= *first;
    }
}

template <class ForwardIterator>
void printer(ForwardIterator first, ForwardIterator last) {
    for (; first != last; first++) {
        cout << *first << endl;
    }
}

int main() {
    srand(clock());
    vector<int> v;
    for (int i = 0; i < 20; i++) {
        int x = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 100);
        cout << x << endl;
        v.push_back(x);
    }
    cout << endl << endl;
    square(v.begin(), v.end());
    printer(v.begin(), v.end());
    return 0;
}