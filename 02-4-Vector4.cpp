#include <vector>
#include <algorithm>
#include <list>

using namespace std;

void process(const vector<int> &v, list<int> &lst)
{
    vector<int> tmp(v);
    sort(tmp.begin(), tmp.end());
    tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
    int cnt = 1;
    vector<int>::const_iterator it1 = tmp.begin();
    list<int>::iterator it2 = lst.begin();
    while (it2 != lst.end() && it1 != tmp.end())
    {
        if (*it1 < cnt)
            ++it1;
        else if (*it1 == cnt++)
        {
            ++it1;
            it2 = lst.erase(it2);
        }
        else
            ++it2;
    }
}
