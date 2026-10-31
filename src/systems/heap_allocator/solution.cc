// heap-allocator: implicit free list, first-fit, boundary-tag coalescing.
// Pure C++14. Line1: H q. Block = 8 overhead + payload; min block 16.
// Ops: 1 s malloc (payload offset/FAIL), 2 p free (OK/FAIL), 3 layout.
#include <iostream>
#include <map>
#include <vector>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int64_t H = 0;
    int q = 0;
    if (!(std::cin >> H >> q)) return 0;
    std::vector<int64_t> sizes;
    std::vector<char> isfree;
    if (H >= 16) { sizes.push_back(H); isfree.push_back(1); }
    std::map<int64_t, int64_t> alloc; // payload -> block size
    auto base = [&](size_t k) {
        int64_t b = 0;
        for (size_t i = 0; i < k; ++i) b += sizes[i];
        return b;
    };
    for (int i = 0; i < q; ++i) {
        int op = 0;
        std::cin >> op;
        if (op == 1) {
            int64_t s = 0;
            std::cin >> s;
            if (s < 1) { std::cout << "FAIL\n"; continue; }
            int64_t need = s + 8;
            int pick = -1;
            for (size_t k = 0; k < sizes.size(); ++k)
                if (isfree[k] && sizes[k] >= need) { pick = (int)k; break; }
            if (pick == -1) { std::cout << "FAIL\n"; continue; }
            int64_t leftover = sizes[pick] - need;
            int64_t b = base(pick);
            if (leftover >= 16) {
                sizes[pick] = need;
                sizes.insert(sizes.begin() + pick + 1, leftover);
                isfree.insert(isfree.begin() + pick + 1, 1);
            }
            isfree[pick] = 0;
            int64_t payload = b + 4;
            alloc[payload] = sizes[pick];
            std::cout << payload << "\n";
        } else if (op == 2) {
            int64_t p = 0;
            std::cin >> p;
            auto it = alloc.find(p);
            if (it == alloc.end()) { std::cout << "FAIL\n"; continue; }
            alloc.erase(it);
            int64_t b = p - 4;
            size_t k = 0;
            int64_t acc = 0;
            for (; k < sizes.size(); ++k) {
                if (acc == b) break;
                acc += sizes[k];
            }
            isfree[k] = 1;
            if (k + 1 < sizes.size() && isfree[k + 1]) {
                sizes[k] += sizes[k + 1];
                sizes.erase(sizes.begin() + k + 1);
                isfree.erase(isfree.begin() + k + 1);
            }
            if (k > 0 && isfree[k - 1]) {
                sizes[k - 1] += sizes[k];
                sizes.erase(sizes.begin() + k);
                isfree.erase(isfree.begin() + k);
            }
            std::cout << "OK\n";
        } else if (op == 3) {
            for (size_t k = 0; k < sizes.size(); ++k) {
                if (k) std::cout << " ";
                std::cout << (isfree[k] ? "F" : "A") << sizes[k];
            }
            std::cout << "\n";
        }
    }
    return 0;
}
