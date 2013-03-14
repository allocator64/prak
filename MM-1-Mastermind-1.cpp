#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>
#include <cassert>
#include <sstream>
#include <algorithm>
#include <iterator>

using std::vector;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::stringstream;


class Game {
    int len, colors;
    vector<int> codeword;

    int counter;
    bool finished;

    struct TurnResult;

    void promt() const;
    vector<int> load() const;
    TurnResult check(const vector<int>) const;
    bool is_valid(const vector<int> &) const;

public:
    Game(int, int);
    bool has_finished() const;
    void next_turn();
    int get_turns_count() const;
};

struct Game::TurnResult {
    int black, white;
    TurnResult(int b, int w) :black(b), white(w) {}
};

Game::Game(int l=4, int c=6) :len(l), colors(c), counter(), finished(), codeword(l) {
    std::generate(codeword.begin(), codeword.end(), [this](){ return (rand() % colors) + 1; });
}

void Game::promt() const {
    if (counter == 0)
        cout << "Input " << len << " numbers, each from 1 to " << colors << endl;
    cout << "Attempt #" << counter + 1 << ": ";
}

vector<int> Game::load() const {
    vector<int> v;
    std::copy_n(std::istream_iterator<int>(cin), len, std::back_inserter(v));
    return v;
}

bool Game::is_valid(const vector<int> &v) const {
    return v.size() == len && std::find_if_not(v.begin(), v.end(), [this](int x){ return 0 < x && x <= colors; }) == v.end();
}

Game::TurnResult Game::check(vector<int> test) const {
    std::vector<int> code(codeword);
    std::transform(code.begin(), code.end(), test.begin(), test.begin(), [](int a, int b){ return a == b ? 0 : b; });
    std::transform(code.begin(), code.end(), test.begin(), code.begin(), [](int a, int b){ return b == 0 ? 0 : a; });
    int black = std::count(code.begin(), code.end(), 0);
    int white = std::count_if(test.begin(), test.end(), [&code](int b){
        if (b == 0) return 0;
        auto it = find(code.begin(), code.end(), b);
        if (it == code.end()) return 0;
        *it = 0;
        return 1;
    });
    return TurnResult(black, white);
}

void Game::next_turn() {
    promt();
    vector<int> test = load();
    if (is_valid(test)) {
        ++counter;
        TurnResult result = check(test);
        cout << result.black << " " << result.white << endl;
        if (result.black == len)
            finished = 1;
    } else {
        cout << "Incorrect input, please, try again" << endl;
    }
}

int Game::get_turns_count() const {
    return counter;
}

bool Game::has_finished() const {
    return finished;
}

int main() {
    srand(time(0));

    Game game(2, 15);

    while (!game.has_finished())
        game.next_turn();

    cout << "Finished" << endl << "Attempt: " << game.get_turns_count() << endl;

    return 0;
}