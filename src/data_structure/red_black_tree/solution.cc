#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

// CLRS Chapter 13: Red-Black Tree with sentinel nil node.
class RedBlackTree {
    enum Color { RED, BLACK };

    struct Node {
        int64_t key;
        Color color;
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
    RedBlackTree() : nodes(), nil_idx(0), root_idx(0) {
        nodes.push_back(Node{0, BLACK, 0, 0, 0});
    }

    void insert(int64_t key) {
        int y = nil_idx;
        int x = root_idx;
        while (x != nil_idx) {
            y = x;
            int64_t xk = nodes[static_cast<size_t>(x)].key;
            if (key == xk) {
                return;
            }
            if (key < xk) {
                x = nodes[static_cast<size_t>(x)].left;
            } else {
                x = nodes[static_cast<size_t>(x)].right;
            }
        }
        int z = static_cast<int>(nodes.size());
        nodes.push_back(Node{key, RED, nil_idx, nil_idx, y});
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
        Color y_original_color = nodes[static_cast<size_t>(y)].color;
        int x = nil_idx;
        int zl = nodes[static_cast<size_t>(z)].left;
        int zr = nodes[static_cast<size_t>(z)].right;
        if (zl == nil_idx) {
            x = zr;
            rb_transplant(z, zr);
        } else if (zr == nil_idx) {
            x = zl;
            rb_transplant(z, zl);
        } else {
            y = tree_minimum(zr);
            y_original_color = nodes[static_cast<size_t>(y)].color;
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
        }
        if (y_original_color == BLACK) {
            rb_delete_fixup(x);
        }
    }

    bool search(int64_t key) const {
        return find_node(key) != nil_idx;
    }

    bool predecessor(int64_t key, int64_t& out) const {
        int cur = root_idx;
        bool found = false;
        while (cur != nil_idx) {
            int64_t ck = nodes[static_cast<size_t>(cur)].key;
            if (ck < key) {
                out = ck;
                found = true;
                cur = nodes[static_cast<size_t>(cur)].right;
            } else {
                cur = nodes[static_cast<size_t>(cur)].left;
            }
        }
        return found;
    }

    bool successor(int64_t key, int64_t& out) const {
        int cur = root_idx;
        bool found = false;
        while (cur != nil_idx) {
            int64_t ck = nodes[static_cast<size_t>(cur)].key;
            if (ck > key) {
                out = ck;
                found = true;
                cur = nodes[static_cast<size_t>(cur)].left;
            } else {
                cur = nodes[static_cast<size_t>(cur)].right;
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

    RedBlackTree tree;
    for (int i = 0; i < q; ++i) {
        int op = 0;
        int64_t x = 0;
        if (!(cin >> op >> x)) {
            break;
        }
        if (op == 1) {
            tree.insert(x);
        } else if (op == 2) {
            tree.remove(x);
        } else if (op == 3) {
            cout << (tree.search(x) ? 1 : 0) << "\n";
        } else if (op == 4) {
            int64_t pred = 0;
            if (tree.predecessor(x, pred)) {
                cout << pred << "\n";
            } else {
                cout << "NONE\n";
            }
        } else if (op == 5) {
            int64_t succ = 0;
            if (tree.successor(x, succ)) {
                cout << succ << "\n";
            } else {
                cout << "NONE\n";
            }
        }
    }

    return 0;
}
