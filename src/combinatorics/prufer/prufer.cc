#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string mode; if (!(cin >> mode)) return 0;
    if (mode == "E") {
        int n; cin >> n;
        vector<set<int>> adj(n);
        vector<int> deg(n, 0);
        for (int i = 0; i < n - 1; i++) {
            int u, v; cin >> u >> v;
            adj[u].insert(v); adj[v].insert(u);
            deg[u]++; deg[v]++;
        }
        set<int> leaves;
        for (int i = 0; i < n; i++) if (deg[i] == 1) leaves.insert(i);
        vector<int> seq;
        for (int i = 0; i < n - 2; i++) {
            int leaf = *leaves.begin(); leaves.erase(leaves.begin());
            int nb = *adj[leaf].begin();
            seq.push_back(nb);
            adj[leaf].erase(nb); adj[nb].erase(leaf);
            if (--deg[nb] == 1) leaves.insert(nb);
        }
        for (size_t i = 0; i < seq.size(); i++) { if (i) cout << ' '; cout << seq[i]; }
        cout << "\n";
    } else {
        int n; cin >> n;
        vector<int> seq(max(0, n - 2));
        for (int i = 0; i < n - 2; i++) cin >> seq[i];
        vector<int> deg(n, 1);
        for (int v : seq) deg[v]++;
        set<int> leaves;
        for (int i = 0; i < n; i++) if (deg[i] == 1) leaves.insert(i);
        vector<pair<int,int>> edges;
        for (int v : seq) {
            int leaf = *leaves.begin(); leaves.erase(leaves.begin());
            edges.push_back({min(leaf, v), max(leaf, v)});
            if (--deg[v] == 1) leaves.insert(v);
        }
        int a = *leaves.begin(); leaves.erase(leaves.begin());
        int b = *leaves.begin();
        edges.push_back({min(a, b), max(a, b)});
        sort(edges.begin(), edges.end());
        for (auto& e : edges) cout << e.first << " " << e.second << "\n";
    }
    return 0;
}
