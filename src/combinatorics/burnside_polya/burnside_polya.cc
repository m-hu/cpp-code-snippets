#include <iostream>
#include <string>
using namespace std;
using int64 = long long;
int64 phi(int64 n) {
    int64 r = n, x = n;
    for (int64 p = 2; p * p <= x; p++) {
        if (x % p == 0) {
            while (x % p == 0) x /= p;
            r -= r / p;
        }
    }
    if (x > 1) r -= r / x;
    return r;
}
int64 ipow(int64 b, int64 e) {
    int64 r = 1;
    while (e) { if (e & 1) r *= b; b *= b; e >>= 1; }
    return r;
}
int64 necklaces(int64 n, int64 k) {
    int64 s = 0;
    for (int64 d = 1; d <= n; d++)
        if (n % d == 0) s += phi(d) * ipow(k, n / d);
    return s / n;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string mode; if (!(cin >> mode)) return 0;
    int64 n, k; cin >> n >> k;
    int64 N = necklaces(n, k);
    if (mode == "N") cout << N << "\n";
    else if (n % 2 == 1) cout << (N + ipow(k, (n + 1) / 2)) / 2 << "\n";
    else cout << (2 * N + ipow(k, n / 2 + 1) + ipow(k, n / 2)) / 4 << "\n";
    return 0;
}
