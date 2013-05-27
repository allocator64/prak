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
<Multiplier> ::= <Number> | (<Expression>)
*/

enum {Number, Plus, Minus, Multiply, Divide, Remaind, Open, Close, End};
typedef int elem_t;
int curlex;
elem_t curnum;
size_t pos;
string s;

elem_t Expression();
elem_t Item();
elem_t Mult();

void nextlexem() {
    for (;isspace(s[pos]);++pos);
    if (s[pos] == '.') {
        curlex = End;
        return;
    }
    curlex = End;
    switch (s[pos]) {
        case '+':
            curlex = Plus;
            ++pos;
            break;
        case '-':
            curlex = Minus;
            ++pos;
            break;
        case '*':
            curlex = Multiply;
            ++pos;
            break;
        case '/':
            curlex = Divide;
            ++pos;
            break;
        case '%':
            curlex = Remaind;
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
        default:
            if (isdigit(s[pos])) {
                curlex = Number;
                curnum = 0;
                while (isdigit(s[pos]))
                    curnum = curnum * 10 + s[pos++] - '0';
            }
    }
    if (curlex == End)
        throw ErrorExp("Unknown symbol");
}

elem_t Expression() {
    elem_t Sum = Item();
    while (curlex == Plus || curlex == Minus) {
        int last = curlex;
        nextlexem();
        if (last == Plus)
            Sum += Item();
        else
            Sum -= Item();
    }
    return Sum;
}

elem_t Item() {
    elem_t Mul = Mult();
    while (curlex == Multiply || curlex == Divide || curlex == Remaind) {
        int last = curlex;
        nextlexem();
        if (last == Multiply)
            Mul *= Mult();
        else {
            elem_t t = Mult();
            if (t == 0)
                throw ErrorExp("Zero divide");
            if (last == Divide)
                Mul /= t;
            else
                Mul %= t;
        }
    }
    return Mul;
}

elem_t Mult() {
    elem_t value = 0;
    switch (curlex) {
        case Number:
            value = curnum;
            nextlexem();
            break;
        case Open:
            nextlexem();
            value = Expression();
            if (curlex != Close)
                throw ErrorExp("Brackets disbalance");
            nextlexem();
            break;
        case Minus:
            nextlexem();
            value = -Mult();
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
    s += '.';
    try {
        nextlexem();
        elem_t result = Expression();
        if (curlex != End)
            throw ErrorExp("Wrong end of input");
        cout << result << endl;
    } catch (const ErrorExp &e) {
        cout << "WRONG" << endl;
        cerr << e.what() << endl;
    }

    return 0;
}
