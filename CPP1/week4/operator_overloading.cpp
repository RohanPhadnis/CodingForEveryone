//
// Created by Rohan on 9/29/23.
//
#include <cmath>
using namespace std;

class Point {
private: double x, y;
public:
    Point(): x(0), y(0) {}
    Point(double u): x(u), y(0) {}

    // function to go from Point to double
    operator double() {
        return sqrt(x*x + y*y);
    }
};


int main() {
    Point s;
    double d = 3.5;
    s = d;  // implicit conversion
    s = static_cast<Point>(d);  // explicit conversion
    d = s; // implicit conversion from Point -> double
    return 0;
}