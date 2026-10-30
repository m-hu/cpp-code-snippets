// link-state-routing: OSPF flooding + per-router Dijkstra SPT.
// Pure C++14. Input: N E; E undirected links. Each router floods and
// runs Dijkstra locally. Output N lines; line i: per dest "dist:nh"
// ("0:-" self, "INF:-" unreachable). Lowest-ID tie-breaks.
#include <iostream>
#include <vector>
const int64_t INFLL = (int64_t)4000000000000000000LL;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N = 0, E = 0;
    if (!(std::cin >> N >> E)) return 0;
    std::vector<std::vector<int64_t>> cost(N, std::vector<int64_t>(N, INFLL));
    for (int i = 0; i < E; ++i) {
        int u, v; int64_t c;
        std::cin >> u >> v >> c;
        cost[u][v] = c; cost[v][u] = c;
    }
    for (int s = 0; s < N; ++s) {
        std::vector<int64_t> dist(N, INFLL);
        std::vector<int> parent(N, -1), done(N, 0);
        dist[s] = 0;
        for (int it = 0; it < N; ++it) {
            int u = -1;
            for (int i = 0; i < N; ++i)
                if (!done[i] && (u == -1 || dist[i] < dist[u])) u = i;
            if (u == -1 || dist[u] == INFLL) break;
            done[u] = 1;
            for (int v = 0; v < N; ++v)
                if (cost[u][v] < INFLL / 2 && dist[u] + cost[u][v] < dist[v]) {
                    dist[v] = dist[u] + cost[u][v];
                    parent[v] = u;
                }
        }
        for (int d = 0; d < N; ++d) {
            if (d) std::cout << " ";
            if (d == s) { std::cout << "0:-"; continue; }
            if (dist[d] >= INFLL / 2) { std::cout << "INF:-"; continue; }
            int x = d;
            while (parent[x] != s) x = parent[x];
            std::cout << dist[d] << ":" << x;
        }
        std::cout << "\n";
    }
    return 0;
}
