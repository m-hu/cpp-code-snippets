#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
bool bpm(int u, const vector<vector<int>>& adj, vector<int>& matchR, vector<bool>& seen) {
    for (int v : adj[u]) {
        if (seen[v]) continue;
        seen[v] = true;
        if (matchR[v] < 0 || bpm(matchR[v], adj, matchR, seen)) {
            matchR[v] = u;
            return true;
        }
    }
    return false;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m, e; if (!(cin >> n >> m >> e)) return 0;
    vector<vector<int>> adj(n);
    for (int i = 0; i < e; i++) { int u, v; cin >> u >> v; adj[u].push_back(v); }
    for (int u = 0; u < n; u++) sort(adj[u].begin(), adj[u].end());
    vector<int> matchR(m, -1);
    for (int u = 0; u < n; u++) {
        vector<bool> seen(m, false);
        bpm(u, adj, matchR, seen);
    }
    vector<int> matchL(n, -1);
    for (int v = 0; v < m; v++) if (matchR[v] >= 0) matchL[matchR[v]] = v;
    for (int u = 0; u < n; u++) if (matchL[u] < 0) { cout << "NO\n"; return 0; }
    for (int u = 0; u < n; u++) cout << u << " " << matchL[u] << "\n";
    return 0;
}
