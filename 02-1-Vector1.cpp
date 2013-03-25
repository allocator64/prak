#include <vector>
#include <list>
#include <iostream>
#include <iterator>

using namespace std;

void process(const vector<int> &v, list<int> &l, size_t step)
{
    vector<int>::const_iterator it1 = v.begin();
    list<int>::iterator it2 = l.begin();
    while (it1 < v.end() && it2 != l.end())
    {
        *it2++ = *it1;
        it1 += step;
    }
    copy(l.rbegin(), l.rend(), ostream_iterator<int>(cout, " "));
}
