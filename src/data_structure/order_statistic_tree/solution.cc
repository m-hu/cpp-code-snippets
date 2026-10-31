#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

// CLRS Ch 17.1 (Order-Statistic Tree): Red-Black Tree augmented with subtree sizes.
class OrderStatisticTree {
    enum Color { RED, BLACK };

    struct Node {
        int64_t key;
        Color color;
        int sz;
        int left;
        int right;
        int p;
    };

    vector<Node> nodes;
    int nil_idx;
    int root_idx;

    void left_rotate(int x) {
        int y = nodes[static_cast<size_t>(x)].right;
        nodes[static_cast<size_t>(x)].right = nodes[static_cast<size_t>(y)].left;
        if (nodes[static_cast<size_t>(y)].left != nil_idx) {
            nodes[static_cast<size_t>(nodes[static_cast<size_t>(y)].left)].p = x;
        }
        nodes[static_cast<size_t>(y)].p = nodes[static_cast<size_t>(x)].p;
        if (nodes[static_cast<size_t>(x)].p == nil_idx) {
            root_idx = y;
        } else if (x == nodes[static_cast<size_t>(nodes[static_cast<size_t>(x)].p)].left) {
            nodes[static_cast<size_t>(nodes[static_cast<size_t>(x)].p)].left = y;
        } else {
            nodes[static_cast<size_t>(nodes[static_cast<size_t>(x)].p)].right = y;
        }
        nodes[static_cast<size_t>(y)].left = x;
        nodes[static_cast<size_t>(x)].p = y;
        nodes[static_cast<size_t>(y)].sz = nodes[static_cast<size_t>(x)].sz;
        int xl = nodes[static_cast<size_t>(x)].left;
        int xr = nodes[static_cast<size_t>(x)].right;
        nodes[static_cast<size_t>(x)].sz =
            nodes[static_cast<size_t>(xl)].sz + nodes[static_cast<size_t>(xr)].sz + 1;
    }

    void right_rotate(int y) {
        int x = nodes[static_cast<size_t>(y)].left;
        nodes[static_cast<size_t>(y)].left = nodes[static_cast<size_t>(x)].right;
        if (nodes[static_cast<size_t>(x)].right != nil_idx) {
            nodes[static_cast<size_t>(nodes[static_cast<size_t>(x)].right)].p = y;
        }
        nodes[static_cast<size_t>(x)].p = nodes[static_cast<size_t>(y)].p;
        if (nodes[static_cast<size_t>(y)].p == nil_idx) {
            root_idx = x;
        } else if (y == nodes[static_cast<size_t>(nodes[static_cast<size_t>(y)].p)].right) {
            nodes[static_cast<size_t>(nodes[static_cast<size_t>(y)].p)].right = x;
        } else {
            nodes[static_cast<size_t>(nodes[static_cast<size_t>(y)].p)].left = x;
        }
        nodes[static_cast<size_t>(x)].right = y;
        nodes[static_cast<size_t>(y)].p = x;
        nodes[static_cast<size_t>(x)].sz = nodes[static_cast<size_t>(y)].sz;
        int yl = nodes[static_cast<size_t>(y)].left;
        int yr = nodes[static_cast<size_t>(y)].right;
        nodes[static_cast<size_t>(y)].sz =
            nodes[static_cast<size_t>(yl)].sz + nodes[static_cast<size_t>(yr)].sz + 1;
    }

