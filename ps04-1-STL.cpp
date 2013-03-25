#include <vector>
#include <iostream>
#include <iterator>


void process(std::vector<int> &v)
{
    for (int i = 0; v.begin() + i < v.end(); ++i)
        v.erase(v.begin() + i);
    std::copy(v.rbegin(), v.rend(), std::ostream_iterator<int>(std::cout, " "));
}