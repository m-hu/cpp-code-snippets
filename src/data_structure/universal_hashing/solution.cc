// universal-hashing: multiply-shift h(x)=((a*x) mod 2^w)>>(w-k) (CLRS 11.3).
// Pure C++14. Line1: a w k. Line2: n then n keys. Output h per key.
#include <cstdint>
#include <iostream>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    uint64_t a = 0;
    int w = 0, k = 0;
    if (!(std::cin >> a >> w >> k)) return 0;
    int n = 0;
    std::cin >> n;
    uint64_t mask = (w >= 64) ? ~0ULL : ((w == 0) ? 0ULL : ((1ULL << w) - 1ULL));
    for (int i = 0; i < n; ++i) {
        uint64_t x = 0;
        std::cin >> x;
        uint64_t p = (a * x) & mask;
        uint64_t h = (w - k >= 64) ? 0ULL : (p >> (w - k));
        std::cout << h << "\n";
    }
    return 0;
}
