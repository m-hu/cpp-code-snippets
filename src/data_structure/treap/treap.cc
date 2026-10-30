#include <iostream>
#include <string>
#include <vector>
#include <random>

using namespace std;

struct Node {
    int key;
    int priority;
    int size = 1;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(int k, int p) : key(k), priority(p) {}
};

int get_sz(Node* t) {
    return t ? t->size : 0;
}

void update_sz(Node* t) {
    if (t) t->size = 1 + get_sz(t->left) + get_sz(t->right);
}

void split(Node* t, int key, Node*& l, Node*& r) {
    if (!t) {
        l = r = nullptr;
    } else if (key < t->key) {
        split(t->left, key, l, t->left);
        r = t;
        update_sz(r);
    } else {
        split(t->right, key, t->right, r);
        l = t;
        update_sz(l);
    }
}

void merge(Node*& t, Node* l, Node* r) {
    if (!l || !r) {
        t = l ? l : r;
    } else if (l->priority > r->priority) {
        merge(l->right, l->right, r);
        t = l;
        update_sz(t);
    } else {
        merge(r->left, l, r->left);
        t = r;
        update_sz(t);
    }
}

class Treap {
    Node* root = nullptr;
    mt19937 rng{1337}; // Deterministic seed for reproducible tests

    void inorder(Node* t, vector<int>& res) const {
        if (!t) return;
        inorder(t->left, res);
        res.push_back(t->key);
        inorder(t->right, res);
    }

    void clear(Node* t) {
        if (!t) return;
        clear(t->left);
        clear(t->right);
        delete t;
    }

public:
    Treap() = default;
    ~Treap() {
        clear(root);
    }

    void insert(int key) {
        Node *l = nullptr, *r = nullptr;
        split(root, key, l, r);
        // Check if key already exists
        Node* cur = l;
        bool exists = false;
        while (cur && cur->right) cur = cur->right;
        if (cur && cur->key == key) exists = true;

        if (exists) {
            merge(root, l, r);
            return;
        }

        Node* m = new Node(key, static_cast<int>(rng() & 0x7FFFFFFF));
        merge(l, l, m);
        merge(root, l, r);
    }

    bool find(int key) {
        Node* cur = root;
        while (cur) {
            if (cur->key == key) return true;
            if (key < cur->key) cur = cur->left;
            else cur = cur->right;
        }
        return false;
    }

    void erase(int key) {
        Node *l = nullptr, *m = nullptr, *r = nullptr;
        split(root, key - 1, l, r);
        split(r, key, m, r);
        delete m;
        merge(root, l, r);
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

    Treap treap;
    for (int i = 0; i < q; ++i) {
        string op;
        int val = 0;
        cin >> op;
        if (op == "INSERT") {
            cin >> val;
            treap.insert(val);
        } else if (op == "FIND") {
            cin >> val;
            cout << (treap.find(val) ? "FOUND\n" : "NOT_FOUND\n");
        } else if (op == "ERASE") {
            cin >> val;
            treap.erase(val);
        } else if (op == "PRINT") {
            auto arr = treap.get_inorder();
            for (size_t j = 0; j < arr.size(); ++j) {
                if (j > 0) cout << " ";
                cout << arr[j];
            }
            cout << "\n";
        }
    }

    return 0;
}
