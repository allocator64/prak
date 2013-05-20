#include <iostream>
#include <vector>
#include <set>

using namespace std;

class Rule
{
public:
    Rule() :from(), to(), color() {}
    Rule(char f, string t, unsigned c) :from(f), to(t), color(c) {}
    char from;
    string to;
    unsigned color;
};

vector<Rule> v;
vector<int> x(256);
vector<Rule> w;

vector<int> n(256);

void dfs(Rule &cur)
{
    cur.color |= 2;
    for (auto &c : cur.to)
        if (isupper(c))
            for (auto &p : w)
                if ((p.color & 2) == 0 && p.from == c)
                    dfs(p);
}


int main()
{
    ios_base::sync_with_stdio(0);

    Rule t;
    while (cin >> t.from >> t.to)
        v.push_back(t);

    for (auto &i : v) {
        size_t pos = 0;
        while ((pos = i.to.find('_')) != string::npos)
            i.to.erase(pos);
    }
    
    for (auto &i : v)
        if (i.to == "")
            x[i.from] = 1;

    size_t cur = 0;
    size_t last = -1;
    while (cur != last) {
        last = cur;
        for (auto &i : v)
            if (x[i.from] == 0) {
                bool ok = 1;
                for (auto &c : i.to)
                    if (!isupper(c) || x[c] == 0){
                        ok = 0;
                        break;
                    }
                x[i.from] = ok;
                cur += ok;
            }
    }
    for (auto &i : v)
        if (i.to != "")
            w.push_back(i);
    char S = 'S';
    if (x[S]) {
        S = '$';
        w.push_back(Rule('$', "S", 0));
        w.push_back(Rule('$', "", 0));
    }
    for (auto &r : w)
        if (r.color == 0) {
            vector<string> alpha;
            vector<char> A;
            string curs;
            size_t len = 0;
            for (auto &c : r.to)
                if (x[c] == 0)
                    curs += c;
                else {
                    alpha.push_back(curs);
                    len += curs.size();
                    curs = "";
                    A.push_back(c);
                }
            unsigned long long mask = 0;
            if (len == 0)
                mask = 1;
            for (; mask < (1ull << A.size()) - 1; ++mask) {
                string to = alpha[0];
                for (size_t i = 0; i < A.size(); ++i){
                    if (mask & (1ull << i))
                        to += A[i];
                    to += alpha[i + 1];
                }
                w.push_back(Rule(r.from, to, 1));
            }
        }

    for (auto &i : w)
        if (i.from == 'S')
            dfs(i);    

    cur = 0;
    last = -1;
    while (cur != last) {
        last = cur;
        for (auto &i : w)
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

    for (auto &i : w)
        if ((i.color & 2) && n[i.from]) {
            bool ok = 1;
            for (auto &c : i.to)
                if (isupper(c) && n[c] == 0) {
                    ok = 0;
                    break;
                }
            if (ok) {
                if (i.to == "")
                    i.to = "_";
                cout << i.from << " " << i.to << "\n";
            }
        }

    return 0;
}