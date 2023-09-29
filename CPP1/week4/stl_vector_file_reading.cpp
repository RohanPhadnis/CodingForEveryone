//
// Created by Rohan on 9/29/23.
//
#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
using namespace std;

int main() {
    ifstream data_file("data.txt"); // creating a variable for reading file input
    istream_iterator<int> start(data_file), end;    // pointer to start of the file
    vector<int> data(start, end);   // vector constructor reads from start to end, initializing vector<int> data
    int sum = 0;
    for (auto p = data.begin(); p != data.end(); p++) {
        sum += *p;
    }
    cout << "total: " << sum << endl << "average: " << static_cast<double>(sum) / data.size() << endl;
}
