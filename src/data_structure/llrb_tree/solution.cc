#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

// Sedgewick Ch 3.3: Left-Leaning Red-Black BST (2-3 tree isomorphism).
class LLRBTree {
    static const bool RED = true;
    static const bool BLACK = false;

    struct Node {
        int64_t key;
        int64_t val;
        bool color;
        int sz;
        int left;
        int right;
    };

    vector<Node> nodes;
    int root_idx = -1;

    bool is_red(int h) const {
        return h != -1 && nodes[static_cast<size_t>(h)].color == RED;
    }

    int node_size(int h) const {
        return h == -1 ? 0 : nodes[static_cast<size_t>(h)].sz;
    }

    void update_size(int h) {
        if (h != -1) {
            int l = nodes[static_cast<size_t>(h)].left;
            int r = nodes[static_cast<size_t>(h)].right;
            nodes[static_cast<size_t>(h)].sz = 1 + node_size(l) + node_size(r);
        }
    }

    int rotate_left(int h) {
        int x = nodes[static_cast<size_t>(h)].right;
        nodes[static_cast<size_t>(h)].right = nodes[static_cast<size_t>(x)].left;
        nodes[static_cast<size_t>(x)].left = h;
        nodes[static_cast<size_t>(x)].color = nodes[static_cast<size_t>(h)].color;
        nodes[static_cast<size_t>(h)].color = RED;
        nodes[static_cast<size_t>(x)].sz = nodes[static_cast<size_t>(h)].sz;
        update_size(h);
        return x;
    }

    int rotate_right(int h) {
        int x = nodes[static_cast<size_t>(h)].left;
        nodes[static_cast<size_t>(h)].left = nodes[static_cast<size_t>(x)].right;
        nodes[static_cast<size_t>(x)].right = h;
        nodes[static_cast<size_t>(x)].color = nodes[static_cast<size_t>(h)].color;
        nodes[static_cast<size_t>(h)].color = RED;
        nodes[static_cast<size_t>(x)].sz = nodes[static_cast<size_t>(h)].sz;
        update_size(h);
        return x;
    }

    void flip_colors(int h) {
        nodes[static_cast<size_t>(h)].color = !nodes[static_cast<size_t>(h)].color;
        int l = nodes[static_cast<size_t>(h)].left;
        int r = nodes[static_cast<size_t>(h)].right;
        nodes[static_cast<size_t>(l)].color = !nodes[static_cast<size_t>(l)].color;
        nodes[static_cast<size_t>(r)].color = !nodes[static_cast<size_t>(r)].color;
    }

    int balance(int h) {
        if (is_red(nodes[static_cast<size_t>(h)].right) &&
            !is_red(nodes[static_cast<size_t>(h)].left)) {
            h = rotate_left(h);
        }
        int hl = nodes[static_cast<size_t>(h)].left;
        if (is_red(hl) && is_red(nodes[static_cast<size_t>(hl)].left)) {
            h = rotate_right(h);
        }
        if (is_red(nodes[static_cast<size_t>(h)].left) &&
            is_red(nodes[static_cast<size_t>(h)].right)) {
            flip_colors(h);
        }
        update_size(h);
        return h;
    }

    int move_red_left(int h) {
        flip_colors(h);
        int hr = nodes[static_cast<size_t>(h)].right;
        if (is_red(nodes[static_cast<size_t>(hr)].left)) {
            nodes[static_cast<size_t>(h)].right = rotate_right(hr);
            h = rotate_left(h);
            flip_colors(h);
        }
        return h;
    }

    int move_red_right(int h) {
        flip_colors(h);
        int hl = nodes[static_cast<size_t>(h)].left;
        if (is_red(nodes[static_cast<size_t>(hl)].left)) {
            h = rotate_right(h);
            flip_colors(h);
        }
        return h;
    }

    int put_node(int h, int64_t key, int64_t val) {
        if (h == -1) {
            int idx = static_cast<int>(nodes.size());
            nodes.push_back(Node{key, val, RED, 1, -1, -1});
            return idx;
        }
        int64_t hk = nodes[static_cast<size_t>(h)].key;
        if (key < hk) {
            int l = put_node(nodes[static_cast<size_t>(h)].left, key, val);
            nodes[static_cast<size_t>(h)].left = l;
        } else if (key > hk) {
            int r = put_node(nodes[static_cast<size_t>(h)].right, key, val);
            nodes[static_cast<size_t>(h)].right = r;
        } else {
            nodes[static_cast<size_t>(h)].val = val;
        }
        return balance(h);
    }

    int min_node(int h) const {
        while (nodes[static_cast<size_t>(h)].left != -1) {
            h = nodes[static_cast<size_t>(h)].left;
        }
        return h;
    }

    int delete_min(int h) {
        if (nodes[static_cast<size_t>(h)].left == -1) {
            return -1;
        }
        int hl = nodes[static_cast<size_t>(h)].left;
        if (!is_red(hl) && !is_red(nodes[static_cast<size_t>(hl)].left)) {
            h = move_red_left(h);
        }
        int nl = delete_min(nodes[static_cast<size_t>(h)].left);
        nodes[static_cast<size_t>(h)].left = nl;
        return balance(h);
    }

