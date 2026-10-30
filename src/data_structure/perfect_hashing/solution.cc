// perfect-hashing: FKS two-level static table (CLRS 11.5). Pure C++14.
// Input: n; n distinct keys (<P); q; q queries. Deterministic grid
// search for level-1 (min sum nj^2) and level-2 (collision-free in
// nj^2 slots) parameters. Output: total slots S, then YES/NO/query.
#include <cstdint>
#include <iostream>
#include <vector>
const int64_t P = 1000003;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n = 0;
    if (!(std::cin >> n)) return 0;
    std::vector<int64_t> keys(n);
    for (int i = 0; i < n; ++i) std::cin >> keys[i];
    int q = 0;
    std::cin >> q;
    std::vector<int64_t> queries(q);
    for (int i = 0; i < q; ++i) std::cin >> queries[i];
    int m = n > 0 ? n : 1;
    // Level 1: min (sumsq, a, b) over grid.
    int64_t bestA = 1, bestB = 0, bestSum = -1;
    std::vector<int> cnt(m);
    for (int64_t a = 1; a <= 500; ++a) {
        for (int64_t b = 0; b <= 500; ++b) {
            for (int j = 0; j < m; ++j) cnt[j] = 0;
            for (int i = 0; i < n; ++i) cnt[((a * keys[i] + b) % P) % m]++;
            int64_t s = 0;
            for (int j = 0; j < m; ++j) s += (int64_t)cnt[j] * cnt[j];
            if (bestSum == -1 || s < bestSum) { bestSum = s; bestA = a; bestB = b; }
        }
    }
    std::vector<std::vector<int64_t>> buckets(m);
    for (int i = 0; i < n; ++i) buckets[((bestA * keys[i] + bestB) % P) % m].push_back(keys[i]);
    // Level 2 per bucket.
    std::vector<int64_t> a2(m, 1), b2(m, 0);
    std::vector<int> m2(m, 1);
    std::vector<std::vector<std::vector<int64_t>>> slots(m);
    int64_t S = 0;
    std::vector<char> seen;
    for (int j = 0; j < m; ++j) {
        int64_t nj = buckets[j].size();
        int mj = nj > 1 ? (int)(nj * nj) : 1;
        m2[j] = mj;
        S += mj;
        int64_t ba = 1, bb = 0;
        int64_t bc = nj + 1;
        for (int64_t a = 1; a <= 500; ++a) {
            for (int64_t b = 0; b <= 500; ++b) {
                seen.assign(mj, 0);
                int64_t col = 0;
                for (int64_t k : buckets[j]) {
                    int s = (int)(((a * k + b) % P) % mj);
                    if (seen[s]) ++col; else seen[s] = 1;
                }
                if (col < bc) { bc = col; ba = a; bb = b; }
            }
        }
        a2[j] = ba; b2[j] = bb;
        slots[j].assign(mj, {});
        for (int64_t k : buckets[j]) slots[j][((ba * k + bb) % P) % mj].push_back(k);
    }
    std::cout << S << "\n";
    for (int i = 0; i < q; ++i) {
        int64_t x = queries[i];
        int j = (int)(((bestA * x + bestB) % P) % m);
        int s = (int)(((a2[j] * x + b2[j]) % P) % m2[j]);
        bool ok = false;
        for (int64_t k : slots[j][s]) if (k == x) { ok = true; break; }
        std::cout << (ok ? "YES\n" : "NO\n");
    }
    return 0;
}
