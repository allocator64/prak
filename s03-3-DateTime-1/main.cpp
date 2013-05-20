#include <ctime>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>

class DateFormater {
protected:
    static int d(std::tm &t) { return t.tm_mday; }
    static int m(std::tm &t) { return t.tm_mon + 1; }
    static int y(std::tm &t) { return t.tm_year + 1900; }
public:
    virtual std::string printDate(std::tm&) const = 0;
    virtual ~DateFormater() {}
};

class NormalDateFormater : public DateFormater{
public:
    std::string printDate(std::tm &t) const {
        std::stringstream ss;
        ss << std::setfill('0') << std::setw(2) << d(t) << "."
            << std::setfill('0') << std::setw(2) << m(t) << "." << y(t);
        return ss.str();
    }
};

class ReverseDateFormater : public DateFormater{
public:
    std::string printDate(std::tm &t) const {
        std::stringstream ss;
        ss << y(t) << "-" << std::setfill('0') << std::setw(2) << m(t) << "-"
            << std::setfill('0') << std::setw(2) << d(t);
        return ss.str();
    }
};

void run(const std::string &s) {
    std::fstream fin(s.c_str(), std::fstream::in);
    int k;
    fin >> k;
    DateFormater *df = 0;
    if (k == 1)
        df = new NormalDateFormater();
    else
        df = new ReverseDateFormater();
    f(df);
    delete(df);
}
