#include <iostream>
#include <set>
#include <map>
#include <iterator>
#include <algorithm>

using namespace std;

typedef set<char> elem_t;

int main() {
    // Init
    elem_t N1 {'A' - 1}, N2 {'Z' + 1};
    map<pair<elem_t, char>, elem_t> m;
    set<elem_t> N {N1, N2};
    elem_t E, L;
    char from;
    string to;
    while ((cin >> from >> to)) {
        N.insert(elem_t {from});
        if (to == "_")
            E.insert(from);
        else if (to.size() == 2) {
            N.insert(elem_t {to[0]});
            L.insert(to[1]);
            m[make_pair(elem_t {to[0]}, to[1])].insert(from);
        } else {
            L.insert(to[0]);
            m[make_pair(N1, to[0])].insert(from);
        }
    }
    // Alphabet
    copy(L.begin(), L.end(), ostream_iterator<char>(cout));
    cout << endl;
    // Remove right empty
    for (auto &i : E)
        for (auto &j : L) {
            auto cp = make_pair(elem_t {i}, j);
            if (m.count(cp))
                m[make_pair(N1, j)] = m[cp];
        }
    // Determining
    bool changes = 1;
    while (changes) {
        changes = 0;
        for (auto &f : m)
            if (!f.second.empty() && !N.count(f.second)) {
                changes = 1;
                for (auto &letter : L) {
                    auto cur = make_pair(f.second, letter);
                    for (auto &i : f.second) {
                        auto add = m[make_pair(elem_t {i}, letter)];
                        m[cur].insert(add.begin(), add.end());
                    }
                }
                N.insert(f.second);
            }
    }
    // Output
    auto dist = [&N](elem_t key) {
        int cnt = 0;
        for (auto &i : N) {
            if (i == key)
                break;
            ++cnt;
        }
        return cnt;
    };
    int cnt_end = (E.count('S') != 0);
    cnt_end += count_if(N.begin(), N.end(), [](elem_t i)->bool { return i.count('S');});
    cout << N.size() << endl << dist(N1) + 1 << " " << cnt_end << " ";
    int cnt = 0;
    for (auto &i : N) {
        ++cnt;
        if (i.count('S'))
            cout << cnt << " ";
    }
    if (E.count('S'))
        cout << dist(N1) + 1;
    cout << endl;
    auto num_N2 = dist(N2) + 1;
    for (auto &i : N) {
        for (auto &j : L) {
            auto cp = make_pair(i, j);
            if (m.count(cp) && N.count(m[cp]))
                cout << dist(m[cp]) + 1 << " ";
            else
                cout << num_N2 << " ";
        }
        cout << endl;
    }
    return 0;
}