    void rb_insert_fixup(int z) {
        while (nodes[static_cast<size_t>(nodes[static_cast<size_t>(z)].p)].color == RED) {
            int zp = nodes[static_cast<size_t>(z)].p;
            int zpp = nodes[static_cast<size_t>(zp)].p;
            if (zp == nodes[static_cast<size_t>(zpp)].left) {
                int y = nodes[static_cast<size_t>(zpp)].right;
                if (nodes[static_cast<size_t>(y)].color == RED) {
                    nodes[static_cast<size_t>(zp)].color = BLACK;
                    nodes[static_cast<size_t>(y)].color = BLACK;
                    nodes[static_cast<size_t>(zpp)].color = RED;
                    z = zpp;
                } else {
                    if (z == nodes[static_cast<size_t>(zp)].right) {
                        z = zp;
                        left_rotate(z);
                        zp = nodes[static_cast<size_t>(z)].p;
                        zpp = nodes[static_cast<size_t>(zp)].p;
                    }
                    nodes[static_cast<size_t>(zp)].color = BLACK;
                    nodes[static_cast<size_t>(zpp)].color = RED;
                    right_rotate(zpp);
                }
            } else {
                int y = nodes[static_cast<size_t>(zpp)].left;
                if (nodes[static_cast<size_t>(y)].color == RED) {
                    nodes[static_cast<size_t>(zp)].color = BLACK;
                    nodes[static_cast<size_t>(y)].color = BLACK;
                    nodes[static_cast<size_t>(zpp)].color = RED;
                    z = zpp;
                } else {
                    if (z == nodes[static_cast<size_t>(zp)].left) {
                        z = zp;
                        right_rotate(z);
                        zp = nodes[static_cast<size_t>(z)].p;
                        zpp = nodes[static_cast<size_t>(zp)].p;
                    }
                    nodes[static_cast<size_t>(zp)].color = BLACK;
                    nodes[static_cast<size_t>(zpp)].color = RED;
                    left_rotate(zpp);
                }
            }
        }
        nodes[static_cast<size_t>(root_idx)].color = BLACK;
    }

    void rb_transplant(int u, int v) {
        int up = nodes[static_cast<size_t>(u)].p;
        if (up == nil_idx) {
            root_idx = v;
        } else if (u == nodes[static_cast<size_t>(up)].left) {
            nodes[static_cast<size_t>(up)].left = v;
        } else {
            nodes[static_cast<size_t>(up)].right = v;
        }
        nodes[static_cast<size_t>(v)].p = up;
    }

    int tree_minimum(int x) const {
        while (nodes[static_cast<size_t>(x)].left != nil_idx) {
            x = nodes[static_cast<size_t>(x)].left;
        }
        return x;
    }

    void rb_delete_fixup(int x) {
        while (x != root_idx && nodes[static_cast<size_t>(x)].color == BLACK) {
            int xp = nodes[static_cast<size_t>(x)].p;
            if (x == nodes[static_cast<size_t>(xp)].left) {
                int w = nodes[static_cast<size_t>(xp)].right;
                if (nodes[static_cast<size_t>(w)].color == RED) {
                    nodes[static_cast<size_t>(w)].color = BLACK;
                    nodes[static_cast<size_t>(xp)].color = RED;
                    left_rotate(xp);
                    w = nodes[static_cast<size_t>(xp)].right;
                }
                int wl = nodes[static_cast<size_t>(w)].left;
                int wr = nodes[static_cast<size_t>(w)].right;
                if (nodes[static_cast<size_t>(wl)].color == BLACK &&
                    nodes[static_cast<size_t>(wr)].color == BLACK) {
                    nodes[static_cast<size_t>(w)].color = RED;
                    x = xp;
                } else {
                    if (nodes[static_cast<size_t>(wr)].color == BLACK) {
                        nodes[static_cast<size_t>(wl)].color = BLACK;
                        nodes[static_cast<size_t>(w)].color = RED;
                        right_rotate(w);
                        w = nodes[static_cast<size_t>(xp)].right;
                        wr = nodes[static_cast<size_t>(w)].right;
                    }
                    nodes[static_cast<size_t>(w)].color = nodes[static_cast<size_t>(xp)].color;
                    nodes[static_cast<size_t>(xp)].color = BLACK;
                    nodes[static_cast<size_t>(wr)].color = BLACK;
                    left_rotate(xp);
                    x = root_idx;
                }
            } else {
                int w = nodes[static_cast<size_t>(xp)].left;
                if (nodes[static_cast<size_t>(w)].color == RED) {
                    nodes[static_cast<size_t>(w)].color = BLACK;
                    nodes[static_cast<size_t>(xp)].color = RED;
                    right_rotate(xp);
                    w = nodes[static_cast<size_t>(xp)].left;
                }
                int wl = nodes[static_cast<size_t>(w)].left;
                int wr = nodes[static_cast<size_t>(w)].right;
                if (nodes[static_cast<size_t>(wr)].color == BLACK &&
                    nodes[static_cast<size_t>(wl)].color == BLACK) {
                    nodes[static_cast<size_t>(w)].color = RED;
                    x = xp;
                } else {
                    if (nodes[static_cast<size_t>(wl)].color == BLACK) {
                        nodes[static_cast<size_t>(wr)].color = BLACK;
                        nodes[static_cast<size_t>(w)].color = RED;
                        left_rotate(w);
                        w = nodes[static_cast<size_t>(xp)].left;
                        wl = nodes[static_cast<size_t>(w)].left;
                    }
                    nodes[static_cast<size_t>(w)].color = nodes[static_cast<size_t>(xp)].color;
                    nodes[static_cast<size_t>(xp)].color = BLACK;
                    nodes[static_cast<size_t>(wl)].color = BLACK;
                    right_rotate(xp);
                    x = root_idx;
                }
            }
        }
        nodes[static_cast<size_t>(x)].color = BLACK;
    }

