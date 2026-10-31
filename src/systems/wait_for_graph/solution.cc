// wait-for-graph: deadlock detection via Kosaraju SCC (Tanenbaum MOS 6.4).
// Pure C++14. Input: n m; m wait edges u v (0-based, u waits for v).
// Output: NO DEADLOCK, or DEADLOCK + sorted cycle nodes.
#include <algorithm>
#include <iostream>
#include <vector>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n = 0, m = 0;
    if (!(std::cin >> n >> m)) return 0;
    std::vector<std::vector<int>> g(n), gr(n);
    std::vector<char> selfLoop(n, 0);
    for (int i = 0; i < m; ++i) {
        int u, v; std::cin >> u >> v;
        if (u < 0 || u >= n || v < 0 || v >= n) continue;
        g[u].push_back(v);
        gr[v].push_back(u);
        if (u == v) selfLoop[u] = 1;
    }
    std::vector<char> seen(n, 0);
    std::vector<int> order;
    for (int s = 0; s < n; ++s) {
        if (seen[s]) continue;
        std::vector<std::pair<int, size_t>> st;
        st.push_back({s, 0});
        seen[s] = 1;
        while (!st.empty()) {
            int u = st.back().first;
            size_t &k = st.back().second;
            if (k < g[u].size()) {
                int v = g[u][k++];
                if (!seen[v]) { seen[v] = 1; st.push_back({v, 0}); }
            } else {
                order.push_back(u);
                st.pop_back();
            }
        }
    }
    std::vector<int> comp(n, -1);
    int nc = 0;
    for (int i = (int)order.size() - 1; i >= 0; --i) {
        int s = order[i];
        if (comp[s] != -1) continue;
        std::vector<int> st;
        st.push_back(s);
        comp[s] = nc;
        while (!st.empty()) {
            int u = st.back(); st.pop_back();
            for (int v : gr[u])
                if (comp[v] == -1) { comp[v] = nc; st.push_back(v); }
        }
        ++nc;
    }
    std::vector<int> size(nc, 0);
    for (int c : comp) size[c]++;
    std::vector<int> cyc;
    for (int u = 0; u < n; ++u)
        if (size[comp[u]] > 1 || selfLoop[u]) cyc.push_back(u);
    if (cyc.empty()) {
        std::cout << "NO DEADLOCK\n";
    } else {
        std::cout << "DEADLOCK";
        for (int u : cyc) std::cout << " " << u;
        std::cout << "\n";
    }
    return 0;
}
