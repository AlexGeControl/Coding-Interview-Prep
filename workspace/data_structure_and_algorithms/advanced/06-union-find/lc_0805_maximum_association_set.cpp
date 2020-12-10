#include <cstdlib>
#include <iostream>

#include "include/union_find.hpp"

#include <vector>

#include <string>

#include <unordered_map>

class Solution {
public:
    /**
     * @param ListA: The relation between ListB's books
     * @param ListB: The relation between ListA's books
     * @return: The answer
     */
    std::vector<std::string> maximumAssociationSet(
        const std::vector<std::string> &ListA, 
        const std::vector<std::string> &ListB
    ) {
        std::vector<std::string> max_association_set;

        if ( 0 < ListA.size() && 0 < ListB.size() ) {
            // longest common sub list:
            const int N = std::min(
                static_cast<int>(ListA.size()),
                static_cast<int>(ListB.size())
            );

            // first, generate book name encoding & build UnionFind:
            std::unordered_map<std::string, int> book_id;
            UnionFind<int> union_find;
            for (int i = 0; i < N; ++i) {
                // update book name encoding:
                const std::string &bookname_A = ListA.at(i);
                const std::string &bookname_B = ListB.at(i);

                if ( book_id.end() == book_id.find(bookname_A) ) {
                    book_id[bookname_A] = static_cast<int>(book_id.size());
                }
                if ( book_id.end() == book_id.find(bookname_B) ) {
                    book_id[bookname_B] = static_cast<int>(book_id.size());
                }

                // update UnionFind:
                const int book_id_A = book_id.at(bookname_A);
                const int book_id_B = book_id.at(bookname_B);

                if ( !union_find.IsInside(book_id_A) ) union_find.Insert(book_id_A);
                if ( !union_find.IsInside(book_id_B) ) union_find.Insert(book_id_B);

                union_find.Union(book_id_A, book_id_B);
            }

            // find maximum connected component using UnionFind:
            int max_component_id;
            int max_component_size;
            union_find.GetMaxComponent(max_component_id, max_component_size);

            max_association_set.clear();
            std::cout << "Size of max. association set: " << max_component_size << std::endl;
            for (const auto &record: book_id) {
                const std::string &bookname = record.first;
                const int id = record.second;

                if ( max_component_id == union_find.Find(id) ) max_association_set.push_back(bookname);
            }
        }

        return max_association_set;
    }
};

int main() {
    Solution solution;

    const std::vector<std::string> ListA1 {
        "abc","abc","abc"
    };
    
    const std::vector<std::string> ListB1 { 
        "bcd","acd","def"
    };

    for (const std::string &bookname: solution.maximumAssociationSet(ListA1, ListB1)) {
        std::cout << bookname << " ";
    }
    std::cout << std::endl << std::endl;
    
    return EXIT_SUCCESS;
}