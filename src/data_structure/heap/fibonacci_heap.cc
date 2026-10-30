#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <map>
#include <algorithm>

using namespace std;

struct FibNode {
    int id;
    long long key;
    int degree = 0;
    bool marked = false;
    FibNode* parent = nullptr;
    FibNode* child = nullptr;
    FibNode* left = nullptr;
    FibNode* right = nullptr;

    FibNode(int i, long long k) : id(i), key(k) {
        left = right = this;
    }
};

class FibonacciHeap {
    FibNode* min_node = nullptr;
    size_t total_nodes = 0;
    map<int, FibNode*> node_map;

    void link_roots(FibNode* y, FibNode* x) {
        // Remove y from root list
        y->left->right = y->right;
        y->right->left = y->left;
        // Make y a child of x
        y->parent = x;
        if (!x->child) {
            x->child = y;
            y->left = y->right = y;
        } else {
            y->right = x->child;
            y->left = x->child->left;
            x->child->left->right = y;
            x->child->left = y;
        }
        ++x->degree;
        y->marked = false;
    }

    void consolidate() {
        size_t max_deg = 50;
        vector<FibNode*> A(max_deg, nullptr);

        vector<FibNode*> root_list;
        if (min_node) {
            FibNode* cur = min_node;
            do {
                root_list.push_back(cur);
                cur = cur->right;
            } while (cur != min_node);
        }

        for (FibNode* w : root_list) {
            FibNode* x = w;
            size_t d = static_cast<size_t>(x->degree);
            while (d < max_deg && A[d]) {
                FibNode* y = A[d];
                if (x->key > y->key) {
                    swap(x, y);
                }
                link_roots(y, x);
                A[d] = nullptr;
                ++d;
            }
            if (d < max_deg) A[d] = x;
        }

        min_node = nullptr;
        for (size_t i = 0; i < max_deg; ++i) {
            if (A[i]) {
                if (!min_node) {
                    min_node = A[i];
                    min_node->left = min_node->right = min_node;
                } else {
                    A[i]->right = min_node;
                    A[i]->left = min_node->left;
                    min_node->left->right = A[i];
                    min_node->left = A[i];
                    if (A[i]->key < min_node->key) {
                        min_node = A[i];
                    }
                }
            }
        }
    }

    void cut(FibNode* x, FibNode* y) {
        // Remove x from y's children
        if (x->right == x) {
            y->child = nullptr;
        } else {
            x->left->right = x->right;
            x->right->left = x->left;
            if (y->child == x) y->child = x->right;
        }
        --y->degree;
        // Add x to root list
        x->right = min_node;
        x->left = min_node->left;
        min_node->left->right = x;
        min_node->left = x;
        x->parent = nullptr;
        x->marked = false;
    }

    void cascading_cut(FibNode* y) {
        FibNode* z = y->parent;
        if (z) {
            if (!y->marked) {
                y->marked = true;
            } else {
                cut(y, z);
                cascading_cut(z);
            }
        }
    }

public:
    FibonacciHeap() = default;
    FibonacciHeap(const FibonacciHeap&) = delete;
    FibonacciHeap& operator=(const FibonacciHeap&) = delete;

    ~FibonacciHeap() {
        for (auto& kv : node_map) delete kv.second;
    }

    void insert(int id, long long key) {
        FibNode* node = new FibNode(id, key);
        node_map[id] = node;
        if (!min_node) {
            min_node = node;
        } else {
            node->right = min_node;
            node->left = min_node->left;
            min_node->left->right = node;
            min_node->left = node;
            if (node->key < min_node->key) {
                min_node = node;
            }
        }
        ++total_nodes;
    }

    bool get_min(int& out_id, long long& out_key) const {
        if (!min_node) return false;
        out_id = min_node->id;
        out_key = min_node->key;
        return true;
    }

    bool extract_min(int& out_id, long long& out_key) {
        FibNode* z = min_node;
        if (!z) return false;

        out_id = z->id;
        out_key = z->key;

        // Add children of z to root list
        if (z->child) {
            vector<FibNode*> children;
            FibNode* cur = z->child;
            do {
                children.push_back(cur);
                cur = cur->right;
            } while (cur != z->child);

            for (FibNode* ch : children) {
                ch->right = min_node;
                ch->left = min_node->left;
                min_node->left->right = ch;
                min_node->left = ch;
                ch->parent = nullptr;
            }
        }

        // Remove z from root list
        z->left->right = z->right;
        z->right->left = z->left;

        if (z == z->right) {
            min_node = nullptr;
        } else {
            min_node = z->right;
            consolidate();
        }

        --total_nodes;
        node_map.erase(z->id);
        delete z;
        return true;
    }

    void decrease_key(int id, long long new_key) {
        auto it = node_map.find(id);
        if (it == node_map.end()) return;
        FibNode* x = it->second;
        if (new_key > x->key) return;
        x->key = new_key;
        FibNode* y = x->parent;
        if (y && x->key < y->key) {
            cut(x, y);
            cascading_cut(y);
        }
        if (x->key < min_node->key) {
            min_node = x;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q = 0;
    if (!(cin >> q)) return 0;

    FibonacciHeap heap;
    for (int i = 0; i < q; ++i) {
        string op;
        cin >> op;
        if (op == "INSERT") {
            int id = 0;
            long long val = 0;
            cin >> id >> val;
            heap.insert(id, val);
        } else if (op == "MIN") {
            int id = 0;
            long long val = 0;
            if (heap.get_min(id, val)) {
                cout << id << " " << val << "\n";
            } else {
                cout << "EMPTY\n";
            }
        } else if (op == "EXTRACT_MIN") {
            int id = 0;
            long long val = 0;
            if (heap.extract_min(id, val)) {
                cout << id << " " << val << "\n";
            } else {
                cout << "EMPTY\n";
            }
        } else if (op == "DECREASE_KEY") {
            int id = 0;
            long long val = 0;
            cin >> id >> val;
            heap.decrease_key(id, val);
        }
    }

    return 0;
}
