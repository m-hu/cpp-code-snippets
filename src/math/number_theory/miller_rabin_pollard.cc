#include <iostream>
#include <vector>
#include <numeric>
#include <random>
#include <algorithm>

using namespace std;

// 128-bit modular multiplication to prevent 64-bit overflow
unsigned long long mod_mul(unsigned long long a, unsigned long long b, unsigned long long m) {
    return static_cast<unsigned long long>((static_cast<__uint128_t>(a) * b) % m);
}

unsigned long long mod_pow(unsigned long long base, unsigned long long exp, unsigned long long m) {
    unsigned long long res = 1;
    base %= m;
    while (exp > 0) {
        if (exp & 1) res = mod_mul(res, base, m);
        base = mod_mul(base, base, m);
        exp >>= 1;
    }
    return res;
}

unsigned long long gcd(unsigned long long a, unsigned long long b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

bool miller_rabin(unsigned long long n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;

    unsigned long long d = n - 1;
    int s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        ++s;
    }

    static const unsigned long long bases[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (unsigned long long a : bases) {
        if (n <= a) break;
        unsigned long long x = mod_pow(a, d, n);
        if (x == 1 || x == n - 1) continue;

        bool composite = true;
        for (int r = 1; r < s; ++r) {
            x = mod_mul(x, x, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

unsigned long long pollard_rho(unsigned long long n) {
    if (n % 2 == 0) return 2;
    unsigned long long x = 2, y = 2, d = 1, c = 1;
    auto f = [&](unsigned long long val, unsigned long long mod) {
        return (mod_mul(val, val, mod) + c) % mod;
    };

    while (d == 1) {
        x = f(x, n);
        y = f(f(y, n), n);
        unsigned long long diff = (x > y) ? (x - y) : (y - x);
        d = gcd(diff, n);
        if (d == n) {
            // Retry with different parameters
            x = 2;
            y = 2;
            ++c;
            d = 1;
        }
    }
    return d;
}

void factorize(unsigned long long n, vector<unsigned long long>& factors) {
    if (n == 1) return;
    if (miller_rabin(n)) {
        factors.push_back(n);
        return;
    }
    unsigned long long d = pollard_rho(n);
    factorize(d, factors);
    factorize(n / d, factors);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 0;
    if (!(cin >> t)) return 0;

    while (t--) {
        unsigned long long n = 0;
        cin >> n;
        if (miller_rabin(n)) {
            cout << "PRIME\n";
        } else {
            cout << "COMPOSITE ";
            vector<unsigned long long> factors;
            factorize(n, factors);
            sort(factors.begin(), factors.end());
            for (size_t i = 0; i < factors.size(); ++i) {
                if (i > 0) cout << " ";
                cout << factors[i];
            }
            cout << "\n";
        }
    }

    return 0;
}
