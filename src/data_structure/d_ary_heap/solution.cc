// d-ary-heap: min-heap with d children per node (CLRS Ch 6 Ex). Pure C++14.
// Line1: d q. Ops: 1 x insert, 2 extract-min, 3 peek.
#include <cstdint>
#include <iostream>
#include <vector>
struct DaryHeap {
    int d;
    std::vector<int64_t> a;
    DaryHeap(int d_) : d(d_) {}
    void swim(size_t k) {
        while (k > 0) {
            size_t p = (k - 1) / (size_t)d;
            if (a[k] >= a[p]) break;
            int64_t t = a[k]; a[k] = a[p]; a[p] = t;
            k = p;
        }
    }
    void sink(size_t k) {
        size_t n = a.size();
        for (;;) {
            size_t m = k;
            for (int j = 1; j <= d; ++j) {
                size_t c = (size_t)d * k + j;
                if (c < n && a[c] < a[m]) m = c;
            }
            if (m == k) break;
            int64_t t = a[k]; a[k] = a[m]; a[m] = t;
            k = m;
        }
    }
    void insert(int64_t x) { a.push_back(x); swim(a.size() - 1); }
    bool extractMin(int64_t &o) {
        if (a.empty()) return false;
        o = a[0];
        a[0] = a.back();
        a.pop_back();
        if (!a.empty()) sink(0);
        return true;
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int d = 2, q = 0;
    if (!(std::cin >> d >> q)) return 0;
    if (d < 2) d = 2;
    DaryHeap h(d);
    for (int i = 0; i < q; ++i) {
        int op = 0;
        std::cin >> op;
        if (op == 1) { int64_t x; std::cin >> x; h.insert(x); }
        else if (op == 2) { int64_t o; if (h.extractMin(o)) std::cout << o << "\n"; else std::cout << "EMPTY\n"; }
        else if (op == 3) { if (h.a.empty()) std::cout << "EMPTY\n"; else std::cout << h.a[0] << "\n"; }
    }
    return 0;
}
