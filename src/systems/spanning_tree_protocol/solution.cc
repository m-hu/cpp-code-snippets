// spanning-tree-protocol: 802.1D root election + ports (Tanenbaum).
// Pure C++14. Input: B E; E lines u v cost (bridge IDs = priority).
// Root = lowest ID. Output: root; per bridge rootport (neighbor/-1);
// per link designated bridge. Dijkstra + lowest-ID tie-breaks.
#include <iostream>
#include <vector>
const int64_t INFLL = (int64_t)4000000000000000000LL;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int B = 0, E = 0;
    if (!(std::cin >> B >> E)) return 0;
    struct Link { int u, v; int64_t c; };
    std::vector<Link> links(E);
    std::vector<std::vector<std::pair<int, int64_t>>> adj(B);
    for (int i = 0; i < E; ++i) {
        int u, v; int64_t c;
        std::cin >> u >> v >> c;
        links[i] = {u, v, c};
        adj[u].push_back({v, c});
        adj[v].push_back({u, c});
    }
    int root = 0;
    std::vector<int64_t> dist(B, INFLL);
    std::vector<char> done(B, 0);
    dist[root] = 0;
    for (int it = 0; it < B; ++it) {
        int u = -1;
        for (int i = 0; i < B; ++i)
            if (!done[i] && (u == -1 || dist[i] < dist[u])) u = i;
        if (u == -1 || dist[u] == INFLL) break;
        done[u] = 1;
        for (auto &e : adj[u])
            if (dist[u] + e.second < dist[e.first]) dist[e.first] = dist[u] + e.second;
    }
    std::cout << root << "\n";
    for (int b = 0; b < B; ++b) {
        if (b == root) { std::cout << "-1\n"; continue; }
        if (dist[b] == INFLL) { std::cout << "-2\n"; continue; }
        int best = -1;
        for (auto &e : adj[b]) {
            int nb = e.first;
            if (dist[nb] + e.second == dist[b] && (best == -1 || nb < best)) best = nb;
        }
        std::cout << best << "\n";
    }
    for (auto &l : links) {
        int d;
        if (dist[l.u] < dist[l.v]) d = l.u;
        else if (dist[l.v] < dist[l.u]) d = l.v;
        else d = l.u < l.v ? l.u : l.v;
        std::cout << d << "\n";
    }
    return 0;
}
