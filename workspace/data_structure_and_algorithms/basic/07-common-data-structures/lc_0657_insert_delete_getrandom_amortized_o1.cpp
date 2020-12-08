#include <iostream>

#include <limits>

#include <vector>
#include <unordered_map>

#include <stdlib.h>
/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet obj = new RandomizedSet();
 * bool param = obj.insert(val);
 * bool param = obj.remove(val);
 * int param = obj.getRandom();
 */

class RandomizedSet {
public:
    RandomizedSet() {
        // init data structure:
        N_ = 0;
        data_.clear();
        index_.clear();
    }

    /*
     * @param val: a value to the set
     * @return: true if the set did not already contain the specified element or false
     */
    bool insert(int val) {
        if ( index_.end() == index_.find(val) ) {
            // update data:
            data_.push_back(val);
            // update index:
            index_[val] = data_.size() - 1;
            // update size:
            ++N_;
            return true;
        } 

        return false;
    }

    /*
     * @param val: a value from the set
     * @return: true if the set contained the specified element or false
     */
    bool remove(int val) {
        if ( index_.end() != index_.find(val) ) {
            // mark value with TOMBSTONE:
            data_.at(index_.at(val)) = TOMBSTONE;
            // remove value index:
            index_.erase(val);
            // update size:
            --N_;
            // if the load rate is too low, compress, amortized complexity O(1):
            double load_ratio = N_ / static_cast<double>(data_.size());
            if ( load_ratio < LOAD_RATIO_THRESH) {
                compressData();
            }
            return true;
        }
        return false;
    }

    /*
     * @return: Get a random element from the set
     */
    int getRandom() {
        int value;

        do {
            value = data_.at( rand() % data_.size() );
        } while ( TOMBSTONE == value);

        return value;
    }
private:
    static const int TOMBSTONE = std::numeric_limits<int>::min();
    static const double LOAD_RATIO_THRESH;

    void swap(std::vector<int> &data, int i, int j) {
        int value = data.at(i);
        data.at(i) = data.at(j);
        data.at(j) = value;
    }

    void compressData(void) {
        if ( 0 == N_ ) {
            data_.clear();
            index_.clear();
        } else {
            const int N = data_.size();

            int data_index = 0, tombstone_index = 0;
            
            while ( data_index < N_ && tombstone_index < N ) {
                while ( data_index < N_ && TOMBSTONE != data_.at(data_index) ) {
                    ++data_index;
                }

                if ( N_ == data_index ) break;

                tombstone_index = data_index + 1;
                while ( tombstone_index < N && TOMBSTONE == data_.at(tombstone_index) ) {
                    ++tombstone_index;
                }

                if ( N == tombstone_index ) break;

                swap(data_, data_index, tombstone_index);
                // update value index:
                index_.at(data_.at(data_index)) = data_index;

                ++data_index;
                ++tombstone_index;
            }

            data_.resize(N_);
        }
    };

    // size:
    int N_;
    // data container:
    std::vector<int> data_;
    // value index:
    std::unordered_map<int, int> index_;
};

const double RandomizedSet::LOAD_RATIO_THRESH = 0.50;

int main() {
    RandomizedSet randomized_set;

    randomized_set.insert(1);
    randomized_set.insert(2);
    randomized_set.insert(3);
    randomized_set.insert(4);
    randomized_set.insert(5);
    randomized_set.insert(6);
    randomized_set.insert(7);

    randomized_set.remove(1);
    randomized_set.remove(2);
    randomized_set.remove(3);
    randomized_set.remove(4);

    randomized_set.insert(1);
    randomized_set.insert(2);
    randomized_set.insert(3);
    randomized_set.insert(4);
    randomized_set.insert(5);
    randomized_set.insert(6);
    randomized_set.insert(7);

    randomized_set.remove(4);
    randomized_set.remove(5);
    randomized_set.remove(6);
    randomized_set.remove(7);

    randomized_set.insert(1);
    randomized_set.insert(2);
    randomized_set.insert(3);
    randomized_set.insert(4);
    randomized_set.insert(5);
    randomized_set.insert(6);
    randomized_set.insert(7);

    randomized_set.remove(2);
    randomized_set.remove(4);
    randomized_set.remove(6);
    randomized_set.remove(7);

    return EXIT_SUCCESS;
}