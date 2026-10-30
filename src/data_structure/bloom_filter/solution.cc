// bloom-filter: bit array + k double-hashed functions (Sedgewick Ch 3).
// Pure C++14. Line1: m k n q. Then n inserts, q queries. YES/NO each.
#include <cstdint>
#include <iostream>
#include <vector>
const uint64_t C1 = 0x9E3779B97F4A7C15ULL;
const uint64_t C2 = 0xBF58476D1CE4E5B9ULL;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int m = 0, k = 0, n = 0, q = 0;
    if (!(std::cin >> m >> k >> n >> q)) return 0;
    std::vector<char> bits(m, 0);
    auto add = [&](uint64_t ux) {
        uint64_t h1 = ux * C1;
        uint64_t h2 = (ux * C2 + 1) | 1ULL;
        for (int i = 0; i < k; ++i) bits[(h1 + (uint64_t)i * h2) % (uint64_t)m] = 1;
    };
    auto query = [&](uint64_t ux) {
        uint64_t h1 = ux * C1;
        uint64_t h2 = (ux * C2 + 1) | 1ULL;
        for (int i = 0; i < k; ++i)
            if (!bits[(h1 + (uint64_t)i * h2) % (uint64_t)m]) return false;
        return true;
    };
    for (int i = 0; i < n; ++i) { int64_t x; std::cin >> x; add((uint64_t)x); }
    for (int i = 0; i < q; ++i) {
        int64_t x; std::cin >> x;
        std::cout << (query((uint64_t)x) ? "YES\n" : "NO\n");
    }
    return 0;
}
