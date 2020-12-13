#include <iostream>

#include <cctype>

#include <unordered_map>

#include <deque>

#include <vector>

#include <string>

class Trie {
public:
    Trie() : size_(0) {}

    /*
     * @brief: free all allocated nodes
     */
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

    /*
     * @brief: insert word into trie
     * @param: word, new target word
     * @return: id of the newly created word
     */
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

    /*
     * @brief: find all the beginning words of given sentence
     * @param: sentence, target sentence
     * @return: beginning words of sentence
     */
    std::vector<std::string> find(const std::string &sentence) const {
        const int N = sentence.size();

        std::vector<std::string> result;

        const Node *node = &root_;
        for ( int n = 0; n < N; ++n ) {
            const char c = std::tolower(sentence.at(n));

            if ( node->children.end() == node->children.find(c) ) break;

            node = node->children.at(c);

            if ( NUL != node->id ) result.push_back(sentence.substr(0, n + 1));
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
     * @param s: A string
     * @param dict: A set of words.
     * @return: All possible sentences.
     */
    std::vector<std::string> wordBreak(
        const std::string &sentence, 
        const std::unordered_set<std::string> &dict
    ) {
        std::vector<std::string> sentences;

        if ( 0 < sentence.size() && 0 < dict.size() ) {
            // encode dict as trie:
            Trie trie;
            for ( const std::string &word: dict ) {
                trie.insert(word);
            }

            // create sentence cache:
            SentenceCache sentence_cache;
            sentence_cache.get(sentence, trie, sentences);
        }

        return sentences;
    }
private:
    class SentenceCache {
    public:
        SentenceCache() { invalid_set_.clear(); cache_.clear(); }

        bool get(const std::string &string, const Trie &trie, std::vector<std::string> &sentences) {
            sentences.clear();

            if ( invalid_set_.end() != invalid_set_.find(string) ) {    
                return false;
            }

            if ( cache_.end() == cache_.find(string) ) {
                for ( const std::string &word: trie.find(string) ) {
                    if ( string.size() == word.size() ) sentences.push_back(word);
                    else {
                        const std::string sub_string = string.substr(word.size(), string.size() - word.size());
                        std::vector<std::string> sub_sentences;
                        if ( get(sub_string, trie, sub_sentences) ) {
                            for ( const std::string &sub_sentence: sub_sentences ) {
                                sentences.push_back( word + " " + sub_sentence ); 
                            }
                        }
                    }
                }

                if ( 0 == sentences.size() ) {
                    invalid_set_.insert(string);
                    return false;
                }

                cache_[string] = sentences;
            } else {
                sentences = cache_.at(string);
            }

            return true;
        }

    private:
        std::unordered_set<std::string> invalid_set_;
        std::unordered_map<std::string, std::vector<std::string>> cache_;
    };
};

int main() {
    Solution solution;

    std::string sentence1("lintcode");
    std::unordered_set<std::string> dict1 {
        "de","ding","co","code","lint"
    };
    for ( const std::string &sentence: solution.wordBreak(sentence1, dict1) ) {
        std::cout << "\t" << sentence << std::endl;
    }

    return EXIT_SUCCESS;
}