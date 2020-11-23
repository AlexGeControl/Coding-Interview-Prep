#include <iostream>

#include <string>

#include <vector>

#include <unordered_set>
#include <unordered_map>

#include <stack>

class Solution {
public:
    static const int ALPHABET_SIZE = 26;

    struct State {
        std::vector<int> char_count;
        std::string word;
        State() {
            char_count.resize(ALPHABET_SIZE);
            std::fill(char_count.begin(), char_count.end(), 0);

            word = "";
        }
    };

    /**
     * @param str: A string
     * @return: all permutations
     */
    std::vector<std::string> stringPermutation2(std::string &str) {
        std::vector<std::string> result;

        const size_t N = str.length();
        if ( 0 < N ) {
            // init state:
            State init_state;
            for (size_t i = 0; i < N; ++i) {
                ++init_state.char_count[str.at(i) - 'a'];
            }

            // init stack for DFS:
            std::stack<State> recursion_stack;
            recursion_stack.push(init_state);

            while ( !recursion_stack.empty() ) {
                State curr_state = recursion_stack.top();
                recursion_stack.pop();

                if ( curr_state.word.size() < N ) {
                    for (int i = 0; i < ALPHABET_SIZE; ++i) {
                        if ( 0 < curr_state.char_count[i] ) {
                            if ( N - 1 == curr_state.word.size() ) {
                                result.push_back( curr_state.word + static_cast<char>('a' + i) );
                            } else {
                                State new_state = curr_state;

                                --new_state.char_count[i];
                                new_state.word += static_cast<char>('a' + i);

                                recursion_stack.push(new_state);
                            }
                        }
                    }
                }
            }
        } else {
            result.push_back(str);
        }

        return result;
    }
};

int main() {
    Solution solution;

    std::string word1 = "aabb";

    for (const std::string &w: solution.stringPermutation2(word1)) {
        std::cout << w << std::endl;
    }

    std::string word2 = "abcgabcdabc";
    for (const std::string &w: solution.stringPermutation2(word2)) {
        std::cout << w << std::endl;
    }

    return EXIT_SUCCESS;
}