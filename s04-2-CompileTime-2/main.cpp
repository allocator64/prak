template<class T>
struct HasX
{
    struct B { int x; };
    struct D : T, B {};

    typedef char yes[1];
    typedef char no[2];

    template<int B::*> struct check;

    template <class P>
    static no& test(check<&P::x>*);

    template <class>
    static yes& test(...);

    static const bool value = sizeof(test<D>(0)) == sizeof(yes);
};
