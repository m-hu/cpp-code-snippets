#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u;
    int v;
    long long w;
};

struct DSU {
    vector<int> parent;
    vector<int> rank;
    int components;

    explicit DSU(int n) : parent(static_cast<size_t>(n)), rank(static_cast<size_t>(n), 0), components(n) {
        for (int i = 0; i < n; ++i) {
            parent[static_cast<size_t>(i)] = i;
        }
    }

    int find(int i) {
        if (parent[static_cast<size_t>(i)] == i) return i;
        return parent[static_cast<size_t>(i)] = find(parent[static_cast<size_t>(i)]);
    }

    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i == root_j) return false;
        if (rank[static_cast<size_t>(root_i)] < rank[static_cast<size_t>(root_j)]) {
            swap(root_i, root_j);
        }
        parent[static_cast<size_t>(root_j)] = root_i;
        if (rank[static_cast<size_t>(root_i)] == rank[static_cast<size_t>(root_j)]) {
            ++rank[static_cast<size_t>(root_i)];
        }
        --components;
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 0, m = 0;
    if (!(cin >> n >> m)) return 0;

    vector<Edge> edges(static_cast<size_t>(m));
    for (int i = 0; i < m; ++i) {
        int u = 0, v = 0;
        long long w = 0;
        cin >> u >> v >> w;
        edges[static_cast<size_t>(i)] = {u, v, w};
    }

    DSU dsu(n);
    long long mst_weight = 0;
    int edges_added = 0;

    while (dsu.components > 1) {
        // cheapest[comp] = index of cheapest edge in edges
        vector<int> cheapest(static_cast<size_t>(n), -1);

        for (size_t i = 0; i < edges.size(); ++i) {
            int root_u = dsu.find(edges[i].u);
            int root_v = dsu.find(edges[i].v);
            if (root_u == root_v) continue;

            if (cheapest[static_cast<size_t>(root_u)] == -1 || edges[i].w < edges[static_cast<size_t>(cheapest[static_cast<size_t>(root_u)])].w) {
                cheapest[static_cast<size_t>(root_u)] = static_cast<int>(i);
            }
            if (cheapest[static_cast<size_t>(root_v)] == -1 || edges[i].w < edges[static_cast<size_t>(cheapest[static_cast<size_t>(root_v)])].w) {
                cheapest[static_cast<size_t>(root_v)] = static_cast<int>(i);
            }
        }

        bool progress = false;
        for (int i = 0; i < n; ++i) {
            int edge_idx = cheapest[static_cast<size_t>(i)];
            if (edge_idx != -1) {
                int u = edges[static_cast<size_t>(edge_idx)].u;
                int v = edges[static_cast<size_t>(edge_idx)].v;
                long long w = edges[static_cast<size_t>(edge_idx)].w;
                if (dsu.unite(u, v)) {
                    mst_weight += w;
                    ++edges_added;
                    progress = true;
                }
            }
        }

        if (!progress) break;
    }

    if (edges_added == n - 1) {
        cout << mst_weight << "\n";
    } else {
        cout << "DISCONNECTED\n";
    }

    return 0;
}
