#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long MOD = 998244353;
const long long G = 3;

long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

long long mod_inverse(long long n) {
    return power(n, MOD - 2);
}

void ntt(vector<long long>& a, bool invert) {
    size_t n = a.size();

    // Bit-reversal permutation
    for (size_t i = 1, j = 0; i < n; ++i) {
        size_t bit = n >> 1;
        for (; j & bit; bit >>= 1) {
            j ^= bit;
        }
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }

    for (size_t len = 2; len <= n; len <<= 1) {
        long long wlen = power(G, (MOD - 1) / static_cast<long long>(len));
        if (invert) {
            wlen = mod_inverse(wlen);
        }

        for (size_t i = 0; i < n; i += len) {
            long long w = 1;
            for (size_t j = 0; j < len / 2; ++j) {
                long long u = a[i + j];
                long long v = (a[i + j + len / 2] * w) % MOD;
                a[i + j] = (u + v < MOD ? u + v : u + v - MOD);
                a[i + j + len / 2] = (u - v >= 0 ? u - v : u - v + MOD);
                w = (w * wlen) % MOD;
            }
        }
    }

    if (invert) {
        long long n_inv = mod_inverse(static_cast<long long>(n));
        for (long long& x : a) {
            x = (x * n_inv) % MOD;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int deg_a = 0, deg_b = 0;
    if (!(cin >> deg_a >> deg_b)) return 0;

    vector<long long> a(static_cast<size_t>(deg_a + 1));
    for (int i = 0; i <= deg_a; ++i) {
        cin >> a[static_cast<size_t>(i)];
    }

    vector<long long> b(static_cast<size_t>(deg_b + 1));
    for (int i = 0; i <= deg_b; ++i) {
        cin >> b[static_cast<size_t>(i)];
    }

    size_t n = 1;
    while (n < static_cast<size_t>(deg_a + deg_b + 1)) {
        n <<= 1;
    }

    a.resize(n, 0);
    b.resize(n, 0);

    ntt(a, false);
    ntt(b, false);

    for (size_t i = 0; i < n; ++i) {
        a[i] = (a[i] * b[i]) % MOD;
    }

    ntt(a, true);

    int final_deg = deg_a + deg_b;
    cout << final_deg << "\n";
    for (int i = 0; i <= final_deg; ++i) {
        if (i > 0) cout << " ";
        cout << a[static_cast<size_t>(i)];
    }
    cout << "\n";

    return 0;
}
