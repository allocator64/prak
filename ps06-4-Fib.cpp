template<int val>
struct Fib
{
    enum {VAL = Fib<val - 1>::VAL + Fib<val - 2>::VAL};
};

template<>
struct Fib<0>
{
    enum {VAL = 0};
};

template<>
struct Fib<1>
{
    enum {VAL = 1};
};
