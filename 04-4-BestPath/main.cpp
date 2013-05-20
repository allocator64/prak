#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>
#include <cassert>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <memory>
#include <set>
#include <map>
#include <queue>

namespace Game{

    template<class T>
    class Coord;

    template <class T>
    class HexTopology;

    template<class M>
    class OneDistance;

    template<class T>
    class PointerMatrix;

    typedef Coord<int> IntCoord;

    template<class M, class F, class T>
    std::vector<IntCoord > bestpath(M&, IntCoord, IntCoord, const F &dist = OneDistance<M>(), const T &topol = HexTopology<M>());
}

template<class T>
class Game::Coord
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

    Coord operator+(const Coord &t) const { return Coord(crd.first + t.get_row(), crd.second + t.get_col()); }

    bool not_in_rect(int rows, int cols) const
    { return !(0 <= crd.first && crd.first < rows && 0 <= crd.second && crd.second < cols); }
    friend std::ostream& operator <<(std::ostream& out, const Coord &t)
    {
        return out << "(" << t.get_row() << "," << t.get_col() << ")";
    }
};

template <class T>
class Game::HexTopology
{
    int rows, cols;
public:
    HexTopology (const T &m) :rows(m.get_rows()), cols(m.get_cols()) {}
    HexTopology (int _rows, int _cols) :rows(_rows), cols(_cols) {}
    std::vector<IntCoord> operator() (const IntCoord &cord) const
    {
        if (cord.not_in_rect(rows, cols)) throw std::range_error("range_error");
        static const std::vector<IntCoord> base = {{1, 0},{-1, 0},{0, -1},{0, 1}},
        extra[2] = {{{1, -1},{1, 1}}, {{-1, -1},{-1, 1}}};
        std::vector<IntCoord> res(base);
        std::copy(extra[cord.get_col() % 2].begin(), extra[cord.get_col() % 2].end(), std::back_inserter(res));
        std::transform(res.begin(), res.end(), res.begin(), std::bind1st(std::plus<IntCoord>(), cord));
        res.resize(std::remove_if(res.begin(), res.end(), std::bind(&IntCoord::not_in_rect, std::placeholders::_1, rows, cols)) - res.begin());
        std::sort(res.begin(), res.end());
        return res;
    }
};

template<class T>
class Game::PointerMatrix
{
private:
    int rows;
    int cols;
    std::vector<std::vector<std::unique_ptr<T> > > m;

    class Ref
    {
    private:
        std::unique_ptr<T> &p;
    public:
        Ref(std::unique_ptr<T> &_p) : p(_p) {}
        Ref& operator=(T *_p)
        {
            p.reset(_p);
            return *this;
        }
        operator T*() { return p.get(); }
    };

public:
    static const int ROWS_MAX = 16384, COLS_MAX = 16384;
    typedef T value_type;
    PointerMatrix(int _rows, int _cols, T *p)
    :rows(_rows), cols(_cols), m()
    {
        if (!(0 < rows && rows < ROWS_MAX && 0 < cols && cols < COLS_MAX && p != 0))
            throw std::invalid_argument("invalid_argument");
        std::generate_n(std::back_inserter(m), rows,
                        [p,_cols]() {
                            std::vector<std::unique_ptr<T> > tmp;
                            std::generate_n(std::back_inserter(tmp), _cols, [p](){ return std::unique_ptr<T>(p->clone()); });
                            return tmp;
                        });
    }

    Ref at(const IntCoord &cord)
    {
        if (cord.not_in_rect(rows, cols))
            throw std::range_error("range_error");
        return Ref(m[cord.get_row()][cord.get_col()]);
    }

    T* at(const IntCoord &cord) const
    {
        if (cord.not_in_rect(rows, cols))
            throw std::range_error("range_error");
        return m[cord.get_row()][cord.get_col()].get();
    }

    int get_rows() const { return rows; }
    int get_cols() const { return cols; }

