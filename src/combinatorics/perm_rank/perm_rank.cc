#include <iostream>
#include <string>
#include <vector>
using namespace std;
using int64 = long long;
int64 fact(int n) { int64 f = 1; for (int i = 2; i <= n; i++) f *= i; return f; }
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string mode; if (!(cin >> mode)) return 0;
    if (mode == "R") {
        int n; cin >> n;
        vector<int> p(n);
        for (int i = 0; i < n; i++) cin >> p[i];
        vector<int> L(n, 0);
        int64 rank = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) if (p[j] < p[i]) L[i]++;
            rank += (int64)L[i] * fact(n - 1 - i);
        }
        cout << rank << "\n";
        for (int i = 0; i < n; i++) { if (i) cout << ' '; cout << L[i]; }
        cout << "\n";
    } else {
        int n; int64 r; cin >> n >> r;
        vector<int> avail(n);
        for (int i = 0; i < n; i++) avail[i] = i;
        vector<int> p;
        for (int i = 0; i < n; i++) {
            int64 f = fact(n - 1 - i);
            int idx = (int)(r / f); r %= f;
            p.push_back(avail[(size_t)idx]);
            avail.erase(avail.begin() + idx);
        }
        for (int i = 0; i < n; i++) { if (i) cout << ' '; cout << p[i]; }
        cout << "\n";
    }
    return 0;
}
