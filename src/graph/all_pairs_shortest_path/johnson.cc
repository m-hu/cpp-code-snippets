#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const long long INF = 1e18;

struct Edge {
    int to;
    long long w;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int v_count = 0, e_count = 0;
    if (!(cin >> v_count >> e_count)) return 0;

    struct FullEdge {
        int u;
        int v;
        long long w;
    };
    vector<FullEdge> all_edges(static_cast<size_t>(e_count));
    vector<vector<Edge>> adj(static_cast<size_t>(v_count));

    for (int i = 0; i < e_count; ++i) {
        int u = 0, v = 0;
        long long w = 0;
        cin >> u >> v >> w;
        all_edges[static_cast<size_t>(i)] = {u, v, w};
        adj[static_cast<size_t>(u)].push_back({v, w});
    }

    // Step 1: Bellman-Ford from dummy vertex with 0-weight edges to all v
    vector<long long> h(static_cast<size_t>(v_count), 0);
    for (int iter = 0; iter < v_count; ++iter) {
        bool updated = false;
        for (const auto& e : all_edges) {
            if (h[static_cast<size_t>(e.u)] + e.w < h[static_cast<size_t>(e.v)]) {
                h[static_cast<size_t>(e.v)] = h[static_cast<size_t>(e.u)] + e.w;
                updated = true;
            }
        }
        if (!updated) break;
        if (iter == v_count - 1) {
            cout << "NEGATIVE CYCLE\n";
            return 0;
        }
    }

    // Step 2: Dijkstra from each vertex with reweighted edges
    for (int src = 0; src < v_count; ++src) {
        vector<long long> d(static_cast<size_t>(v_count), INF);
        d[static_cast<size_t>(src)] = 0;
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
        pq.push({0, src});

        while (!pq.empty()) {
            auto top = pq.top();
            pq.pop();
            long long cur_d = top.first;
            int u = top.second;
            if (cur_d > d[static_cast<size_t>(u)]) continue;

            for (const auto& edge : adj[static_cast<size_t>(u)]) {
                int v = edge.to;
                long long reweighted_w = edge.w + h[static_cast<size_t>(u)] - h[static_cast<size_t>(v)];
                if (d[static_cast<size_t>(u)] + reweighted_w < d[static_cast<size_t>(v)]) {
                    d[static_cast<size_t>(v)] = d[static_cast<size_t>(u)] + reweighted_w;
                    pq.push({d[static_cast<size_t>(v)], v});
                }
            }
        }

        for (int v = 0; v < v_count; ++v) {
            if (v > 0) cout << " ";
            if (d[static_cast<size_t>(v)] >= INF / 2) {
                cout << "INF";
            } else {
                long long real_dist = d[static_cast<size_t>(v)] + h[static_cast<size_t>(v)] - h[static_cast<size_t>(src)];
                cout << real_dist;
            }
        }
        cout << "\n";
    }

    return 0;
}