    PointerMatrix() = delete;
    PointerMatrix(const PointerMatrix &p) = delete;
    PointerMatrix& operator=(const PointerMatrix &p) = delete;
};


template<class M>
class Game::OneDistance
{
public:
    int operator() (const M& m, const IntCoord &from, const IntCoord &to) const
    {
        auto topology = HexTopology<M>(m);
        auto near = topology(from);
        if (std::find(near.begin(), near.end(), to) == near.end())
            throw std::range_error("range_error");
        return 1;
    }
};


namespace Game{

    template<class Col>
    class pop_iterator
    {
        Col &ref;
    public:
        typedef typename Col::value_type value_type;
        typedef typename Col::difference_type difference_type;
        typedef typename Col::pointer pointer;
        typedef typename Col::reference reference;
        typedef typename std::input_iterator_tag iterator_category;

        pop_iterator(Col &_ref) : ref(_ref) {}
        value_type operator*() { value_type t = *ref.begin(); ref.erase(ref.begin()); return t; }
        pop_iterator& operator++() { return *this; }
        bool operator==(const pop_iterator &it) const { return ref.empty(); }
        bool operator!=(const pop_iterator &it) const { return !(*this == it); }
    };

    template<class M, class F, class T>
    std::vector<IntCoord>
    bestpath(M &board, IntCoord from, IntCoord to, const F &dist, const T &topol)
    {
        const int n = board.get_rows();
        const int m = board.get_cols();
        const int INF = 1e9;

        typedef std::set<std::pair<int, int> > set_t;
        set_t bank;
        std::vector<int> len(n * m, INF);
        std::vector<int> parent(n * m, INF);

        int s = from.get_row() * m + from.get_col();
        int f = to.get_row() * m + to.get_col();

        len[s] = 0;
        bank.insert(std::make_pair(0, s));

        std::vector<std::vector<Game::IntCoord> > path(n * m);
        path[s] = std::vector<Game::IntCoord>{from};

        std::for_each(pop_iterator<set_t>(bank), pop_iterator<set_t>(bank),
            [&, m](std::pair<int, int> ref)
        {
            int cur = ref.second;
            auto near = topol(IntCoord(cur / m, cur % m));
            std::for_each(near.begin(), near.end(),
                [&bank, &len, &path, &m, &cur, &dist, &board](IntCoord &j)
            {
                int v = j.get_row() * m + j.get_col();
                int dst = dist(board, IntCoord(cur / m, cur % m), IntCoord(v / m, v % m));
                if (len[cur] + dst < len[v])
                {
                    bank.erase(std::make_pair(len[v], v));
                    len[v] = len[cur] + dst;
                    path[v] = path[cur];
                    path[v].push_back(j);
                    bank.insert(std::make_pair(len[v], v));
                }
                else if (len[cur] + dst == len[v] && path[v] > path[cur])
                {
                    path[v] = path[cur];
                    path[v].push_back(j);
                }
            });
        });
        return path[f];
    }

    template<class M, class F>
    std::vector<IntCoord>
    bestpath(M &board, IntCoord from, IntCoord to, const F &dist)
    {
        return bestpath(board, from, to, dist, HexTopology<M>(board));
    }

    template<class M>
    std::vector<IntCoord>
    bestpath(M &board, IntCoord from, IntCoord to)
    {
        return bestpath(board, from, to, OneDistance<M>(), HexTopology<M>(board));
    }
}

class Data
{
    int x;
public:
    Data() :x() {}
    Data(int _x) :x(_x) {}
    Data(const Data &other) :x(other.x) {}
    virtual Data *clone() { return new Data(*this); }
    virtual ~Data(){}
};

int main ()
{
    using namespace Game;
    Data d(1);
    PointerMatrix<Data> m(5, 5, &d);

    auto res = Game::bestpath(m, IntCoord(0, 0), IntCoord(4, 4), OneDistance<PointerMatrix<Data> >(), HexTopology<PointerMatrix<Data> >(m));
    for (auto &i : res)
        std::cout << i << std::endl;
    return 0;
}
