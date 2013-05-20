#include <iostream>
#include <vector>
#include <set>

using namespace std;

class Rule
{
public:
    Rule() :from(), to() {}
    char from;
    string to;
};

vector<Rule> v;
vector<int> n(256);

int main()
{
    ios_base::sync_with_stdio(0);

    Rule t;
    while (cin >> t.from >> t.to)
        v.push_back(t);


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
        if (n[i.from]) {
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