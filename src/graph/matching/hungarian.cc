#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 1e18;

// Hungarian Algorithm (Kuhn-Munkres) for minimum weight bipartite matching
// 1-based indexing: n workers, m jobs (n <= m)
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 0, m = 0;
    if (!(cin >> n >> m)) return 0;

    // cost[1..n][1..m]
    vector<vector<long long>> cost(static_cast<size_t>(n + 1), vector<long long>(static_cast<size_t>(m + 1), 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> cost[static_cast<size_t>(i)][static_cast<size_t>(j)];
        }
    }

    vector<long long> u(static_cast<size_t>(n + 1), 0);
    vector<long long> v(static_cast<size_t>(m + 1), 0);
    vector<int> p(static_cast<size_t>(m + 1), 0);
    vector<int> way(static_cast<size_t>(m + 1), 0);

    for (int i = 1; i <= n; ++i) {
        p[0] = i;
        int j0 = 0;
        vector<long long> minv(static_cast<size_t>(m + 1), INF);
        vector<bool> used(static_cast<size_t>(m + 1), false);

        do {
            used[static_cast<size_t>(j0)] = true;
            int i0 = p[static_cast<size_t>(j0)];
            long long delta = INF;
            int j1 = 0;

            for (int j = 1; j <= m; ++j) {
                if (!used[static_cast<size_t>(j)]) {
                    long long cur = cost[static_cast<size_t>(i0)][static_cast<size_t>(j)] - u[static_cast<size_t>(i0)] - v[static_cast<size_t>(j)];
                    if (cur < minv[static_cast<size_t>(j)]) {
                        minv[static_cast<size_t>(j)] = cur;
                        way[static_cast<size_t>(j)] = j0;
                    }
                    if (minv[static_cast<size_t>(j)] < delta) {
                        delta = minv[static_cast<size_t>(j)];
                        j1 = j;
                    }
                }
            }

            for (int j = 0; j <= m; ++j) {
                if (used[static_cast<size_t>(j)]) {
                    u[static_cast<size_t>(p[static_cast<size_t>(j)])] += delta;
                    v[static_cast<size_t>(j)] -= delta;
                } else {
                    minv[static_cast<size_t>(j)] -= delta;
                }
            }
            j0 = j1;
        } while (p[static_cast<size_t>(j0)] != 0);

        do {
            int j1 = way[static_cast<size_t>(j0)];
            p[static_cast<size_t>(j0)] = p[static_cast<size_t>(j1)];
            j0 = j1;
        } while (j0 != 0);
    }

    long long min_cost = -v[0];
    cout << min_cost << "\n";

    vector<int> match(static_cast<size_t>(n + 1), 0);
    for (int j = 1; j <= m; ++j) {
        if (p[static_cast<size_t>(j)] <= n) {
            match[static_cast<size_t>(p[static_cast<size_t>(j)])] = j;
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << i << " " << match[static_cast<size_t>(i)] << "\n";
    }

    return 0;
}
