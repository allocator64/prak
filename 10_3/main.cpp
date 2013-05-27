#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

class ErrorExp : public exception
{
    string s; 
public:
    ErrorExp (const std::string &str = "parse error") :s(str) {}
    virtual ~ErrorExp() throw() {}
    virtual const char* what() const throw() {
        return s.c_str();
    }
};

/*
+ - * / %
<Expression> ::= <Summand> { (+|-) <Summand>}
<Summand> ::= <Multiplier> { (*|/|%) <Multiplier>}
<Multiplier> ::= <Value> | (<Expression>) | -<Multiplier>
*/

enum {Number, Not, And, Xor, Or, Open, Close, End};
typedef bool elem_t;
int curlex;
elem_t curnum;
size_t pos;
string s;

elem_t ItemOr();
elem_t ItemXor();
elem_t ItemAnd();
elem_t ItemNot();

void nextlexem() {
    for (;isspace(s[pos]);++pos);
    if (s[pos] == '.') {
        curlex = End;
        return;
    }
    curlex = End;
    switch (s[pos]) {
        case '!':
            curlex = Not;
            ++pos;
            break;
        case '&':
            curlex = And;
            ++pos;
            break;
        case '^':
            curlex = Xor;
            ++pos;
            break;
        case '|':
            curlex = Or;
            ++pos;
            break;
        case '(':
            curlex = Open;
            ++pos;
            break;
        case ')':
            curlex = Close;
            ++pos;
            break;
        case '0':
        case '1':
            curlex = Number;
            curnum = s[pos++] - '0';
            break;
        default:
            break;
    }
    if (curlex == End)
        throw ErrorExp("Unknown symbol");
}

elem_t ItemOr() {
    elem_t value = ItemXor();
    while (curlex == Or) {
        nextlexem();
        value |= ItemXor();
    }
    return value;
}

elem_t ItemXor() {
    elem_t value = ItemAnd();
    while (curlex == Xor) {
        nextlexem();
        value ^= ItemAnd();
    }
    return value;
}

elem_t ItemAnd() {
    elem_t value = ItemNot();
    while (curlex == And) {
        nextlexem();
        value &= ItemNot();
    }
    return value;
}

elem_t ItemNot() {
    elem_t value = 0;
    switch (curlex) {
        case Number:
            value = curnum;
            nextlexem();
            break;
        case Open:
            nextlexem();
            value = ItemOr();
            if (curlex != Close)
                throw ErrorExp("Brackets disbalance");
            nextlexem();
            break;
        case Not:
            nextlexem();
            value = !ItemNot();
            break;
        default:
            throw ErrorExp("Wrong lexem");
    }
    return value;
}

int main() {
    vector<string> tmp;
    string t;
    while (getline(cin, t)) {
        s += " " + t;
        tmp.push_back(t);
    }
    // s += '.';
    try {
        nextlexem();
        elem_t result = ItemOr();
        if (curlex != End)
            throw ErrorExp("Wrong end of input");
        cout << result << endl;
    } catch (const ErrorExp &e) {
        cout << "WRONG" << endl;
        cerr << e.what() << endl;
        throw;
    }

    return 0;
}
