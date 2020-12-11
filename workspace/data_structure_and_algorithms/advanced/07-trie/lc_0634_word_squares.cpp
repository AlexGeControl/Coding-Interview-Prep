#include <iostream>

#include <vector>

#include <string>

class Solution {
public:
    /*
     * @param words: a set of words without duplicates
     * @return: all word squares
     */
    std::vector<std::vector<std::string>> wordSquares(std::vector<std::string> &words) {
        std::vector<std::vector<std::string>> word_squares;

        return word_squares;
     }
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