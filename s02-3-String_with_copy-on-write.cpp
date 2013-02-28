#include <string>
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;


class String {
    class Repr;
    class Cref;

    Repr *rep;
public:
    String(std::string);
    String(const String &);
    String(const char *);

    String& operator=(const String &);
    String& operator+=(const String &);
    Cref operator[](int);
    operator std::string() const;

    char read(int) const;
    void write(int, char);

    friend std::ostream& operator<<(std::ostream &, const String &);

    ~String();
};

class String::Repr {
public:
    std::string str;
    int counter;
    Repr(const std::string s = "") {
        counter = 1;
        str = s;
    }
    Repr* get_own_copy() {
        if (counter == 1)
            return this;
        --counter;
        return new Repr(str);
    }
};

class String::Cref {
    String &str;
    int i;
public:
    Cref(String &s, int pos) :str(s), i(pos) {}
    operator char() const {
        return str.read(i);
    }
    void operator=(char ch) {
        str.write(i, ch);
    }
};

String::String(const String &s) : rep(s.rep) {
    ++rep->counter;
}

String::String(std::string s = "") :rep() {
    rep = new Repr(s);
}

String::String(const char *s) :rep() {
    rep = new Repr(s);
}

String::~String() {
    if (--rep->counter == 0)
        delete rep;
}

String& String::operator=(const String &s) {
    ++s.rep->counter;
    if (--rep->counter == 0)
        delete rep;
    rep = s.rep;
    return *this;
}

String& String::operator+=(const String &s) {
    rep = rep->get_own_copy();
    rep->str += std::string(s);
    return *this;
}

String::operator std::string() const {
    return rep->str;
}

String::Cref String::operator[](int i) {
    return Cref(*this, i);
}

char String::read(int i) const {
    return rep->str[i];
}

void String::write(int i, char ch) {
    rep = rep->get_own_copy();
    rep->str[i] = ch;
}

std::ostream& operator<<(std::ostream &stream, const String &s) {
    stream << std::string(s);
    return stream;
}
/*
int main() {
    String c, a = "abc";
    String b = a; // в памяти хранится "abc" в одном экземпляре
    c = a;
    b += "aaa"; // для b создался новый "массив" символов.
    c[1] = 'f'; // a не изменилось
    cerr << a << endl << b << endl << c << endl << c[1] << endl;
    // String a = "ABC";
    // String b = "DEF";
    // b += a;
    // cerr << "b = " << std::string(b) << endl;
    // b[2] = '_';
    // cerr << "b = " << std::string(b) << endl;
    // cerr << "b[2] = " << b[2] << endl;
    return 0;
}
*/