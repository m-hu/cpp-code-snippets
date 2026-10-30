// cache-simulator: set-associative cache, LRU eviction (S,E,B).
// Pure C++14. Input: S E B n; n byte addresses. Output:
// "hits misses evictions".
#include <iostream>
#include <vector>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int64_t S = 0, E = 0, B = 1;
    int n = 0;
    if (!(std::cin >> S >> E >> B >> n)) return 0;
    std::vector<std::vector<int64_t>> sets(S); // MRU-first tags
    int64_t hits = 0, misses = 0, evict = 0;
    for (int i = 0; i < n; ++i) {
        int64_t addr = 0;
        std::cin >> addr;
        int64_t block = addr / B;
        int64_t set = block % S;
        int64_t tag = block / S;
        auto &lines = sets[set];
        int at = -1;
        for (size_t k = 0; k < lines.size(); ++k)
            if (lines[k] == tag) { at = (int)k; break; }
        if (at != -1) {
            ++hits;
            lines.erase(lines.begin() + at);
            lines.insert(lines.begin(), tag);
        } else {
            ++misses;
            if ((int64_t)lines.size() >= E) { ++evict; lines.pop_back(); }
            lines.insert(lines.begin(), tag);
        }
    }
    std::cout << hits << " " << misses << " " << evict << "\n";
    return 0;
}
