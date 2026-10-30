#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string mode; if (!(cin >> mode)) return 0;
    if (mode == "VC") {
        int n, m; cin >> n >> m;
        vector<int> U(m), V(m);
        for (int i = 0; i < m; i++) cin >> U[i] >> V[i];
        vector<bool> cov(n, false);
        for (int i = 0; i < m; i++)
            if (!cov[U[i]] && !cov[V[i]]) { cov[U[i]] = true; cov[V[i]] = true; }
        vector<int> out;
        for (int i = 0; i < n; i++) if (cov[i]) out.push_back(i);
        cout << out.size() << "\n";
        for (size_t i = 0; i < out.size(); i++) { if (i) cout << ' '; cout << out[i]; }
        cout << "\n";
    } else if (mode == "SC") {
        int n, m; cin >> n >> m;
        vector<vector<int>> sets(m);
        for (int i = 0; i < m; i++) { int k; cin >> k; sets[i].resize(k);
            for (int j = 0; j < k; j++) cin >> sets[i][j]; }
        vector<bool> unc(n, true);
        int left = n;
        vector<int> chosen;
        while (left > 0) {
            int best = -1, bi = -1;
            for (int i = 0; i < m; i++) {
                int cnt = 0;
                for (int e : sets[i]) if (unc[e]) cnt++;
                if (cnt > best) { best = cnt; bi = i; }
            }
            if (best <= 0) break;
            chosen.push_back(bi);
            for (int e : sets[bi]) if (unc[e]) { unc[e] = false; left--; }
        }
        cout << chosen.size() << "\n";
        for (size_t i = 0; i < chosen.size(); i++) { if (i) cout << ' '; cout << chosen[i]; }
        cout << "\n";
    } else if (mode == "TSP") {
        int n; cin >> n;
        vector<vector<int>> d(n, vector<int>(n));
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> d[i][j];
        vector<bool> vis(n, false);
        vector<int> tour; tour.push_back(0); vis[0] = true;
        int cur = 0, total = 0;
        for (int s = 0; s < n - 1; s++) {
            int best = -1, bi = -1;
            for (int j = 0; j < n; j++)
                if (!vis[j] && (best < 0 || d[cur][j] < best)) { best = d[cur][j]; bi = j; }
            tour.push_back(bi); vis[bi] = true; total += best; cur = bi;
        }
        total += d[cur][0]; tour.push_back(0);
        for (size_t i = 0; i < tour.size(); i++) { if (i) cout << ' '; cout << tour[i]; }
        cout << "\n" << total << "\n";
    } else if (mode == "SS") {
        int n, target; double eps; cin >> n >> target >> eps;
        vector<int> vals(n);
        for (int i = 0; i < n; i++) cin >> vals[i];
        double delta = eps / (2 * n);
        vector<int> L; L.push_back(0);
        for (int x : vals) {
            set<int> M(L.begin(), L.end());
            for (int v : L) if (v + x <= target) M.insert(v + x);
            vector<int> mv(M.begin(), M.end());
            vector<int> nl; nl.push_back(mv[0]);
            int last = mv[0];
            for (size_t i = 1; i < mv.size(); i++)
                if (mv[i] > last * (1 + delta)) { nl.push_back(mv[i]); last = mv[i]; }
            L = nl;
        }
        cout << L.back() << "\n";
    }
    return 0;
}