    int find_node(int64_t k) const {
        int cur = root_idx;
        while (cur != nil_idx) {
            int64_t ck = nodes[static_cast<size_t>(cur)].key;
            if (k == ck) {
                return cur;
            }
            if (k < ck) {
                cur = nodes[static_cast<size_t>(cur)].left;
            } else {
                cur = nodes[static_cast<size_t>(cur)].right;
            }
        }
        return nil_idx;
    }

public:
    OrderStatisticTree() : nodes(), nil_idx(0), root_idx(0) {
        nodes.push_back(Node{0, BLACK, 0, 0, 0, 0});
    }

    int size() const {
        return nodes[static_cast<size_t>(root_idx)].sz;
    }

    void insert(int64_t key) {
        if (find_node(key) != nil_idx) {
            return;
        }
        int y = nil_idx;
        int x = root_idx;
        while (x != nil_idx) {
            y = x;
            nodes[static_cast<size_t>(x)].sz += 1;
            if (key < nodes[static_cast<size_t>(x)].key) {
                x = nodes[static_cast<size_t>(x)].left;
            } else {
                x = nodes[static_cast<size_t>(x)].right;
            }
        }
        int z = static_cast<int>(nodes.size());
        nodes.push_back(Node{key, RED, 1, nil_idx, nil_idx, y});
        if (y == nil_idx) {
            root_idx = z;
        } else if (key < nodes[static_cast<size_t>(y)].key) {
            nodes[static_cast<size_t>(y)].left = z;
        } else {
            nodes[static_cast<size_t>(y)].right = z;
        }
        rb_insert_fixup(z);
    }

