//
// Created by Rohan on 12/18/23.
//

#include <iostream>

using namespace std;

template<class ForwardIter>
void print(ForwardIter first, ForwardIter last, const char* title) {
    cout << title << endl;
    while (first != last) {
        cout << *first ++ << '\t';
    }
    cout << endl;
}

int main() {
    int data[3] = {9, 10, 11};

    print(data, data + 3, "original values");

    transform(data, data + 3, data, bind2nd(times<int>(), 2));
    print(data, data + 3, "new values");
    return 0;
}