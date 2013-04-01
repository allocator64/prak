#include <fstream>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

class Date
{
    int day;
    int month;
    int year;
public:
    bool operator<(const Date &d) const
    {
        if (year != d.year)
            return year < d.year;
        if (month != d.month)
            return month < d.month;
        return day < d.day;
    }
    bool operator==(const Date &d) const
    {
        return year == d.year && month == d.month && day == d.day;
    }
    friend ostream& operator<<(ostream &out, const Date &d)
    {
        out << setfill('0') << setw(4) << d.year << "/"
            << setfill('0') << setw(2) << d.month << "/"
            << setfill('0') << setw(2) << d.day;
        return out;
    }
    friend istream& operator>>(istream &in, Date &d)
    {
        in >> d.year;
        in.ignore();
        in >> d.month;
        in.ignore();
        in >> d.day;
        return in;
    }
};

int main()
{
    ifstream fin("02-3.in");
    ofstream fout("02-3.out");

    map<pair<string, Date>, int> marks;
    vector<Date> dates;
    vector<string> names;
    string s;
    Date d;
    int m;

    while (fin >> s >> d >> m)
    {
        dates.push_back(d);
        names.push_back(s);
        marks[make_pair(s, d)] = m;
    }
    sort(dates.begin(), dates.end());
    dates.erase(unique(dates.begin(), dates.end()), dates.end());
    sort(names.begin(), names.end());
    names.erase(unique(names.begin(), names.end()), names.end());

    fout << "." << "\t";
    for (auto &date : dates)
        fout << date << "\t";
    fout << endl;

    for(auto &name : names)
    {
        fout << name << "\t";
        for (auto &date : dates)
        {
            auto it = marks.find(make_pair(name, date));
            if (it != marks.end())
                fout << it->second << "\t";
            else
                fout << ".\t";
        }
        fout << endl;
    }

    return 0;
}
