#include <iostream>
#include <string>
#include <vector>
using namespace std;
void gen(int rem, int maxv, vector<int>& pre) {
    if (rem == 0) {
        for (size_t i = 0; i < pre.size(); i++) { if (i) cout << ' '; cout << pre[i]; }
        cout << "\n";
        return;
    }
    for (int v = min(maxv, rem); v >= 1; v--) {
        pre.push_back(v);
        gen(rem - v, v, pre);
        pre.pop_back();
    }
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string mode; if (!(cin >> mode)) return 0;
    if (mode == "G") {
        int n; cin >> n;
        vector<int> pre;
        gen(n, n, pre);
    } else {
        int k; cin >> k;
        vector<int> p(k);
        for (int i = 0; i < k; i++) cin >> p[i];
        vector<int> c;
        for (int j = 0; j < p[0]; j++) {
            int cnt = 0;
            for (int x : p) if (x > j) cnt++;
            c.push_back(cnt);
        }
        for (size_t i = 0; i < c.size(); i++) { if (i) cout << ' '; cout << c[i]; }
        cout << "\n";
    }
    return 0;
}
