#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string mode; if (!(cin >> mode)) return 0;
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<int> deg(n, 0);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v); adj[v].push_back(u);
        deg[u]++; deg[v]++;
    }
    vector<int> order(n);
    for (int i = 0; i < n; i++) order[i] = i;
    if (mode == "W") sort(order.begin(), order.end(),
        [&](int a, int b) { return deg[a] != deg[b] ? deg[a] > deg[b] : a < b; });
    vector<int> color(n, -1);
    for (int u : order) {
        set<int> used;
        for (int w : adj[u]) if (color[w] >= 0) used.insert(color[w]);
        int c = 0;
        while (used.count(c)) c++;
        color[u] = c;
    }
    int nc = *max_element(color.begin(), color.end()) + 1;
    cout << nc << "\n";
    for (int i = 0; i < n; i++) { if (i) cout << ' '; cout << color[i]; }
    cout << "\n";
    return 0;
}
