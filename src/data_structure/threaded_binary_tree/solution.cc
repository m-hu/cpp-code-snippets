// threaded-binary-tree: double-threaded BST (Karumanchi Ch 6). Pure C++14.
// Null links store inorder predecessor/successor; traversal uses only
// threads (no stack/recursion). Line1: n q; n keys; ops: 1 x pred,
// 2 x succ, 3 inorder line.
#include <cstdint>
#include <iostream>
#include <vector>
struct TBT {
    std::vector<int64_t> key;
    std::vector<int> L, R;
    std::vector<char> lt, rt; // thread flags
    int root;
    TBT() : root(-1) {}
    int alloc(int64_t x) {
        key.push_back(x); L.push_back(-1); R.push_back(-1);
        lt.push_back(1); rt.push_back(1);
        return (int)key.size() - 1;
    }
    void insert(int64_t x) {
        int n = alloc(x);
        if (root == -1) { root = n; return; }
        int cur = root;
        for (;;) {
            if (x == key[cur]) { key.pop_back(); L.pop_back(); R.pop_back(); lt.pop_back(); rt.pop_back(); return; }
            if (x < key[cur]) {
                if (lt[cur]) {
                    L[n] = L[cur]; R[n] = cur;
                    L[cur] = n; lt[cur] = 0;
                    if (L[n] != -1 && rt[L[n]]) R[L[n]] = n;
                    return;
                }
                cur = L[cur];
            } else {
                if (rt[cur]) {
                    R[n] = R[cur]; L[n] = cur;
                    R[cur] = n; rt[cur] = 0;
                    if (R[n] != -1 && lt[R[n]]) L[R[n]] = n;
                    return;
                }
                cur = R[cur];
            }
        }
    }
    int predNode(int i) {
        if (lt[i]) return L[i];
        int j = L[i];
        while (!rt[j]) j = R[j];
        return j;
    }
    int succNode(int i) {
        if (rt[i]) return R[i];
        int j = R[i];
        while (!lt[j]) j = L[j];
        return j;
    }
    // find x or insertion neighbors; returns node or -1, sets lo/hi
    int find(int64_t x, int &lo, int &hi) {
        lo = -1; hi = -1;
        int cur = root;
        while (cur != -1) {
            if (x == key[cur]) return cur;
            if (x < key[cur]) { hi = cur; if (lt[cur]) break; cur = L[cur]; }
            else { lo = cur; if (rt[cur]) break; cur = R[cur]; }
        }
        return -1;
    }
    bool pred(int64_t x, int64_t &o) {
        int lo, hi;
        int f = find(x, lo, hi);
        int p = (f == -1) ? lo : predNode(f);
        if (p == -1) return false;
        o = key[p];
        return true;
    }
    bool succ(int64_t x, int64_t &o) {
        int lo, hi;
        int f = find(x, lo, hi);
        int s = (f == -1) ? hi : succNode(f);
        if (s == -1) return false;
        o = key[s];
        return true;
    }
    void inorder() {
        if (root == -1) { std::cout << "\n"; return; }
        int cur = root;
        while (!lt[cur]) cur = L[cur];
        bool first = true;
        while (cur != -1) {
            if (!first) std::cout << " ";
            first = false;
            std::cout << key[cur];
            cur = succNode(cur);
        }
        std::cout << "\n";
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n = 0, q = 0;
    if (!(std::cin >> n >> q)) return 0;
    TBT t;
    for (int i = 0; i < n; ++i) { int64_t x; std::cin >> x; t.insert(x); }
    for (int i = 0; i < q; ++i) {
        int op = 0;
        std::cin >> op;
        if (op == 1) { int64_t x, o; std::cin >> x; if (t.pred(x, o)) std::cout << o << "\n"; else std::cout << "NONE\n"; }
        else if (op == 2) { int64_t x, o; std::cin >> x; if (t.succ(x, o)) std::cout << o << "\n"; else std::cout << "NONE\n"; }
        else if (op == 3) { t.inorder(); }
    }
    return 0;
}
