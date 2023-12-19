//
// Created by Rohan on 12/18/23.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

enum class suite: short {SPADE, DIAMOND, HEART, CLUB};

class pip{
public:
    pip(int p): p(p) {}
    int get_val() {
        return p;
    }
private:
    int p;
};


class card {
public:
    card(pip p, suite s): p(p), s(s) {}
    int get_pip() {
        return p.get_val();
    }
    suite get_suite() {
        return s;
    }
private:
    pip p;
    suite s;
};


bool is_straight(vector<card> hand) {
    int pips[5]; int i = 0;
    for (auto p = hand.begin(); p != hand.end(); p++) {
        pips[i++] = (*p).get_pip();
    }
    sort(pips, pips+5);
    if (pips[0] == 1) {
        return ((pips[1] == 2 && pips[2] == 3 && pips[3] == 4 && pips[4] == 5)
                ||
                (pips[1] == 10 && pips[2] == 11 && pips[3] == 12 && pips[4] == 13));
    } else {
        for (i = 0; i < 4; i++) {
            if (pips[i+1] != pips[i] + 1) {
                return false;
            }
        }
        return true;
    }
}


bool is_flush(vector<card> hand) {
    suite s = hand[0].get_suite();
    for (auto c: hand) {
        if (c.get_suite() != s) {
            return false;
        }
    }
    return true;
}


inline double calc_probability(long count, long total) {
    return static_cast<double>(count) / total;
}


int main() {

    srand(clock());

    vector<card> deck;
    for (int i = 1; i < 14; i++) {
        deck.push_back( card(i, suite::SPADE));
        deck.push_back( card(i, suite::DIAMOND));
        deck.push_back( card(i, suite::HEART));
        deck.push_back( card(i, suite::CLUB));
    }

    long shots;
    cout << "Enter number of shots: ";
    cin >> shots;
    cout << endl;

    long num_straight = 0;
    long num_flush = 0;
    long num_straight_flush = 0;
    long i = 0;
    while (i < shots) {
        random_shuffle(deck.begin(), deck.end());
        vector<card> hand;
        for (auto p = deck.begin(); p < deck.begin() + 5; p++) {
            hand.push_back(*p);
        }

        bool f = is_flush(hand);
        bool s = is_straight(hand);

        if (f) {
            num_flush++;
        }
        if (s) {
            num_straight++;
        }
        if (f && s) {
            num_straight_flush++;
        }

        i++;
    }

    cout << "Predicted straight: " << calc_probability(num_straight, shots) <<endl;
    cout << "Predicted flush: " << calc_probability(num_flush, shots) << "\t Actual: "<< 1. / 500 << endl;
    cout << "Predicted straight flush: "<< calc_probability(num_straight_flush, shots) << "\t Actual: " << 1./70000 << endl;

    return 0;
}