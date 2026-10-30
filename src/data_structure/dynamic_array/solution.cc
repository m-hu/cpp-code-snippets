// dynamic-array: doubling/halving amortized table (CLRS 16.4). Pure C++14.
// Ops: 1 x push, 2 pop, 3 i get, 4 size+capacity. Capacity doubles when
// full and halves when quarter full (min 1).
#include <cstdint>
#include <iostream>
#include <vector>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int q = 0;
    if (!(std::cin >> q)) return 0;
    std::vector<int64_t> a;
    int64_t cap = 1;
    for (int i = 0; i < q; ++i) {
        int op = 0;
        std::cin >> op;
        if (op == 1) {
            int64_t x = 0;
            std::cin >> x;
            if ((int64_t)a.size() == cap) cap *= 2;
            a.push_back(x);
        } else if (op == 2) {
            if (a.empty()) {
                std::cout << "EMPTY\n";
            } else {
                std::cout << a.back() << "\n";
                a.pop_back();
                if (!a.empty() && (int64_t)a.size() * 4 <= cap && cap > 1) cap /= 2;
            }
        } else if (op == 3) {
            int64_t j = 0;
            std::cin >> j;
            if (j < 0 || j >= (int64_t)a.size())
                std::cout << "NONE\n";
            else
                std::cout << a[(size_t)j] << "\n";
        } else if (op == 4) {
            std::cout << a.size() << " " << cap << "\n";
        }
    }
    return 0;
}
