//
// Created by Rohan on 12/18/23.
//

#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

void incr(int& i) {
    static int n = 1;
    n++;
}

void outvec(int i) {
    cout << i << endl;
}

int main() {

    vector<int> v(6);

    for_each(v.begin(), v.end(), incr);
    for_each(v.begin(), v.end(), outvec);

    return 0;
}