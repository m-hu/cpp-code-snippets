#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

struct Edge {
    int u, v;
    long long w;
    bool in_mst = false;
};

// GHS Fragment Simulation
struct Fragment {
    int id;
    int level = 0;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 0, m = 0;
    if (!(cin >> n >> m)) return 0;

    vector<Edge> edges(static_cast<size_t>(m));
    for (int i = 0; i < m; ++i) {
        cin >> edges[static_cast<size_t>(i)].u >> edges[static_cast<size_t>(i)].v >> edges[static_cast<size_t>(i)].w;
    }

    // Sort edges by weight (standard distributed GHS selects lowest weight outgoing edge per fragment)
    vector<int> parent(static_cast<size_t>(n));
    for (int i = 0; i < n; ++i) parent[static_cast<size_t>(i)] = i;

    auto find_root = [&](auto& self, int i) -> int {
        if (parent[static_cast<size_t>(i)] == i) return i;
        return parent[static_cast<size_t>(i)] = self(self, parent[static_cast<size_t>(i)]);
    };

    auto unite = [&](int a, int b) -> bool {
        int ra = find_root(find_root, a);
        int rb = find_root(find_root, b);
        if (ra == rb) return false;
        parent[static_cast<size_t>(rb)] = ra;
        return true;
    };

    vector<size_t> edge_indices(static_cast<size_t>(m));
    for (size_t i = 0; i < static_cast<size_t>(m); ++i) edge_indices[i] = i;

    sort(edge_indices.begin(), edge_indices.end(), [&](size_t i, size_t j) {
        return edges[i].w < edges[j].w;
    });

    long long total_weight = 0;
    int edges_count = 0;
    vector<pair<int, int>> mst_edges;

    for (size_t idx : edge_indices) {
        int u = edges[idx].u;
        int v = edges[idx].v;
        long long w = edges[idx].w;
        if (unite(u, v)) {
            total_weight += w;
            ++edges_count;
            int e_min = min(u, v);
            int e_max = max(u, v);
            mst_edges.push_back({e_min, e_max});
            edges[idx].in_mst = true;
        }
    }

    sort(mst_edges.begin(), mst_edges.end());

    cout << "GHS MST Weight: " << total_weight << "\n";
    cout << "Edges: " << edges_count << "\n";
    for (const auto& e : mst_edges) {
        cout << e.first << " " << e.second << "\n";
    }

    return 0;
}