    int delete_node(int h, int64_t key) {
        if (key < nodes[static_cast<size_t>(h)].key) {
            int hl = nodes[static_cast<size_t>(h)].left;
            if (!is_red(hl) && !is_red(nodes[static_cast<size_t>(hl)].left)) {
                h = move_red_left(h);
            }
            int nl = delete_node(nodes[static_cast<size_t>(h)].left, key);
            nodes[static_cast<size_t>(h)].left = nl;
        } else {
            if (is_red(nodes[static_cast<size_t>(h)].left)) {
                h = rotate_right(h);
            }
            if (key == nodes[static_cast<size_t>(h)].key &&
                nodes[static_cast<size_t>(h)].right == -1) {
                return -1;
            }
            int hr = nodes[static_cast<size_t>(h)].right;
            if (!is_red(hr) && !is_red(nodes[static_cast<size_t>(hr)].left)) {
                h = move_red_right(h);
            }
            if (key == nodes[static_cast<size_t>(h)].key) {
                int m = min_node(nodes[static_cast<size_t>(h)].right);
                nodes[static_cast<size_t>(h)].key = nodes[static_cast<size_t>(m)].key;
                nodes[static_cast<size_t>(h)].val = nodes[static_cast<size_t>(m)].val;
                int nr = delete_min(nodes[static_cast<size_t>(h)].right);
                nodes[static_cast<size_t>(h)].right = nr;
            } else {
                int nr = delete_node(nodes[static_cast<size_t>(h)].right, key);
                nodes[static_cast<size_t>(h)].right = nr;
            }
        }
        return balance(h);
    }

public:
    void put(int64_t key, int64_t val) {
        root_idx = put_node(root_idx, key, val);
        nodes[static_cast<size_t>(root_idx)].color = BLACK;
    }

    bool get(int64_t key, int64_t& out_val) const {
        int cur = root_idx;
        while (cur != -1) {
            int64_t ck = nodes[static_cast<size_t>(cur)].key;
            if (key == ck) {
                out_val = nodes[static_cast<size_t>(cur)].val;
                return true;
            }
            if (key < ck) {
                cur = nodes[static_cast<size_t>(cur)].left;
            } else {
                cur = nodes[static_cast<size_t>(cur)].right;
            }
        }
        return false;
    }

    bool contains(int64_t key) const {
        int64_t dummy = 0;
        return get(key, dummy);
    }

    void remove(int64_t key) {
        if (!contains(key)) {
            return;
        }
        if (!is_red(nodes[static_cast<size_t>(root_idx)].left) &&
            !is_red(nodes[static_cast<size_t>(root_idx)].right)) {
            nodes[static_cast<size_t>(root_idx)].color = RED;
        }
        root_idx = delete_node(root_idx, key);
        if (root_idx != -1) {
            nodes[static_cast<size_t>(root_idx)].color = BLACK;
        }
    }

    int rank(int64_t key) const {
        int cur = root_idx;
        int ans = 0;
        while (cur != -1) {
            int64_t ck = nodes[static_cast<size_t>(cur)].key;
            if (key < ck) {
                cur = nodes[static_cast<size_t>(cur)].left;
            } else if (key > ck) {
                ans += 1 + node_size(nodes[static_cast<size_t>(cur)].left);
                cur = nodes[static_cast<size_t>(cur)].right;
            } else {
                ans += node_size(nodes[static_cast<size_t>(cur)].left);
                break;
            }
        }
        return ans;
    }

    int range_count(int64_t lo, int64_t hi) const {
        if (lo > hi) {
            return 0;
        }
        return rank(hi) - rank(lo) + (contains(hi) ? 1 : 0);
    }

    bool floor(int64_t key, int64_t& out_key) const {
        int cur = root_idx;
        bool found = false;
        while (cur != -1) {
            int64_t ck = nodes[static_cast<size_t>(cur)].key;
            if (key == ck) {
                out_key = ck;
                return true;
            }
            if (key < ck) {
                cur = nodes[static_cast<size_t>(cur)].left;
            } else {
                out_key = ck;
                found = true;
                cur = nodes[static_cast<size_t>(cur)].right;
            }
        }
        return found;
    }

    bool ceiling(int64_t key, int64_t& out_key) const {
        int cur = root_idx;
        bool found = false;
        while (cur != -1) {
            int64_t ck = nodes[static_cast<size_t>(cur)].key;
            if (key == ck) {
                out_key = ck;
                return true;
            }
            if (key > ck) {
                cur = nodes[static_cast<size_t>(cur)].right;
            } else {
                out_key = ck;
                found = true;
                cur = nodes[static_cast<size_t>(cur)].left;
            }
        }
        return found;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q = 0;
    if (!(cin >> q)) {
        return 0;
    }

    LLRBTree tree;
    for (int i = 0; i < q; ++i) {
        int op = 0;
        if (!(cin >> op)) {
            break;
        }
        if (op == 1) {
            int64_t k = 0;
            int64_t v = 0;
            cin >> k >> v;
            tree.put(k, v);
        } else if (op == 2) {
            int64_t k = 0;
            cin >> k;
            tree.remove(k);
        } else if (op == 3) {
            int64_t k = 0;
            cin >> k;
            int64_t v = 0;
            if (tree.get(k, v)) {
                cout << v << "\n";
            } else {
                cout << "NONE\n";
            }
        } else if (op == 4) {
            int64_t lo = 0;
            int64_t hi = 0;
            cin >> lo >> hi;
            cout << tree.range_count(lo, hi) << "\n";
        } else if (op == 5) {
            int64_t k = 0;
            cin >> k;
            int64_t fk = 0;
            if (tree.floor(k, fk)) {
                cout << fk << "\n";
            } else {
                cout << "NONE\n";
            }
        }
    }

    return 0;
}
