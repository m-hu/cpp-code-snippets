// hash-table-separate-chaining: linked bucket chains (CLRS 11.2). Pure C++14.
// Line1: m q. Ops: 1 k v put, 2 k get, 3 k delete, 4 bucket sizes.
#include <cstdint>
#include <iostream>
#include <vector>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int m = 0, q = 0;
    if (!(std::cin >> m >> q)) return 0;
    std::vector<std::vector<std::pair<int64_t, int64_t>>> t(m);
    auto h = [&](int64_t k) { int r = (int)(k % m); if (r < 0) r += m; return r; };
    for (int i = 0; i < q; ++i) {
        int op = 0;
        std::cin >> op;
        if (op == 1) {
            int64_t k, v; std::cin >> k >> v;
            auto &b = t[h(k)];
            bool found = false;
            for (auto &p : b) if (p.first == k) { p.second = v; found = true; break; }
            if (!found) b.push_back({k, v});
        } else if (op == 2) {
            int64_t k; std::cin >> k;
            auto &b = t[h(k)];
            bool found = false;
            int64_t o = 0;
            for (auto &p : b) if (p.first == k) { o = p.second; found = true; break; }
            if (found) std::cout << o << "\n"; else std::cout << "NONE\n";
        } else if (op == 3) {
            int64_t k; std::cin >> k;
            auto &b = t[h(k)];
            bool done = false;
            for (size_t j = 0; j < b.size(); ++j)
                if (b[j].first == k) { b[j] = b.back(); b.pop_back(); done = true; break; }
            std::cout << (done ? "OK\n" : "NONE\n");
        } else if (op == 4) {
            for (int j = 0; j < m; ++j) {
                if (j) std::cout << " ";
                std::cout << t[j].size();
            }
            std::cout << "\n";
        }
    }
    return 0;
}
