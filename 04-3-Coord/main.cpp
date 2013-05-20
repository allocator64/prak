#include <iostream>
#include <utility>

namespace Game{
    template<class T>
    class Coord
    {
        std::pair<T, T> crd;
    public:
        typedef T value_type;
        Coord() :crd() {}
        Coord(const T &row, const T &col) :crd(row, col) {}
        Coord(const Coord &t) :crd(t.crd) {}

        bool operator<(const Coord &t) const { return crd < t.crd; }
        bool operator>(const Coord &t) const { return t < *this; }
        bool operator<=(const Coord &t) const { return !(t < *this); }
        bool operator>=(const Coord &t) const { return !(*this < t); }

        bool operator==(const Coord &t) const { return !(*this < t || t < *this); }
        bool operator!=(const Coord &t) const { return *this < t || t < *this; }

        Coord& operator=(const Coord &t){ crd = t.crd; return *this; }

        T get_row() const { return crd.first; }
        T get_col() const { return crd.second; }

        friend std::ostream& operator <<(std::ostream& out, const Coord &t)
        {
            return out << "(" << t.get_row() << "," << t.get_col() << ")";
        }
    };
    typedef Coord<int> IntCoord;
}
