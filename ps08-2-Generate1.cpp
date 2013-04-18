#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> v;

void gen(size_t pos = 0, bool flag = 1)
{
    if (pos == v.size()) {
        for (auto &i : v)
            cout << i;
        cout << "\n";
        return;
    }
    v[pos] = 1;
    gen(pos + 1, 0);
    v[pos] = 2;
    gen(pos + 1, 0);

    if (flag) {
        v[pos] = 3;
        gen(pos + 1, 1);
        v[pos] = 4;
        gen(pos + 1, 1);
    }

}

int main()
{
    ios_base::sync_with_stdio(0);
    int k;
    cin >> k;
    v.resize(k);
    gen();
    return 0;
}
