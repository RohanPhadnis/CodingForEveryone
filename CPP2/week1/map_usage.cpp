//
// Created by Rohan on 12/18/23.
//


#include <iostream>
#include <map>
#include <unordered_map>
#include <string>

using namespace std;

int main() {

    map<int, string> workers;
    unordered_map<int, int> payroll;

    workers[123] = "Harold Fish";
    payroll[123] = 67300;

    workers[124] = "Phillip Fish";
    payroll[124] = 67400;

    for (auto p = workers.begin(); p != workers.end(); p++) {
        cout << "name: " << (*p).second << "\tID: " << (*p).first << endl;
    }

    for (auto p = payroll.begin(); p != payroll.end(); p++) {
        cout << "pay: " << (*p).second << "\tID: " << (*p).first << endl;
    }

    return 0;
}