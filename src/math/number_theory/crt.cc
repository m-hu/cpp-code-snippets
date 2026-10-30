#include <iostream>
#include <vector>

using namespace std;

long long ext_gcd(long long a, long long b, long long& x, long long& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1 = 0, y1 = 0;
    long long d = ext_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k = 0;
    if (!(cin >> k)) return 0;

    // x = r_i (mod m_i)
    vector<long long> r(static_cast<size_t>(k));
    vector<long long> m(static_cast<size_t>(k));
    for (int i = 0; i < k; ++i) {
        cin >> r[static_cast<size_t>(i)] >> m[static_cast<size_t>(i)];
    }

    long long r1 = r[0];
    long long m1 = m[0];

    bool ok = true;
    for (int i = 1; i < k; ++i) {
        long long r2 = r[static_cast<size_t>(i)];
        long long m2 = m[static_cast<size_t>(i)];

        long long p = 0, q = 0;
        long long g = ext_gcd(m1, m2, p, q);

        if ((r2 - r1) % g != 0) {
            ok = false;
            break;
        }

        long long m2_reduced = m2 / g;
        // p is inverse of m1/g mod m2_reduced
        long long factor = ((r2 - r1) / g) % m2_reduced;
        long long k1 = (p % m2_reduced * factor) % m2_reduced;
        if (k1 < 0) k1 += m2_reduced;

        long long new_m = m1 * m2_reduced;
        long long new_r = (r1 + m1 * k1) % new_m;
        if (new_r < 0) new_r += new_m;

        r1 = new_r;
        m1 = new_m;
    }

    if (ok) {
        cout << r1 << " " << m1 << "\n";
    } else {
        cout << "NO SOLUTION\n";
    }

    return 0;
}
