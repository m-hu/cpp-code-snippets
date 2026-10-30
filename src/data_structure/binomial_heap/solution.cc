// binomial-heap: mergeable min-heap via binomial trees (CLRS Ch 19).
// Pure C++14. Line1: q. Ops: 1 x insert, 2 extract-min, 3 peek.
#include <cstdint>
#include <iostream>
#include <vector>
struct BinomialHeap {
    std::vector<int64_t> key;
    std::vector<int> parent, child, sibling, degree;
    int head;
    BinomialHeap() : head(-1) {}
    int alloc(int64_t x) {
        key.push_back(x); parent.push_back(-1); child.push_back(-1);
        sibling.push_back(-1); degree.push_back(0);
        return (int)key.size() - 1;
    }
    void link(int y, int z) { // y becomes child of z
        parent[y] = z;
        sibling[y] = child[z];
        child[z] = y;
        degree[z]++;
    }
    int mergeLists(int h1, int h2) {
        if (h1 == -1) return h2;
        if (h2 == -1) return h1;
        int h, t;
        if (degree[h1] <= degree[h2]) { h = t = h1; h1 = sibling[h1]; }
        else { h = t = h2; h2 = sibling[h2]; }
        while (h1 != -1 && h2 != -1) {
            if (degree[h1] <= degree[h2]) { sibling[t] = h1; t = h1; h1 = sibling[h1]; }
            else { sibling[t] = h2; t = h2; h2 = sibling[h2]; }
        }
        sibling[t] = (h1 != -1) ? h1 : h2;
        return h;
    }
    int unite(int h1, int h2) {
        int h = mergeLists(h1, h2);
        if (h == -1) return -1;
        int prev = -1, x = h, next = sibling[x];
        while (next != -1) {
            if (degree[x] != degree[next] ||
                (sibling[next] != -1 && degree[sibling[next]] == degree[x])) {
                prev = x; x = next;
            } else if (key[x] <= key[next]) {
                sibling[x] = sibling[next];
                link(next, x);
            } else {
                if (prev == -1) h = next;
                else sibling[prev] = next;
                link(x, next);
                x = next;
            }
            next = sibling[x];
        }
        return h;
    }
    void insert(int64_t x) { head = unite(head, alloc(x)); }
    bool minimum(int64_t &o) {
        if (head == -1) return false;
        o = key[head];
        for (int r = sibling[head]; r != -1; r = sibling[r])
            if (key[r] < o) o = key[r];
        return true;
    }
    bool extractMin(int64_t &o) {
        if (head == -1) return false;
        int m = head, mp = -1, p = -1;
        for (int r = head; r != -1; r = sibling[r]) {
            if (key[r] < key[m]) { m = r; mp = p; }
            p = r;
        }
        o = key[m];
        if (mp == -1) head = sibling[m];
        else sibling[mp] = sibling[m];
        int rev = -1;
        for (int c = child[m]; c != -1;) {
            int nx = sibling[c];
            sibling[c] = rev;
            parent[c] = -1;
            rev = c;
            c = nx;
        }
        head = unite(head, rev);
        return true;
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int q = 0;
    if (!(std::cin >> q)) return 0;
    BinomialHeap h;
    for (int i = 0; i < q; ++i) {
        int op = 0;
        std::cin >> op;
        if (op == 1) { int64_t x; std::cin >> x; h.insert(x); }
        else if (op == 2) { int64_t o; if (h.extractMin(o)) std::cout << o << "\n"; else std::cout << "EMPTY\n"; }
        else if (op == 3) { int64_t o; if (h.minimum(o)) std::cout << o << "\n"; else std::cout << "EMPTY\n"; }
    }
    return 0;
}
