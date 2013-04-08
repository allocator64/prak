#include <iostream>
#include <fstream>
#include <future>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

unordered_map<string, int> words;

int calc(const string &fn)
{
    ifstream fin(fn);
    string s;
    while (fin >> s)
    {
        words[s]++;
    }
    return 1;
}

int main(int argc, char **argv)
{
    ios_base::sync_with_stdio(0);

    vector<future<int>> fut(argc - 1);
    for (int i = 1; i < argc; ++i)
    {
        packaged_task<int()> f(bind(&calc, argv[i]));
        fut[i - 1] = f.get_future();
        f();
    }

    for (auto &i : fut)
    {
        i.wait();
    }

    size_t size = words.size();
    vector<pair<int, string>> top;
    top.reserve(size);
    for (auto &i : words)
    {
        top.push_back(make_pair(i.second, i.first));
    }
    partial_sort(top.begin(), top.begin() + 20, top.end(), std::greater<pair<int, string>>());
    cout << size << "\n";
    int i = 0;
    for (auto it = top.begin(); i < 20 && it != top.end(); ++it, ++i)
        cout << it->second << " " << it->first << "\n";
    return 0;
}