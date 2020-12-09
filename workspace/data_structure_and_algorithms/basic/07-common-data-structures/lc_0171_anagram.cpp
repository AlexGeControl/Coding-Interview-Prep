#include <cstdlib>
#include <string>
#include <vector>

#include <map>
#include <unordered_map>

#include <iostream>

class Solution {
public:
    /**
     * @param strs: A list of strings
     * @return: A list of strings
     */
    std::vector<std::string> anagrams(std::vector<std::string> &strs) {
        std::vector<std::string> result;
        
        std::unordered_map<std::string, std::vector<std::string>> str_group;
        for (const std::string &str: strs) {
            std::string signature = getSignature(str);

            if ( str_group.end() == str_group.find(signature) ) {
                str_group[signature] = std::vector<std::string>();
            } else {
                if ( 1 == str_group.at(signature).size() ) result.push_back(str_group.at(signature).back());
                result.push_back(str);
            }

            str_group.at(signature).push_back(str);
        }

        return result;
    }
private:
    std::string getSignature(const std::string str) {
        static std::map<char, int> char_counts;

        const size_t N = str.size();

        char_counts.clear();
        for (size_t i = 0; i < N; ++i) {
            if ( char_counts.end() == char_counts.find(str.at(i)) ) {
                char_counts[str.at(i)] = 0;
            }

            ++char_counts.at(str.at(i));
        }

        std::string signature = "";
        for (const auto &char_count: char_counts) {
            signature += std::string(char_count.second, char_count.first);
        }

        return signature;
    }
};

int main() {
    Solution solution;

    std::vector<std::string> strings1 {
        "lint", "intl", "inlt", "code"
    };

    std::cout << "Anagrams, test case 01: " << std::endl;
    for (const std::string &str: solution.anagrams(strings1)) {
        std::cout << str << " " << std::endl;
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}