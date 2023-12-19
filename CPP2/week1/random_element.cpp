//
// Created by Rohan on 12/18/23.
//

#include <vector>
#include <iostream>

using namespace std;

template<class RandomAccessIterator>
int randomElement(RandomAccessIterator first, RandomAccessIterator last) {
    ptrdiff_t range = last - first;
    return *(first + rand() % range);
}

int main() {

    vector<int> v;

    for (int i = 0; i < 20; i++) {
        v.push_back(rand());
    }

    cout << "random element from vector: " << randomElement(v.begin(), v.end()) << endl;

    return 0;
}