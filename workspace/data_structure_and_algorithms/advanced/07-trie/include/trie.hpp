#ifndef TRIE_HPP_
#define TRIE_HPP_

#include <unordered_map>

#include <deque>

#include <string>

#include <vector>

#include <stack>

class Trie {
public:
    static const int NOT_FOUND = -1;

    Trie() : size_(0) {}

    ~Trie() {
        // delete node in reverse BFS order:
        std::deque<Node *> deque;
        deque.push_back(&root_);

        while ( !deque.empty() ) {
            const Node *curr = deque.front();

            for (const auto &r: curr->children) {
                deque.push_back(r.second);
            }

            deque.pop_front();
        }

        for (std::deque<Node *>::reverse_iterator i = deque.rbegin(); deque.rend() != i; ++i) {
            delete *i;
        }

        size_ = 0;
    }

    /*
     * @param word: a word
     * @return: corresponding word ID as int
     */
    int insert(const std::string &word) {
        const int N = word.size();

        Node *curr = &root_;
        for (int i = 0; i < N; ++i) {
            const char c = word.at(i);

            // update height:
            curr->height = std::max(curr->height, N - i);

            if ( curr->children.end() == curr->children.find(c) ) {
                curr->children[c] = new Node(c, N - 1 - i);
            }

            curr = curr->children.at(c);
        }

        if ( NUL == curr->id ) {
            curr->id = size_;
            ++size_;
        }

        return curr->id;
    }

    /*
     * @param word: A string
     * @return: true if the word is in the trie false otherwise.
     */
    bool search(const std::string &word) {
        Node *curr = &root_;
        for (const char &c: word) {
            if ( curr->children.end() == curr->children.find(c) ) return false;

            curr = curr->children.at(c);
        }

        return NUL != curr->id;
    }

    /*
     * @param word: A string
     * @return: if the word is in the trie.
     */
    int getID(const std::string &word) {
        Node *curr = &root_;
        for (const char &c: word) {
            if ( curr->children.end() == curr->children.find(c) ) return NOT_FOUND;

            curr = curr->children.at(c);
        }

        return (NUL == curr->id ? NOT_FOUND : curr->id);
    }

    /*
     * @param prefix: A string
     * @return: if there is any word in the trie that starts with the given prefix.
     */
    bool startsWith(const std::string &prefix) {
        Node *curr = &root_;
        for (const char &c: prefix) {
            if ( curr->children.end() == curr->children.find(c) ) return false;

            curr = curr->children.at(c);
        }

        return true;
    }

    std::vector<std::string> getWordsStartsWith(const std::string &prefix) {
        std::vector<std::string> result;

        // sync with input prefix:
        Node *curr = &root_;
        for (const char &c: prefix) curr = curr->children.at(c);

        // generate all the words using DFS:
        std::stack<State> stack;
        stack.emplace( curr, prefix );

        while ( !stack.empty() ) {
            State curr_state = stack.top();
            stack.pop();

            if ( NUL != curr_state.root->id ) result.push_back(curr_state.word);
            else {
                for ( const auto &r: curr_state.root->children ) {
                    const char c = r.first;
                    const Node *node = r.second;

                    stack.emplace(
                        node, 
                        curr_state.word + c
                    );
                }
            }
        }

        return result;
    }

private:
    static const int NUL = -1;

    struct Node {
        // a. value:
        char c;
        // b. meta data:
        int id;
        int height;
        // c. connectivity:
        std::unordered_map<char, Node*> children;

        Node() : id(NUL), height(0) { children.clear(); }
        Node(const char ch, const int h): c(ch), id(NUL), height(h) {
            children.clear();
        }
    };

    struct State {
        const Node *root;
        std::string word;

        State() : root(nullptr), word("") {}
        State(const Node *node, const std::string &prefix) : root(node), word(prefix) {}
    };

    Node root_;
    int size_;
};

#endif // TRIE_HPP_