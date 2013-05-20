#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

class C {
public:
    C() {}
    C(C c, int i) {}
    C(double d) {}
    double operator~() const { return 0; }
    C operator&() const { return C(); }
    C& operator++() {return *this; }
    double operator*(C *c)const {return 0; }
    friend C operator+(int, C);
};

C operator+(int i, C c) {
    return C();
}
