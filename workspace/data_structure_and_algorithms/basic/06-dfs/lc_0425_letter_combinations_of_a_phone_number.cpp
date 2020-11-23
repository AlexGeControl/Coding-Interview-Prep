#include <iostream>

#include <string>

#include <vector>

#include <unordered_map>

class Solution {
public:
    /**
     * @param digits: A digital string
     * @return: all posible letter combinations
     */
    std::vector<std::string> letterCombinations(std::string &digits) {
        static const std::unordered_map<char, std::string> ALPHABET {
            {'2', "abc"}, 
            {'3', "def"}, 
            {'4', "ghi"},
            {'5', "jkl"},
            {'6', "mno"},
            {'7', "pqrs"},
            {'8', "tuv"},
            {'9', "wxyz"}, 
        };

        const int N = digits.length();

        if ( 0 < N ) {
            std::vector<std::string> buff;
            std::vector<std::string> curr{ "" };
            
            std::vector<std::string> *buff_ptr = &buff, *curr_ptr = &curr;
            
            
            for (int i = 0; i < N; ++i) {
                swap(buff_ptr, curr_ptr);
                curr_ptr->clear();

                const std::string &chars = ALPHABET.at(digits.at(i));
                
                const int M = chars.length();
                for (const std::string &word: *buff_ptr) {
                    for (int j = 0; j < M; ++j) {
                        std::string new_word = word + chars.substr(j, 1);
                        curr_ptr->push_back( new_word );
                    }
                }
            }
            
            return *curr_ptr;
        }

        return std::vector<std::string>();
    }
private:
    void swap(std::vector<std::string> *&x, std::vector<std::string> *&y) {
        std::vector<std::string> *temp_ptr = nullptr;

        temp_ptr = x;
        x = y;
        y = temp_ptr;
    }
};

int main() {
    Solution solution;

    std::string digits1 = "23";

    for (const std::string &word: solution.letterCombinations(digits1) ) {
        std::cout << word << std::endl;
    }

    return EXIT_SUCCESS;
}