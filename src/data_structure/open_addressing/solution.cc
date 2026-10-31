// hash-table-open-addressing: linear probing + tombstones (CLRS 11.4).
// Pure C++14. Line1: m q. Ops: 1 k v put (FULL if full), 2 k get,
// 3 k delete, 4 slot map ('.' empty, 'X' tombstone, 'O' occupied).
#include <cstdint>
#include <iostream>
#include <vector>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int m = 0, q = 0;
    if (!(std::cin >> m >> q)) return 0;
    std::vector<int64_t> keys(m), vals(m);
    std::vector<char> st(m, 0); // 0 empty, 1 occupied, 2 tombstone
    auto h = [&](int64_t k) { int r = (int)(k % m); if (r < 0) r += m; return r; };
    for (int i = 0; i < q; ++i) {
        int op = 0;
        std::cin >> op;
        if (op == 1) {
            int64_t k, v; std::cin >> k >> v;
            int start = h(k), tomb = -1, found = -1;
            for (int t = 0; t < m; ++t) {
                int s = (start + t) % m;
                if (st[s] == 1 && keys[s] == k) { found = s; break; }
                if (st[s] == 2 && tomb == -1) tomb = s;
                if (st[s] == 0) { if (tomb == -1) tomb = s; break; }
            }
            if (found != -1) { vals[found] = v; }
            else if (tomb != -1) { keys[tomb] = k; vals[tomb] = v; st[tomb] = 1; }
            else std::cout << "FULL\n";
        } else if (op == 2) {
            int64_t k; std::cin >> k;
            int start = h(k);
            bool found = false;
            int64_t o = 0;
            for (int t = 0; t < m; ++t) {
                int s = (start + t) % m;
                if (st[s] == 0) break;
                if (st[s] == 1 && keys[s] == k) { o = vals[s]; found = true; break; }
            }
            if (found) std::cout << o << "\n"; else std::cout << "NONE\n";
        } else if (op == 3) {
            int64_t k; std::cin >> k;
            int start = h(k);
            bool done = false;
            for (int t = 0; t < m; ++t) {
                int s = (start + t) % m;
                if (st[s] == 0) break;
                if (st[s] == 1 && keys[s] == k) { st[s] = 2; done = true; break; }
            }
            std::cout << (done ? "OK\n" : "NONE\n");
        } else if (op == 4) {
            for (int s = 0; s < m; ++s) std::cout << (st[s] == 0 ? '.' : st[s] == 1 ? 'O' : 'X');
            std::cout << "\n";
        }
    }
    return 0;
}
