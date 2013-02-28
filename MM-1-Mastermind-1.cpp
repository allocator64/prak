#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>
#include <cassert>
#include <sstream>

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
    TurnResult check(const vector<int> &test) const;
    bool is_valid(const vector<int> &v) const;

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

Game::Game(int l=4, int c=6) :len(l), colors(c), counter(), finished(), codeword() {
    for (int i = 0; i < len; ++i)
        codeword.push_back(rand() % colors);
}

void Game::promt() const {
    if (counter == 0)
        cout << "Input " << len << " numbers, each from 1 to " << colors << endl;
    cout << "Attempt #" << counter + 1 << ": ";
}

vector<int> Game::load() const {
    string s;
    std::getline(std::cin, s);
    stringstream ss(s);
    vector<int> v;
    if (colors < 10) {
        char ch;
        while (ss >> ch)
            v.push_back(ch - '1');
    } else {
        int k;
        while (ss >> k)
            v.push_back(k - 1);
    }
    return v;
}

bool Game::is_valid(const vector<int> &v) const {
    if (v.size() != len)
        return 0;
    for (vector<int>::const_iterator it = v.begin(); it != v.end(); ++it)
        if (!(0 <= *it && *it < colors))
            return 0;
    return 1;
}

Game::TurnResult Game::check(const vector<int> &test) const {
    vector<int> code_used(len, 0), test_used(len, 0);
    int black = 0;
    int white = 0;
    for (int i = 0; i < len; ++i)
        if (test[i] == codeword[i]) {
            test_used[i] = code_used[i] = 1;
            black++;
        }
    for (int i = 0; i < len; ++i)
        if (!code_used[i])
            for (int j = 0; j < len; ++j)
                if (test[j] == codeword[i]) {
                    code_used[i] = test_used[j] = 1;
                    white++;
                    break;
                }
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