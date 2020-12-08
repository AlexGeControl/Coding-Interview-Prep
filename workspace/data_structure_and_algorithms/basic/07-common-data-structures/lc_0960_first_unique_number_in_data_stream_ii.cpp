#include <cstdlib>
#include <unordered_set>
#include <unordered_map>

class DataStream {
public:
    static const int NOT_FOUND = -1;

    DataStream(){
        repeated_.clear();
        unique.head_ = unique.tail_ = new Node();
        index_.clear();
    }
    
    /**
     * @param num: next number in stream
     * @return: nothing
     */
    void add(int num) {
        if ( repeated_.end() != repeated_.find(num) ) return;

        if ( index_.end() == index_.find(num) ) {
            // update unique num list:
            unique.tail_->next = new Node(num);
            unique.tail_->next->prev = unique.tail_;
            unique.tail_ = unique.tail_->next;
            // update index:
            index_[num] = unique.tail_;
        } else {
            // remove from unique num list:
            struct Node *to_be_deleted = index_.at(num);
            if ( to_be_deleted == unique.tail_ ) {
                unique.tail_ = unique.tail_->prev;
            }
            to_be_deleted->prev->next = to_be_deleted->next;
            if ( nullptr != to_be_deleted->next ) {
                to_be_deleted->next->prev = to_be_deleted->prev;
            }
            delete to_be_deleted;
            // remove from index:
            index_.erase(num);
            // add to repeated set:
            repeated_.insert(num);
        }
    }

    /**
     * @return: the first unique number in stream
     */
    int firstUnique() {
        if ( nullptr != unique.head_->next ) {
            return unique.head_->next->val;
        }

        return NOT_FOUND;
    }
private:
    struct Node {
        int val;

        struct Node *prev = nullptr;
        struct Node *next = nullptr;

        Node() {}
        
        Node(const int val) {
            this->val = val;

            this->prev = nullptr;
            this->next = nullptr;
        }
    };

    std::unordered_set<int> repeated_;
    struct {
        Node *head_ = nullptr;
        Node *tail_ = nullptr;
    } unique;
    std::unordered_map<int, struct Node *> index_;
};

int main() {
    DataStream ds;

    return EXIT_SUCCESS;
}