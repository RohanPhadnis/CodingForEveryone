//
// Created by Rohan on 12/18/23.
//

#include <iostream>
#include <string>

using namespace std;

int main() {

    string words[] = {"my", "hop", "mop", "hope", "cope"};
    string* p = find(words, words + 5, "hop");
    cout << *(p+1) << endl;

    sort(words, words+5);
    p = find(words, words+5, "hop");
    cout << *(p+1) << endl;

    return 0;
}