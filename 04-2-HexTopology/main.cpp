#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <memory>

template <class T>
class HexTopology
{
    int rows, cols;
public:
    HexTopology (const T &m) :rows(m.get_rows()), cols(m.get_cols()) {}
    HexTopology (int _rows, int _cols) :rows(_rows), cols(_cols) {}
    std::vector<std::pair<int,int> > operator() (int row, int col) const
    {
        if (!(0 <= row && row < rows && 0 <= col && col < cols))
            throw std::range_error("range_error");
        static const std::vector<std::pair<int, int> >
            base = {{1, 0},{-1, 0},{0, -1},{0, 1}},
            extra[2] = {{{1, -1},{1, 1}}, {{-1, -1},{-1, 1}}};
        std::vector<std::pair<int, int> > res(base);
        std::copy(extra[col % 2].begin(), extra[col % 2].end(), std::back_inserter(res));
        std::transform(res.begin(), res.end(), res.begin(), [row, col](std::pair<int, int> &t)
            { return std::make_pair(row + t.first, col + t.second); });
        res.resize(std::remove_if(res.begin(), res.end(), [this](std::pair<int, int> &t)
            { return !(0 <= t.first && t.first < rows && 0 <= t.second && t.second < cols); }) - res.begin());
        std::sort(res.begin(), res.end());
        return res;
    }
};
