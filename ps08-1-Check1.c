#include <iostream>
#include <string>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    string s;
    while (cin >> s) {
        size_t pos = 0;
        size_t len = s.size();
        while (pos < len && (s[pos] == '3' || s[pos] == '4'))
            ++pos;
        while (pos < len && (s[pos] == '1' || s[pos] == '2'))
            ++pos;
        if (pos == len)
            cout << "1\n";
        else
            cout << "0\n";
    }
    return 0;
}
