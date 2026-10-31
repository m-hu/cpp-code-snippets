// offline-minimum: Off-Line-Minimum via DSU next-slot (CLRS Ch 19 Prob).
// Inserts processed in increasing value order; each claims the earliest
// unclaimed later EXTRACT-MIN via union-find. Line1: q; ops 1 x / 2.
// Output one line per extract (value or EMPTY). Pure C++14.
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>
struct DSU {
    std::vector<int> p;
    DSU(int n) : p(n) { for (int i = 0; i < n; ++i) p[i] = i; }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    void occupy(int x) { p[x] = find(x + 1); }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int q = 0;
    if (!(std::cin >> q)) return 0;
    std::vector<int> isExt(q, 0);
    std::vector<int64_t> val(q, 0);
    for (int i = 0; i < q; ++i) {
        int op = 0;
        std::cin >> op;
        if (op == 1) { std::cin >> val[i]; }
        else { isExt[i] = 1; }
    }
    std::vector<int> E;
    for (int i = 0; i < q; ++i) if (isExt[i]) E.push_back(i);
    int m = E.size();
    std::vector<std::pair<int64_t, int>> ins;
    for (int i = 0; i < q; ++i) if (!isExt[i]) ins.push_back({val[i], i});
    std::sort(ins.begin(), ins.end());
    DSU dsu(m + 1);
    std::vector<int64_t> ans(m, 0);
    std::vector<char> has(m, 0);
    for (auto &pr : ins) {
        int t = pr.second;
        int j0 = std::upper_bound(E.begin(), E.end(), t) - E.begin();
        int j = dsu.find(j0);
        if (j < m) { ans[j] = pr.first; has[j] = 1; dsu.occupy(j); }
    }
    for (int j = 0; j < m; ++j) {
        if (has[j]) std::cout << ans[j] << "\n";
        else std::cout << "EMPTY\n";
    }
    return 0;
}
