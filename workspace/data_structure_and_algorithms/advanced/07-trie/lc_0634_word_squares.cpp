#include <iostream>

#include "include/trie.hpp"

#include <vector>

#include <string>

#include <stack>

class Solution {
public:
    /*
     * @param words: a set of words without duplicates
     * @return: all word squares
     */
    std::vector<std::vector<std::string>> wordSquares(std::vector<std::string> &words) {
        std::vector<std::vector<std::string>> word_squares;
        
        if ( 0 < words.size() ) {
            // first, init trie to generate available prefixes:
            Trie trie;
            for (const std::string &word: words) { trie.insert(word); }

            // Trie accelerated DFS:
            // a. init stack:
            std::stack<State> stack;
            for ( const std::string &word: words ) {
                const int D = word.size();

                int d = 0;
                while ( d < D && trie.startsWith(word.substr(d, 1)) ) { ++d; }

                if ( D == d ) {
                    State init_state(D);

                    init_state.words.push_back(word);

                    stack.push(init_state);
                }
            }

            // b. generate all the solutions:
            while ( !stack.empty() ) {
                State curr_state = stack.top();
                stack.pop();

                // parse:
                const int D = curr_state.D;
                const std::vector<std::string> &words = curr_state.words;

                // generate prefix:
                const int idx = words.size();
                std::string prefix = "";
                for ( const std::string &word: curr_state.words ) {
                    prefix += word.at(idx);
                }

                // generate candidate:
                for (const std::string &candidate: trie.getWordsStartsWith(prefix) ) {
                    if ( D - 1 == idx ) {
                        std::vector<std::string> word_square(words);

                        word_square.push_back(candidate);

                        word_squares.push_back(word_square);
                    } else {
                        const int new_idx = idx + 1;

                        std::string new_prefix = "";
                        for ( const std::string &word: curr_state.words ) {
                            new_prefix += word.at(new_idx);
                        }
                        new_prefix += candidate.at(new_idx);

                        if ( trie.startsWith(new_prefix) ) {
                            State new_state(D);

                            new_state.words = words;
                            new_state.words.push_back(candidate);

                            stack.push(new_state);
                        }
                    }
                }
            }
        }

        return word_squares;
     }
private:
    struct State {
        int D;

        std::vector<std::string> words;

        State() { words.clear(); }
        State(const int DIM) : D(DIM) { words.clear(); }
    }; 
};

int main() {
    Solution solution;

    std::vector<std::string> words1 {
        "area","lead","wall","lady","ball"
    };

    for ( const auto &word_square: solution.wordSquares(words1) ) {
        for ( const auto &word: word_square ) {
            std::cout << word << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Hello, Word Square!" << std::endl;

    return EXIT_SUCCESS;
}