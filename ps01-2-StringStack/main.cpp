#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

class StringStack{
    vector<string> d;
public:

    StringStack();
    StringStack(const string &);
    StringStack(const char *);
    void push(const string &);
    string pop();
    StringStack &operator,(const string &);
    friend ostream& operator<<(ostream &, const StringStack &);
    StringStack& operator+=(const string &);
};

StringStack::StringStack() :d() {};

StringStack::StringStack(const string &s) :d() {
    push(s);
};

StringStack::StringStack(const char *s) {
    push(string(s));
}

void StringStack::push(const string &s) {
    d.push_back(s);
}

string StringStack::pop() {
    string ret = d.back();
    d.pop_back();
    return ret;
}

ostream& operator<<(ostream &stream, const StringStack &s) {
    copy(s.d.rbegin(), s.d.rend(), ostream_iterator<string>(stream, "\n"));
    return stream;
}

StringStack &StringStack::operator,(const string &s) {
    push(s);
    return *this;
}

StringStack& StringStack::operator+=(const string &s) {
    push(s);
    return *this;
}
/*
int main()
{

    StringStack s;
    s = "str1", "str2";
    s += "str3", "str4";
    cout << s;

    return 0;
}
*/
