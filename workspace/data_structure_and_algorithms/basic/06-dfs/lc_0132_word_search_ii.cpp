#include <vector>

// trie through hashmap:
#include <unordered_map>
#include <unordered_set>

// dfs:
#include <stack>

// test cases:
#include <iostream>

class Solution {
public:
    /**
     * @param board: A list of lists of character
     * @param words: A list of string
     * @return: A list of string
     */
    std::vector<std::string> wordSearchII(
        std::vector<std::vector<char>> &board, 
        std::vector<std::string> &words
    ) {
        std::vector<std::string> dict_words;

        if ( 0 < board.size() && 0 < words.size() ) {
            // init trie:
            std::unordered_map<std::string, std::unordered_set<char>> trie;
            buildTrie(words, trie);

            // init visited:
            std::unordered_set<std::string> used;

            // iterate through char matrix:
            const int N = board.size();
            const int M = board.at(0).size();

            for (int n = 0; n < N; ++n) {
                for (int m = 0; m < M; ++m) {
                    const std::string init_prefix = std::string(1, board[n][m]);

                    if ( trie.end() != trie.find(init_prefix) ) {
                        State init_state(
                            init_prefix,
                            n, m
                        );

                        for (
                            const auto &dict_word: findDictWords(
                                board, trie, init_state
                            )
                        ) {
                            used.insert(dict_word);
                        }
                    }
                }
            }

            dict_words.insert(dict_words.end(), used.begin(), used.end());
        }

        return dict_words;
    }
private:
    struct State {
        std::unordered_set<int> visited_;
        std::string prefix_ = "";
        int n_ = 0, m_ = 0;

        State(
            const std::string &prefix,
            const int n, const int m
        ) 
            : prefix_(prefix), n_(n), m_(m)
        {
            visited_.clear();
        }

        State(
            const std::unordered_set<int> &visited,
            const std::string &prefix,
            const int n, const int m
        ) 
            : visited_(visited), prefix_(prefix), n_(n), m_(m)
        {}
    };

    static void buildTrie(
        const std::vector<std::string> &words,
        std::unordered_map<std::string, std::unordered_set<char>> &trie
    ) {
        // init 
        trie.clear();

        for (const std::string &word: words) {
            const int N = word.size();

            for (int n = 1; n < N; ++n) {
                const std::string prefix = word.substr(0, n);

                if ( trie.end() == trie.find(prefix) ) {
                    trie[prefix] = std::unordered_set<char>();
                }

                trie.at(prefix).insert(word.at(n));
            }

            if ( trie.end() == trie.find(word) ) {
                trie[word] = std::unordered_set<char>();
            }

            trie.at(word).insert('\0');
        }
    }

    static int getId(
        const int N, const int M,
        const int n, const int m
    ) {
        return M * n + m;
    }

    static std::vector<State> getNeighbors(
        const std::vector<std::vector<char>> &board,
        const std::unordered_map<std::string, std::unordered_set<char>> &trie,
        const State &curr_state
    ) {
        static std::vector<std::pair<int, int>> deltas {
            {-1,  0},
            {+1,  0},
            { 0, -1},
            { 0, +1}
        };

        std::vector<State> neighbors;

        const int N = board.size();
        const int M = board.at(0).size();

        for (const auto &delta: deltas) {
            const int next_n = curr_state.n_ + delta.first;
            const int next_m = curr_state.m_ + delta.second;
            const int char_id = getId(N, M, next_n, next_m);

            if (
                0 <= next_n && next_n < N &&
                0 <= next_m && next_m < M &&
                curr_state.visited_.end() == curr_state.visited_.find(char_id) &&
                trie.at(curr_state.prefix_).end() != trie.at(curr_state.prefix_).find(board[next_n][next_m])
            ) {
                neighbors.emplace_back(
                    curr_state.visited_,
                    curr_state.prefix_ + board[next_n][next_m],
                    next_n, next_m
                );
            }
        }

        return neighbors;
    }

    static std::vector<std::string> findDictWords(
        const std::vector<std::vector<char>> &board,
        const std::unordered_map<std::string, std::unordered_set<char>> &trie,
        const State &init_state
    ) {
        const int N = board.size();
        const int M = board.at(0).size();

        // init result:
        std::vector<std::string> dict_words;

        // init stack:
        std::stack<State> stack;
        stack.push(init_state);

        while ( !stack.empty() ) {
            State curr_state = stack.top();
            stack.pop();

            // mark as visited:
            const int char_id = getId(N, M, curr_state.n_, curr_state.m_);
            curr_state.visited_.insert(char_id);

            if ( trie.at(curr_state.prefix_).end() != trie.at(curr_state.prefix_).find('\0') ) {
                dict_words.push_back(curr_state.prefix_);
            }
            
            for (
                const State &next_state: getNeighbors(
                    board, trie, curr_state
                )
            ) {
                stack.push(next_state);
            }
        }

        return dict_words;
    }
};

int main() {
    Solution solution;

    std::vector<std::vector<char>> board1{
        {'d', 'o', 'a', 'f'},
        {'a', 'g', 'a', 'i'},
        {'d', 'c', 'a', 'n'}
    };
    std::vector<std::string> words1{
        "dog", "dad", "dgdg", "can", "again"
    };

    for (const auto &word: solution.wordSearchII(board1, words1) ) {
        std::cout << word << std::endl;
    }

    std::vector<std::vector<char>> board2{
        {'a', 'b', 'c', 'e'},
        {'s', 'f', 'c', 's'},
        {'a', 'd', 'e', 'e'}
    };
    std::vector<std::string> words2{
        "see","se"
    };

    for (const auto &word: solution.wordSearchII(board2, words2) ) {
        std::cout << word << std::endl;
    }

    return EXIT_SUCCESS;
}