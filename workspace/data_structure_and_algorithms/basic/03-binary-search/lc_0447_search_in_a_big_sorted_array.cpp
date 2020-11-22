#include <cstdlib>
#include <vector>

class ArrayReader {
public:
    ArrayReader(const std::vector<int> &nums) : nums_(nums) {}
    int get(int i) { return nums_.at(i); }
private:
    std::vector<int> nums_;
};

class Solution {
public:
    static const int NOT_FOUND = -1;
    
    /**
     * @param reader: An instance of ArrayReader.
     * @param target: An integer
     * @return: An integer which is the first index of target.
     */
    int searchBigSortedArray(ArrayReader *reader, const int target) {
        // first, identify the range that contains target:
        int lo = 0, hi = 1;
        
        if ( target < reader->get(lo) ) return NOT_FOUND;
        
        while (reader->get(hi) < target) {
            hi = hi << 1;
        }
        
        // then find the min. index of target:
        int min_index = NOT_FOUND;
        while ( lo <= hi ) {
            int mi = ( lo + hi ) >> 1;
            
            int mi_value = reader->get(mi);
            if ( target <= mi_value ) {
                if ( target == mi_value ) {
                    min_index = mi;
                }
                hi = mi - 1;
            } else {
                lo = mi + 1;
            }
        }
        
        return min_index;
    }
};

int main() {
    return EXIT_SUCCESS;
}