#include <iostream>
#include <vector>

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

    for (auto &i : v)
        if (i.color)
            cout << i.from << " " << i.to << "\n";

    return 0;
}