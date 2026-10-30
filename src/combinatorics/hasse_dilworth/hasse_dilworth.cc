#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
bool bpm(int u, const vector<vector<bool>>& reach, vector<int>& matchR, vector<bool>& seen) {
    int n = (int)reach.size();
    for (int v = 0; v < n; v++) {
        if (u != v && reach[u][v] && !seen[v]) {
            seen[v] = true;
            if (matchR[v] < 0 || bpm(matchR[v], reach, matchR, seen)) {
                matchR[v] = u;
                return true;
            }
        }
    }
    return false;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; if (!(cin >> n >> m)) return 0;
    vector<vector<bool>> reach(n, vector<bool>(n, false));
    for (int i = 0; i < n; i++) reach[i][i] = true;
    for (int i = 0; i < m; i++) { int u, v; cin >> u >> v; reach[u][v] = true; }
    for (int k = 0; k < n; k++) for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
        if (reach[i][k] && reach[k][j]) reach[i][j] = true;
    vector<pair<int,int>> hasse;
    for (int u = 0; u < n; u++) for (int v = 0; v < n; v++) {
        if (u == v || !reach[u][v]) continue;
        bool cover = true;
        for (int w = 0; w < n; w++)
            if (w != u && w != v && reach[u][w] && reach[w][v]) { cover = false; break; }
        if (cover) hasse.push_back({u, v});
    }
    sort(hasse.begin(), hasse.end());
    vector<vector<int>> adj(n);
    vector<int> indeg(n, 0);
    for (auto& e : hasse) { adj[e.first].push_back(e.second); indeg[e.second]++; }
    vector<int> avail;
    for (int i = 0; i < n; i++) if (indeg[i] == 0) avail.push_back(i);
    sort(avail.begin(), avail.end());
    vector<int> topo;
    while (!avail.empty()) {
        int u = avail[0]; avail.erase(avail.begin());
        topo.push_back(u);
        sort(adj[u].begin(), adj[u].end());
        for (int v : adj[u]) if (--indeg[v] == 0) {
            avail.push_back(v);
            sort(avail.begin(), avail.end());
        }
    }
    vector<int> h(n, 1);
    for (int v : topo) for (int u = 0; u < n; u++)
        if (u != v && reach[u][v]) h[v] = max(h[v], h[u] + 1);
    int height = *max_element(h.begin(), h.end());
    vector<int> matchR(n, -1);
    int matching = 0;
    for (int u = 0; u < n; u++) {
        vector<bool> seen(n, false);
        if (bpm(u, reach, matchR, seen)) matching++;
    }
    cout << hasse.size() << "\n";
    for (auto& e : hasse) cout << e.first << " " << e.second << "\n";
    cout << height << "\n" << n - matching << "\n";
    return 0;
}
