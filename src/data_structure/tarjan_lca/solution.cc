// tarjan-lca: offline lowest common ancestors (CLRS Ch 19 Prob). Pure C++14.
// DFS + DSU with ancestor tracking. Input: n; n-1 edges; q; q queries.
// Output LCA per query. Nodes 1-based, root 1.
#include <iostream>
#include <vector>
struct Tarjan {
    int n;
    std::vector<std::vector<int>> adj, qid;
    std::vector<std::vector<int>> qother;
    std::vector<int> parent, ancestor, ans;
    std::vector<char> visited;
    Tarjan(int n_) : n(n_), adj(n + 1), qid(n + 1), qother(n + 1),
                     parent(n + 1), ancestor(n + 1), visited(n + 1, 0) {}
    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
    void dfs(int u, int p) {
        parent[u] = u;
        ancestor[u] = u;
        for (int v : adj[u]) {
            if (v == p) continue;
            dfs(v, u);
            parent[find(v)] = find(u);
            ancestor[find(u)] = u;
        }
        visited[u] = 1;
        for (size_t i = 0; i < qid[u].size(); ++i) {
            int v = qother[u][i];
            if (visited[v]) ans[qid[u][i]] = ancestor[find(v)];
        }
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n = 0;
    if (!(std::cin >> n)) return 0;
    Tarjan t(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v; std::cin >> u >> v;
        t.adj[u].push_back(v);
        t.adj[v].push_back(u);
    }
    int q = 0;
    std::cin >> q;
    t.ans.assign(q, 0);
    for (int i = 0; i < q; ++i) {
        int a, b; std::cin >> a >> b;
        t.qid[a].push_back(i); t.qother[a].push_back(b);
        t.qid[b].push_back(i); t.qother[b].push_back(a);
    }
    t.dfs(1, 0);
    for (int i = 0; i < q; ++i) std::cout << t.ans[i] << "\n";
    return 0;
}
