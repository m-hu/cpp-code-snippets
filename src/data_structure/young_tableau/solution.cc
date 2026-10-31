// young-tableau: m x n sorted matrix (CLRS Ch 6 Problems). Pure C++14.
// Line1: m n q. Ops: 1 x insert (FULL if full), 2 extract-min,
// 3 x search (YES/NO). INF sentinel for empty cells.
#include <cstdint>
#include <iostream>
#include <vector>
const int64_t INF = (int64_t)4000000000000000000LL;
struct Young {
    int m, n;
    std::vector<std::vector<int64_t>> a;
    Young(int m_, int n_) : m(m_), n(n_), a(m_, std::vector<int64_t>(n_, INF)) {}
    bool insert(int64_t x) {
        if (a[m - 1][n - 1] != INF) return false;
        int i = m - 1, j = n - 1;
        a[i][j] = x;
        while (i > 0 || j > 0) {
            int bi = i, bj = j;
            if (i > 0 && a[i - 1][j] > a[bi][bj]) { bi = i - 1; bj = j; }
            if (j > 0 && a[i][j - 1] > a[bi][bj]) { bi = i; bj = j - 1; }
            if (bi == i && bj == j) break;
            int64_t t = a[i][j]; a[i][j] = a[bi][bj]; a[bi][bj] = t;
            i = bi; j = bj;
        }
        return true;
    }
    bool extractMin(int64_t &o) {
        if (a[0][0] == INF) return false;
        o = a[0][0];
        int i = 0, j = 0;
        a[0][0] = INF;
        for (;;) {
            int si = i, sj = j;
            if (i + 1 < m && a[i + 1][j] < a[si][sj]) { si = i + 1; sj = j; }
            if (j + 1 < n && a[i][j + 1] < a[si][sj]) { si = i; sj = j + 1; }
            if (si == i && sj == j) break;
            a[i][j] = a[si][sj]; a[si][sj] = INF;
            i = si; j = sj;
        }
        return true;
    }
    bool search(int64_t x) {
        int i = 0, j = n - 1;
        while (i < m && j >= 0) {
            if (a[i][j] == x) return true;
            if (a[i][j] > x) --j; else ++i;
        }
        return false;
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int m = 0, n = 0, q = 0;
    if (!(std::cin >> m >> n >> q)) return 0;
    Young t(m, n);
    for (int i = 0; i < q; ++i) {
        int op = 0;
        std::cin >> op;
        if (op == 1) { int64_t x; std::cin >> x; if (!t.insert(x)) std::cout << "FULL\n"; }
        else if (op == 2) { int64_t o; if (t.extractMin(o)) std::cout << o << "\n"; else std::cout << "EMPTY\n"; }
        else if (op == 3) { int64_t x; std::cin >> x; std::cout << (t.search(x) ? "YES\n" : "NO\n"); }
    }
    return 0;
}
