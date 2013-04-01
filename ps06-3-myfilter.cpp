struct Pred1
{
    bool operator()(int v) const { return v > 10; }
};

template<typename Ran, typename Pred>
unsigned myfilter(Ran first, Ran last, Pred f, typename Ran::value_type init = typename Ran::value_type())
{
    unsigned cnt = 0;
    while (first != last)
    {
        if (f(*first))
        {
            *first = init;
            ++cnt;
        }
        ++first;
    }
    return cnt;
}

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> v = {1, 2, 3, 123, 4};
    unsigned n = myfilter(v.begin(), v.end(), Pred1(), -1);
    for (auto &i : v)
        cout << i << " ";
    cout << "\ntotal: " << n << endl;
    return 0;
}
