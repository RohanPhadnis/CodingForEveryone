// c++ include statements dont require the .h for header files
// if c is the starting character of the library, it indicates that it is also a library in c (eg ctime, cstdlib)
#include <iostream>
#include <ctime>
#include <cstdlib>

// namespace is a wrapper for tools in a library
// using keyword indicates that that namespace is being used by the program
// using defines the scope of the program
using namespace std;

// const keyword used to indicate constant
// cleaner solution than using #define
const int sides = 6;

// incline used to declare functions
// the code from the body is executed in-line by the compiler, instead of creating a new stack for that function
inline int r_sides() {return rand() % sides + 1;}


int main(void) {

    int d1, d2;
    srand(clock());

    // std::cout if not using namespace std
    // :: is the scope resolution operator
    // << is usually a bitshift operator, but in this case it is overloaded
    // cin and cout are of type istream and ostream which have << and >> overloaded
    cout << "\nEnter number of trails: ";
    int trials;
    cin >> trials;

    // new keyword
    int* outcomes = new int[n_dice * sides + 1];

    for (int j = 0; j < trials; j++) {
        output[ (d1 = r_sides()) + (d2 = r_sides())]++;
    }

    cout << "probability\n";
    for (int j = 2; j < n_dice * sides + 1; j++) {
        cout << "j = " << j << " p = " << static_cast<double>(outcomes[j]) / trials << endl;
    }
}
