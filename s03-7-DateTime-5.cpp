#include <ctime>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <functional>


class DateFormatter
{
protected:
    static int d(const std::tm &t) { return t.tm_mday; }
    static int m(const std::tm &t) { return t.tm_mon + 1; }
    static int y(const std::tm &t) { return t.tm_year + 1900; }
public:
    virtual std::string printDate(const std::tm&) const = 0;
    virtual ~DateFormatter() {}
    const static std::vector<std::function<DateFormatter *()> > creators;
    static DateFormatter *get_formatter(int k) { return creators[k - 1](); }
};

class NormalDateFormater : public DateFormatter
{
public:
    static DateFormatter *create() {return new NormalDateFormater(); }
    std::string printDate(const std::tm &t) const
    {
        std::stringstream ss;
        ss << std::setfill('0') << std::setw(2) << d(t) << "."
            << std::setfill('0') << std::setw(2) << m(t) << "." << y(t);
        return ss.str();
    }
};

class ReverseDateFormater : public DateFormatter{
public:
    static DateFormatter *create() { return new ReverseDateFormater(); }
    std::string printDate(const std::tm &t) const
    {
        std::stringstream ss;
        ss << y(t) << "-" << std::setfill('0') << std::setw(2) << m(t) << "-"
            << std::setfill('0') << std::setw(2) << d(t);
        return ss.str();
    }
};

class LetterDateFormater : public DateFormatter
{
    static std::string m(const std::tm &t)
    {
        char buffer[80];
        std::strftime(buffer,80,"%b", &t);
        return buffer;
    }
public:
    static DateFormatter *create() { return new LetterDateFormater(); }
    std::string printDate(const std::tm &t) const
    {
        std::stringstream ss;
        ss << d(t) << " " << m(t) << " " << y(t);
        return ss.str();
    }
};

const std::vector<std::function<DateFormatter *()> > DateFormatter::creators =
    {NormalDateFormater::create, ReverseDateFormater::create, LetterDateFormater::create};

class MutableDateFormatter : public DateFormatter
{
    DateFormatter *rep;
    MutableDateFormatter(const MutableDateFormatter &);
    MutableDateFormatter& operator=(const MutableDateFormatter &);
public:
    explicit MutableDateFormatter(int k) :rep(DateFormatter::get_formatter(k)) {}
    void toType(int k)
    {
        delete rep;
        rep = DateFormatter::get_formatter(k);
    }
    std::string printDate(const std::tm &t) const
    {
        return rep->printDate(t);
    }
    ~MutableDateFormatter() { delete rep; }
};

void run(const std::string &s)
{
    std::fstream fin(s.c_str(), std::fstream::in);
    int k;
    fin >> k;
    MutableDateFormatter *df = new MutableDateFormatter(k);
    f(df);
    delete df;
}
