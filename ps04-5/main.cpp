#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iomanip>


int main()
{
    std::vector<double> v;
    std::copy(std::istream_iterator<double>(std::cin), std::istream_iterator<double>(), std::back_inserter(v));
    size_t p10 = v.size() / 10;
    v.erase(v.begin(), v.begin() + p10);
    v.erase(v.end() - p10, v.end());
    std::sort(v.begin(), v.end());
    p10 = v.size() / 10;
    v.erase(v.begin(), v.begin() + p10);
    v.erase(v.end() - p10, v.end());
    double sum = 0;
    std::for_each(v.begin(), v.end(), [&sum](double t){ sum += t; });
    double res = sum / v.size();
    std::cout << std::setprecision(12) << res << std::endl;
    return 0;
}