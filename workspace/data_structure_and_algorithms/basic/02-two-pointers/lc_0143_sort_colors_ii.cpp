#include <iostream>

#include <vector>

class Solution {
public:
    /**
     * @param colors: A list of integer
     * @param k: An integer
     * @return: nothing
     */
    void sortColors2(std::vector<int> &colors, int k) {
        const int N = colors.size();

        // perform partition logk times:
        if ( 1 < N ) {
            doSortColor(colors, 0, N - 1, 1, k);
        }
    }
private:
    void doSortColor(std::vector<int> &colors, const int lo, const int hi, const int lo_color, const int hi_color) {
        if ( lo < hi && lo_color < hi_color) {
            if ( hi_color == lo_color + 1 ) {
                partitionByColor(colors, lo, hi, hi_color);
            } else {
                int mi_color = (lo_color + hi_color) >> 1;

                int mi = partitionByColor(colors, lo, hi, mi_color);

                doSortColor(colors, lo, mi - 1, lo_color, mi_color - 1);
                doSortColor(colors, mi, hi, mi_color, hi_color);
            }
        }
    }

    int partitionByColor(std::vector<int> &colors, const int lo, const int hi, const int color) {
        const int N = hi - lo + 1;

        int partition_index = lo;

        if ( 1 < N ) {
            int left = lo - 1, right = hi + 1;

            while ( left < right ) {
                while ( colors.at(++left) < color ) {
                    if ( hi == left ) return hi + 1;
                }

                while ( colors.at(--right) >= color ) {
                    if ( lo == right ) return lo;
                }

                if ( left >= right ) {
                    partition_index = right + 1;
                    break;
                }

                swap(colors, left, right);
            }
        }

        return partition_index;
    }

    inline void swap(std::vector<int> &colors, int i, int j) {
        int color = colors.at(i);
        colors.at(i) = colors.at(j);
        colors.at(j) = color;
    }
};

int main() {
    Solution solution;

    std::vector<int> colors1 {3,2,2,1,4};
    int k1 = 4;

    solution.sortColors2(colors1, k1);
    for (const int &color: colors1) {
        std::cout << color << " ";
    }
    std::cout << std::endl << std::endl;

    std::vector<int> colors2 {2,1,1,2,2};
    int k2 = 2;

    solution.sortColors2(colors2, k2);
    for (const int &color: colors2) {
        std::cout << color << " ";
    }
    std::cout << std::endl << std::endl;

    std::vector<int> colors3 {3,2,3,3,4,3,3,2,4,4,1,2,1,1,1,3,4,3,4,2};
    int k3 = 4;
    solution.sortColors2(colors3, k3);
    for (const int &color: colors3) {
        std::cout << color << " ";
    }
    std::cout << std::endl << std::endl;

    return EXIT_SUCCESS;
}