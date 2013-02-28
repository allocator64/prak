#include <iostream>
#include <sstream>
#include <cstdio>

using namespace std;

class Exp {
    string data;
    mutable int value;
    mutable bool calculated;
    int next();
public:
    Exp(const char *);
    int calc() const;
};

Exp::Exp(const char *s) :data(s), value(), calculated() {}

int Exp::calc() const {
    if (calculated) {
        return value;
    }
    unsigned pos = 0;
    enum {Plus, Minus, Value} state = Plus;
    while (pos < data.size()) {
        if (data[pos] == '+') {
            state = Plus;
            ++pos;
        } else if (data[pos] == '-') {
            state = Minus;
            ++pos;
        } else {
            int t = 0;
            for (;pos < data.size() && isdigit(data[pos]); ++pos)
                t = t * 10 + data[pos] - '0';
            if (state == Minus)
                t *= -1;
            state = Value;
            value += t;
        }
    }
    calculated = true;
    return value;
}
/*
int main() {
    Exp e = "-1+2+3";
    Exp e2 = "123";
    cout << e.calc() << " " << e2.calc() << " " << e.calc();
    return 0;
}
*/