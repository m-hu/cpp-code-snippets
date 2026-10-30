#include <iostream>
#include <vector>
using namespace std;
using int64 = long long;
const int64 MOD = 998244353, G = 3;
int64 modpow(int64 b, int64 e) {
    int64 r = 1;
    while (e) { if (e & 1) r = r * b % MOD; b = b * b % MOD; e >>= 1; }
    return r;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; if (!(cin >> n)) return 0;
    vector<int64> a(n);
    for (int i = 0; i < n; i++) { cin >> a[i]; a[i] %= MOD; }
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) { int64 t = a[i]; a[i] = a[j]; a[j] = t; }
    }
    for (int len = 2; len <= n; len <<= 1) {
        int64 wlen = modpow(G, (MOD - 1) / len);
        for (int i = 0; i < n; i += len) {
            int64 w = 1;
            for (int j = 0; j < len / 2; j++) {
                int64 u = a[i + j], v = a[i + j + len / 2] * w % MOD;
                a[i + j] = (u + v) % MOD;
                a[i + j + len / 2] = (u - v + MOD) % MOD;
                w = w * wlen % MOD;
            }
        }
    }
    for (int i = 0; i < n; i++) { if (i) cout << ' '; cout << a[i]; }
    cout << "\n";
    return 0;
}
