#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int d) : data(d), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, int data) {
    if (root == nullptr) {
        return new Node(data);
    }
    if (data <= root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    return root;
}

Node* lca(Node* root, int v1, int v2) {
    if (root == nullptr) return nullptr;
    if (v1 < root->data && v2 < root->data) {
        return lca(root->left, v1, v2);
    }
    if (v1 > root->data && v2 > root->data) {
        return lca(root->right, v1, v2);
    }
    return root;
}

void delete_tree(Node* root) {
    if (root == nullptr) return;
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
        int v1, v2;
        cin >> v1 >> v2;
        Node* ans = lca(root, v1, v2);
        if (ans) {
            cout << ans->data << "\n";
        }
        delete_tree(root);
    }
    return 0;
}
