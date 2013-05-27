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

void Expression();
void Item();
void Mult();

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
    if (curlex != Number)
        cout << s[pos - 1];
    else
        cout << curnum;
    cout << endl;
}

void Expression() {
    Item();
    while (curlex == Plus || curlex == Minus) {
        nextlexem();
        Item();
    }
}

void Item() {
    Mult();
    while (curlex == Multiply || curlex == Divide || curlex == Remaind) {
        nextlexem();
        Mult();
    }
}

void Mult() {
    switch (curlex) {
        case Number:
            nextlexem();
            break;
        case Open:
            nextlexem();
            Expression();
            nextlexem();
            break;
        case Minus:
            nextlexem();
            Mult();
            break;
        default:
            break;
    }
}

int main() {
    string t;
    while (getline(cin, t))
        s += " " + t;
    s += '.';
    nextlexem();
    try {
        Expression();
    } catch (const ErrorExp &e) {
        cout << "ERROR " << e.what() << endl;
        throw;
    }

    return 0;
}
