#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>
#include <cassert>
#include <sstream>
#include <algorithm>
#include <iterator>


using std::cout;
using std::cin;
using std::cerr;
using std::endl;

template<int len, int colors>
class Game
{
public:
    struct UserData;
private:
    std::istream &in;
    std::ostream &out;
    std::ostream &err;

    std::vector<int> codeword;

    int counter;
    bool finished;

    struct TurnResult;

    void promt() const;
    TurnResult check(std::vector<int>) const;
    bool is_valid(const std::vector<int> &v) const;

    bool next_turn(const UserData &);

public:

    Game(std::istream &_in=cin, std::ostream &_out=cout, std::ostream &_err=cerr);
    void play();
};

template<int len, int colors>
struct Game<len, colors>::TurnResult
{
    size_t black, white;
    TurnResult(size_t b, size_t w) :black(b), white(w) {}
};

template<int len, int colors>
struct Game<len, colors>::UserData
{
    std::vector<int> data;
    UserData() :data() {}
    friend std::istream& operator>>(std::istream &in, UserData &sg)
    {
        sg.data.clear();
        std::copy_n(std::istream_iterator<int>(in), len, std::back_inserter(sg.data));
        return in;
    }
};

template<int len, int colors>
Game<len, colors>::Game(std::istream &_in, std::ostream &_out, std::ostream &_err)
:in(_in), out(_out), err(_err), codeword(len), counter(), finished()
{
    srand(unsigned(time(0)));
    std::generate(codeword.begin(), codeword.end(), [this](){ return (rand() % colors) + 1; });
}

template<int len, int colors>
void Game<len, colors>::promt() const
{
    if (counter == 0)
        cout << "Input " << len << " numbers, each from 1 to " << colors << endl;
    cout << "[#" << counter + 1 << "]> ";
}

template<int len, int colors>
bool Game<len, colors>::is_valid(const std::vector<int> &v) const
{
    return v.size() == len && std::find_if_not(v.begin(), v.end(),
        [this](int x){ return 0 < x && x <= colors; }) == v.end();
}

template<int len, int colors>
typename Game<len, colors>::TurnResult Game<len, colors>::check(std::vector<int> test) const
{
    std::vector<int> code(codeword);
    std::transform(code.begin(), code.end(), test.begin(), test.begin(), [](int a, int b){ return a == b ? 0 : b; });
    std::transform(code.begin(), code.end(), test.begin(), code.begin(), [](int a, int b){ return b == 0 ? 0 : a; });
    size_t black = std::count(code.begin(), code.end(), 0);
    size_t white = std::count_if(test.begin(), test.end(), [&code](int b) -> bool {
        if (b == 0) return 0;
        auto it = find(code.begin(), code.end(), b);
        if (it == code.end()) return 0;
        *it = 0;
        return 1;
    });
    return TurnResult(black, white);
}

template<int len, int colors>
bool Game<len, colors>::next_turn(const UserData &sug)
{
    std::vector<int> test = sug.data;
    if (is_valid(test))
    {
        ++counter;
        TurnResult result = check(test);
        cout << result.black << " " << result.white << endl;
        if (result.black == len)
            finished = 1;
    } else
        cout << "Incorrect input, please, try again" << endl;
    return finished;
}

template<int len, int colors>
void Game<len, colors>::play() {
    std::find_if(std::istream_iterator<UserData>(in), std::istream_iterator<UserData>(),
        [this](const UserData &sg) { return this->next_turn(sg); });
    cout << "Finished" << endl << "Attempt: " << counter << endl;
}

int main() {

    Game<4, 6> game;
    game.play();

    return 0;
}
