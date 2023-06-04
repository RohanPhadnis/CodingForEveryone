//
// Created by Rohan on 6/4/23.
//
#include <iostream>

using namespace std;

class point {
private:
    double x;
    double y;
public:
    double get_x() {
        return x;
    }

    double get_y() {
        return y;
    }

    void set_x(double x) {
        this->x = x;
    }

    void set_y(double y) {
        this->y = y;
    }

    point() {
        x = 0;
        y = 0;
    }

    point(double x, double y) {
        this->x = x;
        this->y = y;
    }
};


ostream& operator<<(ostream& out, point p) {
    out << "(" << p.get_x() << ", " << p.get_y() << ")" << endl;
    return out;
}

point operator+ (point& p1, point& p2) {
    return point(p1.get_x() + p2.get_x(), p1.get_y() + p2.get_y());
}


int main() {
    point p1(3, 4);
    point p2(4, 5);
    cout << p1;
    cout << p2;
    cout << p1 + p2;
}
