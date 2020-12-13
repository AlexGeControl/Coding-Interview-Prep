
#include <iostream>

#include <cctype>

#include <unordered_map>

#include <deque>

#include <vector>

#include <string>

class Trie {
public:
    Trie() : size_(0) {}

    ~Trie() {
        std::deque<Node *> queue;

        for ( const auto &r: root_.children ) {
            queue.push_back(r.second);
        }

        while ( !queue.empty() ) {
            Node *node = queue.front();

            for ( const auto &r: node->children ) {
                queue.push_back(r.second);
            }

            delete node;

            queue.pop_front();
        }
    }

    int insert(const std::string &word) {
        const int N = word.size();

        Node *node = &root_;

        for ( int n = 0; n < N; ++n ) {
            const char c = std::tolower(word.at(n));
            
            node->height = std::max(node->height, N - n);

            if ( node->children.end() == node->children.find(c) ) {
                node->children[c] = new Node(c, N - 1 - n);
            }

            node = node->children.at(c);
        }

        if ( NUL == node->id ) {
            node->id = size_;
            ++size_;
        }

        return node->id;
    }

    std::vector<std::string> find(const std::string &word) const {
        const int N = word.size();

        std::vector<std::string> result;

        const Node *node = &root_;
        for ( int n = 0; n < N; ++n ) {
            const char c = std::tolower(word.at(n));

            if ( node->children.end() == node->children.find(c) ) break;

            node = node->children.at(c);

            if ( NUL != node->id ) result.push_back(word.substr(0, n + 1));
        }

        return result;
    }
private:
    static const int NUL = -1;

    struct Node {
        char c;
        int id;
        int height;
        std::unordered_map<char, Node *> children;

        Node(): id(NUL), height(0) { children.clear(); }
        Node(const char ch, const int h) : c(ch), id(NUL), height(h) { children.clear(); } 
    };

    Node root_;
    int size_;
};


#include <string>

#include <unordered_set>

#include <unordered_map>

class Solution {
public:
    /*
     * @param : A string
     * @param : A set of word
     * @return: the number of possible sentences.
     */
    int wordBreak3(
        const std::string &s, 
        const std::unordered_set<std::string> &dict
    ) {
        int num_sentences = 0;

        if ( 0 < s.size() && 0 < dict.size() ) {
            const int N = s.size();

            // convert word dict to trie:
            Trie trie;
            for ( const std::string &word: dict ) {
                trie.insert(word);
            }

            // init sentence counter with cache:
            SentenceCounter sentence_counter;
            for ( const std::string &word: trie.find(s) ) {
                const std::string sub_s = s.substr(word.size(), N - word.size());
                num_sentences += sentence_counter.get( sub_s, trie );
            }
        }

        return num_sentences;
    }
private:
    class SentenceCounter {
    public:
        SentenceCounter() { count_.clear(); }

        int get(const std::string &s, const Trie &trie) {
            if ( count_.end() == count_.find(s) ) {
                if ( 0 == s.size() ) count_[s] = 0;
                else {
                    int count = 0;
                    for ( const std::string &word: trie.find(s) ) {
                        if ( word.size() == s.size() ) count += 1;
                        else {
                            const std::string sub_s = s.substr(word.size(), s.size() - word.size());
                            count += get(sub_s, trie);
                        }
                    }
                    count_[s] = count;
                }
            }

            return count_.at(s);
        }
    private:
        std::unordered_map<std::string, int> count_;
    };
};

int main() {
    Solution solution;
    
    std::string s1("CatMat");
    std::unordered_set<std::string> dict1{
        "Cat", "Mat", "Ca", "tM", "at", "C", "Dog", "og", "Do"
    };
    std::cout << solution.wordBreak3(s1, dict1) << std::endl;

    return EXIT_SUCCESS;
}