#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    int ht;
    Node(int v) : val(v), left(nullptr), right(nullptr), ht(0) {}
};

int height(Node* node) {
    return node ? node->ht : -1;
}

void update_ht(Node* node) {
    if (node) {
        node->ht = 1 + max(height(node->left), height(node->right));
    }
}

int balance_factor(Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

Node* rotate_right(Node* y) {
    Node* x = y->left;
    Node* t2 = x->right;
    x->right = y;
    y->left = t2;
    update_ht(y);
    update_ht(x);
    return x;
}

Node* rotate_left(Node* x) {
    Node* y = x->right;
    Node* t2 = y->left;
    y->left = x;
    x->right = t2;
    update_ht(x);
    update_ht(y);
    return y;
}

Node* insert(Node* node, int val) {
    if (!node) {
        return new Node(val);
    }
    if (val < node->val) {
        node->left = insert(node->left, val);
    } else {
        node->right = insert(node->right, val);
    }
    update_ht(node);
    int bf = balance_factor(node);
    if (bf > 1) {
        if (val > node->left->val) {
            node->left = rotate_left(node->left);
        }
        return rotate_right(node);
    }
    if (bf < -1) {
        if (val < node->right->val) {
            node->right = rotate_right(node->right);
        }
        return rotate_left(node);
    }
    return node;
}

void print_inorder(Node* root) {
    if (!root) return;
    print_inorder(root->left);
    cout << root->val << "(BF=" << balance_factor(root) << ") ";
    print_inorder(root->right);
}

void print_preorder(Node* root) {
    if (!root) return;
    cout << root->val << "(BF=" << balance_factor(root) << ") ";
    print_preorder(root->left);
    print_preorder(root->right);
}

void delete_tree(Node* root) {
    if (!root) return;
    delete_tree(root->left);
    delete_tree(root->right);
    delete root;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (cin >> n) {
        Node* root = nullptr;
        for (int i = 0; i < n; ++i) {
            int val;
            cin >> val;
            root = insert(root, val);
        }
        int new_val;
        if (cin >> new_val) {
            root = insert(root, new_val);
        }
        print_inorder(root);
        cout << "\n";
        print_preorder(root);
        cout << "\n";
        delete_tree(root);
    }
    return 0;
}
