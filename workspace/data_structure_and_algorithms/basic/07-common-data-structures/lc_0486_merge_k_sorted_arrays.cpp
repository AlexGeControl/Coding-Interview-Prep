#include <cstdlib>
#include <iostream>

#include <vector>

#include <queue>

#include <unordered_map>

#include <algorithm>

class Solution {
public:
    /**
     * @param arrays: k sorted integer arrays
     * @return: a sorted array
     */
    std::vector<int> mergekSortedArrays(std::vector<std::vector<int>> &arrays) {
        std::vector<int> result;

        std::priority_queue<int, std::vector<int>, std::less<int>> max_pq;
        std::unordered_map<int, std::vector<int>> array_index;

        const int N = arrays.size();
        for (int i = 0; i < N; ++i) {
            if ( !arrays.at(i).empty() ) {
                const int curr_val = arrays.at(i).back();
                arrays.at(i).pop_back();

                max_pq.push(curr_val);

                if ( array_index.end() == array_index.find(curr_val) ) array_index[curr_val] = std::vector<int>();
                array_index.at(curr_val).push_back(i);
            }
        }

        while ( !max_pq.empty() ) {
            const int curr_val = max_pq.top();
            max_pq.pop();

            result.push_back(curr_val);

            std::vector<int> &indices = array_index.at(curr_val);
            const int idx = indices.back();
            indices.pop_back();

            if ( !arrays.at(idx).empty() ) {
                const int next_val = arrays.at(idx).back();
                arrays.at(idx).pop_back();

                max_pq.push( next_val );
                
                if ( array_index.end() == array_index.find(next_val) ) array_index[next_val] = std::vector<int>();
                array_index.at(next_val).push_back(idx);
            }
        }

        std::reverse(result.begin(), result.end());

        return result;
    }
};

int main() {
    Solution solution;

    std::vector<std::vector<int>> arrays1{
        {1, 3, 5, 7},
        {2, 4, 6},
        {0, 8, 9, 10, 11}
    };

    for (const int num: solution.mergekSortedArrays(arrays1)) {
        std::cout << num << " ";
    }
    std::cout << std::endl << std::endl;

    return EXIT_SUCCESS;
}