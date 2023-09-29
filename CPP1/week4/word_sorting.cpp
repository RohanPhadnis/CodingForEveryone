//
// Created by Rohan on 9/29/23.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

int main() {

    ifstream word_file("words.txt");    // open the file
    istream_iterator<string> start(word_file), end; // initialize start as an iterator at the beginning of the file
    vector<string> words(start, end);   // initialize a vector words going from start to end of the file
    // in reading from the file the input operator for strings uses white space
    // thus each white space set of characters is read as one string

    cout << "words read in as: " << endl;
    for (auto str : words) {
        cout << str << endl;
    }
    cout << endl << "sorted words: " << endl;
    sort(words.begin(), words.end());   // sorting words in place
    for (auto str : words) {
        cout << str << endl;
    }

    return 0;
}

