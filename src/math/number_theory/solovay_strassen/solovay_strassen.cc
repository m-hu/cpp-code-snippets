#include <iostream>
#include <vector>
using namespace std;
using int64 = long long;
int64 llgcd(int64 a, int64 b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b) { int64 t = a % b; a = b; b = t; }
    return a;
}
int64 modpow(int64 b, int64 e, int64 m) {
    int64 r = 1 % m; b %= m;
    while (e) { if (e & 1) r = (__int128)r * b % m;
        b = (__int128)b * b % m; e >>= 1; }
    return r;
}
int jacobi(int64 a, int64 n) {
    a %= n;
    int t = 1;
    while (a != 0) {
        while (a % 2 == 0) {
            a /= 2;
            int64 r = n % 8;
            if (r == 3 || r == 5) t = -t;
        }
        int64 tmp = a; a = n; n = tmp;
        if (a % 4 == 3 && n % 4 == 3) t = -t;
        a %= n;
    }
    return n == 1 ? t : 0;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int64 n; int t;
    if (!(cin >> n >> t)) return 0;
    vector<int64> b(t);
    for (int i = 0; i < t; i++) cin >> b[i];
    vector<int> js(t, 0);
    bool comp = false;
    if (n < 2) comp = true;
    else if (n == 2) { for (int i = 0; i < t; i++) js[i] = jacobi(b[i], n); }
    else if (n % 2 == 0) comp = true;
    else {
        for (int i = 0; i < t; i++) {
            js[i] = jacobi(b[i], n);
            if (llgcd(b[i], n) > 1) comp = true;
            else if (js[i] == 0 || modpow(b[i], (n - 1) / 2, n) != (js[i] % (int)n + n) % n) comp = true;
        }
    }
    for (int i = 0; i < t; i++) { if (i) cout << ' '; cout << js[i]; }
    cout << "\n" << (comp ? "COMPOSITE" : "PRIME") << "\n";
    return 0;
}
