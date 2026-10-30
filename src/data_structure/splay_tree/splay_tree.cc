#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node {
    int key;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;
    explicit Node(int k) : key(k) {}
};

class SplayTree {
    Node* root = nullptr;

    void rotate_left(Node* x) {
        Node* y = x->right;
        if (!y) return;
        x->right = y->left;
        if (y->left) y->left->parent = x;
        y->parent = x->parent;
        if (!x->parent) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rotate_right(Node* x) {
        Node* y = x->left;
        if (!y) return;
        x->left = y->right;
        if (y->right) y->right->parent = x;
        y->parent = x->parent;
        if (!x->parent) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->right = x;
        x->parent = y;
    }

    void splay(Node* x) {
        while (x->parent) {
            if (!x->parent->parent) {
                // Zig
                if (x == x->parent->left) rotate_right(x->parent);
                else rotate_left(x->parent);
            } else if (x == x->parent->left && x->parent == x->parent->parent->left) {
                // Zig-Zig
                rotate_right(x->parent->parent);
                rotate_right(x->parent);
            } else if (x == x->parent->right && x->parent == x->parent->parent->right) {
                // Zig-Zig
                rotate_left(x->parent->parent);
                rotate_left(x->parent);
            } else if (x == x->parent->right && x->parent == x->parent->parent->left) {
                // Zig-Zag
                rotate_left(x->parent);
                rotate_right(x->parent);
            } else {
                // Zig-Zag
                rotate_right(x->parent);
                rotate_left(x->parent);
            }
        }
    }

    void inorder(Node* u, vector<int>& res) const {
        if (!u) return;
        inorder(u->left, res);
        res.push_back(u->key);
        inorder(u->right, res);
    }

    void clear(Node* u) {
        if (!u) return;
        clear(u->left);
        clear(u->right);
        delete u;
    }

public:
    SplayTree() = default;
    ~SplayTree() {
        clear(root);
    }

    void insert(int key) {
        if (!root) {
            root = new Node(key);
            return;
        }
        Node* cur = root;
        Node* p = nullptr;
        while (cur) {
            p = cur;
            if (key < cur->key) cur = cur->left;
            else if (key > cur->key) cur = cur->right;
            else {
                splay(cur);
                return;
            }
        }
        Node* node = new Node(key);
        node->parent = p;
        if (key < p->key) p->left = node;
        else p->right = node;
        splay(node);
    }

    bool find(int key) {
        Node* cur = root;
        Node* last = nullptr;
        while (cur) {
            last = cur;
            if (key < cur->key) cur = cur->left;
            else if (key > cur->key) cur = cur->right;
            else {
                splay(cur);
                return true;
            }
        }
        if (last) splay(last);
        return false;
    }

    void remove(int key) {
        if (!find(key)) return;
        Node* left_sub = root->left;
        Node* right_sub = root->right;
        if (left_sub) left_sub->parent = nullptr;
        if (right_sub) right_sub->parent = nullptr;
        delete root;

        if (!left_sub) {
            root = right_sub;
        } else {
            Node* m = left_sub;
            while (m->right) m = m->right;
            // Splay max element of left subtree
            Node* old_root = root;
            root = left_sub;
            splay(m);
            (void)old_root;
            root->right = right_sub;
            if (right_sub) right_sub->parent = root;
        }
    }

    vector<int> get_inorder() const {
        vector<int> res;
        inorder(root, res);
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q = 0;
    if (!(cin >> q)) return 0;

    SplayTree tree;
    for (int i = 0; i < q; ++i) {
        string op;
        int val = 0;
        cin >> op;
        if (op == "INSERT") {
            cin >> val;
            tree.insert(val);
        } else if (op == "FIND") {
            cin >> val;
            cout << (tree.find(val) ? "FOUND\n" : "NOT_FOUND\n");
        } else if (op == "DELETE") {
            cin >> val;
            tree.remove(val);
        } else if (op == "PRINT") {
            auto arr = tree.get_inorder();
            for (size_t j = 0; j < arr.size(); ++j) {
                if (j > 0) cout << " ";
                cout << arr[j];
            }
            cout << "\n";
        }
    }

    return 0;
}
