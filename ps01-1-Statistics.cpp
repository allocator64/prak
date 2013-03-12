#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

class Avg{
    double sum, square;
    int n;
    mutable double avg, var;
    mutable bool computed;
    void compute() const;
public:
    Avg();
    Avg& operator+=(const double &);
    friend ostream& operator<<(ostream&, const Avg&);
};

Avg::Avg() :sum(), square(), n(), avg(), var(), computed() {}

Avg& Avg::operator+=(const double &t) {
    ++n;
    sum += t;
    square += t * t;
    computed = false;
    return *this;
}

void Avg::compute() const {
    if (computed)
        return;
    avg = sum / n;
    var = (double(n) / (n - 1)) * (square / n - avg * avg);
}

ostream& operator<<(ostream& stream, const Avg& avg) {
    avg.compute();
    stream << avg.avg << endl << avg.var << endl;
    return stream;
}
