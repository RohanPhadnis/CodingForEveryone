//
// Created by Rohan on 12/18/23.
//


#include <iostream>
#include <numeric>

using namespace std;


int main() {
    double v1[] = {3.5, -4, 2.1};
    double v2[] = {5, 7.5, 1};

    double sum = accumulate(v1, v1+3, 0.);
    double ip = inner_product(v1, v1+3, v2, 0.);

    cout << "sum: " << sum << endl;
    cout << "inner product: " << ip << endl;

    return 0;
}