#include <iostream>
#include <set>
#include <map>
#include <iterator>
#include <algorithm>

using namespace std;

typedef set<char> elem_t;

int main() {
    // Init
    const char c1 = 'A' - 1, c2 = 'Z' + 1;
    const elem_t N1 {c1}, N2 {c2};
    map<pair<elem_t, char>, elem_t> m;
    map<char, elem_t> alias;
    set<elem_t> N {N1, N2};
    elem_t E, L;
    char from, cur = 0;
    string to;
    while ((cin >> from >> to)) {
        N.insert(elem_t {from});
        if (to.size() == 1) {
            if (to == "_")
                E.insert(from);
            else if (islower(to[0])) {
                L.insert(to[0]);
                m[make_pair(N1, to[0])].insert(from);
            } else
                alias[to[0]].insert(from);
        } else {
            bool first = isupper(to[0]);
            elem_t tmp {first ? to[0] : c1};
            for (unsigned i = first; i < to.size() - 1; ++i) {
                N.insert(tmp);
                L.insert(to[i]);
                if (cur == c1)
                    cur = c2 + 1;
                m[make_pair(tmp, to[i])].insert(cur);
                tmp = {cur++};
            }
            N.insert(tmp);
            L.insert(to.back());
            m[make_pair(tmp, to.back())].insert(from);
        }
    }

    // Alphabet
    copy(L.begin(), L.end(), ostream_iterator<char>(cout));
    cout << endl;
    // All empty
    bool ok = 1;
    while (ok) {
        ok = 0;
        for (auto &i : alias) if (E.count(i.first)) for (auto &j : i.second)
            if (!E.count(j)) {
                E.insert(j);
                ok = 1;
            }
    }
    // Remove right empty
    for (auto &i : E) for (auto &j : L) {
        auto cp = make_pair(elem_t {i}, j);
        if (m.count(cp))
            m[make_pair(N1, j)].insert(m[cp].begin(), m[cp].end());
    }
    // Remove unused rules
    ok = 1;
    while (ok) {
        ok = 0;
        for (auto &i : alias) for (auto &j : i.second) for (auto &l : L) for (auto &k : N) {
            auto cp = make_pair(elem_t {k}, l);
            if (m.count(cp) && m[cp].count(i.first) && !m[cp].count(j)) {
                m[cp].insert(j);
                ok = 1;
            }
        }
    }
    // Determining
    ok = 1;
    while (ok) {
        ok = 0;
        for (auto &f : m) if (!f.second.empty() && !N.count(f.second)) {
            ok = 1;
            for (auto &l : L) {
                auto cp = make_pair(f.second, l);
                for (auto &i : f.second) {
                    auto add = m[make_pair(elem_t {i}, l)];
                    m[cp].insert(add.begin(), add.end());
                }
            }
            N.insert(f.second);
        }
    }
    // Output
    auto dist = [&N](const elem_t &key) {
        int cnt = 0;
        for (auto &i : N) {
            ++cnt;
            if (i == key)
                break;
        }
        return cnt;
    };
    set<elem_t> final;
    if (E.count('S'))
        final.insert(N1);
    for (auto &i : N)
        if (i.count('S'))
            final.insert(i);

    cout << N.size() << endl << dist(N1) << " " << final.size() << " ";
    transform(final.begin(), final.end(), ostream_iterator<int>(cout, " "), dist);
    cout << endl;
    int cnt = dist(N2);
    for (auto &i : N) {
        for (auto &j : L) {
            auto cp = make_pair(i, j);
            if (m.count(cp) && N.count(m[cp]))
                cout << dist(m[cp]) << " ";
            else
                cout << cnt << " ";
        }
        cout << endl;
    }

    return 0;
}
