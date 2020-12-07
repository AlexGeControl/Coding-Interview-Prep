#include <iostream>

#include <vector>

// pseudo trie using hashmap:
#include <unordered_map>
#include <unordered_set>

// DFS:
#include <stack>

class Solution {
public:
    /**
     * @param board: A list of lists of character
     * @param words: A list of string
     * @return: return the maximum number
     */
    int wordSearchIII(
        std::vector<std::vector<char>> &board, 
        std::vector<std::string> &words
    ) {
        int max_num_words = 0;

        // init trie:
        std::unordered_map<std::string, std::unordered_set<char>> trie;
        buildTrie(words, trie);

        // search in char matrix:
        if ( 0 < board.size() ) {
            const int N = board.size();
            const int M = board.at(0).size();

            // init state space:
            std::vector<std::vector<StateBoard>> state_space;

            for (int n = 0; n < N; ++n) {
                for (int m = 0; m < M; ++m) {
                    const std::string init_prefix(1, board[n][m]);

                    if ( trie.end() != trie.find(init_prefix) ) {
                        state_space.push_back(
                            getSubBoards(board, trie, N, M, n, m)
                        );
                    }
                }
            }

            const int K = state_space.size();

            if ( 0 < K ) {
                // init state:
                StateBoard init_state;

                // init stack:
                std::stack<StateBoard> stack;
                stack.push(init_state);

                while ( !stack.empty() ) {
                    StateBoard curr_state = stack.top();
                    stack.pop();

                    if ( K == curr_state.depth_ ) {
                        max_num_words = std::max(
                            max_num_words,
                            static_cast<int>(curr_state.used_.size())
                        );
                    } else {
                        for ( const auto &sub_board: state_space.at(curr_state.depth_) ) {
                            if ( !curr_state.isOverlapped(sub_board) ) {
                                StateBoard next_state;

                                next_state.visited_ = curr_state.visited_;
                                next_state.used_ = curr_state.used_;

                                next_state.visited_.insert(sub_board.visited_.begin(), sub_board.visited_.end());
                                next_state.used_.insert(sub_board.used_.begin(), sub_board.used_.end());

                                next_state.depth_ = curr_state.depth_ + 1;

                                stack.push(next_state);
                            }
                        }

                        ++curr_state.depth_;
                        stack.push(curr_state);
                    }
                }
            }
        }

        return max_num_words;
    }
private:
    struct StateWord {
        std::unordered_set<int> visited_;
        std::string prefix_ = "";
        int i_ = 0, j_ = 0;

        StateWord(
            const std::string &prefix, 
            const int i, const int j
        ) 
            : prefix_(prefix), i_(i), j_(j)
        {
            visited_.clear();
        }

        StateWord(
            const std::unordered_set<int> visited,
            const std::string &prefix, 
            const int i, const int j
        ) 
            : visited_(visited), prefix_(prefix), i_(i), j_(j)
        {}
    };

    struct StateBoard {
        std::unordered_set<int> visited_;
        std::unordered_set<std::string> used_;
        int depth_ = 0;

        StateBoard() {
            visited_.clear();
            used_.clear();
        }

        bool isOverlapped(const StateBoard &board) const {
            for (const int id: board.visited_) {
                if ( visited_.end() != visited_.find(id) ) return true;
            }

            for (const std::string &word: board.used_) {
                if ( used_.end() != used_.find(word) ) return true;
            }

            return false;
        }
    };

    static void buildTrie(
        const std::vector<std::string> &words,
        std::unordered_map<std::string, std::unordered_set<char>> &trie
    ) {
        // init:
        trie.clear();

        for (const std::string &word: words) {
            const int N = word.size();

            for (int i = 1; i < N; ++i) {
                const std::string prefix = word.substr(0, i);

                if ( trie.end() == trie.find(prefix) ) {
                    trie[prefix] = std::unordered_set<char>();
                }
                
                trie.at(prefix).insert(word.at(i));
            }

            if ( trie.end() == trie.find(word) ) {
                trie[word] = std::unordered_set<char>();
            }

            trie.at(word).insert('\0');
        }
    }
    
    static int getCharID(
        const int N, const int M,
        const int i, const int j
    ) {
        return M * i + j;
    }

    static std::vector<StateWord> getNeighborPrefixes(
        const std::vector<std::vector<char>> &board,
        const std::unordered_map<std::string, std::unordered_set<char>> &trie,
        const StateWord &state
    ) {
        static std::vector<std::pair<int, int>> deltas = {
            {-1,  0},
            {+1,  0},
            { 0, -1},
            { 0, +1}
        };

        std::vector<StateWord> neighbors;

        const int N = board.size();
        const int M = board.at(0).size();

        for (const auto &delta: deltas) {
            const int n = state.i_ + delta.first;
            const int m = state.j_ + delta.second;
            const int char_id = getCharID(N, M, n, m);
            
            if (
                0 <= n && n < N &&
                0 <= m && m < M &&
                state.visited_.end() == state.visited_.find(char_id) && 
                trie.at(state.prefix_).end() != trie.at(state.prefix_).find(board[n][m])
            ) {
                neighbors.emplace_back( 
                    state.visited_,
                    std::string(state.prefix_ + board[n][m]),
                    n, m
                );
            }
        }

        return neighbors;
    }

    static std::vector<StateBoard> getSubBoards(
        const std::vector<std::vector<char>> &board,
        const std::unordered_map<std::string, std::unordered_set<char>> &trie,
        const int N, const int M, const int n, const int m
    ) {
        std::vector<StateBoard> sub_boards;

        // init state:
        StateWord init_state(
            std::string(1, board[n][m]), 
            n,m
        );
        
        // init queue:
        std::stack<StateWord> stack;
        stack.push(init_state);

        while ( !stack.empty() ) {
            StateWord curr_state = stack.top();
            stack.pop();

            const int char_id = getCharID(N, M, curr_state.i_, curr_state.j_);
            curr_state.visited_.insert(char_id);

            

            if ( 
                trie.at(curr_state.prefix_).end() != trie.at(curr_state.prefix_).find('\0')
            ) {
                StateBoard sub_board;

                sub_board.visited_ = curr_state.visited_;
                sub_board.used_.insert(curr_state.prefix_);

                sub_boards.push_back(sub_board);
            }
            
            for ( 
                const StateWord &next_state: getNeighborPrefixes(
                    board,
                    trie,
                    curr_state
                )
            ) {
                stack.push(next_state);
            }
        }

        return sub_boards;
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

    std::cout << (2 == solution.wordSearchIII(board1, words1)) << std::endl;

    std::vector<std::vector<char>> board2{
        {'a'},
    };
    std::vector<std::string> words2{
        "b"
    };

    std::cout << (0 == solution.wordSearchIII(board2, words2)) << std::endl;

    std::vector<std::vector<char>> board3{
        {'a', 'b', 'c', 'e'},
        {'s', 'f', 'c', 's'},
        {'a', 'd', 'e', 'e'}
    };
    std::vector<std::string> words3{
        "see","se"
    };

    std::cout << (1 == solution.wordSearchIII(board3, words3)) << std::endl;

    std::vector<std::vector<char>> board4{
        {'b'},
        {'a'},
        {'b'},
        {'b'},
        {'a'}
    };
    std::vector<std::string> words4{
        "babbab","b","a","ba"
    };

    std::cout << (3 == solution.wordSearchIII(board4, words4)) << std::endl;

    return EXIT_SUCCESS;
}