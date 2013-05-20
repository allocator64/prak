#include <set>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <queue>


int main()
{
    int n, k;
    std::cin >> n >> k;
    std::vector<int> tmp;
    std::copy_n(std::istream_iterator<int>(std::cin), n, std::back_inserter(tmp));
    std::multiset<int> s;
    std::copy_n(tmp.begin(), k, std::inserter(s, s.begin()));

    std::inner_product(tmp.begin(), tmp.end() - k, tmp.begin() + k, 0,[](int,int){ return 0; },
        [&s](int first, int last){
            std::cout << *(s.begin()) << std::endl;
            s.erase(s.find(first));
            s.insert(last);
            return 0;
        });
    std::cout << *(s.begin()) << std::endl;
    return 0;
}