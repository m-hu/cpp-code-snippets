// buddy-allocator: power-of-2 page frame allocator (Tanenbaum MOS).
// Pure C++14. Line1: U q (total 2^U). Ops: 1 s alloc (addr/FAIL),
// 2 a free (OK/FAIL), 3 free counts per order 0..U.
#include <iostream>
#include <map>
#include <set>
#include <vector>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int U = 0, q = 0;
    if (!(std::cin >> U >> q)) return 0;
    std::vector<std::set<int64_t>> freeList(U + 1);
    freeList[U].insert(0);
    std::map<int64_t, int> alloc;
    for (int i = 0; i < q; ++i) {
        int op = 0;
        std::cin >> op;
        if (op == 1) {
            int64_t s = 0;
            std::cin >> s;
            if (s < 1) { std::cout << "FAIL\n"; continue; }
            int need = 0;
            while (need <= U && ((int64_t)1 << need) < s) ++need;
            int found = -1;
            int64_t at = 0;
            for (int o = need; o <= U; ++o) {
                if (!freeList[o].empty()) { found = o; at = *freeList[o].begin(); break; }
            }
            if (need > U || found == -1) { std::cout << "FAIL\n"; continue; }
            freeList[found].erase(at);
            for (int o = found; o > need; --o) {
                int64_t half = (int64_t)1 << (o - 1);
                freeList[o - 1].insert(at + half);
            }
            alloc[at] = need;
            std::cout << at << "\n";
        } else if (op == 2) {
            int64_t a = 0;
            std::cin >> a;
            auto it = alloc.find(a);
            if (it == alloc.end()) { std::cout << "FAIL\n"; continue; }
            int o = it->second;
            alloc.erase(it);
            int64_t at = a;
            while (o < U) {
                int64_t buddy = at ^ ((int64_t)1 << o);
                auto jt = freeList[o].find(buddy);
                if (jt == freeList[o].end()) break;
                freeList[o].erase(jt);
                if (buddy < at) at = buddy;
                ++o;
            }
            freeList[o].insert(at);
            std::cout << "OK\n";
        } else if (op == 3) {
            for (int o = 0; o <= U; ++o) {
                if (o) std::cout << " ";
                std::cout << freeList[o].size();
            }
            std::cout << "\n";
        }
    }
    return 0;
}
