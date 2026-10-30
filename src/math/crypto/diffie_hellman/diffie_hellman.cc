#include <iostream>
using namespace std;
using int64 = long long;
int64 modpow(int64 b, int64 e, int64 m) {
    int64 r = 1 % m; b %= m;
    while (e) { if (e & 1) r = (int64)((__int128)r * b % m);
        b = (int64)((__int128)b * b % m); e >>= 1; }
    return r;
}
int64 egcd(int64 a, int64 b, int64& x, int64& y) {
    if (b == 0) { x = 1; y = 0; return a; }
    int64 x1, y1, g = egcd(b, a % b, x1, y1);
    x = y1; y = x1 - (a / b) * y1; return g;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int64 p, g, a, b, m, r;
    if (!(cin >> p >> g >> a >> b >> m >> r)) return 0;
    int64 A = modpow(g, a, p), B = modpow(g, b, p), s = modpow(B, a, p);
    int64 c1 = modpow(g, r, p), c2 = (int64)((__int128)m * modpow(B, r, p) % p);
    int64 x, y; egcd(modpow(c1, b, p), p, x, y);
    int64 dm = (int64)((__int128)c2 * ((x % p + p) % p) % p);
    cout << A << " " << B << " " << s << "\n" << c1 << " " << c2 << "\n" << dm << "\n";
    return 0;
}