    void remove(int64_t key) {
        int z = find_node(key);
        if (z == nil_idx) {
            return;
        }
        int y = z;
        int zl = nodes[static_cast<size_t>(z)].left;
        int zr = nodes[static_cast<size_t>(z)].right;
        if (zl != nil_idx && zr != nil_idx) {
            y = tree_minimum(zr);
        }
        int cur = nodes[static_cast<size_t>(y)].p;
        while (cur != nil_idx) {
            nodes[static_cast<size_t>(cur)].sz -= 1;
            cur = nodes[static_cast<size_t>(cur)].p;
        }

        Color y_original_color = nodes[static_cast<size_t>(y)].color;
        int x = nil_idx;
        if (zl == nil_idx) {
            x = zr;
            rb_transplant(z, zr);
        } else if (zr == nil_idx) {
            x = zl;
            rb_transplant(z, zl);
        } else {
            x = nodes[static_cast<size_t>(y)].right;
            if (nodes[static_cast<size_t>(y)].p == z) {
                nodes[static_cast<size_t>(x)].p = y;
            } else {
                rb_transplant(y, nodes[static_cast<size_t>(y)].right);
                nodes[static_cast<size_t>(y)].right = nodes[static_cast<size_t>(z)].right;
                nodes[static_cast<size_t>(nodes[static_cast<size_t>(y)].right)].p = y;
            }
            rb_transplant(z, y);
            nodes[static_cast<size_t>(y)].left = nodes[static_cast<size_t>(z)].left;
            nodes[static_cast<size_t>(nodes[static_cast<size_t>(y)].left)].p = y;
            nodes[static_cast<size_t>(y)].color = nodes[static_cast<size_t>(z)].color;
            nodes[static_cast<size_t>(y)].sz = nodes[static_cast<size_t>(z)].sz;
        }
        if (y_original_color == BLACK) {
            rb_delete_fixup(x);
        }
    }

    bool os_select(int64_t k, int64_t& out_key) const {
        if (k < 1 || k > static_cast<int64_t>(size())) {
            return false;
        }
        int cur = root_idx;
        int64_t i = k;
        while (cur != nil_idx) {
            int l = nodes[static_cast<size_t>(cur)].left;
            int64_t r = static_cast<int64_t>(nodes[static_cast<size_t>(l)].sz) + 1;
            if (i == r) {
                out_key = nodes[static_cast<size_t>(cur)].key;
                return true;
            }
            if (i < r) {
                cur = l;
            } else {
                i -= r;
                cur = nodes[static_cast<size_t>(cur)].right;
            }
        }
        return false;
    }

    int os_rank(int64_t key) const {
        int cur = root_idx;
        int ans = 0;
        while (cur != nil_idx) {
            int64_t ck = nodes[static_cast<size_t>(cur)].key;
            if (key <= ck) {
                cur = nodes[static_cast<size_t>(cur)].left;
            } else {
                int l = nodes[static_cast<size_t>(cur)].left;
                ans += nodes[static_cast<size_t>(l)].sz + 1;
                cur = nodes[static_cast<size_t>(cur)].right;
            }
        }
        return ans;
    }
};

static vector<int64_t> josephus_permutation(int64_t n, int64_t m) {
    OrderStatisticTree jtree;
    for (int64_t i = 1; i <= n; ++i) {
        jtree.insert(i);
    }
    vector<int64_t> order;
    order.reserve(static_cast<size_t>(n));
    int64_t idx = 0;
    for (int64_t rem = n; rem >= 1; --rem) {
        idx = (idx + m - 1) % rem;
        int64_t person = 0;
        jtree.os_select(idx + 1, person);
        order.push_back(person);
        jtree.remove(person);
    }
    return order;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q = 0;
    if (!(cin >> q)) {
        return 0;
    }

    OrderStatisticTree tree;
    for (int i = 0; i < q; ++i) {
        int op = 0;
        if (!(cin >> op)) {
            break;
        }
        if (op == 1) {
            int64_t x = 0;
            cin >> x;
            tree.insert(x);
        } else if (op == 2) {
            int64_t x = 0;
            cin >> x;
            tree.remove(x);
        } else if (op == 3) {
            int64_t k = 0;
            cin >> k;
            int64_t val = 0;
            if (tree.os_select(k, val)) {
                cout << val << "\n";
            } else {
                cout << "NONE\n";
            }
        } else if (op == 4) {
            int64_t x = 0;
            cin >> x;
            cout << tree.os_rank(x) << "\n";
        } else if (op == 5) {
            int64_t n = 0;
            int64_t m = 0;
            cin >> n >> m;
            vector<int64_t> res = josephus_permutation(n, m);
            for (size_t j = 0; j < res.size(); ++j) {
                if (j > 0) {
                    cout << " ";
                }
                cout << res[j];
            }
            cout << "\n";
        }
    }

    return 0;
}
