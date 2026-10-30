// josephus: (n,m)-elimination via order-statistic Fenwick tree (CLRS 17).
// O(n log n). Input: n m. Output: elimination order, 1-based. Pure C++14.
#include <cstdint>
#include <iostream>
#include <vector>
struct Fenwick {
    int n;
    std::vector<int> bit;
    Fenwick(int n_) : n(n_), bit(n + 1, 0) {}
    void add(int i, int d) { for (; i <= n; i += i & -i) bit[i] += d; }
    int kth(int k) { // 1-based k, smallest i with prefix >= k
        int i = 0, step = 1;
        while (step * 2 <= n) step *= 2;
        for (; step; step /= 2) {
            int j = i + step;
            if (j <= n && bit[j] < k) { k -= bit[j]; i = j; }
        }
        return i + 1;
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n = 0;
    int64_t m = 0;
    if (!(std::cin >> n >> m)) return 0;
    Fenwick fw(n);
    for (int i = 1; i <= n; ++i) fw.add(i, 1);
    int64_t pos = 0;
    int rem = n;
    bool first = true;
    while (rem > 0) {
        pos = (pos + m - 1) % rem;
        int idx = fw.kth((int)pos + 1);
        if (!first) std::cout << " ";
        first = false;
        std::cout << idx;
        fw.add(idx, -1);
        --rem;
    }
    std::cout << "\n";
    return 0;
}
