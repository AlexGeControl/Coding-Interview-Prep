#include <iostream>

#include <unordered_map>

#include <deque>

class LRUCache {
public:
    static const int NOT_FOUND = -1;
    
    /*
    * @param capacity: An integer
    */LRUCache(int capacity) : N_(capacity) {
        n_ = 0;
        time_ = 0;
        value_index_.clear();
        access_trace_.clear();
    }

    /*
     * @param key: An integer
     * @return: An integer
     */
    int get(int key) {
        if ( value_index_.end() == value_index_.find(key) ) return NOT_FOUND;
        
        int value = value_index_.at(key).value;
        
        value_index_.at(key).stamp = ++time_;

        // update access time tracker:
        KeyStamped key_stamped(key, time_);
        access_trace_.push_back(key_stamped);

        return value;
    }

    /*
     * @param key: An integer
     * @param value: An integer
     * @return: nothing
     */
    void set(int key, int value) {
        ++time_;
        ValueStamped value_stamped(value, time_);
        
        if ( value_index_.end() == value_index_.find(key) ) {
            if ( n_ < N_ ) {
                ++n_;
            } else {
                while ( N_ == value_index_.size() ) {
                    const KeyStamped &key_stamped = access_trace_.front();

                    const int &key = key_stamped.key;
                    const int &stamp = key_stamped.stamp;
                    
                    if ( value_index_.end() != value_index_.find(key) && stamp == value_index_.at(key).stamp ) {
                        value_index_.erase(key);
                        access_trace_.pop_front();
                        break;
                    }
                    
                    access_trace_.pop_front();
                }
            }
            
            value_index_[key] = value_stamped;
        } else {
            value_index_.at(key) = value_stamped;
        }
        
        // update access time tracker:
        KeyStamped key_stamped(key, time_);
        access_trace_.push_back(key_stamped);
    }
private:
    struct KeyStamped {
        int key;
        int stamp;
        
        KeyStamped() : key(NOT_FOUND), stamp(NOT_FOUND) {}
        KeyStamped(const int k, const int s) : key(k), stamp(s) {}
    };
    struct ValueStamped {
        int value;
        int stamp;

        ValueStamped() : value(NOT_FOUND), stamp(NOT_FOUND) {}
        ValueStamped(const int v, const int s) : value(v), stamp(s) {}
    };

    int time_;
    
    const int N_;
    int n_;
    
    std::unordered_map<int, ValueStamped> value_index_;
    std::deque<KeyStamped> access_trace_;
};

int main() {
    LRUCache lru_cache(1);
    lru_cache.set(2, 1);
    lru_cache.get(2);
    lru_cache.set(3, 2);
    lru_cache.get(2);
    lru_cache.get(3);

    std::cout << "Hello, LRU Cache!" << std::endl;
    return EXIT_SUCCESS;
}