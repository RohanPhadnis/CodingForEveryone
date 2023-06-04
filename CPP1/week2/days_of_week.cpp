//
// Created by Rohan on 6/3/23.
//
#include <iostream>
using namespace std;

typedef enum days{
    MON,
    TUE,
    WED,
    THU,
    FRI,
    SAT,
    SUN
} days;

inline days operator++(days& d) {
    d = static_cast<days>((static_cast<int>(d) + 1) % 7);
    return d;
}

inline ostream& operator<<(ostream& out, const days& d) {
    switch (d) {
        case MON: out << "MON"; break;
        case TUE: out << "TUE"; break;
        case WED: out << "WED"; break;
        case THU: out << "THU"; break;
        case FRI: out << "FRI"; break;
        case SAT: out << "SAT"; break;
        case SUN: out << "SUN";
    }
    return out;
}

int main() {
    days d = MON;
    cout << d << endl;
    ++d;
    cout << d << endl;
    return 0;
}
