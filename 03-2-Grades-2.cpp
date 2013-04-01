#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <vector>
#include <map>

using namespace std;

int main(int argc, char **argv)
{
    ifstream fin("02-2.in");
    ofstream fout("02-2.out");

    map<string, pair<int, int> > m;
    string name;
    int mark;

    while (fin >> name >> mark)
    {
        auto it = m.find(name);
        if (it != m.end())
        {
            it->second.first += mark;
            it->second.second++;
        }
        else
            m[name] = make_pair(mark, 1);
    }
    for (auto &i : m)
        fout << i.first << " " << double(i.second.first) / i.second.second << endl;
    return 0;
}
