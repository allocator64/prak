#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

int main() {
    string word, L;
    unsigned N, H, t;
    set<unsigned> S;
    cin >> word >> L >> N >> H >> t;
    --H;
    for (unsigned i = 0; i < t; ++i) {
        unsigned k;
        cin >> k;
        S.insert(k - 1);
    }
    vector<vector<unsigned>> P(N, vector<unsigned>(L.size()));
    for (unsigned i = 0; i < N; ++i) {
        for (unsigned j = 0; j < L.size(); ++j) {
            cin >> P[i][j];
            --P[i][j];
        }
    }
    unsigned state = H;
    for (auto &c : word)
        state = P[state][L.find(c)];
    cout << (S.find(state) != S.end() ? "YES" : "NO") << endl;
    return 0;
}
