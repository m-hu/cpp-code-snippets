#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long MOD = 1000000007LL;

struct City {
    long long x;
    long long p;
    int rank;
};

struct Fenwick {
    int n;
    vector<long long> tree;
    Fenwick(int n) : n(n), tree(n + 1, 0) {}
    void add(int i, long long delta) {
        for (; i <= n; i += i & -i) {
            tree[i] = (tree[i] + delta) % MOD;
            if (tree[i] < 0) tree[i] += MOD;
        }
    }
    long long query(int i) {
        long long sum = 0;
        for (; i > 0; i -= i & -i) {
            sum = (sum + tree[i]) % MOD;
        }
        return sum;
    }
    long long query_range(int l, int r) {
        if (l > r) return 0;
        long long res = (query(r) - query(l - 1)) % MOD;
        if (res < 0) res += MOD;
        return res;
    }
};

void solve() {
    int n;
    if (!(cin >> n)) return;
    vector<City> cities(n);
    vector<long long> coords(n);
    for (int i = 0; i < n; ++i) {
        cin >> cities[i].x;
        coords[i] = cities[i].x;
    }
    for (int i = 0; i < n; ++i) {
        cin >> cities[i].p;
    }
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());
    int m = coords.size();
    for (int i = 0; i < n; ++i) {
        cities[i].rank = lower_bound(coords.begin(), coords.end(), cities[i].x) - coords.begin() + 1;
    }

    sort(cities.begin(), cities.end(), [](const City& a, const City& b) {
        return a.p < b.p;
    });

    Fenwick count_bit(m);
    Fenwick sum_bit(m);

    long long total_cost = 0;

    for (int i = 0; i < n; ++i) {
        long long x = cities[i].x;
        long long p = cities[i].p % MOD;
        int r = cities[i].rank;

        long long count_left = count_bit.query(r - 1);
        long long sum_left = sum_bit.query(r - 1);

        long long count_right = count_bit.query_range(r + 1, m);
        long long sum_right = sum_bit.query_range(r + 1, m);

        long long left_contrib = (count_left * (x % MOD) - sum_left) % MOD;
        if (left_contrib < 0) left_contrib += MOD;

        long long right_contrib = (sum_right - count_right * (x % MOD)) % MOD;
        if (right_contrib < 0) right_contrib += MOD;

        long long cost = (left_contrib + right_contrib) % MOD;
        cost = (cost * p) % MOD;
        total_cost = (total_cost + cost) % MOD;

        count_bit.add(r, 1);
        sum_bit.add(r, x % MOD);
    }

    cout << total_cost << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
