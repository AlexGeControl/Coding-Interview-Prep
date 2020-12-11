#ifndef TRIE_HPP_
#define TRIE_HPP_

#include <unordered_map>

#include <deque>

#include <string>

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
     * @return: nothing
     */
    int insert(const std::string &word) {
        Node *curr = &root_;
        for (size_t i = 0; i < word.size(); ++i) {
            const char c = word.at(i);

            if ( curr->children.end() == curr->children.find(c) ) {
                curr->children[c] = new Node(c);
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
     * @return: if the word is in the trie.
     */
    bool search(const std::string &word) {
        Node *curr = &root_;
        for (size_t i = 0; i < word.size(); ++i) {
            const char c = word.at(i);

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
        for (size_t i = 0; i < word.size(); ++i) {
            const char c = word.at(i);

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
        for (size_t i = 0; i < prefix.size(); ++i) {
            const char c = prefix.at(i);

            if ( curr->children.end() == curr->children.find(c) ) return false;

            curr = curr->children.at(c);
        }

        return true;
    }

private:
    static const int NUL = -1;
    struct Node {
        char c;
        int id;
        std::unordered_map<char, Node*> children;

        Node() {}

        Node(const char ch): c(ch), id(NUL) {
            children.clear();
        }
    };

    Node root_;
    int size_;
};

#endif // TRIE_HPP_