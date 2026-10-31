// distance-vector-routing: Bellman-Ford + split horizon/poison reverse.
// Pure C++14. Input: N E; E undirected links u v cost. Synchronous DV
// to convergence. Output: rounds; per node i: dist+nexthop to node N-1
// ("0 -" for self).
#include <iostream>
#include <vector>
const int64_t INFLL = (int64_t)4000000000000000000LL;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N = 0, E = 0;
    if (!(std::cin >> N >> E)) return 0;
    std::vector<std::vector<int64_t>> cost(N, std::vector<int64_t>(N, INFLL));
    std::vector<std::vector<int>> nbr(N);
    for (int i = 0; i < E; ++i) {
        int u, v; int64_t c;
        std::cin >> u >> v >> c;
        cost[u][v] = c; cost[v][u] = c;
        nbr[u].push_back(v); nbr[v].push_back(u);
    }
    std::vector<std::vector<int64_t>> dist(N, std::vector<int64_t>(N, INFLL));
    std::vector<std::vector<int>> nx(N, std::vector<int>(N, -1));
    for (int i = 0; i < N; ++i) {
        dist[i][i] = 0;
        nx[i][i] = i;
        for (int nb : nbr[i]) { dist[i][nb] = cost[i][nb]; nx[i][nb] = nb; }
    }
    int rounds = 0;
    for (int r = 0; r < 1000; ++r) {
        // advertised[i][nb][d]
        std::vector<std::vector<std::vector<int64_t>>> adv(
            N, std::vector<std::vector<int64_t>>(N, std::vector<int64_t>(N, INFLL)));
        for (int i = 0; i < N; ++i)
            for (int nb : nbr[i])
                for (int d = 0; d < N; ++d)
                    adv[i][nb][d] = (nx[i][d] == nb && d != i) ? INFLL : dist[i][d];
        bool changed = false;
        std::vector<std::vector<int64_t>> nd = dist;
        std::vector<std::vector<int>> nn = nx;
        for (int i = 0; i < N; ++i) {
            for (int d = 0; d < N; ++d) {
                if (d == i) continue;
                int64_t best = INFLL;
                int bn = -1;
                for (int nb : nbr[i]) {
                    int64_t a = adv[nb][i][d];
                    int64_t cand = (a >= INFLL / 2) ? INFLL : cost[i][nb] + a;
                    if (cand < best || (cand == best && (bn == -1 || nb < bn))) {
                        best = cand; bn = nb;
                    }
                }
                if (best != dist[i][d] || bn != nx[i][d]) {
                    nd[i][d] = best; nn[i][d] = bn; changed = true;
                }
            }
        }
        dist.swap(nd);
        nx.swap(nn);
        if (!changed) break;
        ++rounds;
    }
    std::cout << rounds << "\n";
    int dst = N - 1;
    for (int i = 0; i < N; ++i) {
        if (i == dst) { std::cout << "0 -\n"; continue; }
        if (dist[i][dst] >= INFLL / 2) std::cout << "INF -\n";
        else std::cout << dist[i][dst] << " " << nx[i][dst] << "\n";
    }
    return 0;
}
