#include <iostream>

#include <vector>

class Solution {
public:
    /**
     * @param L: Given n pieces of wood with length L[i]
     * @param k: An integer
     * @return: The maximum length of the small pieces
     */
    int woodCut(const std::vector<int> &L, int k) {
        // first, find max wood length, O(N):
        int max_length = 0;
        for (const int &l: L) {
            max_length = std::max(max_length, l);
        }

        // then perform binary search on wood length, O(log(max_length) * N):
        int cut_length = 0;

        int min_length = 1;
        while ( min_length <= max_length) {
            int64_t total_length = static_cast<int64_t>(min_length) + static_cast<int64_t>(max_length);
            int mid_length = static_cast<int>(total_length >> 1);

            int cut_count = getCutCount(L, mid_length);

            if ( k <= cut_count ) {
                cut_length = mid_length;
                min_length = mid_length + 1;
            } else {
                max_length = mid_length - 1;
            }
        }

        return cut_length;
    }
private:
    int getCutCount(const std::vector<int> &L, const int length) {
        int cut_count = 0;

        for (const int &l: L) {
            cut_count += l / length;
        }

        return cut_count;
    }
};

int main() {
    Solution solution;

    std::vector<int> L1 {232, 124, 456};
    int k1 = 7;

    std::cout << (114 == solution.woodCut(L1, k1)) << std::endl << std::endl;

    std::vector<int> L2 {1, 2, 3};
    int k2 = 7;

    std::cout << (0 == solution.woodCut(L2, k2)) << std::endl << std::endl;

    std::vector<int> L3{2147483644,2147483645,2147483646,2147483647};
    int k3 = 4;

    std::cout << (2147483644 == solution.woodCut(L3, k3)) << std::endl << std::endl;

    return EXIT_SUCCESS;
}