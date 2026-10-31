// cartesian-rmq: Cartesian tree + Euler tour + sparse table (Bender-Farach).
// O(n) build, O(1) range-min queries. Input: n; n values; q; q ranges
// l r (0-based inclusive). Output min value per query. Pure C++14.
#include <iostream>
#include <vector>
struct CartesianRMQ {
    int n;
    std::vector<int64_t> a;
    std::vector<int> left, right, tour, depth, first, lg;
    std::vector<std::vector<int>> st;
    CartesianRMQ(const std::vector<int64_t> &av) : n(av.size()), a(av) {
        left.assign(n, -1); right.assign(n, -1);
        std::vector<int> parent(n, -1), stack;
        for (int i = 0; i < n; ++i) {
            int last = -1;
            while (!stack.empty() && a[stack.back()] > a[i]) { last = stack.back(); stack.pop_back(); }
            if (!stack.empty()) { right[stack.back()] = i; parent[i] = stack.back(); }
            left[i] = last;
            if (last != -1) parent[last] = i;
            stack.push_back(i);
        }
        int root = 0;
        for (int i = 0; i < n; ++i) if (parent[i] == -1) root = i;
        first.assign(n, -1);
        euler(root, 0);
        int m = tour.size();
        lg.assign(m + 1, 0);
        for (int i = 2; i <= m; ++i) lg[i] = lg[i / 2] + 1;
        st.assign(lg[m] + 1, std::vector<int>(m));
        for (int i = 0; i < m; ++i) st[0][i] = i;
        for (int k = 1; k <= lg[m]; ++k)
            for (int i = 0; i + (1 << k) <= m; ++i) {
                int x = st[k - 1][i], y = st[k - 1][i + (1 << (k - 1))];
                st[k][i] = depth[x] <= depth[y] ? x : y;
            }
    }
    void euler(int u, int d) {
        first[u] = (int)tour.size();
        tour.push_back(u); depth.push_back(d);
        if (left[u] != -1) { euler(left[u], d + 1); tour.push_back(u); depth.push_back(d); }
        if (right[u] != -1) { euler(right[u], d + 1); tour.push_back(u); depth.push_back(d); }
    }
    int64_t query(int l, int r) {
        int i = first[l], j = first[r];
        if (i > j) { int t = i; i = j; j = t; }
        int k = lg[j - i + 1];
        int x = st[k][i], y = st[k][j - (1 << k) + 1];
        return a[tour[depth[x] <= depth[y] ? x : y]];
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n = 0;
    if (!(std::cin >> n)) return 0;
    std::vector<int64_t> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    CartesianRMQ rmq(a);
    int q = 0;
    std::cin >> q;
    for (int i = 0; i < q; ++i) {
        int l, r; std::cin >> l >> r;
        std::cout << rmq.query(l, r) << "\n";
    }
    return 0;
}
