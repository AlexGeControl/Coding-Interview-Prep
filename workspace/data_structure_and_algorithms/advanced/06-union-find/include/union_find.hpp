#ifndef UNION_FIND_HPP_
#define UNION_FIND_HPP_

#include <unordered_map>

#include <stack>

class UnionFind {
public:
    UnionFind() {
        uf_tree_.clear();
        components_ = 0;
    }

    bool IsInside(const int id) const { return uf_tree_.end() != uf_tree_.find(id); }

    int GetNumComponents(void) const { return components_; }

    void Insert(const int id) {
        if ( uf_tree_.end() == uf_tree_.find(id) ) {                
            uf_tree_[id] = Node(id);
            ++components_;
        }
    }

    int Find(const int id) {
        int root_id = id;
        std::stack<int> path;
        while ( uf_tree_.at(root_id).parent_id_ != root_id ) {
            path.push(root_id);
            root_id = uf_tree_.at(root_id).parent_id_;
        }

        // compress:
        while ( !path.empty() ) {
            int curr_id = path.top();
            path.pop();
            uf_tree_.at(curr_id).parent_id_ = root_id;
        }

        return root_id;
    }

    void Union(const int x, const int y) {
        int root_id_x = Find(x);
        int root_id_y = Find(y);

        if ( root_id_x == root_id_y ) return;

        if ( uf_tree_.at(root_id_x).size_ > uf_tree_.at(root_id_y).size_ ) {
            uf_tree_.at(root_id_x).size_ += uf_tree_.at(root_id_y).size_;
            uf_tree_.at(root_id_y).parent_id_ = root_id_x;
        } else {
            uf_tree_.at(root_id_y).size_ += uf_tree_.at(root_id_x).size_;
            uf_tree_.at(root_id_x).parent_id_ = root_id_y;
        }

        --components_;
    }

private:
    struct Node {
        int parent_id_;
        int size_;

        Node() {}
        Node(const int id) : parent_id_(id), size_(1) {}
    };

    std::unordered_map<int, Node> uf_tree_;
    int components_;
};

#endif // UNION_FIND_HPP_