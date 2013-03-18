#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <memory>


template<class T>
class PointerMatrix
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

    Ref at(int row, int col)
    {
        if (!(0 <= row && row < rows && 0 <= col && col < cols))
            throw std::range_error("range_error");
        return Ref(m[row][col]);
    }

    T* at(int row, int col) const
    {
        if (!(0 <= row && row < rows && 0 <= col && col < cols))
            throw std::range_error("range_error");
        return m[row][col].get();
    }

    int get_rows() const { return rows; }
    int get_cols() const { return cols; }

    PointerMatrix() = delete;
    PointerMatrix(const PointerMatrix &p) = delete;
    PointerMatrix& operator=(const PointerMatrix &p) = delete;
};
