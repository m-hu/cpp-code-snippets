// csma-cd-backoff: binary exponential backoff (truncated at 2^10).
// Pure C++14. Input: q; each: k d1..dk (draws). After i-th collision
// window = 2^min(i,10); slots = d_i mod window. Output per line:
// "<total> <win1> ... <wink>" (total only when k=0).
#include <iostream>
#include <vector>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int q = 0;
    if (!(std::cin >> q)) return 0;
    for (int i = 0; i < q; ++i) {
        int k = 0;
        std::cin >> k;
        int64_t tot = 0;
        std::vector<int64_t> wins;
        for (int j = 1; j <= k; ++j) {
            int64_t d = 0;
            std::cin >> d;
            int e = j < 10 ? j : 10;
            int64_t win = (int64_t)1 << e;
            wins.push_back(win);
            int64_t dd = d < 0 ? -d : d;
            tot += dd % win;
        }
        std::cout << tot;
        for (auto w : wins) std::cout << " " << w;
        std::cout << "\n";
    }
    return 0;
}
