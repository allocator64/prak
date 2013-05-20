#include <iostream>
#include <iterator>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    transform(istream_iterator<string>(cin), istream_iterator<string>(), ostream_iterator<string>(cout, "\n"),
        [](string s) {
            for (auto it = s.end(); it != s.begin(); --it)
                if (equal(s.begin(), it, s.rbegin() + (s.end() - it)))
                    return string(s.begin(), it);
            return string();
        });
    return 0;
}