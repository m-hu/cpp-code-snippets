#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
using int64 = long long;
int64 ipow(int64 b, int n) {
    int64 r = 1;
    for (int i = 0; i < n; i++) r *= b;
    return r;
}
int64 chrom(int n, vector<pair<int,int>> edges, int64 k) {
    set<pair<int,int>> s;
    for (auto& e : edges) {
        int a = min(e.first, e.second), b = max(e.first, e.second);
        if (a != b) s.insert({a, b});
    }
    vector<pair<int,int>> es(s.begin(), s.end());
    if (es.empty()) return ipow(k, n);
    int u = es[0].first, v = es[0].second;
    vector<pair<int,int>> rest(es.begin() + 1, es.end());
    int64 p1 = chrom(n, rest, k);
    vector<int> mp(n, -1);
    int nxt = 0;
    for (int i = 0; i < n; i++) {
        if (i == v) continue;
        mp[i] = nxt++;
    }
    vector<pair<int,int>> ne;
    for (auto& e : rest) {
        int a = (e.first == v) ? mp[u] : mp[e.first];
        int b = (e.second == v) ? mp[u] : mp[e.second];
        if (a != b) ne.push_back({a, b});
    }
    return p1 - chrom(n - 1, ne, k);
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; int64 k;
    if (!(cin >> n >> m >> k)) return 0;
    vector<pair<int,int>> edges;
    for (int i = 0; i < m; i++) { int u, v; cin >> u >> v; edges.push_back({u, v}); }
    cout << chrom(n, edges, k) << "\n";
    return 0;
}
