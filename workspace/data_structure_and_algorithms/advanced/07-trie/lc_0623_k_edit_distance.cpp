#include <cstdlib>

#include <iostream>

#include <unordered_map>

#include <deque>

#include <vector>

class Trie {
public:
    Trie() : size_(0) {}
    ~Trie() {
        std::deque<Node *> queue;
        
        for ( const auto &r: root_.children ) queue.push_back(r.second);

        while ( !queue.empty() ) {
            Node *curr = queue.front();
            queue.pop_front();

            for (const auto &r: curr->children) {
                queue.push_back( r.second );
            }

            delete curr;
        }
    }

    int insert(
        const std::string &word,
        const std::string &target
    ) {
        const int N = word.size();
        const int M = target.size();

        if ( 0 == N ) { return M; }

        // compute edit distance using Dynamic Programming
        // and save intermediate result into Trie:

        // init DP table
        std::vector<std::vector<int>> dp_table(
            2, 
            std::vector<int>(M + 1, 0)
        );
        for (int m = 0; m <= M; ++m) {
            dp_table[0][m] = m;
        }

        // init Trie:
        Node *node = &root_;

        for (int n = 0; n < N; ++n) {
            // set indices for rolling DP table:
            const int prev = ( n + 0 ) % 2;
            const int curr = ( n + 1 ) % 2;

            // update trie:
            const char c = word.at(n);

            // update height:
            node->height = std::max(node->height, N - n);

            // if not exist, insert new node:
            if ( node->children.end() == node->children.find(c) ) {
                node->children[c] = new Node(c, N - 1 - n);

                // set id:
                node->children.at(c)->id = size_;
                ++size_;

                // compute DP table for sub-string:
                dp_table[curr][0] = n + 1;
                for (int m = 1; m <= M; ++m) {
                    if ( word.at(n) == target.at(m - 1) ) {
                        dp_table[curr][m] = std::min(
                            // do nothing
                            dp_table[prev][m - 1],
                            std::min(
                                // add:
                                dp_table[curr][m - 1] + 1,
                                // delete:
                                dp_table[prev][m] + 1
                            )
                        );
                    } else {
                        dp_table[curr][m] = std::min(
                            // replace:
                            dp_table[prev][m - 1] + 1,
                            std::min(
                                // add:
                                dp_table[curr][m - 1] + 1,
                                // delete:
                                dp_table[prev][m] + 1
                            )
                        );
                    }
                }

                // set data:
                node->children.at(c)->data = dp_table[curr];
            } else {
                dp_table[curr] = node->children.at(c)->data;
            }

            node = node->children.at(c);
        }

        return dp_table[N % 2][M];
    }
private:
    static const int NUL = -1;

    struct Node {
        // a. metadata:
        char c;
        int id;
        int height;
        std::unordered_map<char, Node *> children;
        // b. data load:
        std::vector<int> data;

        Node() : id(NUL), height(0) { children.clear(); data.clear(); }
        Node(const char ch, const int h) : c(ch), id(NUL), height(h) { children.clear(); data.clear(); }
    };

    Node root_;
    int size_;
};

#include <vector>

#include <string>

class Solution {
public:
    /**
     * @param words: a set of stirngs
     * @param target: a target string
     * @param k: An integer
     * @return: output all the strings that meet the requirements
     */
    std::vector<std::string> kDistance(
        const std::vector<std::string> &words, 
        const std::string &target, 
        const int k
    ) {
        std::vector<std::string> result;

        // compute trie accelerated edit distance:
        Trie trie;
        for (const std::string &word: words) {
            int edit_distance = trie.insert(word, target);

            if ( edit_distance <= k ) result.push_back(word);
        }

        return result;
    }
};

int main() {
    Solution solution;

    std::vector<std::string> words1 {
        "abc","abd","abcd","adc"
    };
    std::string target1("ac");
    int k1 = 1;

    for (const std::string &candidate: solution.kDistance(words1, target1, k1)) {
        std::cout << "\t" << candidate << std::endl;
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}