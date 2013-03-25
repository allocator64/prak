#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

void process(vector<int> &v1, const vector<int> &v2, int k)
{
    for_each(v2.begin(), v2.end(), [&](size_t i){ if (0 < i && i <= v1.size()) *(v1.begin() + i - 1) *= k; });
    copy(v1.begin(), v1.end(), ostream_iterator<int>(cout, " "));
}
