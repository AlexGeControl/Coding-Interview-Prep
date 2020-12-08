#include <iostream>

#include <unordered_map>

#include <deque>

class LRUCache {
public:
    static const int NOT_FOUND = -1;
    
    /*
    * @param capacity: An integer
    */LRUCache(int capacity) : N_(capacity) {
        time_ = 0;
        value_index_.clear();
        access_trace_.clear();
    }

    /*
     * @param key: An integer
     * @return: An integer
     */
    int get(int key) {
        // update timer:
        ++time_;

        if ( value_index_.end() == value_index_.find(key) ) return LRUCache::NOT_FOUND;

        // update access trace:
        access_trace_.emplace_back( time_, key );

        // fetch value:
        value_index_.at(key).timestamp_ = time_;
        int value = value_index_.at(key).value_;

        return value;
    }

    /*
     * @param key: An integer
     * @param value: An integer
     * @return: nothing
     */
    void set(int key, int value) {
        // update timer:
        ++time_;

        // update access trace:
        access_trace_.emplace_back( time_, key );

        if ( 
            value_index_.end() != value_index_.find(key)
        ) {
            TimestampedValue &stamped_value = value_index_.at(key);

            stamped_value.timestamp_ = time_;
            stamped_value.value_ = value;
        } else {
            while ( 
                value_index_.size() == N_ &&
                !access_trace_.empty()
            ) {
                const TimestampedKey &stamped_key = access_trace_.front();

                if (
                    value_index_.end() != value_index_.find(stamped_key.key_) &&
                    value_index_.at(stamped_key.key_).timestamp_ == stamped_key.timestamp_
                ) {
                    value_index_.erase(stamped_key.key_);
                    break;
                }

                access_trace_.pop_front();
            }

            value_index_[key] = TimestampedValue(time_, value);
        }
    }
private:
    struct TimestampedKey {
        int timestamp_;
        int key_;

        TimestampedKey() {}

        TimestampedKey(
            const int timestamp, const int key
        ) : timestamp_(timestamp), key_(key) {}
    };
    struct TimestampedValue {
        int timestamp_;
        int value_;

        TimestampedValue() {}

        TimestampedValue(
            const int timestamp, const int value
        ) : timestamp_(timestamp), value_(value) {}
    };

    // time:
    int time_;

    // capacity:
    const size_t N_;

    // a. value_index for latest value lookup:
    std::unordered_map<int, TimestampedValue> value_index_;

    // b. access_trace for LRU element remove:
    std::deque<TimestampedKey> access_trace_;
};

int main() {
    LRUCache lru_cache1(1);
    lru_cache1.set(2, 1);
    std::cout << lru_cache1.get(2) << std::endl;
    lru_cache1.set(3, 2);
    std::cout << lru_cache1.get(2) << std::endl;
    std::cout << lru_cache1.get(3) << std::endl;
    std::cout << std::endl;

    LRUCache lru_cache2(2);
    lru_cache2.set(2, 1);
    lru_cache2.set(1, 1);
    std::cout << lru_cache2.get(2) << std::endl;
    lru_cache2.set(4, 1);
    std::cout << lru_cache2.get(1) << std::endl;
    std::cout << lru_cache2.get(2) << std::endl;

    std::cout << "Hello, LRU Cache!" << std::endl;
    return EXIT_SUCCESS;
}