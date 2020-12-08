#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class RandomizedCollection {
public:
    static const int NOT_FOUND = -1;

    /** Initialize your data structure here. */
    RandomizedCollection() {
        data_.clear();
        index_.clear();
    }
    
    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        bool new_val = false;

        if ( index_.end() == index_.find(val) ) {
            new_val = true;
            index_[val] = std::unordered_set<int>();
        }

        // update index:
        const int idx = data_.size();
        index_.at(val).insert(idx);

        // update data:
        data_.push_back(val);

        return new_val;
    }
    
    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        if ( index_.end() != index_.find(val) ) {
            // update index:
            std::unordered_set<int> &indices = index_.at(val);

            const int curr_idx = *indices.begin();
            if ( 1 < data_.size() ) {
                const int last_idx = static_cast<int>(data_.size() - 1);

                if ( curr_idx != last_idx ) {
                    index_.at(data_.back()).insert(curr_idx);
                    index_.at(data_.back()).erase(last_idx);

                    moveToLast(curr_idx);
                }
            }

            indices.erase(curr_idx);
            if ( indices.empty() ) index_.erase(val);

            // update data:
            data_.pop_back();

            return true;
        }

        return false;
    }
    
    /** Get a random element from the collection. */
    int getRandom() {
        if ( 0 < data_.size() ) {
            const int N = data_.size();
            const int idx = rand() % N;

            return data_.at(idx);
        }

        return NOT_FOUND;
    }
private:
    std::vector<int> data_;
    std::unordered_map<int, std::unordered_set<int>> index_;

    void moveToLast(const int idx) {
        int val = data_.back();
        data_.back() = data_.at(idx);
        data_.at(idx) = val;
    }
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection obj = new RandomizedCollection();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */
int main() {
    RandomizedCollection rc1;
    
    return EXIT_SUCCESS;
}