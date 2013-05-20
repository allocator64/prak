#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

typedef double (*fn_t)(double);

double f3(double x) {return x * x;}
double f6(double x) {return pow(42 + x * x, .5);}
double f7(double x) {return x * x * x;}
double f8(double x) {return cos(x + M_PI / 3);}
double f9(double x) {return sin(x - M_PI / 42);}
double f10(double x) {return log(2 + x * x);}

vector<function<double(double)> > func_list = {fn_t(sin), fn_t(cos), f3, fn_t(fabs), fn_t(exp), f6, f7, f8, f9, f10};

class Function {
    function<double(double)> func;
    int id;
public:
    Function() :func(), id() {}
    Function(std::function<double(double)>, int);
    double calc(double) const;
    int get_id() const;
};

Function::Function(std::function<double(double)> f, int i) :func(f), id(i) {}

double Function::calc(double x) const {
    return func(x);
}

int Function::get_id() const {
    return id;
}

class Compare1{
    double x, eps;
public:
    Compare1(double _x, double _eps=1e-6) :x(_x), eps(_eps) {}
    bool operator() (const Function &a, const Function &b) {
        double val1 = a.calc(x);
        double val2 = b.calc(x);
        if (fabs(val1 - val2) < eps)
            return a.get_id() < b.get_id();
        return val1 < val2;
    }
};

class Compare2{
    double x, eps;
public:
    Compare2(double _x, double _eps=1e-6) :x(_x), eps(_eps) {}
    bool operator() (const Function &a, const Function &b) {
        double val1 = a.calc(x);
        double val2 = b.calc(x);
        if (fabs(val1 - val2) < eps)
            return a.get_id() > b.get_id();
        return fabs(val1) < fabs(val2);
    }
};

int main() {
    vector<Function> v;
    {
        int cnt = 0;
        transform(func_list.begin(), func_list.end(), back_inserter(v),
            [&cnt](const function<double(double)> &f){
                return Function(f, ++cnt);
            });
    }
    int t;
    double y, z;
    cin >> t >> y >> z;

    if (t == 1)
        sort(v.rbegin(), v.rend(), Compare1(y));
    else
        sort(v.rbegin(), v.rend(), Compare2(y));

    double val = z;

    val = accumulate(v.begin(), v.end(), val, [](double x, Function f) { return f.calc(x); });

    cout.precision(10);
    cout << val << endl;

    return 0;
}
