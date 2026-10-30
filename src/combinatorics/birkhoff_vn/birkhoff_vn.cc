#include <iostream>
#include <vector>
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
    int n; long long S; if (!(cin >> n >> S)) return 0;
    vector<vector<long long>> a(n, vector<long long>(n));
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> a[i][j];
    vector<pair<long long, vector<int>>> terms;
    while (true) {
        bool any = false;
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (a[i][j] > 0) any = true;
        if (!any) break;
        vector<vector<int>> adj(n);
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
            if (a[i][j] > 0) adj[i].push_back(j);
        vector<int> matchR(n, -1);
        for (int u = 0; u < n; u++) {
            vector<bool> seen(n, false);
            bpm(u, adj, matchR, seen);
        }
        vector<int> ml(n, -1);
        for (int v = 0; v < n; v++) if (matchR[v] >= 0) ml[matchR[v]] = v;
        long long c = -1;
        for (int i = 0; i < n; i++) {
            if (c < 0 || a[i][ml[i]] < c) c = a[i][ml[i]];
        }
        for (int i = 0; i < n; i++) a[i][ml[i]] -= c;
        terms.push_back({c, ml});
    }
    cout << terms.size() << "\n";
    for (auto& t : terms) {
        cout << t.first;
        for (int x : t.second) cout << " " << x;
        cout << "\n";
    }
    return 0;
}
