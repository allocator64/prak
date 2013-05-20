#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>
#include <cassert>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <array>


using std::vector;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

class Game {
    int len, colors;
    vector<int> codeword;

    int counter;
    bool finished;

    struct TurnResult;

    TurnResult check(const vector<int>) const;
    bool is_valid(const vector<int> &) const;

public:
    Game(int l=4, int c=6);
    bool next_turn(const vector<int> &);
    int get_turns_count() const;
};

struct Game::TurnResult {
    int black, white;
    TurnResult(int b, int w) :black(b), white(w) {}
};

Game::Game(int l, int c) :len(l), colors(c), codeword(l), counter(), finished() {
    std::generate(codeword.begin(), codeword.end(), [this](){ return (rand() % colors) + 1; });
}

bool Game::is_valid(const vector<int> &v) const {
    return int(v.size()) == len && std::find_if_not(v.begin(), v.end(), [this](int x){ return 0 < x && x <= colors; }) == v.end();
}

Game::TurnResult Game::check(vector<int> test) const {
    std::vector<int> code(codeword);
    std::transform(code.begin(), code.end(), test.begin(), test.begin(), [](int a, int b){ return a == b ? 0 : b; });
    std::transform(code.begin(), code.end(), test.begin(), code.begin(), [](int a, int b){ return b == 0 ? 0 : a; });
    int black = std::count(code.begin(), code.end(), 0);
    int white = std::count_if(test.begin(), test.end(), [&code](int b) -> bool {
        if (b == 0) return 0;
        auto it = find(code.begin(), code.end(), b);
        if (it == code.end()) return 0;
        *it = 0;
        return 1;
    });
    return TurnResult(black, white);
}

bool Game::next_turn(const vector<int> &test) {
    if (is_valid(test)) {
        ++counter;
        TurnResult result = check(test);
        cout << result.black << " " << result.white << endl;
        if (result.black == len)
            finished = 1;
    } else {
        cout << "Incorrect input, please, try again" << endl;
    }
    return finished;
}

int Game::get_turns_count() const {
    return counter;
}

template<class T, int n>
struct Array
{
    vector<int> v;
    Array() :v() {}
};

template<class T, int n>
std::istream& operator>>(std::istream &in, Array<T, n> &a)
{
    a.v.clear();
    std::copy_n(std::istream_iterator<T>(cin), n, std::back_inserter(a.v));
    return in;
}

int main() {

    srand(time(0));

    enum { N = 4, M = 6 };

    Game game(N, M);

    find_if(std::istream_iterator<Array<int, N>>(cin),
        std::istream_iterator<Array<int, N>>(),[&game](const Array<int, N> &a) {
            return game.next_turn(a.v);
        });

    cout << "Finished" << endl << "Attempt: " << game.get_turns_count() << endl;

    return 0;
}