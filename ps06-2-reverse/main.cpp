#include <iostream>
#include <vector>

template<typename T>
void myswap(T &a, T &b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

template<typename Ran>
void myreverse(Ran first, Ran last)
{
    while (first != last && first != --last)
    {
        myswap(*first++, *last);
    }
}

int main()
{
    std::vector<int> v = {1, 2, 3};
    myreverse(v.begin(), v.end());
    for (auto &i : v)
        std::cout << i << " ";
    std::cout << std::endl;
    return 0;
}