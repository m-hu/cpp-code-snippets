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
int64 modinv(int64 a, int64 m) {
    int64 x, y; egcd(a, m, x, y); x %= m; if (x < 0) x += m; return x;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int64 p, q, e, m; if (!(cin >> p >> q >> e >> m)) return 0;
    int64 n = p * q, phi = (p - 1) * (q - 1), d = modinv(e, phi);
    int64 c = modpow(m, e, n);
    int64 dp = d % (p - 1), dq = d % (q - 1), qinv = modinv(q, p);
    int64 m1 = modpow(c, dp, p), m2 = modpow(c, dq, q);
    int64 h = ((qinv * ((m1 - m2) % p)) % p + p) % p;
    cout << n << " " << phi << " " << d << "\n" << c << "\n" << m2 + h * q << "\n";
    return 0;
}
