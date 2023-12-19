//
// Created by Rohan on 12/18/23.
//


#include <iostream>
#include <numeric>

using namespace std;

class gen {
public:
    gen(double x, double incr): x(x), incr(incr) {}
    double operator()() {
        x += incr;
        return x*x;
    }
private:
    double x;
    double incr;
};


double integrate(gen g, int n) {
    vector<double> fx(n);
    generate(fx.begin(), fx.end(), g);
    return accumulate(fx.begin(), fx.end(), 0.) / n;
}


int main() {
    double v1[] = {3.5, -4, 2.1};

    double sum = accumulate(v1, v1+3, 0., minus<int>());

    cout << "sum: " << sum << endl;

    double integral = integrate(gen(1, 0.001), 1000);
    cout << "integral: " << integral << endl;

    return 0;
}