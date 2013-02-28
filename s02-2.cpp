#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

double f1(double x) {
    return sin(x);
}

double f2(double x) {
    return cos(x);
}

double f3(double x) {
    return x * x;
}

double f4(double x) {
    return fabs(x);
}

double f5(double x) {
    return exp(x);
}

double f6(double x) {
    return pow(42 + x * x, .5);
}

double f7(double x) {
    return x * x * x;
}

double f8(double x) {
    return cos(x + M_PI / 3);
}

double f9(double x) {
    return sin(x - M_PI / 42);
}

double f10(double x) {
    return log(2 + x * x);
}

vector<function<double(double)> > func_list = {f1, f2, f3, f4, f5, f6, f7, f8, f9, f10};

class Function {
    function<double(double)> func;
    int id;
public:
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

class Compare {
protected:
    static int cmp(double a, double b) {
        double tmp = a - b;
        if (fabs(tmp) < 1e-5)
            return 0;
        return (tmp > 0) ? 1 : -1;
    }
    double x;
public:
    explicit Compare(double p) :x(p) {}
    virtual bool operator()(const Function a, const Function b) = 0;
    virtual ~Compare(){};
};

class Compare1 :public Compare{
public:
    explicit Compare1(double p) :Compare(p) {}
    bool operator() (const Function a, const Function b) {
        return cmp(a.calc(x), b.calc(x)) < 0 || (a.get_id() < b.get_id() && cmp(a.calc(x), b.calc(x)) == 0);
    }
};

class Compare2 :public Compare{
public:
    explicit Compare2(double p) :Compare(p) {}
    bool operator() (const Function a, const Function b) {
        return cmp(fabs(a.calc(x)), fabs(b.calc(x))) < 0 || (a.get_id() > b.get_id() && cmp(a.calc(x), b.calc(x)) == 0);
    }
};

class MyComparator {
    Compare *link;
public:
    explicit MyComparator(Compare *p) :link(p) {}
    bool operator()(const Function a, const Function b) {
        return link->operator()(a, b);
    }
};

int main() {
    vector<Function> v;
    for (int i = 1; i <= 10; ++i)
        v.push_back(Function(func_list[i - 1], i));
    int t;
    double y, z;
    cin >> t >> y >> z;

    Compare *base_comparator = 0;

    if (t == 1)
        base_comparator = dynamic_cast<Compare*>(new Compare1(y));
    else
        base_comparator = dynamic_cast<Compare*>(new Compare2(y));

    MyComparator compare(base_comparator);

    sort(v.rbegin(), v.rend(), compare);

    double val = z;
    for (vector<Function>::const_iterator it = v.begin(); it != v.end(); ++it)
        val = it->calc(val);

    cout.precision(10);
    cout << val << endl;

    delete base_comparator;

    return 0;
}