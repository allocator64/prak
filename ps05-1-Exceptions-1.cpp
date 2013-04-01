#include <iostream>

using namespace std;

struct End{};

struct Int
{
    int x;
    ~Int()
    {
        cout << x << endl;
    }
};

void print() throw (End)
{
    int t;
    if (cin >> t)
    {
        Int tmp = {t};
        tmp.x = tmp.x;
        print();
    } else
        throw End();

}

int main()
{
    try
    {
        print();
    }
    catch (End&)
    {
    }
    return 0;
}