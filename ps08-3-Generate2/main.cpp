#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

vector<vector<int>> result;
vector<int> v1, v2;
size_t k;

void gen(bool flag = 1)
{
    if (v1.size() + v2.size() == k / 2) {
        vector<int> ans;
        copy(v1.begin(), v1.end(), back_inserter(ans));
        copy(v1.rbegin(), v1.rend(), back_inserter(ans));
        copy(v2.begin(), v2.end(), back_inserter(ans));
        copy(v2.rbegin(), v2.rend(), back_inserter(ans));
        result.push_back(move(ans));
        return;
    }
    
    v2.push_back(1);
    gen(0);
    v2.pop_back();

    v2.push_back(2);
    gen(0);
    v2.pop_back();

    if (flag) {
        v1.push_back(3);
        gen(1);
        v1.pop_back();

        v1.push_back(4);
        gen(1);
        v1.pop_back();
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin >> k;
    v1.reserve(k/2);
    v2.reserve(k/2);
    gen();
    sort(result.begin(), result.end());
    for (auto &i : result) {
        copy(i.begin(), i.end(), ostream_iterator<int>(cout));
        cout << "\n";
    }
    return 0;
}
