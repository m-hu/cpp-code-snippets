#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <set>
#include <algorithm>
using namespace std;
int Vv;
vector<array<int,3>> Trips;
map<pair<int,int>, vector<int>> ByPair;
vector<vector<bool>> Covered;
vector<array<int,3>> Chosen;
bool bt(int need) {
    if ((int)Chosen.size() == need) return true;
    int fa = -1, fb = -1;
    for (int a = 0; a < Vv; a++) {
        for (int b = a + 1; b < Vv; b++) if (!Covered[a][b]) { fa = a; fb = b; break; }
        if (fa >= 0) break;
    }
    for (int ti : ByPair[{fa, fb}]) {
        auto& t = Trips[ti];
        int ps[3][2] = {{t[0],t[1]},{t[0],t[2]},{t[1],t[2]}};
        bool ok = true;
        for (int i = 0; i < 3; i++) if (Covered[ps[i][0]][ps[i][1]]) ok = false;
        if (!ok) continue;
        for (int i = 0; i < 3; i++) Covered[ps[i][0]][ps[i][1]] = true;
        Chosen.push_back(t);
        if (bt(need)) return true;
        Chosen.pop_back();
        for (int i = 0; i < 3; i++) Covered[ps[i][0]][ps[i][1]] = false;
    }
    return false;
}
bool kbt(int i, int T, int per, vector<vector<array<int,3>>>& classes,
         const vector<array<int,3>>& triples) {
    if (i == T) {
        for (auto& c : classes) if ((int)c.size() != per) return false;
        return true;
    }
    for (auto& c : classes) {
        if ((int)c.size() >= per) continue;
        bool used[16] = {false};
        for (auto& t : c) { used[t[0]] = true; used[t[1]] = true; used[t[2]] = true; }
        auto& t = triples[i];
        if (used[t[0]] || used[t[1]] || used[t[2]]) continue;
        c.push_back(t);
        if (kbt(i + 1, T, per, classes, triples)) return true;
        c.pop_back();
        if (c.empty()) break;
    }
    return false;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string mode; if (!(cin >> mode)) return 0;
    if (mode == "S" || mode == "K") {
        int v; cin >> v; Vv = v;
        Trips.clear(); ByPair.clear();
        for (int a = 0; a < v; a++) for (int b = a + 1; b < v; b++) for (int c = b + 1; c < v; c++) {
            int ti = (int)Trips.size();
            Trips.push_back({a, b, c});
            ByPair[{a,b}].push_back(ti);
            ByPair[{a,c}].push_back(ti);
            ByPair[{b,c}].push_back(ti);
        }
        Covered = vector<vector<bool>>(v, vector<bool>(v, false));
        Chosen.clear();
        bt(v * (v - 1) / 6);
        sort(Chosen.begin(), Chosen.end());
        if (mode == "S") {
            for (auto& t : Chosen) cout << t[0] << " " << t[1] << " " << t[2] << "\n";
        } else {
            int per = v / 3;
            int nc = ((int)Chosen.size() + per - 1) / per;
            vector<vector<array<int,3>>> classes(nc);
            kbt(0, (int)Chosen.size(), per, classes, Chosen);
            for (auto& c : classes) {
                sort(c.begin(), c.end());
                for (size_t i = 0; i < c.size(); i++) {
                    if (i) cout << " ";
                    cout << c[i][0] << " " << c[i][1] << " " << c[i][2];
                }
                cout << "\n";
            }
        }
    } else {
        int v, t; cin >> v >> t;
        vector<array<int,3>> tr(t);
        for (int i = 0; i < t; i++) cin >> tr[i][0] >> tr[i][1] >> tr[i][2];
        bool valid = ((int)tr.size() == v * (v - 1) / 6);
        set<pair<int,int>> seen;
        for (auto& x : tr) {
            int a = x[0], b = x[1], c = x[2];
            if (!(0 <= a && a < b && b < c && c < v)) valid = false;
            pair<int,int> ps[3] = {{a,b},{a,c},{b,c}};
            for (int i = 0; i < 3; i++) {
                if (seen.count(ps[i])) valid = false;
                seen.insert(ps[i]);
            }
        }
        if ((int)seen.size() != v * (v - 1) / 2) valid = false;
        cout << (valid ? "VALID" : "INVALID") << "\n";
    }
    return 0;
}
