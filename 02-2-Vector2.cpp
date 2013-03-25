#include <vector>
#include <list>
#include <iostream>
#include <iterator>

using namespace std;

void process(const vector<int> &v1, vector<int> &v2)
{
    size_t len = min(v1.size(), v2.size());
    vector<int>::const_iterator it1 = v1.begin();
    vector<int>::iterator it2 = v2.begin();
    while (len--)
    {
        if (*it1 > *it2)
            v2.push_back(*it1);
        ++it1;
        it2 = v2.begin() + (it1 - v1.begin());
    }
    copy(v2.begin(), v2.end(), ostream_iterator<int>(cout, " "));
}
