// https://www.hackerrank.com/challenges/primsmstsub/problem
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    int start;
    cin >> start;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<bool> in_mst(n + 1, false);

    pq.emplace(0, start);
    long long total_weight = 0;

    while (!pq.empty()) {
        auto [w, u] = pq.top();
        pq.pop();

        if (in_mst[u]) continue;
        in_mst[u] = true;
        total_weight += w;

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (!in_mst[v]) {
                pq.emplace(weight, v);
            }
        }
    }

    cout << total_weight << "\n";
    return 0;
}
