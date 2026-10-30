#include <algorithm>
#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

namespace {

struct Node {
    int64_t lo;
    int64_t hi;
    int64_t id;
    int64_t max_hi;
    int height;
    Node* left;
    Node* right;

    Node(int64_t l, int64_t h, int64_t i)
        : lo(l), hi(h), id(i), max_hi(h), height(1), left(nullptr), right(nullptr) {}
};

int cmp_key(int64_t lo1, int64_t hi1, int64_t id1, int64_t lo2, int64_t hi2, int64_t id2) {
    if (lo1 != lo2) return (lo1 < lo2) ? -1 : 1;
    if (hi1 != hi2) return (hi1 < hi2) ? -1 : 1;
    if (id1 != id2) return (id1 < id2) ? -1 : 1;
    return 0;
}

class IntervalTree {
    Node* root_ = nullptr;
    std::unordered_map<int64_t, std::pair<int64_t, int64_t>> by_id_;

    static int node_height(const Node* u) {
        return u ? u->height : 0;
    }

    static void pull(Node* u) {
        if (!u) return;
        int hl = node_height(u->left);
        int hr = node_height(u->right);
        u->height = 1 + (hl > hr ? hl : hr);
        u->max_hi = u->hi;
        if (u->left && u->left->max_hi > u->max_hi) {
            u->max_hi = u->left->max_hi;
        }
        if (u->right && u->right->max_hi > u->max_hi) {
            u->max_hi = u->right->max_hi;
        }
    }

    static Node* rotate_left(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        pull(x);
        pull(y);
        return y;
    }

    static Node* rotate_right(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        x->right = y;
        pull(y);
        pull(x);
        return x;
    }

    static Node* balance(Node* u) {
        if (!u) return nullptr;
        pull(u);
        int bf = node_height(u->left) - node_height(u->right);
        if (bf > 1) {
            if (node_height(u->left->left) < node_height(u->left->right)) {
                u->left = rotate_left(u->left);
            }
            return rotate_right(u);
        }
        if (bf < -1) {
            if (node_height(u->right->right) < node_height(u->right->left)) {
                u->right = rotate_right(u->right);
            }
            return rotate_left(u);
        }
        return u;
    }

    static Node* insert_node(Node* u, int64_t lo, int64_t hi, int64_t id) {
        if (!u) return new Node(lo, hi, id);
        int c = cmp_key(lo, hi, id, u->lo, u->hi, u->id);
        if (c < 0) {
            u->left = insert_node(u->left, lo, hi, id);
        } else if (c > 0) {
            u->right = insert_node(u->right, lo, hi, id);
        } else {
            return u;
        }
        return balance(u);
    }

    static Node* remove_node(Node* u, int64_t lo, int64_t hi, int64_t id) {
        if (!u) return nullptr;
        int c = cmp_key(lo, hi, id, u->lo, u->hi, u->id);
        if (c < 0) {
            u->left = remove_node(u->left, lo, hi, id);
        } else if (c > 0) {
            u->right = remove_node(u->right, lo, hi, id);
        } else {
            if (!u->left || !u->right) {
                Node* child = u->left ? u->left : u->right;
                delete u;
                return child;
            }
            Node* succ = u->right;
            while (succ->left) succ = succ->left;
            u->lo = succ->lo;
            u->hi = succ->hi;
            u->id = succ->id;
            u->right = remove_node(u->right, succ->lo, succ->hi, succ->id);
        }
        return balance(u);
    }

    static void query_node(const Node* u, int64_t qlo, int64_t qhi, std::vector<int64_t>& out) {
        if (!u || u->max_hi < qlo) return;
        query_node(u->left, qlo, qhi, out);
        if (u->lo <= qhi && qlo <= u->hi) {
            out.push_back(u->id);
        }
        if (u->lo <= qhi) {
            query_node(u->right, qlo, qhi, out);
        }
    }

    static void clear_nodes(Node* u) {
        if (!u) return;
        clear_nodes(u->left);
        clear_nodes(u->right);
        delete u;
    }

public:
    IntervalTree() = default;
    ~IntervalTree() {
        clear_nodes(root_);
    }

    IntervalTree(const IntervalTree&) = delete;
    IntervalTree& operator=(const IntervalTree&) = delete;

    void insert(int64_t lo, int64_t hi, int64_t id) {
        auto it = by_id_.find(id);
        if (it != by_id_.end()) {
            root_ = remove_node(root_, it->second.first, it->second.second, id);
        }
        by_id_[id] = std::make_pair(lo, hi);
        root_ = insert_node(root_, lo, hi, id);
    }

    void remove(int64_t id) {
        auto it = by_id_.find(id);
        if (it == by_id_.end()) return;
        int64_t lo = it->second.first;
        int64_t hi = it->second.second;
        by_id_.erase(it);
        root_ = remove_node(root_, lo, hi, id);
    }

    std::vector<int64_t> query(int64_t qlo, int64_t qhi) const {
        std::vector<int64_t> out;
        query_node(root_, qlo, qhi, out);
        std::sort(out.begin(), out.end());
        return out;
    }
};

}  // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q = 0;
    if (!(std::cin >> q)) return 0;

    IntervalTree tree;
    for (int i = 0; i < q; ++i) {
        int type = 0;
        if (!(std::cin >> type)) break;
        if (type == 1) {
            int64_t lo = 0;
            int64_t hi = 0;
            int64_t id = 0;
            std::cin >> lo >> hi >> id;
            tree.insert(lo, hi, id);
        } else if (type == 2) {
            int64_t id = 0;
            std::cin >> id;
            tree.remove(id);
        } else if (type == 3) {
            int64_t lo = 0;
            int64_t hi = 0;
            std::cin >> lo >> hi;
            std::vector<int64_t> res = tree.query(lo, hi);
            if (res.empty()) {
                std::cout << "NONE\n";
            } else {
                for (size_t j = 0; j < res.size(); ++j) {
                    if (j > 0) std::cout << ' ';
                    std::cout << res[j];
                }
                std::cout << '\n';
            }
        }
    }
    return 0;
}
