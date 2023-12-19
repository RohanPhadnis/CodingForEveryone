//
// Created by Rohan on 12/18/23.
//

#include <iostream>
#include <iterator>

using namespace std;

template<typename BidirectionalIterator>
bool isPalindrome(BidirectionalIterator first, BidirectionalIterator last) {
    while (true) {
        last--;
        if (first == last) {
            break;
        }
        if (*first != *last) {
            return false;
        }
        first++;
        if (first == last) {
            break;
        }
    }
    return true;
}

int main() {

    char* word;
    cout << "Enter a word: ";
    cin >> word;
    cout << endl;
    vector<char> word_vect;
    int i = 0;
    while (word[i] != '\0') {
        word_vect.push_back(word[i++]);
    }
    cout << "is palindrome: " << (isPalindrome(word_vect.begin(), word_vect.end()) ? "true": "false") << endl;

    return 0;
}