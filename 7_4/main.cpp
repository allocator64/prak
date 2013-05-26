#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <iterator>
#include <functional>

using namespace std;

struct Rule {
    char from;
    string to;
    Rule() :from(), to() {}
    Rule(const char _from, const string &_to) : from(_from), to(_to) {}
    friend istream & operator >> (istream & in, Rule &G)
    {
        in >> G.from >> G.to;
        return in;
    }
    bool operator < (const Rule &a)
    {
        return from < a.from || (from == a.from && to < a.to);
    }
};

bool is_eps_r(const Rule &r)
{
    return ('A' <= r.from && r.from <= 'Z' && r.to == "_");
}

inline bool is_term_itm(const char c)
{
    return c >= 'a' && c <= 'z';
}

unordered_set<char> get_eps_r(const vector<Rule> &G)
{
    unordered_set<char> res;

    for(auto &i : G)
        if(is_eps_r(i))
            res.insert(i.from);

    while( 1 ) {
        auto sz = res.size();
        for(auto &i : G)
            if(find_if_not(i.to.begin(), i.to.end(), [&res](char c) -> bool
            {
                return static_cast<bool>(res.count(c));
            }) == i.to.end())
                res.insert(i.from);

        if(sz == res.size())
            break;
    }
    return res;
}

vector<Rule> morph_r(const Rule &r, const unordered_set<char> &e_gen)
{
    vector<Rule> res;
    string curr;
    function<void(size_t)> solve = [&solve, &r, &e_gen, &res, &curr](size_t ind) {
        if(ind == r.to.size()) {
            if(curr != "")
                res.push_back(Rule(r.from, curr));
        } else if(e_gen.count(r.to[ind])) {
            curr += r.to[ind];
            solve(ind + 1);
            curr.pop_back();
            solve(ind + 1);
        } else {
            curr += r.to[ind];
            solve(ind + 1);
            curr.pop_back();
        }
    };

    solve(0);

    return res;
}

bool cut_eps_r(vector<Rule> &G)
{
    auto e_gen = get_eps_r(G);

    vector<Rule> res;
    for(auto &i : G) {
        if(is_eps_r(i))
            continue;
        auto v = morph_r(i, e_gen);
        res.insert(res.end(), v.begin(), v.end());
    }

    bool changed = false;

    if(e_gen.count('S')) {
        res.push_back(Rule('$', "_"));
        res.push_back(Rule('$', "S"));
        changed = true;
    }

    G = res;

    return changed;
}

void cut_end(vector<Rule> &G)
{
    unordered_set<char> ok;
    while(true) {
        auto sz = ok.size();
        for(auto r : G) {
            bool f = true;
            for(auto c : r.to) {
                if('A' <= c && c <= 'Z' && !ok.count(c)) {
                    f = false;
                    break;
                }
            }
            if(f)
                ok.insert(r.from);
        }
        if(sz == ok.size())
            break;
    }
    vector<Rule> tmp;
    for(auto r : G) {
        if(!ok.count(r.from))
            continue;
        if(find_if(r.to.begin(), r.to.end(), [&ok](char c) -> bool {
            return 'A' <= c && c <= 'Z' && !ok.count(c);
        }) == r.to.end())
            tmp.push_back(r);
    }
    G = tmp;
}

void cut_next(vector<Rule> &G, char start = 'S')
{
    unordered_set<char> H;
    H.insert(start);

    while(true) {
        auto sz = H.size();
        for(auto &i : G) {
            if(H.count(i.from))
                for(auto &c : i.to)
                    if(!is_term_itm(c))
                        H.insert(c);
        }
        if(sz == H.size())
            break;
    }

    vector<Rule> tmp;

    for(auto &i : G)
        if(H.count(i.from))
            tmp.push_back(i);
    G = tmp;
}

int main()
{
    vector<Rule> G;
    copy(istream_iterator<Rule>(cin), istream_iterator<Rule>(), back_inserter(G));

    bool f = cut_eps_r(G);
    cut_end(G);
    cut_next(G, f ? '$' : 'S');

    for (auto &i : G)
        cout << i.from << " " << i.to << endl;

    return 0;
}