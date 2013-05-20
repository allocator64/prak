#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;

struct Student
{
    string filename;
    string name;
    vector<int> marks;

    Student() : filename(), name(), marks() {}

    friend istream& operator>>(istream &in, Student &t)
    {
        in >> t.name;

        t.marks.clear();
        int k;
        in >> k;
        while (k)
        {
            t.marks.push_back(k);
            in >> k;
        }
        return in;
    }

    friend ostream& operator<<(ostream &out, const Student &t)
    {
        out << t.filename << " " << t.name << " ";
        copy(t.marks.begin(), t.marks.end(), ostream_iterator<int>(out, " "));
        return out;
    }

    double avg() const
    {
        return accumulate(marks.begin(), marks.end(), 0.0) / marks.size();
    }
};

int main(int argc, char **argv)
{
    vector<Student> v;
    for (int i = 1; i < argc; ++i)
    {
        ifstream in(argv[i]);
        Student t;
        while (in >> t)
        {
            t.filename = argv[i];
            v.push_back(t);
        }
    }

    double avg = 0;
    for_each(v.begin(), v.end(), [&avg](const Student &t){ avg += t.avg(); });
    avg /= v.size();
    ofstream out("02-1.out");
    copy_if(v.begin(), v.end(), ostream_iterator<Student>(out, "\n"),
        [&avg](const Student &t){ return !(t.avg() < avg);});
    return 0;
}
