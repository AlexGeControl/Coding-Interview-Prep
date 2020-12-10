#ifndef UNION_FIND_HPP_
#define UNION_FIND_HPP_

#include <unordered_map>

#include <unordered_set>

#include <stack>

template <typename T>
class UnionFind {
public:
    UnionFind() {
        uf_tree_.clear();
        components_ = 0;
    }

    bool IsInside(const T &id) const { return uf_tree_.end() != uf_tree_.find(id); }

    int GetNumComponents(void) const { return components_; }

    int GetSize(const T &id) const { return uf_tree_.at(id).size_; }

    void GetMaxComponent(T &id, int &size) const {
        id = max_component_.id_;
        size = max_component_.size_;
    }

    void Insert(const T &id) {
        if ( uf_tree_.end() == uf_tree_.find(id) ) {                
            uf_tree_[id] = Node(id);
            ++components_;
        }
    }

    T Find(const T &id) {
        T root_id = id;
        std::stack<T> path;
        while ( uf_tree_.at(root_id).parent_id_ != root_id ) {
            path.push(root_id);
            root_id = uf_tree_.at(root_id).parent_id_;
        }

        // compress:
        while ( !path.empty() ) {
            T curr_id = path.top();
            path.pop();
            uf_tree_.at(curr_id).parent_id_ = root_id;
        }

        return root_id;
    }

    void Union(const T &x, const T &y) {
        T root_id_x = Find(x);
        T root_id_y = Find(y);

        if ( root_id_x == root_id_y ) return;

        if ( uf_tree_.at(root_id_x).size_ >= uf_tree_.at(root_id_y).size_ ) {
            uf_tree_.at(root_id_x).size_ += uf_tree_.at(root_id_y).size_;
            uf_tree_.at(root_id_y).parent_id_ = root_id_x;

            if ( max_component_.size_ < uf_tree_.at(root_id_x).size_ ) {
                max_component_.size_ = uf_tree_.at(root_id_x).size_;
                max_component_.id_ = root_id_x;
            }
        } else {
            uf_tree_.at(root_id_y).size_ += uf_tree_.at(root_id_x).size_;
            uf_tree_.at(root_id_x).parent_id_ = root_id_y;

            if ( max_component_.size_ < uf_tree_.at(root_id_y).size_ ) {
                max_component_.size_ = uf_tree_.at(root_id_y).size_;
                max_component_.id_ = root_id_y;
            }
        }

        --components_;
    }

private:
    struct Node {
        T parent_id_;
        int size_;

        Node() {}
        Node(const T &id) : parent_id_(id), size_(1) {}
    };

    struct MaxComponent {
        T id_;
        int size_ = -1;

        MaxComponent() : size_(-1) {}
    };

    std::unordered_map<T, Node> uf_tree_;
    int components_;
    MaxComponent max_component_;
};

#endif // UNION_FIND_HPP_