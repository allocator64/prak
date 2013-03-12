#include <iostream>
#include <algorithm>

using namespace std;

class Exp {
    string data;
    mutable int value;
    mutable bool calculated;
public:
    Exp(const char *);
    int calc() const;
};

Exp::Exp(const char *s) :data(s), value(), calculated() {}

int Exp::calc() const {
    if (calculated) {
        return value;
    }
    int tmp = 0, sgn = 1;
    for_each(data.begin(), data.end(), [this, &tmp, &sgn](char c){
        if (c == '-' || c == '+') {
            value += tmp * sgn;
            sgn = c == '+' ? 1 : -1;
            tmp = 0;
        } else
            tmp = tmp * 10 + c - '0';
    });

    value += tmp * sgn;

    calculated = true;
    return value;
}
