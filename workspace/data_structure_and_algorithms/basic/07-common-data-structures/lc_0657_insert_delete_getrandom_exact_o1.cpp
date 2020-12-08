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
        data_.clear();
        index_.clear();
    }

    /*
     * @param val: a value to the set
     * @return: true if the set did not already contain the specified element or false
     */
    bool insert(int val) {
        if ( index_.end() == index_.find(val) ) {
            // a. add to index:
            const int idx = static_cast<int>(data_.size());
            index_[val] = idx;
            // b. add to data:
            data_.push_back(val);

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
            // a. remove from data:
            const int idx = index_.at(val);

            if ( 
                1 < data_.size() && 
                static_cast<size_t>(idx) != data_.size() - 1 
            ) {
                moveToLast(idx);
                index_.at(data_.at(idx)) = idx;
            }
            
            data_.pop_back();
            
            // b. remove from index:
            index_.erase(val);
            
            return true;
        }

        return false;
    }

    /*
     * @return: Get a random element from the set
     */
    int getRandom(void) {
        const int N = data_.size();
        const int idx = rand() % N;

        return data_.at(idx);
    }
private:
    // a. use vector for data storage:
    std::vector<int> data_;
    // b. use hashmap for data indexing:
    std::unordered_map<int, int> index_;

    void moveToLast(const int idx) {
        int val = data_.back();
        data_.back() = data_.at(idx);
        data_.at(idx) = val;
    }
};

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