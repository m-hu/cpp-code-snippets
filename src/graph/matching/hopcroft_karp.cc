#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;

class HopcroftKarp {
    int n; // |U|
    vector<vector<int>> adj;
    vector<int> pair_u;
    vector<int> pair_v;
    vector<int> dist;

public:
    HopcroftKarp(int n_u, int n_v)
        : n(n_u),
          adj(static_cast<size_t>(n_u + 1)),
          pair_u(static_cast<size_t>(n_u + 1), 0),
          pair_v(static_cast<size_t>(n_v + 1), 0),
          dist(static_cast<size_t>(n_u + 1), INF) {}

    void add_edge(int u, int v) {
        adj[static_cast<size_t>(u)].push_back(v);
    }

    bool bfs() {
        queue<int> q;
        for (int u = 1; u <= n; ++u) {
            if (pair_u[static_cast<size_t>(u)] == 0) {
                dist[static_cast<size_t>(u)] = 0;
                q.push(u);
            } else {
                dist[static_cast<size_t>(u)] = INF;
            }
        }
        dist[0] = INF;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (dist[static_cast<size_t>(u)] < dist[0]) {
                for (int v : adj[static_cast<size_t>(u)]) {
                    int next_u = pair_v[static_cast<size_t>(v)];
                    if (dist[static_cast<size_t>(next_u)] == INF) {
                        dist[static_cast<size_t>(next_u)] = dist[static_cast<size_t>(u)] + 1;
                        q.push(next_u);
                    }
                }
            }
        }
        return dist[0] != INF;
    }

    bool dfs(int u) {
        if (u != 0) {
            for (int v : adj[static_cast<size_t>(u)]) {
                int next_u = pair_v[static_cast<size_t>(v)];
                if (dist[static_cast<size_t>(next_u)] == dist[static_cast<size_t>(u)] + 1) {
                    if (dfs(next_u)) {
                        pair_v[static_cast<size_t>(v)] = u;
                        pair_u[static_cast<size_t>(u)] = v;
                        return true;
                    }
                }
            }
            dist[static_cast<size_t>(u)] = INF;
            return false;
        }
        return true;
    }

    int max_matching() {
        int matching = 0;
        while (bfs()) {
            for (int u = 1; u <= n; ++u) {
                if (pair_u[static_cast<size_t>(u)] == 0 && dfs(u)) {
                    ++matching;
                }
            }
        }
        return matching;
    }

    const vector<int>& get_pair_u() const {
        return pair_u;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 0, m = 0, e = 0;
    if (!(cin >> n >> m >> e)) return 0;

    HopcroftKarp hk(n, m);
    for (int i = 0; i < e; ++i) {
        int u = 0, v = 0;
        cin >> u >> v;
        hk.add_edge(u, v);
    }

    int size = hk.max_matching();
    cout << size << "\n";

    const auto& pairs = hk.get_pair_u();
    for (int u = 1; u <= n; ++u) {
        if (pairs[static_cast<size_t>(u)] != 0) {
            cout << u << " " << pairs[static_cast<size_t>(u)] << "\n";
        }
    }

    return 0;
}
