#include <ctime>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <functional>

template<class T>
class Ptr
{
    T* ptr;
public:
    Ptr(T *p) :ptr(p) {}
    Ptr(Ptr &&p) :ptr(p.ptr)
    {
        p.ptr = 0;
    }   
    T* operator*() const
    {
        return ptr;
    }
    
    T* operator->() const
    {
        return ptr;
    }
    
    ~Ptr()
    {
        if (ptr)
            delete ptr;
    }
    Ptr() = delete;
    Ptr(Ptr &p) = delete;
    Ptr &operator=(Ptr &) = delete;
};

class DateFormatter {
protected:
    static int d(const std::tm &t) { return t.tm_mday; }
    static int m(const std::tm &t) { return t.tm_mon + 1; }
    static int y(const std::tm &t) { return t.tm_year + 1900; }
public:
    virtual std::string printDate(const std::tm&) const = 0;
    virtual ~DateFormatter() {}
    const static std::vector<std::function<DateFormatter *()> > creators;
    static DateFormatter *get_formatter(int k) {
        return creators[k - 1]();
    }
};

class NormalDateFormater : public DateFormatter{
public:
    static DateFormatter *create() {return new NormalDateFormater(); }
    std::string printDate(const std::tm &t) const {
        std::stringstream ss;
        ss << std::setfill('0') << std::setw(2) << d(t) << "."
            << std::setfill('0') << std::setw(2) << m(t) << "." << y(t);
        return ss.str();
    }
};

class ReverseDateFormater : public DateFormatter{
public:
    static DateFormatter *create() {return new ReverseDateFormater(); }
    std::string printDate(const std::tm &t) const {
        std::stringstream ss;
        ss << y(t) << "-" << std::setfill('0') << std::setw(2) << m(t) << "-"
            << std::setfill('0') << std::setw(2) << d(t);
        return ss.str();
    }
};


const std::vector<std::function<DateFormatter *()> > DateFormatter::creators =
    {NormalDateFormater::create, ReverseDateFormater::create};


class TimeFormatter {
public:
    virtual std::string printTime(const std::tm&) const = 0;
    virtual ~TimeFormatter() {}
    const static std::vector<std::function<TimeFormatter *()> > creators;
    static TimeFormatter *get_formatter(int k) {
        return creators[k - 1]();
    }
};

class EuropeTimeFormatter : public TimeFormatter{
public:
    static TimeFormatter *create() {return new EuropeTimeFormatter(); }
    std::string printTime(const std::tm &t) const {
        char buffer[80];
        std::strftime(buffer,80,"%R", &t);
        return buffer;
    }
};

class USTimeFormatter : public TimeFormatter{
public:
    static TimeFormatter *create() {return new USTimeFormatter(); }
    std::string printTime(const std::tm &t) const {
        char buffer[80];
        std::strftime(buffer,80,"%I:%M %p", &t);
        return buffer;
    }

};

const std::vector<std::function<TimeFormatter *()> > TimeFormatter::creators =
    {EuropeTimeFormatter::create, USTimeFormatter::create};

Ptr<DateFormatter> createDateFormatter(int k)
{
    return Ptr<DateFormatter>(DateFormatter::get_formatter(k));
}

Ptr<TimeFormatter> createTimeFormatter(int k)
{
    return Ptr<TimeFormatter>(TimeFormatter::get_formatter(k));
}
