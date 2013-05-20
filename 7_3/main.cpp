#include <iostream>
#include <vector>
#include <set>

using namespace std;

class Rule
{
public:
    Rule() :from(), to(), color() {}
    char from;
    string to;
    int color;
};

vector<Rule> v;
vector<int> n(256);

void dfs(Rule &cur)
{
    cur.color = 1;
    for (auto &c : cur.to)
        if (isupper(c))
            for (auto &p : v)
                if (p.color == 0 && p.from == c)
                    dfs(p);
}


int main()
{
    ios_base::sync_with_stdio(0);

    Rule t;
    while (cin >> t.from >> t.to)
        v.push_back(t);

    for (auto &i : v)
        if (i.from == 'S')
            dfs(i);

    size_t cur = 0;
    size_t last = -1;
    while (cur != last) {
        last = cur;
        for (auto &i : v)
            if (n[i.from] == 0) {
                bool ok = 1;
                for (auto &c : i.to)
                    if (isupper(c) && n[c] == 0){
                        ok = 0;
                        break;
                    }
                n[i.from] = ok;
                cur += ok;
            }
    }

    for (auto &i : v)
        if (i.color && n[i.from]) {
            bool ok = 1;
            for (auto &c : i.to)
                if (isupper(c) && n[c] == 0) {
                    ok = 0;
                    break;
                }
            if (ok)
                cout << i.from << " " << i.to << "\n";
        }

    return 0;
}