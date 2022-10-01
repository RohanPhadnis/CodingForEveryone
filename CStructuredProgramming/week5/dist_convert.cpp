#include <iostream> // IO stream library for IO functions
using namespace :: std; // namespace identifier change. std:: cout vs cout --> omits std
const double m_to_k = 1.609;    // const means that the variable's value cannot change

inline double convert(int mi) {return mi * m_to_k;}  // replacing macros (#define) with optimized functions

int main(void) {
    int miles = 1;

    while (miles != 0) {
        cout << "Enter distance (miles) or 0 to terminate: ";
        cin >> miles;
        cout << "\n Distance is " << convert(miles) << " km." << endl;
    }
    cout << endl;
}
