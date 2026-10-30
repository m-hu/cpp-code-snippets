#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

static int64_t gcd64(int64_t a, int64_t b) {
    while (b != 0) {
        int64_t t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 0;
    int q = 0;
    if (!(cin >> n >> q)) {
        return 0;
    }

    size_t un = static_cast<size_t>(n);
    vector<int64_t> a(un);
    for (size_t i = 0; i < un; ++i) {
        cin >> a[i];
    }

    vector<int> lg(un + 1, 0);
    for (size_t i = 2; i <= un; ++i) {
        lg[i] = lg[i / 2] + 1;
    }

    int max_k = lg[un] + 1;
    size_t uk = static_cast<size_t>(max_k);

    vector<vector<int64_t>> st_min(uk, vector<int64_t>(un));
    vector<vector<int64_t>> st_max(uk, vector<int64_t>(un));
    vector<vector<int64_t>> st_gcd(uk, vector<int64_t>(un));

    for (size_t i = 0; i < un; ++i) {
        st_min[0][i] = a[i];
        st_max[0][i] = a[i];
        st_gcd[0][i] = a[i];
    }

    for (int j = 1; j < max_k; ++j) {
        size_t uj = static_cast<size_t>(j);
        size_t prev_j = static_cast<size_t>(j - 1);
        size_t len = static_cast<size_t>(1) << uj;
        size_t half = static_cast<size_t>(1) << prev_j;
        for (size_t i = 0; i + len <= un; ++i) {
            st_min[uj][i] = min(st_min[prev_j][i], st_min[prev_j][i + half]);
            st_max[uj][i] = max(st_max[prev_j][i], st_max[prev_j][i + half]);
            st_gcd[uj][i] = gcd64(st_gcd[prev_j][i], st_gcd[prev_j][i + half]);
        }
    }

    for (int qi = 0; qi < q; ++qi) {
        int type = 0;
        int l = 0;
        int r = 0;
        cin >> type >> l >> r;
        size_t ul = static_cast<size_t>(l);
        size_t ur = static_cast<size_t>(r);
        size_t span = ur - ul + 1;
        size_t k = static_cast<size_t>(lg[span]);
        size_t right_start = ur + 1 - (static_cast<size_t>(1) << k);
        if (type == 1) {
            cout << min(st_min[k][ul], st_min[k][right_start]) << "\n";
        } else if (type == 2) {
            cout << max(st_max[k][ul], st_max[k][right_start]) << "\n";
        } else if (type == 3) {
            cout << gcd64(st_gcd[k][ul], st_gcd[k][right_start]) << "\n";
        }
    }

    return 0;
}
