// indexed-priority-queue: IndexMinPQ (Sedgewick Ch 2.4). Pure C++14.
// Binary heap with inverse index; ties broken by smaller handle.
// Line1: n q. Ops: 1 i key insert/change, 2 min_index, 3 del_min,
// 4 i delete, 5 i key_of.
#include <cstdint>
#include <iostream>
#include <vector>
struct IndexMinPQ {
    int n, sz;
    std::vector<int> pq, qp;
    std::vector<int64_t> keys;
    IndexMinPQ(int n_) : n(n_), sz(0), pq(n + 1), qp(n, -1), keys(n) {}
    bool less(int i, int j) {
        if (keys[i] != keys[j]) return keys[i] < keys[j];
        return i < j;
    }
    void exch(int a, int b) {
        int t = pq[a]; pq[a] = pq[b]; pq[b] = t;
        qp[pq[a]] = a; qp[pq[b]] = b;
    }
    void swim(int k) {
        while (k > 1 && less(pq[k], pq[k / 2])) { exch(k, k / 2); k /= 2; }
    }
    void sink(int k) {
        while (2 * k <= sz) {
            int j = 2 * k;
            if (j < sz && less(pq[j + 1], pq[j])) ++j;
            if (!less(pq[j], pq[k])) break;
            exch(k, j); k = j;
        }
    }
    void insert(int i, int64_t key) {
        if (qp[i] != -1) { change(i, key); return; }
        ++sz; qp[i] = sz; pq[sz] = i; keys[i] = key; swim(sz);
    }
    void change(int i, int64_t key) {
        keys[i] = key; swim(qp[i]); sink(qp[i]);
    }
    bool has(int i) { return i >= 0 && i < n && qp[i] != -1; }
    int minIndex() { return pq[1]; }
    int delMin() {
        int m = pq[1]; exch(1, sz--); sink(1);
        qp[m] = -1; return m;
    }
    void erase(int i) {
        int k = qp[i]; exch(k, sz--); swim(k); sink(k); qp[i] = -1;
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n = 0, q = 0;
    if (!(std::cin >> n >> q)) return 0;
    IndexMinPQ pq(n);
    for (int i = 0; i < q; ++i) {
        int op = 0;
        std::cin >> op;
        if (op == 1) { int idx; int64_t k; std::cin >> idx >> k; if (idx >= 0 && idx < n) pq.insert(idx, k); }
        else if (op == 2) { if (pq.sz == 0) std::cout << "EMPTY\n"; else std::cout << pq.minIndex() << "\n"; }
        else if (op == 3) { if (pq.sz == 0) std::cout << "EMPTY\n"; else std::cout << pq.delMin() << "\n"; }
        else if (op == 4) { int idx; std::cin >> idx; if (pq.has(idx)) { pq.erase(idx); std::cout << "OK\n"; } else std::cout << "NONE\n"; }
        else if (op == 5) { int idx; std::cin >> idx; if (pq.has(idx)) std::cout << pq.keys[idx] << "\n"; else std::cout << "NONE\n"; }
    }
    return 0;
}
