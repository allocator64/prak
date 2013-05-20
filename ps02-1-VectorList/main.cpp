#include <vector>
#include <iostream>
#include <iterator>
#include <list>

using namespace std;

size_t process(vector<int> &v, const list<int> &l, size_t step)
{
    size_t cnt = 0;
    vector<int>::iterator it1 = v.begin();
    list<int>::const_iterator it2 = l.begin();
    while (it1 < v.end() && it2 != l.end())
    {
        if (*it2 < 0)
        {
            ++cnt;
            *it1 = *it2;
        }
        it1 += step;
        ++it2;
    }
    copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
    return cnt;
}