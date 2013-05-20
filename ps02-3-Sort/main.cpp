#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

unsigned bits(unsigned x)
{
    unsigned cnt = 0;
    while(x)
    {
        cnt += x & 1;
        x >>= 1;
    }
    return cnt;
}

struct Compare
{
    bool operator()(unsigned a, unsigned b)
    {
        return bits(a) < bits(b);
    }
};

int main()
{
    vector<unsigned> v;
    copy(istream_iterator<unsigned>(cin), istream_iterator<unsigned>(), back_inserter(v));
    stable_sort(v.begin(), v.end(), Compare());
    copy(v.begin(), v.end(), ostream_iterator<unsigned>(cout, "\n"));
    return 0;
}