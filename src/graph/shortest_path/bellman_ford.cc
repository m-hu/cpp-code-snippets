#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u;
    int v;
    long long w;
};

const long long INF = 1e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int v_count = 0, e_count = 0, start_node = 0;
    if (!(cin >> v_count >> e_count >> start_node)) return 0;

    vector<Edge> edges(static_cast<size_t>(e_count));
    for (int i = 0; i < e_count; ++i) {
        int u = 0, v = 0;
        long long w = 0;
        cin >> u >> v >> w;
        edges[static_cast<size_t>(i)] = {u, v, w};
    }

    vector<long long> dist(static_cast<size_t>(v_count), INF);
    vector<int> parent(static_cast<size_t>(v_count), -1);
    dist[static_cast<size_t>(start_node)] = 0;

    int last_relaxed = -1;
    for (int iter = 0; iter < v_count; ++iter) {
        last_relaxed = -1;
        for (const auto& e : edges) {
            if (dist[static_cast<size_t>(e.u)] < INF) {
                if (dist[static_cast<size_t>(e.u)] + e.w < dist[static_cast<size_t>(e.v)]) {
                    dist[static_cast<size_t>(e.v)] = dist[static_cast<size_t>(e.u)] + e.w;
                    parent[static_cast<size_t>(e.v)] = e.u;
                    last_relaxed = e.v;
                }
            }
        }
        if (last_relaxed == -1) break;
    }

    if (last_relaxed != -1) {
        // Trace back v_count times to guarantee being inside the cycle
        int cycle_node = last_relaxed;
        for (int i = 0; i < v_count; ++i) {
            cycle_node = parent[static_cast<size_t>(cycle_node)];
        }

        vector<int> cycle;
        for (int cur = cycle_node;; cur = parent[static_cast<size_t>(cur)]) {
            cycle.push_back(cur);
            if (cur == cycle_node && cycle.size() > 1) {
                break;
            }
        }
        reverse(cycle.begin(), cycle.end());

        cout << "NEGATIVE CYCLE\n";
        for (size_t i = 0; i < cycle.size(); ++i) {
            if (i > 0) cout << " ";
            cout << cycle[i];
        }
        cout << "\n";
    } else {
        for (int i = 0; i < v_count; ++i) {
            if (dist[static_cast<size_t>(i)] >= INF / 2) {
                cout << "INF\n";
            } else {
                cout << dist[static_cast<size_t>(i)] << "\n";
            }
        }
    }

    return 0;
}
