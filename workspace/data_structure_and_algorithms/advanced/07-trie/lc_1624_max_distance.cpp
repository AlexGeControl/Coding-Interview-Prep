#include <iostream>

#include <vector>

#include <unordered_map>

#include <stack>

#include <deque>

class Trie {
public:
    Trie() : size_(0) {}

    ~Trie() {
        std::deque<Node *> queue;
        for ( const auto &r: root_.children ) queue.push_back(r.second);

        while ( !queue.empty() ) {
            Node *curr = queue.front();
            queue.pop_front();

            delete curr;

            for ( const auto &r: curr->children ) queue.push_back(r.second);
        }
    }

    int insert(const std::string &word) {
        const int N = word.size();

        int max_distance = 0;

        if ( 0 < N ) {
            Node *curr = &root_;

            for (int i = 0; i < N; ++i) {
                const char c = word.at(i);
                const char c_comp = getComplementaryChar(c);

                curr->height = std::max(curr->height, N - i);
                if ( curr->children.end() == curr->children.find(c) ) {
                    curr->children[c] = new Node(c, N - i - 1);
                }

                // update max. distance when there is a branch:
                if ( curr->children.end() != curr->children.find(c_comp) ) {
                    const int distance = curr->children.at(c_comp)->height + 1 + N - i;
                    
                    max_distance = std::max(max_distance, distance);
                }

                // update max. distance when there is a sub-string:
                if ( NUL != curr->id ) {
                    const int distance = N - i;

                    max_distance = std::max(max_distance, distance);
                }

                curr = curr->children.at(c);
            }

            if ( NUL == curr->id ) {
                curr->id = size_;
                ++size_;

                // update max. distance when current string is a sub-string:
                if ( !curr->children.empty() ) {
                    const int distance = curr->height + 1 - N;

                    max_distance = std::max(max_distance, distance);
                }
            }
        }

        return max_distance;
    }

private:
    static const int NUL = -1;

    struct Node {
        char c;
        int id;
        int height;
        std::unordered_map<char, Node *> children;

        Node() : id(NUL), height(0) { children.clear(); }
        Node( const char ch, const int h ) : c(ch), id(NUL), height(h) { children.clear(); }
    };

    Node root_;
    int size_;

    static char getComplementaryChar(const char c) {
        return '0' + (1 - (c - '0'));
    }
};

#include <vector>

#include <string>

class Solution {
public:
    /**
     * @param s: the list of binary string
     * @return: the max distance
     */
    int getAns(const std::vector<std::string> &bss) {
        int max_distance = 0;
        
        if ( 0 < bss.size() ) {
            Trie trie;

            for (size_t i = 0; i < bss.size(); ++i) {
                const int distance = trie.insert(bss.at(i));
                max_distance = std::max(max_distance, distance);
            }
        }

        return max_distance;
    }
};

int main() {
    Solution solution;

    std::vector<std::string> bss1{
        "011000","0111010","01101010"
    };

    std::cout << (9 == solution.getAns(bss1)) << std::endl;

    std::vector<std::string> bss2 {
        "01","10","0","1","1001010"
    };
    std::cout << (9 == solution.getAns(bss2)) << std::endl;

    std::vector<std::string> bss3 {
        "01","0","0101010"
    };
    std::cout << (6 == solution.getAns(bss3)) << std::endl;

    std::vector<std::string> bss4 {
        "10","1"
    };
    std::cout << (1 == solution.getAns(bss4)) << std::endl;

    std::vector<std::string> bss5 {
        "0","1","101","10101","10001"
    };
    std::cout << (6 == solution.getAns(bss5)) << std::endl;

    return EXIT_SUCCESS;
}